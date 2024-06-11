#include "../../header/Card/CardModel.h"

namespace Card
{
	CardModel::CardModel(Rank rank, Suit suit)
	{
		card_data = new CardData(rank, suit, State::OPEN);
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

	CardData* CardModel::getCardData()
	{
		return card_data;
	}
}
