#pragma once
#include "Card/CardController.h"
#include "Stack/ArrayStack.h"

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

		CardController* generateCard(Type card_type, Rank rank, Suit suit);

		ArrayStack::Stack<CardController*>* generateRandomizedCardDeck(int number_of_decks = 1);

		ArrayStack::Stack<CardController*>* generateSequentialCardDeck(int number_of_decks = 1);
	};
} // namespace Card