#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sevencore_io.h"

extern xQueueHandle KeyQueue;
#define MAX_KEY_LOG		10

void
key_init(void)
{
	int i;
	u8 key;

	for (i = 0; i < MAX_KEY_LOG; i++)
		xQueueReceive(KeyQueue, &key, 0);
}

int
kbhit(void)
{
	u8 key;
	int ret = xQueuePeek(KeyQueue, &key, 0);
	return (ret == pdPASS);
}
u8
getkey(void)
{
	u8 key;
	xQueueReceive(KeyQueue, &key, portMAX_DELAY);
	//while (pdPASS != xQueueReceive(KeyQueue, &key, 0))
	//		vTaskDelay(MSEC2TICK(5));
	return key;
}

u8 seg7led[NUM_7SEG_LED];

void
Exp_5_Homework_A(void)
{
	int i;
	u8 key;

	for (i = 0; i < NUM_7SEG_LED; i++){			// Turn Off All
	  	writeb_virtual_io(SEG7LED, 0x80 + (i << 4));
	   	seg7led[i] = 0x80;
	}
	key_init();

	while(1){
		if((key = getkey()) != 0){
			for(i=0;i<NUM_7SEG_LED;i++){
				seg7led[i] = seg7led[i+1];
			}
			seg7led[NUM_7SEG_LED-1] = key;

			for (i = 0; i < NUM_7SEG_LED; i++){
				writeb_virtual_io(SEG7LED, seg7led[i] + (i << 4) );
			}
		}else{
			break;
		}
	}
}

void
Exp_5_Homework_B(void)
{
	u8 barled = 0x80;
	u8 mode = FALSE;
	u8 key;
	int i, count = 0;
	portTickType xLastWakeTime = xTaskGetTickCount();

	writeb_virtual_io(BARLED1, barled);

	while(1){
		vTaskDelayUntil(&xLastWakeTime, MSEC2TICK(1));
		count++;
		if(count == 500){
			if(mode == FALSE){
				if(barled > 0x01){
					barled = barled >> 1;
				}else if(barled == 0x01){
					mode = TRUE;
				}
			}else{
				if(barled < 0x80){
					barled = barled << 1;
				}else if(barled == 0x80){
					mode = FALSE;
				}
			}
			writeb_virtual_io(BARLED1, barled);
			count = 0;
		}else{
			if(kbhit()){
				key = getkey();
				for(i=0;i<NUM_7SEG_LED;i++){
					seg7led[i] = seg7led[i+1];
				}
				seg7led[NUM_7SEG_LED-1] = key;

				for (i = 0; i < NUM_7SEG_LED; i++){
					writeb_virtual_io(SEG7LED, seg7led[i] + (i << 4) );
				}
			}
		}

		if (NDS_SWITCH() & KEY_START)
			break;
	}

	while (NDS_SWITCH() & KEY_START)
		vTaskDelay(MSEC2TICK(10));
}

portTASK_FUNCTION(Key_Task, pvParameters)
{
	u8 key, scan = 0;
	int i;
	u8  key_pressed = FALSE;

	while (1) {
		if(key_pressed == FALSE){
			//스캔
			writeb_virtual_io(KEY_MATRIX, 0x80 >> scan);
			key = scan * 4;
			switch (readb_virtual_io(KEY_MATRIX)) {
			  case 8 :
				  key += 1;
				  break;
			  case 4 :
				  key += 2;
				  break;
			  case 2 :
				  key += 3;
				  break;
			  case 1 :
				  key += 4;
				  if (key == 16)
					  key = 0;
				  break;
			  default :
				  key = 255;
				  break;
			}
			scan++;
			if (scan == 4)
				scan = 0;
			if (key < 16){
				xQueueSend(KeyQueue, &key, 0);
				key_pressed = TRUE;
			}
		}

		if (key_pressed == TRUE && readb_virtual_io(KEY_MATRIX) == 0){
				key_pressed = FALSE;
		}
		vTaskDelay(MSEC2TICK(1));
	}
}