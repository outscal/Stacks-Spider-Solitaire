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

	CardData* CardController::getCardData()
	{
		return card_model->getCardData();
	}

	sf::Vector2f CardController::getCardPosition()
	{
		return card_model->getPosition();
	}

	void CardController::setCardPosition(sf::Vector2f card_position)
	{
		card_model->setPosition(card_position);
		card_view->setCardPosition(card_position);
		positionSet = true; //to stop flickering 
	}

	void CardController::setCardState(State card_state)
	{
		card_model->setCardState(card_state);
		card_view->updateCardTexture();
	}
}