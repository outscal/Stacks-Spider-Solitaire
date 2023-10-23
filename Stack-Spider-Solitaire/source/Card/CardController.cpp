#include "../../header/Card/CardController.h"

namespace Card
{
	CardController::CardController(Rank rank, Suit suit)
	{
		card_model = new CardModel(rank, suit);
		card_view = new CardView();
	}

	CardController::~CardController()
	{
		delete card_model;
		delete card_view;
	}

	void CardController::initialize(float card_width, float card_height)
	{
		card_view->initialize(card_width, card_height, this);
	}

	void CardController::update()
	{
		card_view->update();
	}

	void CardController::render()
	{
		card_view->render();
	}

	CardType* CardController::getCardType()
	{
		return card_model->getCardType();
	}

	State CardController::getCardState()
	{
		return card_model->getCardType()->state;
	}

	void CardController::setCardState(State card_state)
	{
		card_model->setCardState(card_state);

		switch (card_state)
		{
		case Card::State::OPEN:
			card_view->setCardHighLight(false);
			break;
		case Card::State::SELECTED:
			card_view->setCardHighLight(true);
			break;
		case Card::State::CLOSE:
			card_view->setCardHighLight(false);
			break;
		}

		card_view->updateCardTexture();
	}

	sf::Vector2f CardController::getCardPosition()
	{
		return card_model->getPosition();
	}

	void CardController::setCardPosition(sf::Vector2f card_position)
	{
		card_model->setPosition(card_position);
	}
}