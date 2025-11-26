#ifndef HAND_H
#define HAND_H
#include <stdbool.h>

typedef enum {
    TWO = 0,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    NOT_A_CARD = -2
} Card;

typedef enum {
    HIGH_CARD = 1,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
    NOT_A_TYPE = -2
} Type;

typedef struct {
    Card hand[5];
    int bid;
    int rank;
    Type type;
    bool is_valid;
} Hand;


/**
 * create a Card from a character
 * @param c the character to convert
 * @return the created Card
 */
Card create_card(const char c);

/**
 * read a line and create a Hand struct
 * @param line the line to read
 * @return the created Hand struct
 */
Hand create_hand(const char* line);

/**
 * evaluate the type of hand
 * @param hand pointer to the Card array
 * @return the evaluated Type
 */
Type evaluate_hand(Card* hand);

/**
 * compare two Hand structs
 * @param hand1 pointer to the first Hand struct
 * @param hand2 pointer to the second Hand struct
 * @return negative if hand1 < hand2, positive if hand1 > hand2, zero if equal
 */
int compare_hand(const void * hand1, const void * hand2);

#endif // HAND_H
