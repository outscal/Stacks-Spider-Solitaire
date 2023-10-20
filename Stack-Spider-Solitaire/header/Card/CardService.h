#pragma once
#include "../../header/Card/CardController.h"
#include "../../header/Stack/ArrayStack.h"

namespace Card
{
	class CardService
	{
	private:
		void shuffleDeck(ArrayStack::Stack<CardController*>* card_deck);

	public:
		CardService();
		~CardService();

		void initialize();
		void update();
		void render();

		CardController* generateCard(Rank rank, Suit suit);
		ArrayStack::Stack<CardController*>* generateRandomizedCardDeck();
		ArrayStack::Stack<CardController*>* generateSequentialCardDeck();
	};
}