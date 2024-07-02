#ifndef COLLISION_H
#define COLLISION_H


#include <stdio.h>
#include <stdlib.h>

#include "../game_rules/rules.h"


/**
 * @brief Structure representing a collision area.
 * 
 * Represents a collision area in a 2D space. Contains the initial and final coordinates for both x and y axes.
 * 
 * @param xi Initial x-coordinate of the collision area.
 * @param xf Final x-coordinate of the collision area.
 * @param yi Initial y-coordinate of the collision area.
 * @param yf Final y-coordinate of the collision area.
 */
typedef struct{
    int xi;
    int xf;
    int yi;
    int yf;
} Collision;



/**
 * @brief Allocates collision arrays for the main and pause menus.
 * 
 * Allocates collision arrays for the main and pause menus. Calls separate functions to allocate each array,
 * and returns an error code if any allocation fails.
 */
int allocate_collision_array();


/**
 * @brief Allocates collision array for the main menu.
 * 
 * Allocates a collision array for the main menu. Initializes the collision areas for the start, exit, and multiplayer buttons.
 * returns an error code if any allocation fails.
 */
int allocate_collision_array_main_menu();


/**
 * @brief Allocates collision array for the pause menu.
 * 
 * Allocates a collision array for the pause menu. Initializes the collision areas for the resume, restart, and exit buttons.
 * returns an error code if any allocation fails.
 */
int allocate_collision_array_pause_menu();


/**
 * @brief Frees the collision arrays.
 * 
 * Frees the memory for collision arrays for the main and pause menus.
 */
void free_collision_array();


/**
 * @brief Checks if a point is inside a collision area.
 * 
 * Checks if a point is inside a collision area. Returns 1 if the point is inside the collision area, and 0 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @param collision Collision area to check.
 * @return int 1 if the point is inside the collision area, 0 otherwise.
 */
int isCollision(int x, int y, Collision collision);


/**
 * @brief Checks if a point is inside the start button collision area.
 * 
 * Checks if a point is inside the start button collision area. Returns 1 if the point is inside the collision area, and 0 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @return int 1 if the point is inside the collision area, 0 otherwise.
 */
int testStartButtonCollision(int x, int y);


/**
 * @brief Checks if a point is inside the exit button collision area.
 * 
 * Checks if a point is inside the exit button collision area. Returns 1 if the point is inside the collision area, and 0 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @return int 1 if the point is inside the collision area, 0 otherwise.
 */
int testExitButtonCollision(int x, int y);


/**
 * @brief Checks if a point is inside the multiplayer button collision area.
 * 
 * Checks if a point is inside the multiplayer button collision area. Returns 1 if the point is inside the collision area, and 0 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @return int 1 if the point is inside the collision area, 0 otherwise.
 */
int testMultiButtonCollision(int x, int y);


/**
 * @brief Checks if a point is inside the resume button collision area.
 * 
 * Checks if a point is inside the resume button collision area. Returns 1 if the point is inside the collision area, and 0 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @return int 1 if the point is inside the collision area, 0 otherwise.
 */
int testResumeButtonCollision(int x, int y);


/**
 * @brief Checks if a point is inside the restart button collision area.
 * 
 * Checks if a point is inside the restart button collision area. Returns 1 if the point is inside the collision area, and 0 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @return int 1 if the point is inside the collision area, 0 otherwise.
 */
int testRestartButtonCollision(int x, int y);


/**
 * @brief Checks if a point is inside the exit button collision area in the pause menu.
 * 
 * Checks if a point is inside the exit button collision area in the pause menu. Returns 1 if the point is inside the collision area, and 0 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @return int 1 if the point is inside the collision area, 0 otherwise.
 */
int testExitButtonCollisionPause(int x, int y);


/**
 * @brief Checks if a point is inside the card grab area.
 * 
 * Checks if a point is inside the card grab area. Returns the index of the card if the point is inside the collision area, and -1 otherwise.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @return int Index of the card if the point is inside the collision area, -1 otherwise.
 */
int selected_card(int x, int y);


/**
 * @brief Tests if a given point is within a card grab collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing a card grab area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testCardGrabCollision(int x, int y);


/**
 * @brief Tests if a given point is within the cancel button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing a cancel button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testCancelButtonCollision(int x, int y);


/**
 * @brief Tests if a given point is within the accept button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing an accept button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testAcceptButtonCollision(int x, int y);


/**
 * @brief Tests if a given point is within the decline button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing a decline button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testDeclineButtonCollision(int x, int y);


/**
 * @brief Tests if a given point is within the top button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing the top button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testTopButton(int x, int y);


/**
 * @brief Tests if a given point is within the bot button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing the bot button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testBotButton(int x, int y);



/**
 * @brief Tests if a given point is within the slide button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing the button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testSlideButton(int x, int y);


/**
 * @brief Tests if a given point is within the square button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing the square button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testSquareCollision(int x, int y);



/**
 * @brief Tests if a given point is within the timer tracker "confirm" button collision area.
 * 
 * Checks if a given point (x, y) is within the predefined collision area representing the confirm button area.
 * If the point is within the collision area, returns 1. Otherwise, returns 0.
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return Returns 1 if the point is within the collision area, 0 otherwise.
 */
int testTimerTrackerCollision(int x, int y);

#endif // COLLISION_H
