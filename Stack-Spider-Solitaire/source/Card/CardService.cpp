#include "Card/CardService.h"
#include "Card/CardConfig.h"
#include "Card/CardController.h"
#include "Gameplay/GameplayService.h"
#include "Global/ServiceLocator.h"
#include <ctime>
#include <random>

namespace Card
{
	using namespace ArrayStack;
	using namespace Global;

	CardService::CardService() = default;

	CardService::~CardService() = default;

	void CardService::initialize()
	{
	}

	void CardService::update()
	{
	}

	void CardService::render()
	{
	}

	CardController* CardService::generateCard(CardTypeEnum card_type, Rank rank, Suit suit)
	{
		float card_width =
			ServiceLocator::getInstance()->getGameplayService()->getCardWidth();
		float card_height =
			ServiceLocator::getInstance()->getGameplayService()->getCardHeight();

		CardController* card = new CardController(card_type, rank, suit);
		card->initialize(card_width, card_height);
		return card;
	}

	Stack<CardController*>*
	CardService::generateSequentialCardDeck(int number_of_decks)
	{
		Stack<CardController*>* card_deck = new Stack<CardController*>();

		for (int i = 0; i < number_of_decks; i++)
		{
			for (int rank = 1; rank <= static_cast<int>(number_of_ranks); rank++)
			{
				for (int suit = 0; suit < static_cast<int>(number_of_suits);
					 suit++)
				{
					CardController* card = generateCard(
						CardTypeEnum::DEFAULT,
						static_cast<Rank>(rank),
						static_cast<Suit>(suit));
					card_deck->push(card);
				}
			}
		}

		return card_deck;
	}

	Stack<CardController*>*
	CardService::generateRandomizedCardDeck(int number_of_decks)
	{
		Stack<CardController*>* card_deck =
			generateSequentialCardDeck(number_of_decks);

		shuffleDeck(card_deck);
		return card_deck;
	}

	void CardService::shuffleDeck(Stack<CardController*>* card_deck)
	{
		std::vector<CardController*> card_deck_to_shuffle;

		while (!card_deck->empty())
		{
			card_deck_to_shuffle.push_back(card_deck->pop());
		}

		std::random_device device;
		std::mt19937 random_engine(device());
		std::shuffle(card_deck_to_shuffle.begin(), card_deck_to_shuffle.end(),
					 random_engine);

		card_deck->clear();
		for (CardController* card : card_deck_to_shuffle)
		{
			card_deck->push(card);
		}
	}
} // namespace Card