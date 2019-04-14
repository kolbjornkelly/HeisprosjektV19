
#include "timer.h"

#include <stdlib.h>
#include <time.h>

clock_t m_init_time;
static unsigned int m_diff = 3;
static unsigned int m_timer_is_on = 0;


void timer_start() {
    m_timer_is_on = 1;
    m_init_time = clock();
}


void timer_stop() {
	m_timer_is_on = 0;
}


int timer_is_out() {
    
    clock_t current_time = clock();
    
    if ((current_time - m_init_time) / CLOCKS_PER_SEC >= m_diff && m_timer_is_on) {
        return 1;
    }
    return 0;
}
