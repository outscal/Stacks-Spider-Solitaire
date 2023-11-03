#pragma once
#include "Card/CardConfig.h"
#include <SFML/Graphics.hpp>

namespace Card
{
	enum class CardVisibility
	{
		VISIBLE,
		HIDDEN,
	};

	struct CardType
	{
		CardType(Type card_type, Rank card_rank, Suit card_suit, State card_state)
			: type(card_type), rank(card_rank), suit(card_suit), state(card_state)
		{
		}

		Type type;
		Rank rank;
		Suit suit;
		State state;
	};

	class CardModel
	{
	  private:
		CardType* card_type;
		sf::Vector2f position;

		CardVisibility card_visibility;
		float hide_duration;

	  public:
		CardModel(Type card_type, Rank rank, Suit suit);
		~CardModel();

		void setPosition(const sf::Vector2f& card_position);
		sf::Vector2f getPosition();

		void setCardState(State card_state);
		CardType* getCardType();

		void setCardVisibility(CardVisibility visibility);
		CardVisibility getCardVisibility();

		void setHideDuration(float duration);
		float getHideDuration();
	};
} // namespace Card