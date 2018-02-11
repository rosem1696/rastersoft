/**
 * @file basic_cmds.c
 * @author Mitchell Rose
 * @date 10 Feb 2018
 * @brief Implementations of commands not grouped under a specific purpose
 * @copyright Copyright (c) 2018 Mitchell Rose
 * @license MIT License
 */

/*** Standard Library ***/
/*** External Libraries ***/

/*** Local Headers ***/
#include "basic_cmds.h"
#include "cmd_handler.h"
#include "system_vars.h"

/*** Local Defines ***/
/*** Local Enums ***/
/*** Local Structs ***/
/*** Local Functions ***/
/*** Local Variables ***/
/*** Function Implementations ***/

/**
 * @brief Quit Command - tells the application to exit. Same as selecting
 * the exit button on the main window.  
 * 
 * @param num_ops number of entered options
 * @param ops help (-h) prints command function
 * @param num_p Unused
 * @param params Unused
 */
void cmd_quit(int num_ops, struct Cmd_Option * ops, int * num_p, char * params) {

}
