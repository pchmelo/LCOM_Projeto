#include "rules.h"

Card deck[DECK_SIZE];

Player player1;
Player player2;
Player player3;
Player player4;

Card card_player_1;
Card card_player_2;
Card card_player_3;
Card card_player_4;

Card trump_card;

int player_a_dar = 1;
int player_a_split = 4;


int num_cards = 0;
int turn = 0;

int roundSuit = -1;
int trumpSuit = -1;

int selected_card_player_1 = -1;
int selected_card_player_2 = -1;
int selected_card_player_3 = -1;
int selected_card_player_4 = -1;

int player_1_played = 0;
int player_3_played = 0;

int trump_location = -1;
int slide_number = -1;

int blueScore = 0;
int redScore = 0;

void (fillDeck)() {
    Card newCard;
    int rank = 0, suit = 0, deckIndex = 0, value;

    for (int i = 0; i < (DECK_SIZE / 4); i++) {
        switch (i) {
            case 5:
                value = 2;
                break;
            case 6:
                value = 3;
                break;
            case 7:
                value = 4;
                break;
            case 8:
                value = 10;
                break;
            case 9:
                value = 11;
                break;
            default:
                value = 0;
                break;
        }
        
        for (int j = 0; j < (DECK_SIZE / 10); j++) {
            newCard.rank = rank;
            newCard.suit = suit;
            newCard.value = value;
            newCard.sprite = getSprite(rank, suit);

            deck[deckIndex] = newCard;
            deckIndex++;

            suit++;
        }
        
        rank++;
        suit = 0;
    }
}

