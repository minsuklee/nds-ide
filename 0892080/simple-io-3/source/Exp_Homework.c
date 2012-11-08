/*
 * Exp_Homework.c
 *
 *  Created on: 2011. 9. 22.
 *      Author: Minsuk Lee
 */

#include "FreeRTOS.h"
#include "task.h"
#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sevencore_io.h"

portTickType short_timer;
//portTickType start_time_c = 0;
u16 barled;
short int led_state;

#define NUM_STATE	1
#define NUM_INPUT	1

// Actions

struct state_machine_x {
	int check_timer;
	int next_state[NUM_INPUT];
	void (* action[NUM_INPUT])(void *p);
};
enum { SW_ON, SW_OFF, TO };/*
static void f_led1(void *p){//s
	writeb_virtual_io(BARLED1, 0xFF);
	writeb_virtual_io(BARLED2, 0);
	printf("S");
}
static void f_led2(void *p){//ss
	writeb_virtual_io(BARLED1, 0xFF);
	writeb_virtual_io(BARLED2, 0);
	printf("SS");
}
static void f_led3(void *p){//sl
	writeb_virtual_io(BARLED1, 0x80);
	writeb_virtual_io(BARLED1, 0x40);
	writeb_virtual_io(BARLED1, 0x20);
	writeb_virtual_io(BARLED1, 0x10);
	writeb_virtual_io(BARLED1, 0x08);
	writeb_virtual_io(BARLED1, 0x06);
	writeb_virtual_io(BARLED2, 0);
	printf("SL");
}
static void f_led4(void *p){//l
	writeb_virtual_io(BARLED1, 0xFF);
	writeb_virtual_io(BARLED2, 0);
	printf("L");
}
static void f_led5(void *p){//ls
	writeb_virtual_io(BARLED1, 0xFF);
	writeb_virtual_io(BARLED2, 0xFF);
	printf("LS");
}
static void f_led6(void *p){//ll
	writeb_virtual_io(BARLED1, 0);
	writeb_virtual_io(BARLED2, 0);
	printf("LL");
}
static void f_ts(void *P){
	short_timer = xTaskTickCount();
}
struct state_machine_x SM[NUM_STATE] = {
		//ct, nextstate{on,off,to},action{on,off,to}
		{0,{1,0,0},{f_ts,NULL,NULL}},
		{1,{1,2,5},{NULL,f_ts,NULL}},
		{0,{3,2,0},{f_ts,NULL,f_led1}}, //s
		{1,{3,0,4},{NULL,f_led2,NULL}}, //ss
		{1,{4,0,4},{NULL,f_led3,NULL}}, //sl
		{0,{5,6,5},{NULL,f_ts,NULL}},
		{1,{7,6,0},{f_ts,NULL,f_led4}}, //l
		{1,{7,0,8},{NULL,f_led5,NULL}}, //ls
		{0,{8,0,8},{NULL,f_led6,NULL}}, //ll
};

void
Exp_3_Homework(void)
{
    int state = 0;
    int input;

    printf("Exp_3_Homework 0892080 장영창");

    writeb_virtual_io(BARLED1, 0);
    writeb_virtual_io(BARLED2, 0);

	while (1) {*/
		/* Step 0: Generate Input Event */
	/*	if(SM[NUM_STATE].check_timer){
			if ((xTaskGetTickCount() - short_timer) >= MSEC2TICK(200)) {
				input = TO;
				goto do_action;
			}
		}
		if(NDS_SWITCH() & KEY_A)
			input = SW_ON;
		else
			input = SW_OFF;*/

		/* Step 1: Do Action */
	/*	do_action:
		if(SM[NUM_STATE].action[input])
			SM[NUM_STATE].action[input](NULL);*/

		/* Step 2: Set Next State */
	/*	state = SM[NUM_STATE].next_state;

		if (NDS_SWITCH() & KEY_START)
			break;
		vTaskDelay(MSEC2TICK(50));
	}
	while (NDS_SWITCH() & KEY_START)
		vTaskDelay(MSEC2TICK(10));		// Wait while START KEY is being pressed
}*/
