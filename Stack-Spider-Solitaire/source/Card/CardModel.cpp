#include "Card/CardModel.h"

namespace Card
{
	CardModel::CardModel(Rank rank, Suit suit)
	{
		card_type = new CardType(rank, suit, State::CLOSE);
		card_visibility = CardVisibility::VISIBLE;
	}

	CardModel::~CardModel()
	{
		delete (card_type);
	}

	void CardModel::setPosition(sf::Vector2f card_position)
	{
		position = card_position;
	}

	sf::Vector2f CardModel::getPosition()
	{
		return position;
	}

	void CardModel::setCardState(State card_state)
	{
		card_type->state = card_state;
	}

	CardType* CardModel::getCardType()
	{
		return card_type;
	}

	void CardModel::setCardVisibility(CardVisibility visibility)
	{
		card_visibility = visibility;
	}

	CardVisibility CardModel::getCardVisibility()
	{
		return card_visibility;
	}

	void CardModel::setHideDuration(float duration)
	{
		hide_duration = duration;
	}

	float CardModel::getHideDuration()
	{
		return hide_duration;
	}
} // namespace Card
