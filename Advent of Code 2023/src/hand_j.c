#include <stdio.h>
#include <string.h>
#include "hand_j.h"


/**
 * create a Card from a character
 * @param c the character to convert
 * @return the created Card
 */
Card create_card(const char c)
{
    switch (c) {
        case '2': return TWO;
        case '3': return THREE;
        case '4': return FOUR;
        case '5': return FIVE;
        case '6': return SIX;
        case '7': return SEVEN;
        case '8': return EIGHT;
        case '9': return NINE;
        case 'T': return TEN;
        case 'J': return JOKER;
        case 'Q': return QUEEN;
        case 'K': return KING;
        case 'A': return ACE;
        default:  return NOT_A_CARD;
    }
}

/**
 * read a line and create a Hand struct
 * @param line the line to read
 * @return the created Hand struct
 */
Hand create_hand(const char* line)
{
    Hand hand = {
        .hand = {NOT_A_CARD, NOT_A_CARD, NOT_A_CARD, NOT_A_CARD, NOT_A_CARD},
        .bid = -2,
        .rank = -2,
        .type = NOT_A_TYPE,
        .is_valid = false,
        .jokers = 0
    };
    char buffer[10];
    if (sscanf(line, "%s %d", buffer, &hand.bid) != 2) {
        return hand;
    }
    if (strlen(buffer) != 5) {
        return hand;
    }

    // convert char to card
    for (int i = 0; i < 5; i++) {
        hand.hand[i] = create_card(buffer[i]);
        if (hand.hand[i] == NOT_A_CARD) {
            return hand;
        }
        if (hand.hand[i] == JOKER) {
            hand.jokers++;
        }
    }

    // evaluate_hand
    hand.type = evaluate_hand(&hand.hand, hand.jokers);
    if (hand.type == NOT_A_TYPE) {
        return hand;
    }
    hand.is_valid = true;
    return hand;
}

/**
 * evaluate the type of hand
 * @param hand pointer to the Card array
 * @return the evaluated Type
 */
Type evaluate_hand(Card* hand, int jokers){
    int counts[13] = {0}; // at this point, NOT_A_CARD is not possible
    for (int i = 0; i < 5; i++) {
        counts[hand[i]]++;
    }
    for (int i = 0; i < 13; i++) {
        if (counts[i] == 5) {
            return FIVE_OF_A_KIND;
        }
        else if (counts[i] == 4) {
            if (jokers > 0) {
                return FIVE_OF_A_KIND;
            }
            return FOUR_OF_A_KIND;
        }
        else if (counts[i] == 3) {
            // check for four or five of a kind
            if (jokers == 2) { return FIVE_OF_A_KIND;}
            else if (jokers == 1) { return FOUR_OF_A_KIND;}
            // check for full house
            for (int j = 0; j < 13; j++) {
                if (j != i && counts[j] == 2) {
                    return FULL_HOUSE;
                }
            }
            return THREE_OF_A_KIND;
        }
        else if (counts[i] == 2) {
            // check for four or five of a kind
            if (jokers == 3) { return FIVE_OF_A_KIND;}
            else if (jokers == 2) { return FOUR_OF_A_KIND;}
            else if (jokers == 1) { // check for full house or three of a kind
                for (int j = 0; j < 13; j++) {
                    if (j != i && counts[j] == 2) {
                        return FULL_HOUSE;
                    }
                    return THREE_OF_A_KIND;
                }
            }
            else { // no jokers check for full house and two pair
                for (int j = 0; j < 13; j++) {
                    if (j != i && counts[j] == 3) {
                        return FULL_HOUSE;
                    }
                    if (j != i && counts[j] == 2) {
                        return TWO_PAIR;
                    }
                }
            }
        }
        else {
        // check for four or five of a kind
        if (jokers == 4) { return FIVE_OF_A_KIND;}
        else if (jokers == 3) { return FOUR_OF_A_KIND;}
        else if (jokers == 2) { // check for full house or three of a kind
            for (int j = 0; j < 13; j++) {
                if (j != i && counts[j] == 3) {
                    return FULL_HOUSE;
                }
                if (j != i && counts[j] == 2) {
                    return FULL_HOUSE;
                }
                return THREE_OF_A_KIND;
            }
        }
        else if (jokers == 1) {
            // check for full house, two pair, or one pair
            for (int j = 0; j < 13; j++) {
                if (j != i && counts[j] == 3) {
                    return FOUR_OF_A_KIND;
                }
                if (j != i && counts[j] == 2) {
                    return THREE_OF_A_KIND;
                }
            }
            return ONE_PAIR;
        }
        // check for full house and two pair
        for (int j = 0; j < 13; j++) {
            if (j != i && (counts[j] == 3  || (counts[j] == 2 && jokers > 0))) {
                return FULL_HOUSE;
            }
            if (j != i && (counts[j] == 2 || (counts[j] == 1 && jokers > 0))) {
                return TWO_PAIR;
            }
        }
            return ONE_PAIR;
        }
    }
    return HIGH_CARD;
}

/**
 * compare two Hand structs
 * @param hand1 pointer to the first Hand struct
 * @param hand2 pointer to the second Hand struct
 * @return negative if hand1 < hand2, positive if hand1 > hand2, zero if equal
 */
int compare_hand(const void * hand1, const void * hand2){
    int diff = ((Hand*)hand1)->type - ((Hand*)hand2)->type;
    if (diff != 0) {
        return diff;
    }
    for (int i = 0; i < 5; i++) {
        diff = ((Hand*)hand1)->hand[i] - ((Hand*)hand2)->hand[i];
        if (diff != 0) {
            return diff;
        }
    }
    return 0;
}

/**
 * get the winning points for a hand type
 * @param hand pointer to the Hand struct
 * @return the winning points
 */
long get_winning_points(Hand* hand)
{
    return (long)hand->bid * hand->rank;
}