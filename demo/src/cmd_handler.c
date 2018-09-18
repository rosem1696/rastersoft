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
#include <ctype.h>

/*** External Libraries ***/

/*** Local Headers ***/
#include "cmd_handler.h"
#include "demo.h"
#include "system_vars.h"
#include "basic_cmds.h"

/*** Local Defines ***/
#define NUM_COMMANDS 2
#define CMD_BUF_SIZE 200
#define CMD_HELP_NAME "help"
#define CMD_HELP_FUNC "Displays all available commands"

/*** Local Enums ***/
/*** Local Structs ***/

/*** Local Functions ***/
void add_cmd(const char * name, const char * func, void(*handler)(struct Cmd_Input input));
void init_cmds();
void cmd_help(struct Cmd_Input * input);
bool parse_op(char * op_str, struct Cmd_Option * op);
bool parse_input(char * input, struct Command ** cmd, struct Cmd_Input * in);
struct Command * get_cmd(char * cmd_name);
void free_input(struct Cmd_Input * in);

/*** Local Variables ***/
struct Command commands[NUM_COMMANDS];
int cmd_count = 0;
char cmd_buffer[CMD_BUF_SIZE];

/*** Function Implementations ***/

/**
* @brief Calls add_cmd for all commands
*
*/
void init_cmds() {
	//Call add for every command that is runnable
	
	/* Help */
	add_cmd(CMD_HELP_NAME, CMD_HELP_FUNC, cmd_help);

	/* Basic */
	add_cmd(CMD_QUIT_NAME, CMD_QUIT_FUNC, cmd_quit);
	//To add a new command, add an add cmd call under an existing or new category
}

/**
 * @brief Thread entry point for command handler. Watches stdin for command input.
 * Parses input and passes options and parameters to command implementation.
 * 
 * @param params Not used
 * @return int Not used
 */
int cmd_watch(void * params) {
	//setup command array
	init_cmds();

	//print welcome message
	printf("Rastersoft Demo Command Prompt\n");

	//command watch loop
	while (!quit) {
		//get command input
		printf("\n>");
		char * str = fgets(cmd_buffer, CMD_BUF_SIZE, stdin);
		if (str) {
			//remove newline from input
			char * nl = strchr(cmd_buffer, '\n');
			if (nl)
				nl[0] = '\0';
			//check for empty line
			if (strlen(cmd_buffer) > 0) {
				struct Command * cmd;
				struct Cmd_Input input;
				input.ops = NULL;
				input.params = NULL;
				input.num_op = 0;
				input.num_param = 0;
				bool good_input = parse_input(str, &cmd, &input);
				if (good_input) {
					cmd->handler(&input);
					//free parsed strings from command input
					free_input(&input);
				}
			}
		}
	}
	return 0;
}


bool parse_input(char * input, struct Command ** cmd, struct Cmd_Input * in) {
	//check if entered command is valid and get handler
	char * tok = strtok(input, " ");
	*cmd = get_cmd(tok);
	bool good_input = true;
	if (*cmd) {
		//process and parse all parameters and options
		while (tok && good_input) {
			tok = strtok(NULL, " ");
			if (tok) {
				if (tok[0] == '-') {
					//process option
					in->num_op++;
					//allocate memory
					if (in->num_op == 1)
						in->ops = malloc(sizeof(struct Cmd_Option));
					else
						in->ops = realloc(in->ops, in->num_op * sizeof(struct Cmd_Option));
					//extract option character and parameter
					if (parse_op(tok, &in->ops[in->num_op - 1])) {
						//check for duplicate option error
						int i;
						for (i = 0; i < (in->num_op - 1) && good_input; i++) {
							if (in->ops[in->num_op - 1].option == in->ops[i].option) {
								//error, duplicate option entered
								printf("Bad option input - Duplicate Option: %c\n", in->ops[i].option);
								good_input = false;
							}
						}
					} else {
						//error in option syntax
						in->num_op--;
						good_input = false;
						printf("Bad option input: %s\n", tok);
					}
				} else {
					//process param
					in->num_param++;
					//allocate array memory
					if(in->num_param == 1)
						in->params = malloc(sizeof(char **));
					else
						in->params = realloc(in->params, in->num_param * sizeof(char **));
					
					//Check for quotes
					if (tok[0] == '\"') {
						tok = &tok[1];
						if (tok[strlen(tok) - 1] == '\"') {
							//current token contains start and end of quotes
							tok[strlen(tok) - 1] = '\0';
							in->params[in->num_param - 1] = malloc(strlen(tok) + 1);
							strcpy(in->params[in->num_param - 1], tok);
						} else {
							//End quote not in first token. Copy and look in next tokens
							in->params[in->num_param - 1] = malloc(strlen(tok) + 1);
							strcpy(in->params[in->num_param - 1], tok);
							bool quote_found = false;
							while (tok && !quote_found) {
								tok = strtok(NULL, " ");
								if (tok) {
									printf("%c\n", tok[strlen(tok) - 1]);
									if (tok[strlen(tok) - 1] == '\"') {
										tok[strlen(tok) - 1] = '\0';
										quote_found = true;
									}
									in->params[in->num_param - 1] = realloc(in->params[in->num_param - 1], strlen(in->params[in->num_param - 1]) + strlen(tok) + 2);
									strcat(in->params[in->num_param - 1], " ");
									strcat(in->params[in->num_param - 1], tok);
								}
							}
							good_input = quote_found;
						}
					} else {
						//no quotes, simple parameter
						//check for hyphen escape character
						if (tok[0] == '\\' && strlen(tok) > 1) {
							if (tok[1] == '-')
								tok = &tok[1];
						}
						in->params[in->num_param - 1] = malloc(strlen(tok) + 1);
						//copy parameter
						strcpy(in->params[in->num_param - 1], tok);
					}
					if (!good_input) {
						printf("Bad Parameter: Couldn't find ending quote\n");
					}
				}
			}
			if (!good_input) {
				//free up allocated memory because no command fired
				free_input(in);
			}
		}
	} else {
		printf("Unrecognized command %s\n", tok);
		good_input = false;
	}
	return good_input;
}

