#pragma once

namespace Card
{
	// Compile time constants
	constexpr int number_of_ranks = 13;
	constexpr int number_of_suits = 2;
	constexpr auto number_of_wildcards = 4;

	// Come up with a better name for this
	enum class Type
	{
		SORT,
		VISION,
		SWAP,
		TIME,
		DEFAULT
	};

	// rank + suit * num_ranks
	enum class Suit
	{
		HEARTS,
		SPADES,
		DEFAULT
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
		DEFAULT,
	};

	enum class State
	{
		OPEN,
		SELECTED,
		CLOSE,
	};
} // namespace Card