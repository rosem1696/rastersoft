#ifndef cmd_handler_h
#define cmd_handler_h

//Global Defines

//Global Structs

//Global Enums

//Extern Variables

//Global Functions

#define CMD_THREAD_NAME "Command_Watch"
#define NUM_COMMANDS 1

struct Command {
	char * name;
	char * func;
	void(*handler)(int *, struct Cmd_Option *, int *, char *);
};

struct Cmd_Option {
	char option;
	char * param;
};

int cmd_watch(void * params);
void free_cmds();

#endif