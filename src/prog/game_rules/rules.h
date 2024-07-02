#ifndef RULES_H
#define RULES_H

#include <stdbool.h>
#include <string.h>

#include "../functions/sprite.h"
#include "../functions/aux_func.h"

#define DECK_SIZE 40

typedef struct {
    int rank;
    int value;
    int suit;          //suits: clubs (♣, 0), diamonds (♦, 1), hearts (♥, 2) and spades (♠, 3)
    Sprite *sprite;
} Card;

typedef struct rules{
    int playerNum;
    int numCards;
    Card playerHand[10];
} Player;



/**
 * @brief Fills a deck of cards.
 *
 * Initializes a deck of cards, assigning each card a rank, suit, value, and sprite.
 * Fills the deck in a specific order, with the rank and suit incrementing sequentially.
 * The value of the cards is determined by a switch statement, with specific values assigned to ranks 5-9.
 * All other ranks are assigned a value of 0.
 *
 */
void (fillDeck)();


/**
 * @brief Shuffles the deck of cards.
 *
 * Shuffles the deck of cards using the Fisher-Yates algorithm.
 * The deck is shuffled in place, with each card being swapped with another card at a random index.
 *
 */
void (shuffleDeck)();


/**
 * @brief Shuffles the deck of cards with a seed.
 *
 * Shuffles the deck of cards using the Fisher-Yates algorithm.
 * The deck is shuffled in place, with each card being swapped with another card at a random index.
 * The seed is used to generate a random number, which is used to shuffle the deck.
 *
 */
void (shuffleDeckSeed)();



/**
 * @brief Deals a card from the deck.
 *
 * Deals a card from the deck, removing the card from the deck and returning it.
 * The card is removed from the top of the deck, and the deck is resized accordingly.
 *
 * @return The card that was dealt.
 */
Card (getTop)();


/**
 * @brief Deals a card from the deck.
 *
 * Deals a card from the deck, removing the card from the deck and returning it.
 * The card is removed from the bottom of the deck, and the deck is resized accordingly.
 *
 * @return The card that was dealt.
 */
Card (getBottom)();


/**
 * @brief Splits and reorders a deck of cards.
 *
 * Splits the deck at a given index and reorders it by placing the second half before the first.
 *
 * @param index The index at which to split and reorder the deck.
 */
void (splitDeck)();    //splits the deck at the index(1-40)


/**
 * @brief Processes a round of a card game.
 *
 * Calculates the rank of each player's card, taking into account the trump suit and the round suit.
 * Determines the winner of the round based on the calculated ranks.
 *
 * @return The player number (1-4) who won the round.
 */
int (processRound)();




/**
 * @brief Checks if a selected card is playable.
 *
 * Checks if a selected card from a player's hand is playable based on the round suit.
 * If the player has a card of the round suit in their hand, they must play a card of that suit.
 * If they do not have a card of the round suit, they can play any card.
 *
 * @param playerHand Pointer to the array of cards in the player's hand.
 * @param numCards The number of cards in the player's hand.
 * @param selectedCard The card the player has selected to play.
 * @return true if the selected card is playable, false otherwise.
 */
bool (isPlayable)(Card *playerHand, int numCards, Card selectedCard);


/**
 * @brief Determines the card to be played by the bot.
 *
 * Decides which card the bot should play based on the current round suit and trump suit.
 * If the round suit hasn't been set, it sets the round suit to the suit of the first card in the bot's deck and plays that card.
 * If the bot has a card of the round suit, it plays that card.
 * If the bot doesn't have a card of the round suit, but has a card of the trump suit, it plays that card.
 * If the bot doesn't have a card of either the round suit or the trump suit, it plays the first card in its deck.
 *
 * @param playerDeck Pointer to the array of cards in the bot's deck.
 * @return The index of the card to be played in the bot's deck.
 */
int (botPlayCard)(Card* playerDeck);



/**
 * @brief Retrieves the sprite for a card based on its rank and suit.
 *
 * Maps a card's rank and suit to it's sprite.
 * The rank is mapped to a number from 0 to 9, representing 2, 3, 4, 5, 6, Q, J, K, 7, and Ace respectively.
 * The suit is mapped to a number from 0 to 3, representing clubs, diamonds, hearts, and spades respectively.
 * If the rank or suit does not match any of the predefined values, the function returns NULL.
 *
 * @param rank The rank of the card.
 * @param suit The suit of the card.
 * @return A pointer to the sprite representing the card, or NULL if the rank or suit is invalid.
 */
Sprite* (getSprite)(int rank, int suit);




/**
 * @brief Fills the hands of the players with cards from the deck.
 *
 * Distributes cards from the deck to the players' hands.
 * The order of distribution is determined by the 'order' parameter: 1 for clockwise and 0 for counter-clockwise.
 * Each player is given 10 cards from the deck.
 *
 * @param order The order of distribution: 1 for clockwise, 0 for counter-clockwise.
 * @param playerNum The player number (1-4) to be dealt cards first.
 */
void (fillPlayersHand)(int order, int playerNum);


/**
 * @brief Removes a card from a player's hand.
 *
 * Removes a card at a specific index from a player's hand.
 * After the card is removed, the number of cards in the player's hand is decremented.
 *
 * @param player The player number (1-4) from whose hand the card is to be removed.
 * @param cardIndex The index of the card to be removed in the player's hand.
 */
void (removeCard)(int player, int cardIndex);



/**
 * @brief Removes a card from a player's hand.
 *
 * Removes a card at a specific index from a player's hand.
 * The 'player' parameter is a pointer to the player structure whose hand the card is to be removed from.
 * Creates a temporary hand without the card to be removed, then copies this back to the player's hand.
 *
 * @param player A pointer to the player structure.
 * @param cardIndex The index of the card to be removed in the player's hand.
 * @param numCards The current number of cards in the player's hand.
 */
void (removeCardHand)(Player * player, int cardIndex, int numCards);

#endif // RULES_H
