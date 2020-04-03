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
#include <SDL.h>

/*** Local Headers ***/
#include "basic_cmds.h"
#include "cmd_handler.h"
#include "system_vars.h"

/*** Local Defines ***/
//quit
#define QUIT_OUT_USAGE "Usage: quit"
#define QUIT_OUT_UNKWN_USG "Unkown usage of quit"
#define QUIT_OUT_EXIT_MSG "Exiting Rastersoft Demo"

//Cmdtest
#define CMDTEST_OUT_NUM_OP "%d options entered"
#define CMDTEST_OUT_NUM_PARAM "%d paramaters entered"
#define CMDTEST_OUT_OP "Option: -%c = %s"
#define CMDTEST_OUT_PARAM "Paramater: %s"

/*** Local Enums ***/
/*** Local Structs ***/
/*** Local Functions ***/
/*** Local Variables ***/
/*** Function Implementations ***/

/**
 * @brief Quit Command - tells the application to exit. 
 */
void cmd_quit(struct Cmd_Input* input) {
    CONSOLE_PRINT("");
    for (int i = 0; i < input->num_op; i++) {
		switch (input->ops[i].option) {
		case 'h':
            CONSOLE_PRINT(QUIT_OUT_USAGE);
            CONSOLE_PRINT(CMD_QUIT_FUNC);
			return;
		default:
            CONSOLE_PRINT(QUIT_OUT_UNKWN_USG);
            CONSOLE_PRINT(QUIT_OUT_USAGE);
			return;
		}
	}

	if (input->num_param > 0) {
        CONSOLE_PRINT(QUIT_OUT_UNKWN_USG);
        CONSOLE_PRINT(QUIT_OUT_USAGE);
		return;
	}

    CONSOLE_PRINT(QUIT_OUT_EXIT_MSG);

	SDL_Event sdlevent;
	sdlevent.type = SDL_QUIT;
	SDL_PushEvent(&sdlevent);
}


/**
 * @brief Command Test Command - Outputs all entered parameters and options
 */
void cmd_cmdtest(struct Cmd_Input* input) {
    //print options and count
    CONSOLE_PRINT(CMDTEST_OUT_NUM_OP, input->num_op);
    for (int i = 0; i < input->num_op; i++) {
        CONSOLE_PRINT(CMDTEST_OUT_OP, input->ops[i].option, input->ops[i].param);
    }
    CONSOLE_PRINT("");

    //print parameters and count
    CONSOLE_PRINT(CMDTEST_OUT_NUM_PARAM, input->num_param);
    for (int i = 0; i < input->num_param; i++) {
        CONSOLE_PRINT(CMDTEST_OUT_PARAM, input->params[i]);
    }
}
