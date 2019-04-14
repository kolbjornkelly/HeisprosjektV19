/**
 * @file
 * @brief A module controlling the timer
 * used to keep the door open
 */


/**
 * @brief Starts the timer
 */
void timer_start();

/**
 * @brief Stops the timer
 */
void timer_stop();

/**
 * @brief Used by @c main() to check if there
 * is 3 seconds since the timer started
 */
int timer_is_out();