void (shuffleDeck)() {
    fillDeck();
    srand(time(NULL));
    for (int i = 0; i < DECK_SIZE; i++) {
        int j = rand() % DECK_SIZE;
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void (shuffleDeckSeed)(){
    fillDeck();
    for (int i = 0; i < DECK_SIZE; i++) {
        int j = lcg_rand() % DECK_SIZE;
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

Card (getTop)() {
    return deck[0];
}

Card (getBottom)() {
    return deck[DECK_SIZE - 1];
}

void (splitDeck)() {
    Card tempDeck[slide_number], splitDeck[DECK_SIZE];
    int aux = 0;

    for (int i = 0; i < DECK_SIZE; i++) {
        if (i < slide_number) {
            tempDeck[i] = deck[i];
        }
        else {
            splitDeck[aux] = deck[i];
            aux++;
        }
    }

    for (int i = 0; i < slide_number; i++) {
        splitDeck[aux] = tempDeck[i];
        aux++;
    }

    for (int i = 0; i < DECK_SIZE; i++) {
        deck[i] = splitDeck[i];
    }
}

int (processRound)() {
    int playerRank = card_player_1.rank, allyRank = card_player_3.rank, opponent1Rank = card_player_2.rank, opponent2Rank = card_player_4.rank;
    int roundValue = card_player_1.value + card_player_3.value + card_player_2.value + card_player_4.value;

    if (card_player_1.suit == trumpSuit) {
        playerRank += 100;
    }
    else if (card_player_1.suit != roundSuit) {
        playerRank = 0;
    }

    if (card_player_3.suit == trumpSuit) {
        allyRank += 100;
    }
    else if (card_player_3.suit != roundSuit) {
        allyRank = 0;
    }

    if (card_player_2.suit == trumpSuit) {
        opponent1Rank += 100;
    }
    else if (card_player_2.suit != roundSuit) {
        opponent1Rank = 0;
    }

    if (card_player_4.suit == trumpSuit) {
        opponent2Rank += 100;
    }
    else if (card_player_4.suit != roundSuit) {
        opponent2Rank = 0;
    }


    if (playerRank > opponent1Rank && playerRank > opponent2Rank) {
        blueScore += roundValue;
        return 1;
    }
    if (allyRank > opponent1Rank && allyRank > opponent2Rank) {
        blueScore += roundValue;
        return 3;
    }
    if (opponent1Rank > opponent2Rank) {
        redScore += roundValue;
        return 2;
    }
    else {
        redScore += roundValue;
        return 4;
    }
}

bool (isPlayable)(Card *playerHand, int numCards, Card selectedCard) {
    bool hasRoundSuit = false;

    for (int i = 0; i < numCards; i++) {
        if (playerHand[i].suit == roundSuit) {
            hasRoundSuit = true;
        }
    }

    if (hasRoundSuit) {
        if (selectedCard.suit == roundSuit) {
            return true;
        }
        else {
            return false;
        }
    }
    
    return true;
}

int (botPlayCard)(Card *playerDeck) {
    //printf("Round Suit: %d\n", roundSuit);
    //printf("Trump Suit: %d\n", trumpSuit);
    //printf("Num cards: %d\n", num_cards);


    if(roundSuit == -1){
        //printf("Round Suit: %d\n", roundSuit);
        roundSuit = playerDeck[0].suit;
        return 0;
    }

    for (int i = 0; i < num_cards; i++) {
        //printf("Template Suit: %d\n", playerDeck[i].suit);
        if (playerDeck[i].suit == roundSuit) {
            //printf("Find assisted card\n");
            return i;
        }
    }

    for (int i = 0; i < num_cards; i++) {
        if (playerDeck[i].suit == trumpSuit) {
            //printf("Find trump\n");
            return i;
        }
    }
    //printf("Find nothing\n");
    return 0;
}

Sprite* (getSprite)(int rank, int suit) {
    if (rank == 0) {
        if (suit == 0) {
            return sprite_clubs_2;
        } else if (suit == 1) {
            return sprite_diamonds_2;
        } else if (suit == 2) {
            return sprite_hearts_2;
        } else if (suit == 3) {
            return sprite_spades_2;
        }
    } else if (rank == 1){
        if (suit == 0) {
            return sprite_clubs_3;
        } else if (suit == 1) {
            return sprite_diamonds_3;
        } else if (suit == 2) {
            return sprite_hearts_3;
        } else if (suit == 3) {
            return sprite_spades_3;
        }
    } else if (rank == 2) {
        if (suit == 0) {
            return sprite_clubs_4;
        } else if (suit == 1) {
            return sprite_diamonds_4;
        } else if (suit == 2) {
            return sprite_hearts_4;
        } else if (suit == 3) {
            return sprite_spades_4;
        }
    } else if (rank == 3) {
        if (suit == 0) {
            return sprite_clubs_5;
        } else if (suit == 1) {
            return sprite_diamonds_5;
        } else if (suit == 2) {
            return sprite_hearts_5;
        } else if (suit == 3) {
            return sprite_spades_5;
        }
    } else if (rank == 4) {
        if (suit == 0) {
            return sprite_clubs_6;
        } else if (suit == 1) {
            return sprite_diamonds_6;
        } else if (suit == 2) {
            return sprite_hearts_6;
        } else if (suit == 3) {
            return sprite_spades_6;
        }
    } else if (rank == 5) {
        if (suit == 0) {
            return sprite_clubs_q;
        } else if (suit == 1) {
            return sprite_diamonds_q;
        } else if (suit == 2) {
            return sprite_hearts_q;
        } else if (suit == 3) {
            return sprite_spades_q;
        }
    } else if (rank == 6) {
        if (suit == 0) {
            return sprite_clubs_j;
        } else if (suit == 1) {
            return sprite_diamonds_j;
        } else if (suit == 2) {
            return sprite_hearts_j;
        } else if (suit == 3) {
            return sprite_spades_j;
        }
    } else if (rank == 7) {
        if (suit == 0) {
            return sprite_clubs_k;
        } else if (suit == 1) {
            return sprite_diamonds_k;
        } else if (suit == 2) {
            return sprite_hearts_k;
        } else if (suit == 3) {
            return sprite_spades_k;
        }
    } else if (rank == 8) {
        if (suit == 0) {
            return sprite_clubs_7;
        } else if (suit == 1) {
            return sprite_diamonds_7;
        } else if (suit == 2) {
            return sprite_hearts_7;
        } else if (suit == 3) {
            return sprite_spades_7;
        }
    } else if (rank == 9) {
        if (suit == 0) {
            return sprite_clubs_ace;
        } else if (suit == 1) {
            return sprite_diamonds_ace;
        } else if (suit == 2) {
            return sprite_hearts_ace;
        } else if (suit == 3) {
            return sprite_spades_ace;
        }
    }

    return NULL;
}

void (fillPlayersHand)(int order, int playerNum) { //order: 1 - ponteiro dos relogios, 0 - contra-ponteiro dos relogios
    int index = 0;

    while (index < 40){
        for(int i = 0; i < 10; i++){
            if (playerNum == 1){
                player1.playerHand[i] = deck[index];
            }
            else if (playerNum == 2){
                player2.playerHand[i] = deck[index];
            }
            else if (playerNum == 3){
                player3.playerHand[i] = deck[index];
            }
            else if (playerNum == 4){
                player4.playerHand[i] = deck[index];
            }
            index++;        
        }
        if(order == 1){
            playerNum--;
            if(playerNum == 0){
                playerNum = 4;
            }
        }
        else{
            playerNum++;
            if(playerNum == 5){
                playerNum = 1;
            }
        }
    }

    player1.playerNum = 1;
    player2.playerNum = 2;
    player3.playerNum = 3;
    player4.playerNum = 4;

    player1.numCards = 10;
    player2.numCards = 10;
    player3.numCards = 10;
    player4.numCards = 10;
}

void removeCard (int player, int cardIndex) {
    //printf("Player: %d Round: %d\n", player, num_cards);
    if (player == 1) {
        card_player_1 = player1.playerHand[cardIndex];
        removeCardHand(&player1, cardIndex, player1.numCards);
        player1.numCards--;
    }
    else if (player == 2) {
        card_player_2 = player2.playerHand[cardIndex];
        removeCardHand(&player2, cardIndex, player2.numCards);
        player2.numCards--;
    }
    else if (player == 3) {
        card_player_3 = player3.playerHand[cardIndex];
        removeCardHand(&player3, cardIndex, player3.numCards);
        player3.numCards--;
    }
    else if (player == 4) {
        card_player_4 = player4.playerHand[cardIndex];
        removeCardHand(&player4, cardIndex, player4.numCards);
        player4.numCards--;
    }
}

void removeCardHand(Player * player, int cardIndex, int numCards) {
    Card tempHand[numCards - 1];
    int aux = 0;

    for (int i = 0; i < numCards; i++) {
        if (i != cardIndex) {
            tempHand[aux] = player->playerHand[i];
            aux++;
        }
    }

    for (int i = 0; i < numCards - 1; i++) {
        player->playerHand[i] = tempHand[i];
    }
}
