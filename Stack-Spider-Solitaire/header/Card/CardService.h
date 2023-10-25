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
		IStack<CardController*>* generateRandomizedCardDeck(int number_of_decks = 1);
		IStack<CardController*>* generateSequentialCardDeck(int number_of_decks = 1);
	};
}