#pragma once
#include "../../header/Card/CardService.h"
#include "../../header/Card/CardController.h"
#include "../../header/Card/CardConfig.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Stack/ArrayStack/ArrayStack.h"
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
		gameplay_service = ServiceLocator::getInstance()->getGameplayService();
		calculateCardExtends();
	}

	void CardService::update() { }

	void CardService::render() { }

	float CardService::getCardWidth() { return card_width; }

	float CardService::getCardHeight() { return card_height; }

	void CardService::calculateCardExtends()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
		float total_width = game_window->getSize().x;

		float total_spacing_width = gameplay_service->getTotalCardSpacingWidth();

		card_width = calculateCardWidth(total_width-total_spacing_width);
		card_height = calculateCardHeight(card_width);
	}

	float CardService::calculateCardWidth(float width_space_for_cards) 
	{
		int number_of_playstacks = gameplay_service->getNumberOfPlaystacks();
		return width_space_for_cards / number_of_playstacks;
	}

	float CardService::calculateCardHeight(float card_width)
	{
		return card_width * card_height_to_width_ratio;
	}

	CardController* CardService::generateCard(Rank rank, Suit suit)
	{
		return new CardController(rank, suit);
	}

	IStack<CardController*>* CardService::generateSequentialCardDeck(int number_of_decks)
	{
		IStack<CardController*>* card_deck = new ArrayStack::Stack<CardController*>();

		for (int i = 0; i < number_of_decks; i++)
		{
			for (int suit = 0; suit < static_cast<int>(number_of_suits); suit++)
			{
				for (int rank = 0; rank < static_cast<int>(number_of_ranks); rank++)
				{
					CardController* card = generateCard(static_cast<Rank>(rank), static_cast<Suit>(suit));

					card->initialize(card_width, card_height);
					card_deck->push(card);
				}
			}
		}

		return card_deck;
	}

	IStack<CardController*>* CardService::generateRandomizedCardDeck(int number_of_decks)
	{
		IStack<CardController*>* card_deck = generateSequentialCardDeck(number_of_decks);

		shuffleDeck(card_deck);
		return card_deck;
	}

	void CardService::shuffleDeck(IStack<CardController*>* card_deck)
	{
		std::vector<CardController*> card_deck_to_shuffle;

		while (!card_deck->isEmpty())
		{
			card_deck_to_shuffle.push_back(card_deck->pop());
		}

		std::random_device device;
		std::mt19937 random_engine(device());
		std::shuffle(card_deck_to_shuffle.begin(), card_deck_to_shuffle.end(), random_engine);

		card_deck->clear();
		for (CardController* card : card_deck_to_shuffle)
		{
			card_deck->push(card);
		}
	}
}