/**
 * @file
 * @brief Implementation of the
 * Finite State Machine
 */




#include <stdio.h>

#include "fsm.h"
#include "panel.h"
#include "timer.h"
#include "elev.h"
#include "driver.h"



enum FSM_STATE {
	MOVE,
	STOP_AT_FLOOR,
	STOP_BETWEEN_FLOORS,
	DOORS_OPEN,
	STOP_BUTTON_PRESSED_AT_FLOOR,
	STOP_BUTTON_PRESSED_BETWEEN_FLOORS
} STATE;


void fsm_init() {
	STATE = STOP_AT_FLOOR;
}

void fsm_button_pressed() {

	switch (STATE) {

		case STOP_BUTTON_PRESSED_AT_FLOOR:
			break;

		case STOP_BUTTON_PRESSED_BETWEEN_FLOORS:
			break;

		default:
			panel_set_button_lamp();
			driver_queue_set_order();
			break;
	}
}


void fsm_stop_button_pressed() {

	panel_set_stop_button_lamp();
	panel_clear_all_button_lamps();
	driver_queue_clear_all_orders();

	switch (STATE) {

		case STOP_AT_FLOOR:
			panel_set_door_light();
			STATE = STOP_BUTTON_PRESSED_AT_FLOOR;
			break;

		case STOP_BETWEEN_FLOORS:
			STATE = STOP_BUTTON_PRESSED_BETWEEN_FLOORS;	
			break;

		case MOVE:
			driver_stop_motor();
			STATE = STOP_BUTTON_PRESSED_BETWEEN_FLOORS;
			break; 	

		default:
			break;
	};
}


void fsm_stop_button_released() {

	panel_clear_stop_button_lamp();

	switch (STATE) {

		case STOP_BUTTON_PRESSED_AT_FLOOR:
			timer_start();
			STATE = DOORS_OPEN;
			break;

		case STOP_BUTTON_PRESSED_BETWEEN_FLOORS:
			STATE = STOP_BETWEEN_FLOORS;
			break;

		default:
			break;
	};
}


void fsm_queue_not_empty() {

	switch (STATE) {

		case STOP_AT_FLOOR:
			driver_set_direction();
			driver_start_motor();
			STATE = MOVE;
			break;

		case STOP_BETWEEN_FLOORS:
			driver_set_direction();
			driver_start_motor();
			STATE = MOVE;
			break;

		default:
			break;
	}
}


void fsm_pass_ordered_floor() {

	panel_set_floor_indicator();

	switch (STATE) {

		case MOVE:
			driver_queue_clear_order();
			panel_clear_order_lamps();
			driver_stop_motor();
			panel_set_door_light();
			timer_start();
			STATE = DOORS_OPEN;
			break;

		default:
			break;
	};

}


void fsm_pass_not_ordered_floor() {
	panel_set_floor_indicator();
}


void fsm_timer_is_out() {

	switch (STATE) {

		case DOORS_OPEN:
			panel_clear_door_light();
			timer_stop();
			STATE = STOP_AT_FLOOR;
			break;

		default:
			break;
	};
}
