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

#define BOX_WIDTH  	8
#define BOX_HEIGHT	8
#define BOX_Y_POS	   13
#define BOX_X_MAX	(SCREEN_WIDTH / BOX_WIDTH)

#define WALL_Y_POS  3
#define WALL_WIDTH  32
#define WALL_HEIGHT 32
#define WALL_X_MAX (SCREEN_WIDTH / WALL_WIDTH)
// �ʿ��� global ����
u8 ballLeftLimit = 0;
u8 ballPos = 0;
xSemaphoreHandle sem;

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
	u8 pos=0;
	u8 prePos=0;
    while (1) {
    	if(kbhit()){
    		pos = getkey();
    		if(pos >=WALL_X_MAX)
    		    continue;
    		draw_my_wall(prePos,WALL_Y_POS,COLOR_BLACK);
    		draw_my_wall(pos,WALL_Y_POS,COLOR_WHITE);
    		prePos = pos;
    	}
    	if(NDS_SWITCH() & KEY_START){
    		draw_my_wall(prePos,WALL_Y_POS,COLOR_BLACK);
    		break;
    	}
    	// Ű ��Ʈ�������� ������ ��ġ�� white box
    	// START key�� ������ ����
    }
	while (NDS_SWITCH() & KEY_START)
		vTaskDelay(10);		// Wait while START KEY is being pressed
}

void
Exp_8_Homework_B(void)
{
    // ���� ���� �� �ʱ�ȭ (������ ����)
	vSemaphoreCreateBinary(sem);
    vTaskResume(BallTask);
	u8 pos=0;
	u8 prePos=0;
	int i=0;
	while (1) {
		if(kbhit()){
			pos = getkey();
		   if(pos >=WALL_X_MAX)
			   continue;
		   if(xSemaphoreTake(sem,0)!=pdFALSE)
		   {
			   if(pos*WALL_WIDTH > ballPos*BOX_WIDTH)
			   {
				   xSemaphoreGive(sem);
				   continue;
			   }
			   ballLeftLimit = (pos*WALL_WIDTH)/BOX_WIDTH;
			   xSemaphoreGive(sem);
			}
			for(i=0; i<prePos; i++)
				draw_my_wall(i,WALL_Y_POS,COLOR_BLACK);
			for(i=0; i<pos; i++)
				draw_my_wall(i,WALL_Y_POS,COLOR_WHITE);
			prePos = pos;
	    }
		if(NDS_SWITCH() & KEY_START){
			draw_my_wall(prePos,WALL_Y_POS,COLOR_BLACK);
		    break;
	    }
		    	// Ű ��Ʈ�������� ������ ��ġ�� white box
		    	// START key�� ������ ����
	}

}

portTASK_FUNCTION(Ball_Task, pvParameters)
{
	// �ʿ��� ����, �ʱ�ȭ
	enum {LEFT_DIRECTION, RIGHT_DIRECTION};
	u8 direction = RIGHT_DIRECTION;
	portTickType XLastWakeTime = xTaskGetTickCount();
	while (1) {
		if(ballPos==ballLeftLimit)
			direction = RIGHT_DIRECTION;
		else if(ballPos==(BOX_X_MAX-1))
			direction = LEFT_DIRECTION;
		else
			;

		draw_my_box(ballPos,BOX_Y_POS,COLOR_BLACK);

		if(xSemaphoreTake(sem,0)!=pdFALSE)
		{
			if(direction == LEFT_DIRECTION)
				ballPos--;
			else if(direction == RIGHT_DIRECTION)
				ballPos++;
			else
				;
			xSemaphoreGive(sem);
		}
		draw_my_box(ballPos,BOX_Y_POS,COLOR_RED);
		vTaskDelayUntil(&XLastWakeTime, MSEC2TICK(1000)/(BOX_X_MAX-1-ballLeftLimit));
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

			vTaskDelay(MSEC2TICK(30));
		}
}
