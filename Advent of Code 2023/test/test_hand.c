#include "unity.h"
#include "hand.h"

// test create_card
TEST_CASE('2', TWO)
TEST_CASE('3', THREE)
TEST_CASE('4', FOUR)
TEST_CASE('5', FIVE)
TEST_CASE('6', SIX)
TEST_CASE('7', SEVEN)
TEST_CASE('8', EIGHT)
TEST_CASE('9', NINE)
TEST_CASE('T', TEN)
TEST_CASE('J', JACK)
TEST_CASE('Q', QUEEN)
TEST_CASE('K', KING)
TEST_CASE('A', ACE)
TEST_CASE('X', NOT_A_CARD)
void test_create_card(const char c, Card expected)
{
    Card result = create_card(c);
    TEST_ASSERT_EQUAL(expected, result);
}

// test create_hand
TEST_CASE(0, true)
TEST_CASE(1, false)
TEST_CASE(2, false)
TEST_CASE(3, false)
TEST_CASE(4, false)
TEST_CASE(5, false)
TEST_CASE(6, false)
TEST_CASE(7, false)
TEST_CASE(8, true)
void test_create_hand(const int index, bool is_valid)
{
    const char* test_strings[] = {
        "K43AT 328", // good input
        "2345 123", // short hand
        "234567 123", // long hand
        "2345X 123", // invalid card
        " 123", // empty card
        "K43AT ", // missing bid
        "K43AT $", // invalid bid
        "", // empty line
        "K43AT 328 extra" // extra input
    };
    Hand result = create_hand(test_strings[index]);
    TEST_ASSERT_EQUAL(is_valid, result.is_valid);
    if (is_valid) {
        TEST_ASSERT_EQUAL(328, result.bid);
        TEST_ASSERT_EQUAL(KING, result.hand[0]);
        TEST_ASSERT_EQUAL(FOUR, result.hand[1]);
        TEST_ASSERT_EQUAL(THREE, result.hand[2]);
        TEST_ASSERT_EQUAL(ACE, result.hand[3]);
        TEST_ASSERT_EQUAL(TEN, result.hand[4]);
        TEST_ASSERT_EQUAL(HIGH_CARD, result.type);
        TEST_ASSERT_EQUAL(-2, result.rank);
    }
}

// test evaluate_hand
TEST_CASE(0, HIGH_CARD)
TEST_CASE(1, ONE_PAIR)
TEST_CASE(2, TWO_PAIR)
TEST_CASE(3, THREE_OF_A_KIND)
TEST_CASE(4, FULL_HOUSE)
TEST_CASE(5, FOUR_OF_A_KIND)
TEST_CASE(6, FIVE_OF_A_KIND)
void test_evaluate_hand(const int index, Type expected){
    Card test_data[][5] = {
        {TWO, THREE, FOUR, FIVE, SIX}, // HIGH_CARD
        {TWO, TWO, FOUR, FIVE, SIX}, // ONE_PAIR
        {TWO, TWO, THREE, THREE, SIX}, // TWO_PAIR
        {THREE, THREE, THREE, FIVE, SIX}, // THREE_OF_A_KIND
        {FOUR, FOUR, FOUR, FIVE, FIVE}, // FULL_HOUSE
        {FIVE, FIVE, FIVE, FIVE, SIX}, // FOUR_OF_A_KIND
        {SIX, SIX, SIX, SIX, SIX} // FIVE_OF_A_KIND
    };
    Type result = evaluate_hand(&test_data[index]);
    TEST_ASSERT_EQUAL(expected, result);
}


// test compare_hand
TEST_CASE(0, 1, -1) // HIGH_CARD vs HIGH_CARD
TEST_CASE(1, 0, 1)  // HIGH_CARD vs HIGH_CARD (reversed)
TEST_CASE(1, 1, 0)  // HIGH_CARD vs HIGH_CARD (equal)
TEST_CASE(1, 2, -1) // HIGH_CARD vs ONE_PAIR
TEST_CASE(3, 4 , -1) // ONE_PAIR vs TWO_PAIR
TEST_CASE(5, 6 , -1) // TWO_PAIR vs THREE_OF_A_KIND
TEST_CASE(8, 7 , 1) // FULL_HOUSE vs THREE_OF_A_KIND
TEST_CASE(13, 2 , 1) // FIVE_OF_A_KIND vs ONE_PAIR
void test_compare_hand(const int index1, const int index2, int expected)
{
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
    int result = compare_hand(&test_hands[index1], &test_hands[index2]);
    if (result < 0) result = -1;
    else if (result > 0) result = 1;
    TEST_ASSERT_EQUAL(expected, result);
}

void test_get_winning_points()
{
    Hand test_hand = {
        .hand = {TWO, THREE, FOUR, FIVE, SIX},
        .bid = 100,
        .rank = 3,
        .type = HIGH_CARD,
        .is_valid = true
    };
    long result = get_winning_points(&test_hand);
    TEST_ASSERT_EQUAL(300, result);
}