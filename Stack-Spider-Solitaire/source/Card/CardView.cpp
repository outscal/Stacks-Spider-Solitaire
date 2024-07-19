#pragma once
#include "../../header/Card/CardView.h"
#include "../../header/Global/Config.h"
#include "../../header/Card/CardController.h"
#include "../../header/Card/CardConfig.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Sound/SoundService.h"

namespace Card
{
	using namespace UI::UIElement;
	using namespace Global;
	using namespace Sound;

	CardView::CardView()
	{
		card_button_view = new ButtonView();
	}

	CardView::~CardView()
	{
		delete (card_button_view);
	}

	void CardView::initialize(float width, float height, CardController* controller)
	{
		card_controller = controller;
		card_width = width;
		card_height = height;

		initializeButton();
	}

	void CardView::initializeButton()
	{
		card_button_view->initialize("Card", Config::closed_card_texture_path, card_width, card_height, sf::Vector2f(30,30));
		card_button_view->registerCallbackFuntion(std::bind(&CardView::cardButtonCallback, this));
	}

	void CardView::update()
	{
		
		card_button_view->update();
	}

	void CardView::render()
	{
		card_button_view->render();
	}

	void CardView::updateCardTexture()
	{
		card_button_view->setTexture(getCardTexturePath(card_controller->getCardData()));
	}

	void CardView::setCardPosition(sf::Vector2f card_position)
	{
		card_button_view->setPosition(card_position);
	}

	sf::String CardView::getCardTexturePath(CardData* card_type)
	{
		if (card_type->state == State::CLOSE)
		{
			return sf::String("assets/textures/cards/closed_card.png");
		}

		int card_number = static_cast<int>(card_type->rank) + (static_cast<int>(card_type->suit) * number_of_ranks);
		sf::String path = "assets/textures/cards/card_" + std::to_string(card_number) + ".png";
		return path;
	}

	void CardView::cardButtonCallback()
	{
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
		ServiceLocator::getInstance()->getGameplayService()->processCard(card_controller);
	}
}