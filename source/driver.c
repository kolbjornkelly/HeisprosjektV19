#include "elev.h"
#include "driver.h"

#include <stdio.h>

int driver_find_orders_past_floor(int in_floor);

static int order_matrix[N_FLOORS][N_BUTTONS];
static int direction;
static int current_floor;


void driver_queue_init() {

	driver_queue_clear_all_orders();
	direction = DIRN_UP; // Skriv opp her
	current_floor = elev_get_floor_sensor_signal();
}


int driver_queue_not_empty() {

	for (int floor = 0; floor < N_FLOORS; floor++) {
		
		for (int button = 0; button < N_BUTTONS; button++) {

			if (order_matrix[floor][button] == 1) {
				return 1;
			}
		}
	}
	return 0;
}


int driver_floor_passed() {

	if (elev_get_floor_sensor_signal() != -1) {
		current_floor = elev_get_floor_sensor_signal();

		if (direction == 1) {

			if (order_matrix[current_floor][0] || order_matrix[current_floor][2]) {
				return 1;
			}
		}

		if (direction == -1) {

			if (order_matrix[current_floor][1] || order_matrix[current_floor][2]) {
				return 1;
			}
		}

		if (!(driver_find_orders_past_floor(current_floor))) {
			return 1;
		}
		return -1;
	}
	return 0;
}


void driver_queue_set_order() {

	for (int floor = 0; floor < N_FLOORS; floor++) {

		for (int button = 0; button < N_BUTTONS; button++) {

			if (!((floor == 0 && button == BUTTON_CALL_DOWN) || (floor == N_FLOORS -1 && button == BUTTON_CALL_UP))) {

				if (elev_get_button_signal(button, floor) && !(order_matrix[floor][button])) {
					order_matrix[floor][button] = 1;
				}
			}
		}
	}
}


void driver_queue_clear_order() {

	if (current_floor != -1) {

		for (int button = 0; button < N_BUTTONS; button++) {
			order_matrix[current_floor][button] = 0;
		}
	}
}


void driver_queue_clear_all_orders() {

	for (int floor = 0; floor < N_FLOORS; floor++) {
		
		for (int button = 0; button < N_BUTTONS; button++) {
			order_matrix[floor][button] = 0;
		}
	}
}


void driver_start_motor() {
	elev_set_motor_direction(direction);
}


void driver_stop_motor() {
	elev_set_motor_direction(0);
}


void driver_set_direction() {

	if (!(driver_find_orders_past_floor(current_floor))) {
		direction = -direction;
		current_floor -= direction;
	}
}


int driver_find_orders_past_floor(int in_floor) {

	for (int floor = in_floor + direction; ((floor < N_FLOORS) && (floor >= 0)); floor += direction) {
		
		for (int button = 0; button < N_BUTTONS; button++) {
			
			if (order_matrix[floor][button]) {
				return 1;
			}
		}
	}
	return 0;
}