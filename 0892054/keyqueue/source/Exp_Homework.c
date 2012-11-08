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

void
Exp_5_Homework_A(void)
{
	u8 key;
	u8  keyArr[8];
	int i;

	key_init();

	for (i=0; i<8; i++)
    	keyArr[i] = 0x80;

	for (i=0; i<NUM_7SEG_LED; i++)					// Turn Off All
		writeb_virtual_io(SEG7LED, 0x80 + (i << 4));

	while(1){
		key = getkey();
		if(key == 0)
			break;
		for(i = 0; i<7; i++){
			keyArr[i] =keyArr[i+1];
		}
		keyArr[7]= key;
		for(i=0; i<8; i++){
			writeb_virtual_io(SEG7LED, 0x00+(0x10*i) + keyArr[i]);
		}
	}

}

void
Exp_5_Homework_B(void)
{
	u8 barled = 0x80;
	u8 key;
	u8 keyArr[8];
	u8 state = TRUE;
	int timeCnt = 0;
	int i=0;

	portTickType xLastWakeTime = xTaskGetTickCount();
	for (i=0; i<8; i++)
    	keyArr[i] = 0x80;
	for (i=0; i<NUM_7SEG_LED; i++)					// Turn Off All
		writeb_virtual_io(SEG7LED, 0x80 + (i << 4));

	while(1){

		vTaskDelayUntil(&xLastWakeTime, MSEC2TICK(1));
		timeCnt++;
		if(timeCnt == 500){
			if(state){
				if(barled > 0x01)
					barled = barled/2;
				else{
					barled = barled*2;
					state = FALSE;
				}
			}
			else{
				if(barled < 0x80)
					barled = barled*2;
				else{
					barled = barled/2;
					state = TRUE;
				}
			}
			timeCnt = 0;
		}

		if(kbhit()){
			key = getkey();

			for(i = 0; i<7; i++){
				keyArr[i] =keyArr[i+1];
			}
			keyArr[7]= key;
		}

		writeb_virtual_io(BARLED1, barled);

		for(i=0; i<8; i++){
			writeb_virtual_io(SEG7LED, 0x00+(0x10*i) + keyArr[i]);
		}
		if (NDS_SWITCH() & KEY_START)
			break;

	}

}

portTASK_FUNCTION(Key_Task, pvParameters)
{
    u8 key, scan = 0;
    u8 keyPressed = FALSE;
    u8 prekey;
    int i;

	for (i = 0; i < NUM_7SEG_LED; i++)					// Turn Off All
		writeb_virtual_io(SEG7LED, 0x80 + (i << 4));

	while (1) {
		if(keyPressed == FALSE){
			writeb_virtual_io(KEY_MATRIX, 0x80 >> scan);
			key = scan * 4;
			switch (readb_virtual_io(KEY_MATRIX)) {
			  case 8 :  key += 1; break;
			  case 4 :  key += 2; break;
			  case 2 :  key += 3; break;
			  case 1 :  key += 4; if (key == 16) key = 0; break;
			  default : key = 255; break;
			}
			scan++;
			if (scan == 4)
				scan = 0;
			if (key < 16){
				xQueueSend(KeyQueue, &key, 0);
				prekey = readb_virtual_io(KEY_MATRIX);
				keyPressed = TRUE;
			}
		}
		else if(prekey != readb_virtual_io(KEY_MATRIX) || readb_virtual_io(KEY_MATRIX) == FALSE)
			keyPressed = FALSE;

			vTaskDelay(MSEC2TICK(30));
	}
}