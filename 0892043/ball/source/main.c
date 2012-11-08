// Free RTOS Headers
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "sevencore_io.h"

#include "card_spi.h"
#include "gdbStub.h"
#include "gdbStubAsm.h"

static portTASK_FUNCTION(Exp_Task, pvParameters);
portTASK_FUNCTION(Key_Task, pvParameters);
void Exp_Sample(void);

void InitDebug(void);

int main(void) {
	InitDebug();
	init_virtual_io(ENABLE_SW | ENABLE_MATRIX);	// Enable Virtual LED's on Top Screen
	//init_printf();							// Initialize Bottom Screen for printf()

	/*xTaskCreate(Key_Task, (const signed char * const)"Key_Task", 2048,
	 (void *)NULL, tskIDLE_PRIORITY + 2, NULL);*/
	/*xTaskCreate(Exp_Task, (const signed char * const)"Exp_Task", 2048,
			(void *)NULL, tskIDLE_PRIORITY + 2, NULL);*/
	Exp_Sample();

	KeyQueue = xQueueCreate(MAX_KEY_LOG, sizeof(u8));
	// Error Processing Needed !

	vTaskStartScheduler();		// Never returns
	while (1)
		;
	return 0;
}

void InitDebug(void) {
#ifdef DEBUG
	irqInit();
	initSpi();
	initDebug();
	BreakPoint();
#endif
}

static
portTASK_FUNCTION(Exp_Task, pvParameters) {


		Exp_Sample();

}
// task add
portTASK_FUNCTION(Key_Task, pvParameters) {

	u8 key, scan = 0;
	u8 key_pressed = FALSE;
	key_init();

	while (1) {

		if (key_pressed == FALSE) {

			writeb_virtual_io(KEY_MATRIX, 0x80 >> scan);
			key = scan * 4;

			switch (readb_virtual_io(KEY_MATRIX)) {
			case 8:
				key += 1;
				break;
			case 4:
				key += 2;
				break;
			case 2:
				key += 3;
				break;
			case 1:
				key += 4;
				if (key == 16)
					key = 0;
				break;
			default:
				key = 255;
				break;
			}
			scan++;
			if (scan == 4)
				scan = 0;

			if ((key < 16)) {
				key_pressed = TRUE;
				xQueueSend(KeyQueue, &key, 0);
			}
		}

		if ((key_pressed == TRUE) && (readb_virtual_io(KEY_MATRIX) == 0))
			key_pressed = FALSE;

		vTaskDelay(MSEC2TICK(30) );
	}
}
