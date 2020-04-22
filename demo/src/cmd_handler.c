/**
 * @file cmd_handler.c
 * @author Mitchell Rose
 * @date 9 Feb 2018
 * @brief Commandline interface implementation
 * @copyright Copyright (c) 2018 Mitchell Rose
 * @license MIT License
 */

 /*** Standard Library ***/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>


/*** External Libraries ***/

/*** Local Headers ***/
#include "cmd_handler.h"
#include "demo.h"
#include "system_vars.h"
#include "basic_cmds.h"

/*** Local Defines ***/
//Buffer
#define CMD_BUF_SIZE 500
#define CMD_OP_BUF_COUNT 20
#define CMD_OP_PARAM_BUF_SIZE 50
#define CMD_PARAM_BUF_COUNT 20 
#define CMD_PARAM_BUF_SIZE 50

//Helper Macros
#define NUM_COMMANDS (sizeof(commands)/sizeof(struct Command) - 1)

//Console Output strings
#define CMD_IN_DELIM " "

#define OUT_INPUT_STR ">"
#define OUT_WELCOME "Rastersoft Demo Command Prompt"
#define OUT_NO_CMD "Unrecognized Command '%s'"
#define OUT_OP_DUP "Bad option input - Duplicate Option: %c"
#define OUT_OP_BAD "Bad option input: %s"
#define OUT_OP_LIMIT "More options entered than system limit %d"
#define OUT_OP_LENGTH_LIMIT "Option '%s' parameter length exceeds system limit %d"
#define OUT_PARAM_NO_END_QUOTE "Bad parameter - No ending quote: %s"
#define OUT_PARAM_LIMIT "More paramaters entered than system limit %d"
#define OUT_PARAM_LENGTH_LIMIT "Parameter '%s' length exceeds system limit %d"

//Help
#define CMD_HELP_NAME "help"
#define CMD_HELP_FUNC "Displays all available commands"

#define CMD_HELP_OUT_USG "Usage: help"
#define CMD_HELP_OUT_UNKWN_USG "Unknown usage of help"
#define CMD_HELP_OUT_MORE_INFO "For more information on a command, enter '[Command Name] -h'"
#define CMD_HELP_OUT_AVAIL_CMD "Available Commands:"
#define CMD_HELP_OUT_CMD_INFO "%s - %s"


/*** Local Enums ***/
/*** Local Structs ***/

/*** Local Functions ***/

void init_input(struct Cmd_Input** in);
const struct Command* parse_cmd(char* input, char** tok_save);
bool parse_input(char* input, char** tok_save, struct Cmd_Input* in);
bool parse_op(char* op_str, struct Cmd_Option* op);
const struct Command* get_cmd(char* cmd_name);
void free_input(struct Cmd_Input* in);
bool remove_newline(char* str);

//commands
void cmd_help(struct Cmd_Input* input);

/*** Local Variables ***/

// Holds constant info for all enabled commands
struct Command commands[] =
{
    {CMD_HELP_NAME, CMD_HELP_FUNC, cmd_help},
    {CMD_QUIT_NAME, CMD_QUIT_FUNC, cmd_quit},
    {CMD_CMDTEST_NAME, CMD_CMDTEST_FUNC, cmd_cmdtest},
    {NULL, NULL, NULL}
};


/*** Function Implementations ***/

/**
 * @brief Thread entry point for command handler. Watches stdin for command input.
 * Parses input and passes options and parameters to command implementation.
 *
 * @param params Not used
 * @return int Not used
 */
int cmd_watch(void* params) {
    //init command input structure
    struct Cmd_Input* input;
    init_input(&input);

    //init input buffer
    char cmd_buffer[CMD_BUF_SIZE];

    //print welcome message
    CONSOLE_PRINT(OUT_WELCOME);

    //command watch loop
    while (!quit) {
        //print starting character
        CONSOLE_PRINT("");
        console_print(OUT_INPUT_STR, false);
        //get command input
        char* str = fgets(cmd_buffer, CMD_BUF_SIZE, stdin);
        if (str) {
            remove_newline(cmd_buffer);
            //check for empty line
            if (strlen(cmd_buffer) > 0) {
                //save ptr for strtok_s
                char* save_tok;

                //Extract command from buffer and check if enabled
                const struct Command* cmd = parse_cmd(cmd_buffer, &save_tok);
                if (cmd) {
                    //reset input counts
                    input->num_op = 0;
                    input->num_param = 0;

                    bool good_input = parse_input(str, &save_tok, input);
                    if (good_input) {
                        cmd->handler(input);
                    }
                }
            }
        } 
    }

    free_input(input);

    return 0;
}

