#ifndef AUX_FUNC_H
#define AUX_FUNC_H

#include "lcom/lcf.h"
#include "../../dispositivos/rtc/rtc.h"
#include "sprite.h"


/**
 * @brief Converts the current RTC time into an array of integers.
 * 
 * Allocates an array of integers and fills it with the current RTC time, split into tens and units for hours, minutes, and seconds.
 * The array is then returned.
 * 
 * @return Returns a pointer to the array of integers representing the current RTC time.
 */
int* time_to_int();


/**
 * @brief Converts a number into a sprite.
 * 
 * Receives a number and returns a pointer to the corresponding sprite.
 * 
 * @param num Number to be converted into a sprite.
 * @return Returns the sprite corresponding to the number.
 */
Sprite* num_to_sprite(int num);


/**
 * @brief Returns the current seed.
 * 
 * Returns the current seed used for the random number generator.
 * 
 * @return Returns the current seed.
 */
uint8_t get_seed();


/**
 * @brief Sets the seed for the random number generator and prints some random numbers.
 * 
 * Sets the seed for the random number generator to the provided value. Generates and prints ten random numbers.
 * 
 * @param seed_res The seed to be set for the random number generator.
 */
void set_seed(uint8_t seed);


/**
 * @brief Generates a random number using a linear congruential generator (LCG).
 * 
 * Generates a random number using a linear congruential generator (LCG) algorithm. Multiplies the seed by a count, 
 * multiplies the result by a large prime number, adds a constant, and masks the result to 31 bits. The count is then incremented.
 * 
 * @return Returns the generated number.
 */
uint32_t lcg_rand();


/**
 * @brief Converts a score into an array of integers.
 * 
 * Allocates an array of integers and fills it with the provided score, split into tens and units.
 * The array is then returned.
 * 
 * @param score The score to be converted into an array of integers.
 * @return Returns a pointer to the array of integers representing the score.
 */
int* score_to_int(int score);


/**
 * @brief Gets the position of the slider.
 * 
 * Receives the x position of the slider and returns the corresponding card
 * 
 * @param x The x position of the slider.
 * 
 * @return Returns the deck index corresponding to the slider position.
*/
int get_slider_pos(int x);




/**
 * @brief Calculates the time spent between two RTC times.
 * 
 * Calculates the time spent between two RTC times, in minutes.
 * 
 * @param start The start time.
 * @param end The end time.
 * @return Returns the time spent between the two times, in minutes.
 */
int get_time_spent(rtc_struct start, rtc_struct end);


/**
 * @brief Converts a time interval into an array of integers.
 * 
 * Allocates an array of integers and fills it with the provided time interval, split into hours, minutes, and seconds.
 * The array is then returned.
 * 
 * @param time_spent The time interval to be converted into an array of integers.
 * @param size The size of the array to be allocated.
 * @return Returns a pointer to the array of integers representing the time interval.
 */
int* time_spent_to_array(int time_spent, int* size);

#endif // AUX_FUNC_H

