#ifndef commands_h
#define commands_h

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

#endif