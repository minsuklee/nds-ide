/*
 * Exp_Homework.c
 *
 *  Created on: 2011. 9. 22.
 *      Author: Minsuk Lee
 */

#include <stdio.h>			// C-Standard Header
#include <time.h>
#include <stdlib.h>

#include "FreeRTOS.h"		// Free RTOS Headers
#include "task.h"

#include <nds.h>			// NDS / Sevencore Board Headers
#include <sevencore_io.h>
#include "realio.h"

// LED Bar Left-and-Right (BARLED 1)
// LEFT key - going left, RIGHT key - going right
void
Exp_1_Homework_A(void)
{
	u16 sw;

	u8 button;
	button = 0x01;
	u8  key_pressed = FALSE;

	while (1) {
		sw = NDS_SWITCH();
		writeb_virtual_io(BARLED1, button);
		writeb_virtual_io(BARLED2, 0x00);

		if ((key_pressed == FALSE) && (sw & KEY_LEFT)) {
			if(button < 0x80){
				button = button << 1;
				key_pressed = TRUE;
			}
			writeb_virtual_io(BARLED1, button);
		}else if ((key_pressed == FALSE) && (sw & KEY_RIGHT)) {
			if(button > 0x01){
				button = button >> 1;
				key_pressed = TRUE;
			}
			writeb_virtual_io(BARLED1, button);
		}

		if(key_pressed == TRUE){
			if(!(sw & KEY_LEFT) && !(sw & KEY_RIGHT))
				key_pressed = FALSE;
		}

		if (NDS_SWITCH() & KEY_START)
			break;
		vTaskDelay(50);
	}

	while (NDS_SWITCH() & KEY_START)
		vTaskDelay(10);		// Wait while START KEY is being pressed
}

// LED Bar Left-and-Right & Round (BARLED 1 and BARLED 2)
// L key - going left, R key - going right
void
Exp_1_Homework_B(void)
{

}
