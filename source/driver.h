/**
 * @file
 * @brief A module responsible for movement and queue handling
 *
 */


/**
 * @brief Initializes the queue matrix, position and direction
 */

void driver_queue_init();

/**
 * @brief Checks if the queue is not empty
 * @return 0 if empty, 1 if there is an order pending
 */

int driver_queue_not_empty();

/**
 * @brief Checks if the elevator is passing a floor
 * @return 0 if not, 1 if passing an ordered floor,
 * -1 if passing an insignificant floor
 */

int driver_floor_passed();

/**
 * @brief Sets order from the button currently being pushed
 */

void driver_queue_set_order();

/**
 * @brief Clears all orders from the current floor
 */

void driver_queue_clear_order();

/**
 * @brief Clears all orders
 */

void driver_queue_clear_all_orders();

/**
 * @brief Starts elevator in @p m_direction
 */

void driver_start_motor();

/**
 * @brief Stops the elevator
 */

void driver_stop_motor();

/**
 * @brief Toggles direction if there are no orders trailing
 * in the current @p m_direction. Uses the local function
 * @p int driver_find_orders_past_floor(int in_floor);
 * @warning Changes @p m_current_floor to take care of
 * direction changes inbetween floors
 */

void driver_set_direction();

