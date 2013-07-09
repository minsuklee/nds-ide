// Free RTOS Headers
// See API reference Document in http://www.freertos.org/

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

// NDS / Sevencore Board Headers
#include <nds.h>
#include <sevencore_io.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define COLOR_RED       RGB(31,  0,  0) /* Bright Red  	*/
#define COLOR_WHITE     RGB(31, 31, 31) /* Bright White */
#define COLOR_BLACK     RGB( 0,  0,  0)	/* Black : Zero	*/

#define BOX_WIDTH		8
#define BOX_HEIGHT	8
#define BOX_Y_POS		13
#define BOX_X_MAX	(SCREEN_WIDTH / BOX_WIDTH)

#define WALL_WIDTH	32
#define WALL_HEIGHT	32
#define WALL_Y_POS	3
#define WALL_X_MAX  (SCREEN_WIDTH / WALL_WIDTH)

#define LEFT	1
#define RIGHT	2

#define RATE	(WALL_WIDTH / BOX_WIDTH)
#define SEMA(x)	(((x) / RATE) - 1)

xSemaphoreHandle xSemaphore[WALL_X_MAX-1];
u8 limit_x;

void
draw_my_box(int pos_x, int pos_y, u16 color)
{
	int i, j;
	u32 *basePoint, pixel;

	pixel = (color << 16) + color;
	for (i = 0; i < BOX_HEIGHT; i++) {
		basePoint = (u32 *)BG_GFX +
				((((pos_y * BOX_HEIGHT) + i) * SCREEN_WIDTH) + pos_x * BOX_WIDTH) / 2;
		for (j = 0; j < (BOX_WIDTH / 2); j++)
			*basePoint++ = pixel;
	}
}

void
draw_my_wall(int pos_x, int pos_y, u16 color)
{
	int i, j;
	u32 *basePoint, pixel;

	pixel = (color << 16) + color;
	for (i = 0; i < WALL_HEIGHT; i++) {
		basePoint = (u32 *)BG_GFX +
				((((pos_y * WALL_HEIGHT) + i) * SCREEN_WIDTH) + pos_x * WALL_WIDTH) / 2;
		for (j = 0; j < (WALL_WIDTH / 2); j++)
			*basePoint++ = pixel;
	}


}

extern xTaskHandle BallTask;

void
Exp_8_Homework_A(void)
{
	u8 key;
	u8 pos_x = 0;
	u8 prev_x;

	while (1) {
		if(kbhit()) {
			if((key = getkey()) < 8) {
				prev_x = pos_x;
				pos_x = key;

				draw_my_wall(prev_x, WALL_Y_POS, COLOR_BLACK);
				draw_my_wall(pos_x, WALL_Y_POS, COLOR_WHITE);
			}
		}
		if (NDS_SWITCH() & KEY_START) {
			draw_my_wall(pos_x, WALL_Y_POS, COLOR_BLACK);
			break;
		}
		vTaskDelay(10);
	}
	while(NDS_SWITCH() & KEY_START)
		vTaskDelay(10);
}

void
Exp_8_Homework_B(void)
{
	int i;
	u8 key;
	u8 pos_x = 0;

	for(i=0; i<WALL_X_MAX-1; i++)
		vSemaphoreCreateBinary( xSemaphore[i] );

	vTaskResume(BallTask);

	while (1) {
		 key = getkey();

		 if(key < 8) {
			 if(key > pos_x) {
				 i = pos_x;
				 while(i < key) {
					 if(xSemaphoreTake(xSemaphore[i], 0) == pdTRUE) {
						 limit_x += RATE;
						 draw_my_wall(i, WALL_Y_POS, COLOR_WHITE);
						 i++;
					 }
				 }
				 pos_x = key;
			 }
			 else if(key < pos_x) {
				 i = pos_x-1;
				 while(i >= key) {
					 if(xSemaphoreGive(xSemaphore[i]) == pdTRUE) {
						 limit_x -= RATE;
						 draw_my_wall(i, WALL_Y_POS, COLOR_BLACK);
						 i--;
					 }
				 }
				 pos_x = key;
			 }
		 }
	}
}

portTASK_FUNCTION(Ball_Task, pvParameters)
{
	u8 direction = LEFT;
	u8 pos_x = BOX_X_MAX-1;
	u8 prev_x;
	int tick_time;
	int i;
	portTickType xLastWakeTime = xTaskGetTickCount();

	while (1) {
		prev_x = pos_x;

		if(direction == LEFT) {
			if((pos_x != 0) && (pos_x % 4 == 0)) {
				if(xSemaphoreTake(xSemaphore[SEMA(pos_x)], 0) == pdTRUE)
					;
				else
					direction = RIGHT;
			}
		}
		else {
			if(pos_x % 4 == 0) {
				xSemaphoreGive(xSemaphore[SEMA(pos_x)])
						;
			}
		}
		tick_time = 1000 / (BOX_X_MAX - limit_x);

		if(direction == LEFT) {
			if(pos_x > limit_x)
				pos_x--;
			else {
				pos_x++;
				direction = RIGHT;
			}
		}
		else {
			if(pos_x < (BOX_X_MAX - 1))
				pos_x++;
			else {
				pos_x--;
				direction = LEFT;
			}
		}
		draw_my_box(prev_x, BOX_Y_POS, COLOR_BLACK);
		draw_my_box(pos_x, BOX_Y_POS, COLOR_RED);

		vTaskDelayUntil(&xLastWakeTime, MSEC2TICK(tick_time));
	}
}

// Key Matrix Scanning Task

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
	return key;
}

portTASK_FUNCTION(Key_Task, pvParameters)
{
	u8 key, scan = 0;
	u8 key_pressed = FALSE;
	u8 pre_line;

	while(1) {
		if(!key_pressed) {
			writeb_virtual_io(KEY_MATRIX, 0x80 >> scan);
			key = scan * 4;

			pre_line = readb_virtual_io(KEY_MATRIX);
			switch(readb_virtual_io(KEY_MATRIX)) {
			case 8 : key += 1; break;
			case 4 : key += 2; break;
			case 2 : key += 3; break;
			case 1 : key += 4; if(key == 16) key = 0; break;
			default : key = 255; break;
			}
			scan++;
			if(scan == 4)
				scan = 0;

			if(key < 16) {
				key_pressed = TRUE;
				xQueueSend(KeyQueue, &key, 0);
			}
		}
		if(key_pressed && ((readb_virtual_io(KEY_MATRIX) == 0) ||
				(readb_virtual_io(KEY_MATRIX) != pre_line)))
				key_pressed = FALSE;
		vTaskDelay(MSEC2TICK(25));
	}
}