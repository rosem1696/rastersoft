//Standard Library
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Project Headers
#include "cmd_handler.h"
#include "demo.h"
#include "system_vars.h"

//Local Definitions
#define CMD_BUF_SIZE 200
#define CMD_HELP_NAME "help"
#define CMD_HELP_FUNC "Displays all available commands"

//Local Functions
void add_cmd(const char * name, const char * func, void(*handler)(int *, struct Cmd_Option *, int *, char *));
void init_cmds();

void cmd_help(int num_ops, struct Cmd_Option * ops, int * num_p, char * params);

//Local Variables
struct Command commands[NUM_COMMANDS];
int cmd_count = 0;
char cmd_buffer[CMD_BUF_SIZE];

//Function Implementations

int cmd_watch(void * params) {
	//setup command array
	init_cmds();

	//command watch loop
	while (!quit) {
		printf(">");
		char * str = fgets(cmd_buffer, CMD_BUF_SIZE, stdin);
		if (str) {
			printf("%s", str);
		}
	}

	//free memory from comand array
	free_cmds();
	return 0;
}

void add_cmd(const char * name, const char * func, void(*handler)(int *, struct Cmd_Option *, int *, char *)) {
	if (cmd_count < NUM_COMMANDS) {
		commands[cmd_count].handler = handler;
		commands[cmd_count].name = malloc(strlen(name) + 1);
		commands[cmd_count].func = malloc(strlen(func) + 1);
		cmd_count++;
	}
}

void init_cmds() {

}

void free_cmds() {
	int i;
	for (i = 0; i < NUM_COMMANDS; i++) {
		free(commands[i].name);
		free(commands[i].func);
	}
}

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

	printf("For more information on a command, type \"[Command Name] -h\"\n");

	for (i = 0; i < NUM_COMMANDS; i++) {
		printf("%s - %s.\n", commands[i].name, commands[i].func);
	}
}