/**
 * @file cmd_handler.h
 * @author Mitchell Rose
 * @date 10 Feb 2018
 * @brief Commandline interface header
 * @copyright Copyright (c) 2018 Mitchell Rose
 * @license MIT License
 */

#ifndef cmd_handler_h
#define cmd_handler_h

/*** Standard Library ***/
/*** External Libraries ***/
/*** Local Headers ***/

/*** Global Defines ***/
#define CMD_THREAD_NAME "Command_Thread"

/*** Global Enums ***/

/*** Global Structs ***/

/**
 * @brief Structure for adding command to interface
 * 
 * Structure that commands must fit to be added to the command interface.
 * 'name' - the alias that the user can enter to call the command.
 * 'func'- a brief description of what the command does. Displayed with 'help'.
 * 'handler' - function pointer called when the command is entered. Accepts options
 * 		and parameters (counts for each). Has no return value.
 */
struct Command {
	char * name;
	char * func;
	void(*handler)(int *, struct Cmd_Option *, int *, char *);
};

/**
 * @brief A command operation
 * 
 * Structure which holds a single command option.
 * Option Syntax - [option]=[param]
 * An option which has no equals sign will have a NULL param.
 * If nothing follows the equals, param will be an empty string.
 */
struct Cmd_Option {
	char option;
	char * param;
};

/*** Extern Variables ***/

/*** Global Functions ***/
int cmd_watch(void * params);
void free_cmds();

#endif //cmd_handler_h
