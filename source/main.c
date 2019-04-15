/**
 * @file
 * @brief Main file of the elevator
 * controll system
 */


#include <stdio.h>


#include "fsm.h"
#include "panel.h"
#include "timer.h"
#include "elev.h"
#include "driver.h"



int main() {

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    elev_set_motor_direction(DIRN_DOWN);
    while (elev_get_floor_sensor_signal() == -1){}
    elev_set_motor_direction(DIRN_STOP);

    fsm_init();
    driver_queue_init();

    while (1) {

        if (panel_button_pressed()) {
            fsm_button_pressed();
        }

        if (panel_stop_button_pressed()) {
            fsm_stop_button_pressed();
        }

        if (panel_stop_button_released()) {
        	fsm_stop_button_released();
        }

        if (driver_queue_not_empty()) {
    		fsm_queue_not_empty();
    	}
        
        if (driver_floor_passed() == 1) {
        	fsm_pass_ordered_floor();
        }

        if (driver_floor_passed() == -1) {
        	fsm_pass_not_ordered_floor();
        }

        if (timer_is_out()) {
        	fsm_timer_is_out();
        }

    }
    return 0;
}
