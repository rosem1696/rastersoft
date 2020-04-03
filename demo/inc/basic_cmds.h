/**
 * @file basic_cmds.h
 * @author Mitchell Rose
 * @date 10 Feb 2018
 * @brief Commands not grouped under a specific purpose
 * @copyright Copyright (c) 2018 Mitchell Rose
 * @license MIT License
 */

#ifndef basic_cmds_h
#define basic_cmds_h

/*** Standard Library ***/
/*** External Libraries ***/

/*** Local Headers ***/
#include "cmd_handler.h"

/*** Global Defines ***/
//quit
#define CMD_QUIT_NAME "quit"
#define CMD_QUIT_FUNC "Exits the application"

//cmdtest
#define CMD_CMDTEST_NAME "cmdtest"
#define CMD_CMDTEST_FUNC "Prints out all entered parameters and options"

/*** Global Enums ***/
/*** Global Structs ***/
/*** Extern Variables ***/

/*** Global Functions ***/
void cmd_quit(struct Cmd_Input* input);
void cmd_cmdtest(struct Cmd_Input* input);

#endif //basic_cmds_h
