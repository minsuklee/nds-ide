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

void key_init(void) {
	int i;
	u8 key;

	for (i = 0; i < MAX_KEY_LOG; i++)
		xQueueReceive(KeyQueue, &key, 0);
}

int kbhit(void) {
	u8 key;
	int ret = xQueuePeek(KeyQueue, &key, 0);
	return (ret == pdPASS);
}
u8 getkey(void) {
	u8 key;
	xQueueReceive(KeyQueue, &key, portMAX_DELAY);
	//while (pdPASS != xQueueReceive(KeyQueue, &key, 0))
	//		vTaskDelay(MSEC2TICK(5));
	return key;
}

void Exp_5_Homework_A(void) {
	int i;
	u8 key;
	u8 array_key[8] = { 123, 123, 123, 123, 123, 123, 123, 123 };

	key_init();

	for (i = 0; i < NUM_7SEG_LED; i++)
		writeb_virtual_io(SEG7LED, 0x80 + (i << 4));

	while (1) {

		key = getkey();

		if (key == 0)
			break;
		for (i = 6; i >= 0; i--)
			array_key[i + 1] = array_key[i];
		array_key[0] = key;
		for (i = 0; i < NUM_7SEG_LED; i++) {
			if (array_key[i] == 123)
				writeb_virtual_io(SEG7LED, 0x80 - (0x10 * i) + (i << 4));
			else
				writeb_virtual_io(SEG7LED, 0x70 - (0x10 * i) + array_key[i]);
		}

	}
}

void Exp_5_Homework_B(void) {
	int i;
	u8 key;
	u8 array_key[8] = { 123, 123, 123, 123, 123, 123, 123, 123 };
	u8 led_direction = FALSE;
	int led_state = 0x80;

	portTickType xLastWakeTime = xTaskGetTickCount();

	key_init();

	for (i = 0; i < NUM_7SEG_LED; i++)
		writeb_virtual_io(SEG7LED, 0x80 + (i << 4));

	while (1) {
		if (kbhit() == 1) {

			key = getkey();

			for (i = NUM_7SEG_LED - 2; i >= 0; i--)
				array_key[i + 1] = array_key[i];
			array_key[0] = key;

		}
		else {

			writeb_virtual_io(BARLED1, led_state);
			if (led_direction == FALSE) {
				led_state /= 2;
				if (led_state == 0x01) {
					led_direction = TRUE;
				}
			} else {
				led_state *= 2;
				if (led_state == 0x80) {
					led_direction = FALSE;
				}
			}

			for (i = 0; i < NUM_7SEG_LED; i++) {
				if (array_key[i] == 123)
					writeb_virtual_io(SEG7LED, 0x80 - (0x10 * i) + (i << 4));
				else
					writeb_virtual_io(SEG7LED,
							0x70 - (0x10 * i) + array_key[i]);
			}
			vTaskDelayUntil(&xLastWakeTime, MSEC2TICK(500) );

		}

	}
}

portTASK_FUNCTION(Key_Task, pvParameters) {
	u8 key, scan = 0;
//	u8 present_key = TRUE;
	while (1) {

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

		if (key < 16) {
			xQueueSend(KeyQueue, &key, 0);
			writeb_virtual_io(SEG7LED, 0x70 + key);
		}

		vTaskDelay(MSEC2TICK(20) );
	}
}