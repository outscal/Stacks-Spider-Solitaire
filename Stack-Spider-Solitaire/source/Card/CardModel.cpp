#include "../../header/Card/CardModel.h"

namespace Card
{
	CardModel::CardModel(Rank rank, Suit suit)
	{
		card_type = new CardType(rank, suit, State::OPEN);
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

	CardType* CardModel::getCardType()
	{
		return card_type;
	}
}
