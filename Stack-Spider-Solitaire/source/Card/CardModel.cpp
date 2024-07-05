#include "../../header/Card/CardModel.h"

namespace Card
{
	CardModel::CardModel(Rank rank, Suit suit)
	{

		card_data = new CardData(rank, suit, State::CLOSE);
		card_visibility = CardVisibility::VISIBLE;
		
	}

	CardModel::~CardModel()
	{
		delete (card_data);
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
		card_data->state = card_state;
	}

	CardData* CardModel::getCardData()
	{
		return card_data;
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

}
