#include "Card/CardView.h"
#include "Card/CardController.h"
#include "Card/CardTexture.h"
#include "Event/EventService.h"
#include "Gameplay/GameplayService.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Sound/SoundService.h"

namespace Card
{
	using namespace UIElement;
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

	void CardView::initialize(float width, float height,
							  CardController* controller)
	{
		card_controller = controller;
		card_width = width;
		card_height = height;

		initializeButton();
		initializeImage();
	}

	void CardView::update()
	{
		updateCardView();
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

	void CardView::initializeButton()
	{
		card_button_view->initialize("Card", getCardTexturePath(), card_width,
									 card_height, sf::Vector2f(0, 0));
		registerButtonCallback();
	}

	void CardView::initializeImage()
	{
		card_highlight->initialize(Config::card_highlight_texture_path, card_width,
								   card_height, sf::Vector2f(0, 0));
		card_highlight->hide();
	}

	void CardView::updateCardView()
	{
		card_button_view->setPosition(card_controller->getCardPosition());
		card_highlight->setPosition(card_controller->getCardPosition());
	}

	void CardView::updateCardTexture()
	{
		card_button_view->setTexture(getCardTexturePath());
	}

	void CardView::setCardHighLight(bool b_highlight)
	{
		if (b_highlight)
		{
			card_highlight->show();
		}
		else
		{
			card_highlight->hide();
		}
	}

	void CardView::registerButtonCallback()
	{
		card_button_view->registerCallbackFuntion(
			std::bind(&CardView::cardButtonCallback, this));
	}

	void CardView::cardButtonCallback()
	{
		ServiceLocator::getInstance()->getSoundService()->playSound(
			SoundType::BUTTON_CLICK);
		ServiceLocator::getInstance()->getGameplayService()->setCardToProcessInput(
			card_controller);
		ServiceLocator::getInstance()->getEventService()->setLeftMouseButtonState(
			ButtonState::HELD);
	}

	sf::String CardView::getCardTexturePath()
	{
		CardType* card = card_controller->getCardType();
		sf::String texture_path =
			CardTexture::getCardTexturePath(card->rank, card->suit, card->state);
		return texture_path;
	}
} // namespace Card