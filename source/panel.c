/**
 * @file
 * @brief Implementation of the panel module
 *
 */



#include <stdio.h>

#include "panel.h"
#include "elev.h"


static int m_stop_button_state;


int panel_button_pressed() {

	for (int floor = 0; floor < N_FLOORS; floor++) {

		for (int button = 0; button < N_BUTTONS; button++) {

			if (!((floor == 0 && button == BUTTON_CALL_DOWN) || (floor == N_FLOORS -1 && button == BUTTON_CALL_UP))) {
				
				if (elev_get_button_signal(button, floor) && !(lamp_matrix[floor][button])) {
					return 1;
				}
			}
		}
	}
	return 0;
}


int panel_stop_button_pressed() {

	if (elev_get_stop_signal()) {
		m_stop_button_state = 1;
		return 1;
	}
	return 0;
}


int panel_stop_button_released() {

	if ((m_stop_button_state == 1) && (elev_get_stop_signal() == 0)) {
		m_stop_button_state = 0;
		return 1;
	}
	return 0;
}


void panel_set_button_lamp() {

	for (int floor = 0; floor < N_FLOORS; floor++) {

		for (int button = 0; button < N_BUTTONS; button++) {

			if (!((floor == 0 && button == BUTTON_CALL_DOWN) || (floor == N_FLOORS -1 && button == BUTTON_CALL_UP))) {

				if (elev_get_button_signal(button, floor) && !(lamp_matrix[floor][button])) {
					elev_set_button_lamp(button, floor, 1);
					lamp_matrix[floor][button] = 1;
				}
			}
		}
	}
}


void panel_clear_order_lamps() {
	
	int current_floor = elev_get_floor_sensor_signal();

	if (current_floor >= 0) {

		for (int button = 0; button < N_BUTTONS; button++) {

			if ((!(button == BUTTON_CALL_DOWN && current_floor == 0)) && (!(button == BUTTON_CALL_UP && current_floor == N_FLOORS - 1))) {
				elev_set_button_lamp(button, current_floor, 0);
				lamp_matrix[current_floor][button] = 0;
			}
		}
	}
}

void panel_set_floor_indicator() {

	int current_floor = elev_get_floor_sensor_signal();

	if (current_floor != -1) {
		elev_set_floor_indicator(current_floor);
	}
}

void panel_clear_all_button_lamps() {

	for (int floor = 0; floor < N_FLOORS; floor++) {

		for (int button = 0; button < N_BUTTONS; button++) {

			if ((!(button == BUTTON_CALL_DOWN && floor == 0)) && (!(button == BUTTON_CALL_UP && floor == N_FLOORS - 1))) {
				elev_set_button_lamp(button, floor, 0);
				lamp_matrix[floor][button] = 0;
			}
		}
	}
}

void panel_set_stop_button_lamp() {
	elev_set_stop_lamp(1); 
}


void panel_clear_stop_button_lamp() {
	elev_set_stop_lamp(0); 
}


void panel_set_door_light() {
	elev_set_door_open_lamp(1);
}


void panel_clear_door_light() {
	elev_set_door_open_lamp(0);
}