bool parse_op(char * op_str, struct Cmd_Option * op) {
	if (strlen(op_str) == 2) {
		//check for valid option
		if (isalpha(op_str[1])) {
			//set simple option
			op->option = op_str[1];
			op->param = NULL;
			return true;
		} else {
			return false;
		}
	} else if (strlen(op_str) > 2) {
		//check for valid option and parameter
		if (isalpha(op_str[1]) && op_str[2] == '=') {
			op->option = op_str[1];
			char * param_ptr = &op_str[3];
			if (strlen(param_ptr) > 0) {
				//set option with parameter string
				op->param = malloc(strlen(param_ptr) + 1);
				strcpy(op->param, param_ptr);
			} else {
				//set option with empty parameter string+
				op->param = malloc(1);
				op->param[0] = '\0';
			}
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void free_input(struct Cmd_Input * in) {
	int i;
	if (in->ops != NULL) {
		for (i = 0; i < in->num_op; i++) {
			//free option parameter string
			free(in->ops[i].param);
		}

		//free options array
		free(in->ops);
	}
	
	if (in->params) {
		for (i = 0; i < in->num_param; i++) {
			//free individual parameter strings
			free(in->params[i]);
		}

		//free parameter string arrary
		free(in->params);
	}
}

struct Command * get_cmd(char * cmd_name) {
	struct Command * ret = NULL;
	int i;
	for (i = 0; i < cmd_count; i++) {
		if (strcmp(cmd_name, commands[i].name) == 0)
			ret = &commands[i];
	}
	return ret;
}


/**
 * @brief Adds a command to the list of runnable commands
 * 
 * @param name Command name/alias
 * @param func Command function description
 * @param handler Function pointer called when command entered
 */
void add_cmd(const char * name, const char * func, void(*handler)(struct Cmd_Input input)) {
	if (cmd_count < NUM_COMMANDS) {
		commands[cmd_count].handler = handler;
		commands[cmd_count].name = malloc(strlen(name) + 1);
		strcpy(commands[cmd_count].name, name);
		commands[cmd_count].func = malloc(strlen(func) + 1);
		strcpy(commands[cmd_count].func, func);
		cmd_count++;
	}
}

/**
 * @brief Frees up the allocated memory for all commands
 * 
 */
void free_cmds() {
	int i;
	for (i = 0; i < NUM_COMMANDS; i++) {
		free(commands[i].name);
		free(commands[i].func);
	}
}

/**
 * @brief Help Command - Lists all runnable commands and their functions
 * 
 * @param num_ops number of entered options
 * @param ops help (-h) prints command function
 * @param num_p Unused
 * @param params Unused
 */
void cmd_help(struct Cmd_Input * input) {
	int i;
	for (i = 0; i < input->num_op; i++) {
		switch (input->ops[i].option) {
		case 'h':
			printf("Usage: help\n");
			printf("%s.\n", CMD_HELP_FUNC);
			return;
		default:
			printf("Unknown usage of help\n");
			printf("Usage: help\n");
			return;
		}
	}

	if (input->num_param > 0) {
		printf("Unknown usage of help\n");
		printf("Usage: help\n");
		return;
	}

	printf("For more information on a command, enter \"[Command Name] -h\"\n\n");
	printf("Available Commands:\n");
	for (i = 0; i < NUM_COMMANDS; i++) {
		printf("%s - %s.\n", commands[i].name, commands[i].func);
	}
}
