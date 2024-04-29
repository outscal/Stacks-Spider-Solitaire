#pragma once
#include "../../header/Card/CardView.h"
#include "../../header/Global/Config.h"
#include "../../header/Card/CardController.h"
#include "../../header/Card/CardConfig.h"

namespace Card
{
	using namespace UI::UIElement;
	using namespace Global;

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

		card_button_view->initialize("Card", Config::closed_card_texture_path, card_width, card_height, sf::Vector2f(30,30));
	}

	void CardView::update()
	{
		updateCardView();
		card_button_view->update();
	}

	void CardView::render()
	{
		card_button_view->setTexture(getCardTexturePath(card_controller->getCardType()));
		card_button_view->render();
	}

	sf::String CardView::getCardTexturePath(CardType* card_type)
	{
		if (card_type->state == State::CLOSE)
		{
			return sf::String("assets/textures/cards/closed_card.png");
		}

		int card_number = static_cast<int>(card_type->rank) + (static_cast<int>(card_type->suit) * number_of_ranks);
		sf::String path = "assets/textures/cards/card_" + std::to_string(card_number) + ".png";
		return path;
	}

	void CardView::updateCardView()
	{
		card_button_view->setPosition(card_controller->getCardPosition());
	}
}