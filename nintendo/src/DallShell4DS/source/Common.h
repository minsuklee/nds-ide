/*
 * Common.h
 *
 *  Created on: 2011. 7. 24.
 *      Author: Administrator
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <PA9.h>       // Include for PA_Lib
#include <nds/ndstypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fat.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

#include "FreeRTOS.h"
#include "task.h"
#include <time.h>
#include <sevencore_io.h>

#include "all_gfx.h" // For Image Processing

static portTASK_FUNCTION( testTask1, pvParameters );
static portTASK_FUNCTION( testTask2, pvParameters );

#endif /* COMMON_H_ */
