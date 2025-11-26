#include "unity.h"
#include "hand.h"
#include "day7.h"
#include <stdio.h>


void test_get_total(){
    int total = 0;
    int result = get_total("test/day7.txt", &total);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(15, total);
    result = get_total("fake.txt", &total);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL(0, total);
}

void test_populate_hands(){
    FILE* in = fopen("test/day7.txt", "r");
    TEST_ASSERT_NOT_NULL(in);
    int size;
    Hand* hands = populate_hands(in, &size);
    TEST_ASSERT_NOT_NULL(hands);
    // TEST_ASSERT_EQUAL(3, *size);
    // TEST_ASSERT_EQUAL(10, hands[0].bid);
    for (int i = 0; i < size; i++) {
        TEST_ASSERT_TRUE(hands[i].is_valid);
    }
    free(hands);
    fclose(in);
}

void test_rank_hands(){
    Hand test_hands[] = {
        // hand, bid, rank, type, is_valid
        {{TWO, THREE, FOUR, FIVE, SIX}, 100, 1, HIGH_CARD, true},
        {{TWO, TEN, FOUR, FIVE, SIX}, 100, 1, HIGH_CARD, true}, // same type, higher card
        {{TWO, TWO, FOUR, FIVE, SIX}, 200, 1, ONE_PAIR, true},
        {{TWO, TWO, TEN, FIVE, SIX}, 200, 1, ONE_PAIR, true}, // same type, higher pair
        {{TWO, TWO, THREE, THREE, SIX}, 150, 1, TWO_PAIR, true},
        {{TWO, TWO, FOUR, FOUR, SIX}, 150, 1, TWO_PAIR, true}, // same type, higher second pair
        {{THREE, THREE, THREE, FIVE, SIX}, 300, 1, THREE_OF_A_KIND, true},
        {{THREE, THREE, THREE, TEN, SIX}, 300, 1, THREE_OF_A_KIND, true}, // same type, higher kicker
        {{FOUR, FOUR, FOUR, FIVE, FIVE}, 250, 1, FULL_HOUSE, true},
        {{FOUR, FOUR, FOUR, SIX, SIX}, 250, 1, FULL_HOUSE, true}, // same type, higher pair
        {{FIVE, FIVE, FIVE, FIVE, SIX}, 400, 1, FOUR_OF_A_KIND, true},
        {{FIVE, FIVE, FIVE, FIVE, TEN}, 400, 1, FOUR_OF_A_KIND, true}, // same type, higher kicker
        {{SIX, SIX, SIX, SIX, SIX}, 500, 1, FIVE_OF_A_KIND, true},
        {{TEN, TEN, TEN, TEN, TEN}, 600, 1, FIVE_OF_A_KIND, true} // same type, higher card
    };
    rank_hands(test_hands, 14);
    for (int i = 0; i < 14; i++) {
        TEST_ASSERT_EQUAL(i + 1, test_hands[i].rank);
    }
}