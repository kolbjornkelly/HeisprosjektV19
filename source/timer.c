
#include "timer.h"

#include <stdlib.h>
#include <time.h>

clock_t init_time;
unsigned int diff = 3;
unsigned int timer_is_on = 0;


void timer_start() {
    timer_is_on = 1;
    init_time = clock(); 
}


void timer_stop() {
	timer_is_on = 0;
}


int timer_is_out() {
    
    clock_t current_time = clock();
    
    if ((current_time - init_time) / CLOCKS_PER_SEC >= diff && timer_is_on) {
        return 1;
    }
    return 0;
}