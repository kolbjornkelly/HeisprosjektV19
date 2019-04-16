/**
 * @file
 * @brief A module responsible for the panel.
 * This includes polling button pushes, setting
 * and clearing button and floor lights
 */


/**
 * @brief Used by @c main() to check if any button,
 * besides the stop button, is being pressed
 * @return 1 if pressed
 */
int panel_button_pressed();


/**
 * @brief Used by @c main() to check if the stop
 * button is being pressed
 * @return 1 if pressed
 */
int panel_stop_button_pressed();


/**
 * @brief Used by @c main() to check if the stop
 * button has been released
 * @return 1 if released
 */
int panel_stop_button_released();


/**
 * @brief Ignites lamp of the button
 * being pressed
 */
void panel_set_button_lamp();


/**
 * @brief Clears all lamps asosciated
 * with a floor
 */
void panel_clear_order_lamps();


/**
 * @brief Ignites lamp at the current floor
 */
void panel_set_floor_indicator();


/**
 * @brief Clears all button lamps
 * besides the stop button lamp
 */
void panel_clear_all_button_lamps();


/**
 * @brief Ignites the stop button lamp
 */
void panel_set_stop_button_lamp();


/**
 * @brief Clears the stop button lamp
 */
void panel_clear_stop_button_lamp();


/**
 * @brief Ignites the "door open" lamp
 */
void panel_set_door_light();


/**
 * @brief Clears the "door open" lamp
 */
void panel_clear_door_light();
