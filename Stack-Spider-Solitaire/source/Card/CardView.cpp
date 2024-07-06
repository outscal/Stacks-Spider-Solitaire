#pragma once
#include "../../header/Card/CardView.h"
#include "../../header/Global/Config.h"
#include "../../header/Card/CardController.h"
#include "../../header/Card/CardConfig.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Event/EventService.h"


namespace Card
{
	using namespace UI::UIElement;
	using namespace Global;
	using namespace Sound;
	using namespace Event;

	CardView::CardView()
	{
		card_button_view = new ButtonView();
		card_highlight = new ImageView();
	}

	CardView::~CardView()
	{
		delete (card_button_view);
		delete (card_highlight);
	}

	void CardView::initialize(float width, float height, CardController* controller)
	{
		card_controller = controller;
		card_width = width;
		card_height = height;

		initializeButton();
		initializeImage();
	}

	void CardView::initializeButton()
	{
		card_button_view->initialize("Card", Config::closed_card_texture_path, card_width, card_height, sf::Vector2f(30,30));
		card_button_view->registerCallbackFuntion(std::bind(&CardView::cardButtonCallback, this));
	}

	void CardView::update()
	{
		
		card_button_view->update();
		card_highlight->update();
	}

	void CardView::render()
	{
		if (card_controller->getCardVisibility() == CardVisibility::VISIBLE)
		{
			card_button_view->render();
			card_highlight->render();
		}
	}

	void CardView::initializeImage()
	{
		card_highlight->initialize(Config::card_highlight_texture_path, card_width, card_height, sf::Vector2f(0, 0));
		card_highlight->hide();
	}


	void CardView::updateCardTexture()
	{
		card_button_view->setTexture(getCardTexturePath(card_controller->getCardData()));
	}

	void CardView::setCardHighLight(bool b_highlight)
	{
		if (b_highlight) card_highlight->show();
		else card_highlight->hide();
	}

	void CardView::setCardPosition(sf::Vector2f card_position)
	{
		card_button_view->setPosition(card_position);
		card_highlight->setPosition(card_position);
	}

	sf::String CardView::getCardTexturePath(CardData* card_type)
	{
		if (card_type->state == State::CLOSE)
		{
			return sf::String("assets/textures/cards/closed_card.png");
		}

		if (card_type->rank == Rank::DEFAULT)
		{
			return sf::String("assets/textures/cards/frame.png");
		}

		// Calculate card number based on rank and suit
		int card_number = static_cast<int>(card_type->rank) + (static_cast<int>(card_type->suit) * Card::number_of_ranks);
		sf::String path = "assets/textures/cards/card_" + std::to_string(card_number) + ".png";
		return path;
	}

	void CardView::cardButtonCallback()
	{
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
		ServiceLocator::getInstance()->getGameplayService()->setCardToProcessInput(card_controller);
		
		//set the button state to held on the same frame so only top button is pressed
		ServiceLocator::getInstance()->getEventService()->setLeftMouseButtonState(ButtonState::HELD); 

	}

}