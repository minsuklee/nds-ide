/*
 * main.c
 *
 *  Created on: 2011. 9. 24.
 *      Author: Minsuk Lee
 */

#include <stdio.h>          // C-Standard Header
#include <time.h>
#include <stdlib.h>

#include <FreeRTOS.h>       // Free RTOS Headers
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include <nds.h>            // NDS / Sevencore Board Headers
#include <sevencore_io.h>

#include "card_spi.h"
#include "gdbStub.h"
#include "gdbStubAsm.h"

static portTASK_FUNCTION(Sample_Task_1, pvParameters);
static portTASK_FUNCTION(Sample_Task_2, pvParameters);

void InitDebug(void);

int
main(void)
{
	InitDebug();
	init_virtual_io(ENABLE_LED);	// Enable Virtual IO Devices
	init_printf();					// Initialize Bottom Screen for printf()

	xTaskCreate(Sample_Task_1,
					     (const signed char * const)"Sample_Task_1",
					     2048,
					     (void *)NULL,
					     tskIDLE_PRIORITY + 1,
					     NULL);
	xTaskCreate(Sample_Task_2,
					     (const signed char * const)"Sample_Task_2",
					     2048,
					     (void *)NULL,
					     tskIDLE_PRIORITY + 2,
					     NULL);
	vTaskStartScheduler();		// Never returns
	while(1)
		;
	return 0;
}

void
InitDebug(void)
{
#ifdef DEBUG
	irqInit();
	initSpi();
	initDebug();
	BreakPoint();
#endif
}

static
portTASK_FUNCTION(Sample_Task_1, pvParameters)
{
	u16 sw;
	u8 L_key_pressed = FALSE;
	u8 R_key_pressed = FALSE;
	short int curr_led = 0x0001;

	writeb_virtual_io(BARLED1, curr_led);
	writeb_virtual_io(BARLED2, 0);

	while (1) {
		printf(".");
		sw = NDS_SWITCH();
		if((L_key_pressed == FALSE) && (sw & KEY_L) && (curr_led < 0x080)){
			L_key_pressed = TRUE;
			curr_led = curr_led*2;
			printf("L");
			writeb_virtual_io(BARLED1, curr_led);
			}

		if((L_key_pressed == TRUE) && !(sw & KEY_L))
			L_key_pressed = FALSE;

		if((R_key_pressed == FALSE) && (sw & KEY_R) && (curr_led > 0X001)){
			R_key_pressed = TRUE;
			curr_led = curr_led/2;
			printf("R");
			writeb_virtual_io(BARLED1, curr_led);
			}

		if((R_key_pressed == TRUE) && !(sw & KEY_R))
			R_key_pressed = FALSE;

			vTaskDelay(50);
	}
}

static
portTASK_FUNCTION(Sample_Task_2, pvParameters)
{
	u8 barled = 0;
	portTickType xLastWakeTime = xTaskGetTickCount();
	int i;

	barled = 0x001;

	while (1) {

		writeb_virtual_io(BARLED2, barled);

		for (i = 0; i < 100000; i++)
			barled = ~barled;

		if(barled < 0x080)
			barled = barled * 2;
		else
			barled = 0x001;

		vTaskDelayUntil(&xLastWakeTime, MSEC2TICK(500));
	}
}

