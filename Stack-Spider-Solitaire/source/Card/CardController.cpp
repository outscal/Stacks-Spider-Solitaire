#include "../../header/Card/CardController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Time/TimeService.h"

namespace Card
{
	using namespace Global;

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

	void CardController::initialize(float card_width, float card_height, float hide_duration)
	{
		card_view->initialize(card_width, card_height, this);
		card_model->setCardVisibility(CardVisibility::HIDDEN);
	}

	void CardController::update()
	{
		updateCardVisibility();
		card_view->update();
	}

	void CardController::render()
	{
		card_view->render();
	}

	void CardController::updateCardVisibility()
	{
		if (card_model->getHideDuration() <= 0)
		{
			card_model->setCardVisibility(CardVisibility::VISIBLE);
		}
		else
		{
			card_model->setCardVisibility(CardVisibility::HIDDEN);

			float delta_time = ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
			card_model->setHideDuration(card_model->getHideDuration() - delta_time);
		}
	}



	CardData* CardController::getCardData()
	{
		return card_model->getCardData();
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
			if(card_model->getCardData()->rank != Rank::DEFAULT) card_view->setCardHighLight(true);
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
		card_view->setCardPosition(card_position);
		positionSet = true; //to stop flickering 
	}

	void CardController::setCardPosition()
	{
		card_view->setCardPosition(card_model->getPosition());
	}


	CardVisibility CardController::getCardVisibility()
	{
		return card_model->getCardVisibility();
	}

	void CardController::hideCard(float duration)
	{
		card_model->setHideDuration(duration);
	}

}