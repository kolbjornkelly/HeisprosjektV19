/**
 * @file
 * @brief Implementation of the driver module
 *
 */




#include "elev.h"
#include "driver.h"

#include <stdio.h>

int driver_find_orders_past_floor(int in_floor);

static int m_order_matrix[N_FLOORS][N_BUTTONS];
static int m_direction;
static int m_current_floor;


void driver_queue_init() {

	driver_queue_clear_all_orders();
	m_direction = DIRN_UP;
	m_current_floor = elev_get_floor_sensor_signal();
}


int driver_queue_not_empty() {

	for (int floor = 0; floor < N_FLOORS; floor++) {
		
		for (int button = 0; button < N_BUTTONS; button++) {

			if (m_order_matrix[floor][button] == 1) {
				return 1;
			}
		}
	}
	return 0;
}


int driver_floor_passed() {

	if (elev_get_floor_sensor_signal() != -1) {
		m_current_floor = elev_get_floor_sensor_signal();

		if (m_direction == 1) {

            if (m_order_matrix[m_current_floor][0] || m_order_matrix[m_current_floor][2]) {
				return 1;
			}
		}

		if (m_direction == -1) {

			if (m_order_matrix[m_current_floor][1] || m_order_matrix[m_current_floor][2]) {
				return 1;
			}
		}

		if (!(driver_find_orders_past_floor(m_current_floor))) {
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

				if (elev_get_button_signal(button, floor) && !(m_order_matrix[floor][button])) {
					m_order_matrix[floor][button] = 1;
				}
			}
		}
	}
}


void driver_queue_clear_order() {

	if (m_current_floor != -1) {

		for (int button = 0; button < N_BUTTONS; button++) {
			m_order_matrix[m_current_floor][button] = 0;
		}
	}
}


void driver_queue_clear_all_orders() {

	for (int floor = 0; floor < N_FLOORS; floor++) {
		
		for (int button = 0; button < N_BUTTONS; button++) {
			m_order_matrix[floor][button] = 0;
		}
	}
}


void driver_start_motor() {
	elev_set_motor_direction(m_direction);
}


void driver_stop_motor() {
	elev_set_motor_direction(DIRN_STOP);
}


void driver_set_direction() {

	if (!(driver_find_orders_past_floor(m_current_floor))) {
		m_direction = -m_direction;
		m_current_floor -= m_direction;
	}
}


int driver_find_orders_past_floor(int in_floor) {

	for (int floor = in_floor + m_direction; ((floor < N_FLOORS) && (floor >= 0)); floor += m_direction) {
		
		for (int button = 0; button < N_BUTTONS; button++) {
			
			if (m_order_matrix[floor][button]) {
				return 1;
			}
		}
	}
	return 0;
}
