#pragma once
#include "../../header/Card/CardController.h"
#include "../../header/Stack/IStack.h"

namespace Card
{
	using namespace Stack;

	class CardService
	{
	private:
		void shuffleDeck(IStack<CardController*>* card_deck);

	public:
		CardService();
		~CardService();

		void initialize();
		void update();
		void render();

		CardController* generateCard(Rank rank, Suit suit);
		IStack<CardController*>* generateRandomizedCardDeck();
		IStack<CardController*>* generateSequentialCardDeck();
	};
}