void console_print(char* format, bool newline, ...) {
    if (!format) {
        return;
    }
    va_list args;
    va_start(args, newline);
    vprintf(format, args);
    if (newline) {
        printf("\r\n");
    }
}

void init_input(struct Cmd_Input** in) {
    //allocate base struct
    *in = malloc(sizeof(struct Cmd_Input));

    //allocate ops array
    (*in)->ops = malloc(CMD_OP_BUF_COUNT * sizeof(struct Cmd_Option));
    for (int i = 0; i < CMD_OP_BUF_COUNT; i++) {
        //allocate option paramater string
        (*in)->ops[i].param = malloc(CMD_OP_PARAM_BUF_SIZE * sizeof(char));
        //init to empty string
        (*in)->ops[i].param[0] = '\0';
    }

    //allocate parameter array
    (*in)->params = malloc(CMD_PARAM_BUF_COUNT * sizeof(char*));
    for (int i = 0; i < CMD_PARAM_BUF_COUNT; i++) {
        //allocate parameter string
        (*in)->params[i] = malloc(CMD_PARAM_BUF_SIZE * sizeof(char));
        //init to a empty string
        (*in)->params[i][0] = '\0';
    }
}

void free_input(struct Cmd_Input* in) {
    if (in->ops != NULL) {
        for (int i = 0; i < CMD_OP_BUF_COUNT; i++) {
            //free option parameter string
            free(in->ops[i].param);
        }
        //free options array
        free(in->ops);
    }

    if (in->params) {
        for (int i = 0; i < CMD_PARAM_BUF_COUNT; i++) {
            //free individual parameter strings
            free(in->params[i]);
        }
        //free parameter string arrary
        free(in->params);
    }

    //free the base input struct
    free(in);
}

const struct Command* parse_cmd(char* input, char** tok_save) {
    //check if entered command is valid and get handler
    char* tok = strtok_s(input, CMD_IN_DELIM, tok_save);
    if (!tok) {
        return NULL;
    }

    const struct Command* cmd = get_cmd(tok);
    if (!cmd) {
        CONSOLE_PRINT(OUT_NO_CMD, tok);
    }
    return cmd;
}

bool parse_input(char* input, char** tok_save, struct Cmd_Input* in) {
    char* tok;
    //bool good_input = true;
    //process and parse all parameters and options
    while ((tok = strtok_s(NULL, CMD_IN_DELIM, tok_save))) {
        if (tok[0] == '-') {
            if (in->num_op < CMD_OP_BUF_COUNT) {
                //check op parameter length limit
                if ((strlen(tok) - 2) < CMD_OP_PARAM_BUF_SIZE) {
                    //process option
                    in->num_op++;
                    //extract option character and parameter
                    if (parse_op(tok, &in->ops[in->num_op - 1])) {
                        //check for duplicate option error
                        int i;
                        for (i = 0; i < (in->num_op - 1) /*&& good_input*/; i++) {
                            if (in->ops[in->num_op - 1].option == in->ops[i].option) {
                                //error, duplicate option entered
                                CONSOLE_PRINT(OUT_OP_DUP, in->ops[i].option);
                                /*good_input = false;*/
                                return false;
                            }
                        }
                    } else {
                        //error in option syntax
                        CONSOLE_PRINT(OUT_OP_BAD, tok);
                        return false;
                    }
                } else {
                    CONSOLE_PRINT(OUT_OP_LENGTH_LIMIT, tok, CMD_OP_PARAM_BUF_SIZE);
                    return false;
                }
            } else {
                CONSOLE_PRINT(OUT_OP_LIMIT, CMD_OP_BUF_COUNT);
                return false;
            }
        } else {
            //check against paramater limit
            if (in->num_param < CMD_PARAM_BUF_COUNT) {
                //process param
                in->num_param++;
                //Check for quotes
                if (tok[0] == '\"') {
                    tok = &tok[1];
                    if (tok[strlen(tok) - 1] == '\"') {
                        //current token contains start and end of quotes
                        tok[strlen(tok) - 1] = '\0';
                        if (strlen(tok) < CMD_PARAM_BUF_SIZE) {
                            strcpy_s(in->params[in->num_param - 1], CMD_PARAM_BUF_SIZE, tok);
                        } else {
                            CONSOLE_PRINT(OUT_PARAM_LENGTH_LIMIT, tok, CMD_PARAM_BUF_SIZE);
                            return false;
                        }
                    } else {
                        //End quote not in first token. 
                        //keep track of total length across tokens 
                        size_t total_length = 0;
                        //init param to empty string for future strcat
                        in->params[in->num_param - 1][0] = '\0';
                        //search future tokens for an end quote
                        bool quote_found = false;
                        while (tok && !quote_found) {
                            //check if token final character is a quote
                            if (tok[strlen(tok) - 1] == '\"') {
                                //end quote found, remove from string and terminate routine
                                tok[strlen(tok) - 1] = '\0';
                                quote_found = true;
                            }
                            //add token length to total
                            total_length += strlen(tok);
                            //check total length
                            if (total_length < CMD_PARAM_BUF_SIZE) {
                                //append the token to the parameter string
                                strcat_s(in->params[in->num_param - 1], CMD_PARAM_BUF_SIZE, tok);
                                //append a space if we haven't found an end quote
                                if (!quote_found) {
                                    strcat_s(in->params[in->num_param - 1], CMD_PARAM_BUF_SIZE, " ");
                                }
                            } else {
                                CONSOLE_PRINT(OUT_PARAM_LENGTH_LIMIT, tok, CMD_PARAM_BUF_SIZE);
                                return false;
                            }
                            //get next token
                            if (!quote_found) {
                                tok = strtok_s(NULL, CMD_IN_DELIM, tok_save);
                            }
                        }
                        if (!quote_found) {
                            printf("Bad Parameter: Couldn't find ending quote\n");
                            return false;
                        }
                    }
                } else { 
                    //no quotes, simple parameter
                    //check paramater character limit
                    if (strlen(tok) < CMD_PARAM_BUF_SIZE) {
                        //copy parameter
                        strcpy_s(in->params[in->num_param - 1], CMD_PARAM_BUF_SIZE, tok);
                    } else {
                        CONSOLE_PRINT(OUT_PARAM_LENGTH_LIMIT, tok, CMD_PARAM_BUF_SIZE);
                        return false;
                    }
                }
            } else {
                CONSOLE_PRINT(OUT_PARAM_LIMIT, CMD_PARAM_BUF_COUNT);
                return false;
            }
        }
    }
    //successfully parsed all parameters and options
    return true;
}

