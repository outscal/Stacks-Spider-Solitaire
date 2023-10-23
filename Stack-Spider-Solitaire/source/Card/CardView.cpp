#include "../../header/Card/CardView.h"
#include "../../header/Global/Config.h"
#include "../../header/Card/CardController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Card/CardTexture.h"
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Event/EventService.h"

namespace Card
{
	using namespace UIElement;
	using namespace Global;
	using namespace Sound;
	using namespace Event;

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

		card_button_view->initialize("Card", getCardTexturePath(), card_width, card_height, sf::Vector2f(30, 30));
		registerButtonCallback();
	}

	void CardView::update()
	{
		updateCardView();
		card_button_view->update();
	}

	void CardView::render()
	{
		card_button_view->render();
	}

	void CardView::updateCardView()
	{
		card_button_view->setPosition(card_controller->getCardPosition());
	}

	void CardView::updateCardTexture()
	{
		card_button_view->setTexture(getCardTexturePath());
	}

	void CardView::setCardHighLight(bool b_highlight)
	{
		if (b_highlight)
		{
			card_button_view->setImageAlpha(100);
		}
		else
		{
			card_button_view->setImageAlpha(255);
		}
	}

	void CardView::registerButtonCallback()
	{
		card_button_view->registerCallbackFuntion(std::bind(&CardView::cardButtonCallback, this));
	}

	void CardView::cardButtonCallback()
	{
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
		ServiceLocator::getInstance()->getGameplayService()->setCardToProcessInput(card_controller);
		ServiceLocator::getInstance()->getEventService()->setLeftMouseButtonState(ButtonState::HELD);
	}

	sf::String CardView::getCardTexturePath()
	{
		CardType* card = card_controller->getCardType();
		sf::String texture_path = CardTexture::getCardTexturePath(card->rank, card->suit, card->state);
		return texture_path;
	}
}