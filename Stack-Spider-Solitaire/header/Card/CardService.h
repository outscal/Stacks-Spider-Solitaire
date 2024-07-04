#pragma once
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Stack/IStack.h"
#include "../../header/Card/CardController.h"

namespace Card
{
	using namespace Stack;
	using namespace Gameplay;

	class CardService
	{
	private:
		const float card_height_to_width_ratio = 1.37f;
		float card_width;
		float card_height;

		void shuffleDeck(IStack<CardController*>* card_deck);
		float calculateCardWidth(float width_space_for_cards, int play_stack_count);
		float calculateCardHeight(float card_width);

	public:
		CardService();
		~CardService();

		void initialize();
		void update();
		void render();

		float getCardWidth();
		float getCardHeight();

		IStack<CardController*>* generateRandomizedCardDeck();
		IStack<CardController*>* generateSequentialCardDeck();
		CardController* generateCard(Rank rank, Suit suit);
		void calculateCardExtends(float spacing, int play_stack_count);
	};
}