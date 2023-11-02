#include "Card/CardController.h"
#include "Global/ServiceLocator.h"
#include "Global/TimeService.h"

#include <SFML/Window/Mouse.hpp>

#include <cmath>
#include <iostream>

namespace Card
{
	using namespace Global;

	CardController::CardController(CardTypeEnum card_type, Rank rank, Suit suit)
	{
		card_model = new CardModel(card_type, rank, suit);
		card_view = new CardView();
	}

	CardController::~CardController()
	{
		delete card_model;
		delete card_view;
	}

	void CardController::initialize(float card_width, float card_height,
									[[maybe_unused]] float hide_duration)
	{
		card_view->initialize(card_width, card_height, this);
		card_model->setCardVisibility(CardVisibility::HIDDEN);
	}

	void CardController::update()
	{

		updateCardVisibility();
		card_view->update();
	}

	bool CardController::shouldFollowMouse()
	{
		return this->card_follow_mouse;
	}

	void CardController::followMouse()
	{
		// Save the prev position of the card for later use
		// in the this->stopFollowingMouse() function.
		this->card_follow_mouse = true;
	}

	void CardController::stopFollowingMouse()
	{
		this->card_follow_mouse = false;
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

			float delta_time =
				ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
			card_model->setHideDuration(card_model->getHideDuration() - delta_time);
		}
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
			card_view->unselectCard();
			break;

		case Card::State::SELECTED: {
			if (card_model->getCardType()->rank != Rank::DEFAULT || card_model->getCardType()->type != CardTypeEnum::DEFAULT)
			{
				card_view->selectCard();
			}

			break;
		}

		case Card::State::CLOSE:
			card_view->unselectCard();
			break;
		}

		card_view->updateCardTexture();
	}

	sf::Vector2f CardController::getCardPosition() const
	{
		return card_model->getPosition();
	}

	void CardController::setCardPosition(const sf::Vector2f& card_position)
	{
		card_model->setPosition(card_position);
	}

	void CardController::moveCardPosition(const sf::Vector2f& step)
	{
		sf::Vector2f pos = this->getCardPosition();
		this->setCardPosition({pos.x + step.x, pos.y + step.y});
	}

	CardVisibility CardController::getCardVisibility()
	{
		return card_model->getCardVisibility();
	}

	void CardController::hideCard(float duration)
	{
		card_model->setHideDuration(duration);
	}
} // namespace Card