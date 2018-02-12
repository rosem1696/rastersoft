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

/*** External Libraries ***/

/*** Local Headers ***/
#include "cmd_handler.h"
#include "demo.h"
#include "system_vars.h"

/*** Local Defines ***/
#define NUM_COMMANDS 1
#define CMD_BUF_SIZE 200
#define CMD_HELP_NAME "help"
#define CMD_HELP_FUNC "Displays all available commands"

/*** Local Enums ***/
/*** Local Structs ***/

/*** Local Functions ***/
void add_cmd(const char * name, const char * func, void(*handler)(int *, struct Cmd_Option *, int *, char *));
void init_cmds();
void cmd_help(int num_ops, struct Cmd_Option * ops, int * num_p, char * params);

/*** Local Variables ***/
struct Command commands[NUM_COMMANDS];
int cmd_count = 0;
char cmd_buffer[CMD_BUF_SIZE];

/*** Function Implementations ***/

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

	//command watch loop
	while (!quit) {
		printf(">");
		char * str = fgets(cmd_buffer, CMD_BUF_SIZE, stdin);
		if (str) {
			char * tok = strtok(cmd_buffer, " ");
			printf("%s\n", tok);
			while(tok) {
				tok = strtok(NULL , " ");
				if (tok) {
					printf("%s\n", tok);
				}
			}
		}
	}

	//free memory from comand array
	free_cmds();
	return 0;
}

/**
 * @brief Adds a command to the list of runnable commands
 * 
 * @param name Command name/alias
 * @param func Command function description
 * @param handler Function pointer called when command entered
 */
void add_cmd(const char * name, const char * func, void(*handler)(int *, struct Cmd_Option *, int *, char *)) {
	if (cmd_count < NUM_COMMANDS) {
		commands[cmd_count].handler = handler;
		commands[cmd_count].name = malloc(strlen(name) + 1);
		commands[cmd_count].func = malloc(strlen(func) + 1);
		cmd_count++;
	}
}

/**
 * @brief Calls add_cmd for all commands
 * 
 */
void init_cmds() {

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
void cmd_help(int num_ops, struct Cmd_Option * ops, int * num_p, char * params) {
	int i;
	for (i = 0; i < num_ops; i++) {
		switch (ops[i].option) {
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

	if (num_p > 0) {
		printf("Unknown usage of help\n");
		printf("Usage: help\n");
		return;
	}

	printf("For more information on a command, enter \"[Command Name] -h\"\n");

	for (i = 0; i < NUM_COMMANDS; i++) {
		printf("%s - %s.\n", commands[i].name, commands[i].func);
	}
}
