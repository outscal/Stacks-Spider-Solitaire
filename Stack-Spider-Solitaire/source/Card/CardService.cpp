#include "../../header/Card/CardService.h"
#include "../../header/Card/CardController.h"
#include "../../header/Card/CardConfig.h"
#include <ctime>

namespace Card
{
	using namespace ArrayStack;

	CardService::CardService() = default;

	CardService::~CardService() = default;

	void CardService::initialize() { }

	void CardService::update() { }

	void CardService::render() { }

	CardController* CardService::generateCard(Rank rank, Suit suit)
	{
		return new CardController(rank, suit);
	}

	Stack<CardController*>* CardService::generateSequentialCardDeck()
	{
		//Stack<CardController*>* card_deck = new Stack<CardController*>();

		for (int rank = 0; rank < static_cast<int>(number_of_ranks); rank++)
		{
			for (int suit = 0; suit < static_cast<int>(number_of_suits); suit++)
			{
				CardController* card = generateCard(static_cast<Rank>(rank), static_cast<Suit>(suit));
				//card_deck->push(card);
			}
		}

		return nullptr;
	}

	Stack<CardController*>* CardService::generateRandomizedCardDeck()
	{
		Stack<CardController*>* card_deck = generateSequentialCardDeck();

		//shuffleDeck(card_deck);
		return card_deck;
	}

	void CardService::shuffleDeck(Stack<CardController*>* card_deck)
	{
		srand(static_cast<unsigned>(time(nullptr))); 
		std::vector<CardController*> card_deck_to_shuffle;

		//while (!card_deck->empty())
		{
			//card_deck_to_shuffle.push_back(card_deck->pop());
		}

		//for (int i = card_deck->size() - 1; i > 0; i--)
		{
			//int j = rand() % (i + 1);
			//std::swap(card_deck_to_shuffle[i], card_deck_to_shuffle[j]);
		}

		//card_deck->clear();
		for (CardController* card : card_deck_to_shuffle)
		{
			//card_deck->push(card);
		}
	}
}