bool parse_op(char* op_str, struct Cmd_Option* op) {
    if (isalpha(op_str[1])) {
        //check for simple option (no parameter)
        if (strlen(op_str) == 2) {
            op->option = op_str[1];
            op->param[0] = '\0';
            return true;
        } else if (strlen(op_str) > 2) {
            //check for valid option and parameter
            if (isalpha(op_str[1]) && op_str[2] == '=') {
                op->option = op_str[1];
                char* param_ptr = &op_str[3];
                if (strlen(param_ptr) > 0) {
                    //set option with parameter string
                    strcpy_s(op->param, CMD_OP_PARAM_BUF_SIZE, param_ptr);
                } else {
                    //set option with empty parameter string
                    op->param[0] = '\0';
                }
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

const struct Command* get_cmd(char* cmd_name) {
    int i;
    for (i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(cmd_name, commands[i].name) == 0)
            return &commands[i];
    }
    return NULL;
}

bool remove_newline(char* str) {
    char* nl = strchr(str, '\n');
    if (nl) {
        nl[0] = '\0';
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Help Command - Lists all runnable commands and their functions
 */
void cmd_help(struct Cmd_Input* input) {
    CONSOLE_PRINT("");
    for (int i = 0; i < input->num_op; i++) {
        switch (input->ops[i].option) {
        case 'h':
            CONSOLE_PRINT(CMD_HELP_OUT_USG);
            CONSOLE_PRINT(CMD_HELP_FUNC);
            return;
        default:
            CONSOLE_PRINT(CMD_HELP_OUT_UNKWN_USG);
            CONSOLE_PRINT(CMD_HELP_OUT_USG);
            return;
        }
    }

    if (input->num_param > 0) {        
        CONSOLE_PRINT(CMD_HELP_OUT_UNKWN_USG);
        CONSOLE_PRINT(CMD_HELP_OUT_USG);
        return;
    }

    CONSOLE_PRINT(CMD_HELP_OUT_MORE_INFO);
    CONSOLE_PRINT("");
    CONSOLE_PRINT(CMD_HELP_OUT_AVAIL_CMD);
    for (int i = 0; i < NUM_COMMANDS; i++) {
        CONSOLE_PRINT(CMD_HELP_OUT_CMD_INFO, commands[i].name, commands[i].func);
    }
}


