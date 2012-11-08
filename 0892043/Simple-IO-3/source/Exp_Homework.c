#include "FreeRTOS.h"
#include "task.h"
#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sevencore_io.h"

portTickType short_timer;
u16 barled = 0x0000;

#define NUM_STATE 9
#define NUM_INPUT 3
// Actions

portTickType start_time = 0;

struct state_machine_x {
	int check_timer;
	int next_state[NUM_INPUT];
	void (*action[NUM_INPUT])(void *p);
};

static void f_led1(void *p) { //s
	if (barled == 0x0000)
		barled = 0x8000;
	else if (barled != 0xFFFF) {
		barled = barled | (barled >> 1);
	}
	writeb_virtual_io(BARLED1, barled >> 8);
	writeb_virtual_io(BARLED2, barled);
}

static void f_led2(void *p) { // l
	barled = 0xFF00;

	writeb_virtual_io(BARLED1, barled >> 8);
	writeb_virtual_io(BARLED2, barled);
}
static void f_led3(void *p) { // ss
	if (barled != 0x0000) {
		barled = barled & (barled << 1);
	}

	writeb_virtual_io(BARLED1, barled >> 8);
	writeb_virtual_io(BARLED2, barled);
}
static void f_led4(void *p) { //sl
	barled = 0xFC00;

	writeb_virtual_io(BARLED1, barled >> 8);
	writeb_virtual_io(BARLED2, barled);
}
static void f_led5(void *p) {
	barled = 0xFFFF;

	writeb_virtual_io(BARLED1, barled);
	writeb_virtual_io(BARLED2, barled);
}
static void f_led6(void *p) { //초기상태
	barled = 0;

	writeb_virtual_io(BARLED1, barled);
	writeb_virtual_io(BARLED2, barled);
}

static void f_ts(void *p) {
	start_time = xTaskGetTickCount();
}

enum {
	SW_ON, SW_OFF, TO
};

struct state_machine_x SM[NUM_STATE] = { //time check on off to
				{ 0, { 1, 0, 0 }, { f_ts, NULL, NULL } }, // 0
				{ 1, { 1, 3, 2 }, { NULL, f_ts, NULL } }, // 1
				{ 0, { 2, 5, 2 }, { NULL, f_ts, NULL } }, // 2
				{ 1, { 4, 3, 0 }, { f_ts, NULL, f_led1 } }, // 3
				{ 1, { 4, 0, 6 }, { NULL, f_led3, NULL } }, // 4
				{ 1, { 7, 5, 0 }, { f_ts, NULL, f_led2 } }, // 5
				{ 0, { 6, 0, 6 }, { NULL, f_led4, NULL } }, // 6
				{ 1, { 7, 0, 8 }, { NULL, f_led5, NULL } }, // 7
				{ 0, { 8, 0, 8 }, { NULL, f_led6, NULL } } // 8
		};

void Exp_3_Homework(void) {
	// variables
	int state;
	int input;
	printf("Exp_3_Homework");

	state = 0;
	barled = 0;
	writeb_virtual_io(BARLED1, 0);
	writeb_virtual_io(BARLED2, 0);

	while (1) {
		/* Step 0: Generate Input Event */
		if (SM[state].check_timer) {
			if ((xTaskGetTickCount() - start_time) >= MSEC2TICK(200) ) {
				input = TO;
				goto do_action;
				// Input happens
			}
		}
		if (NDS_SWITCH() & KEY_A)
			input = SW_ON;
		else
			input = SW_OFF;
		/* Step 1: Do Action */

		do_action: if (SM[state].action[input])
			SM[state].action[input](NULL);

		/* Step 2: Set Next State */
		state = SM[state].next_state[input];

		if (NDS_SWITCH() & KEY_START)
			break;

		vTaskDelay(MSEC2TICK(50) );
	}
	while (NDS_SWITCH() & KEY_START)
		vTaskDelay(MSEC2TICK(10) ); // Wait while START KEY is being pressed
}
