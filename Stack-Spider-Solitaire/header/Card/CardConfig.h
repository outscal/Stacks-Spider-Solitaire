#pragma once

namespace Card
{
    static const int number_of_decks = 4;
    static const int number_of_ranks = 13;
    static const int number_of_suits = 2;

    enum class Suit
    {
        HEARTS,
        SPADES
    };

    enum class Rank
    {
        ACE = 1,
        TWO,
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
    };

    enum class State
    {
        OPEN,
        CLOSE,
    };
}