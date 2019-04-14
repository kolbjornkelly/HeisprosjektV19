
/**
 * @file
 * @brief The Finite State Machine
 * controlling the logic of the elevator
 */


/**
 * @brief Sets state to idle
 */
void fsm_init();


/**
 * @brief Handles the event of a pressed
 * button
 */
void fsm_button_pressed();


/**
 * @brief Handles the event of a pressed
 * stop button
 */
void fsm_stop_button_pressed();


/**
 * @brief Handles the event of a released
 * stop button
 */
void fsm_stop_button_released();


/**
 * @brief Handles the event of the queue
 * not being empty
 */
void fsm_queue_not_empty();


/**
 * @brief Handles the event of passing
 * an ordered floor
 */
void fsm_pass_ordered_floor();


/**
 * @brief Handles the event of passing
 * a floor that has not been ordered
 */
void fsm_pass_not_ordered_floor();


/**
 * @brief Handles the event of the
 * the timer running for 3 seconds
 */
void fsm_timer_is_out();
