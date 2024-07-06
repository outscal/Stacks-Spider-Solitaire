#pragma once
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Card/CardService.h"
#include "../../header/Card/CardController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Stack/ArrayStack/ArrayStack.h"
#include "../../header/Stack/LinkedListStack/LinkedListStack.h"
#include "../../header/Stack/IStack.h"

namespace Gameplay
{
	using namespace ArrayStack;
	using namespace LinkedListStack;
	using namespace Card;
	using namespace Global;

	const float LevelModel::card_hide_duration_multiplyer = 0.15f;

	LevelModel::LevelModel()
	{
		createPlayStacks();
		createSolutionStacks();
		createDrawingStack();
	}

	LevelModel::~LevelModel()
	{
		destroy();
	}

	void LevelModel::createPlayStacks()
	{
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			IStack<CardController*>* stack = new LinkedListStack::Stack<CardController*>();
			play_stacks.push_back(stack);
		}
	}

	void LevelModel::createSolutionStacks()
	{
		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			IStack<CardController*>* stack = new ArrayStack::Stack<CardController*>();
			solution_stacks.push_back(stack);
		}
	}

	void LevelModel::createDrawingStack()
	{
		drawing_stack = new ArrayStack::Stack<CardController*>();
	}

	void LevelModel::initialize() 
	{
		populateCardPiles();
		openTopPlayStackCards();
	}

	void LevelModel::reset()
	{
		deleteAllStackElemets();
		initialize();
	}

	void LevelModel::populateCardPiles()
	{
		IStack<CardController*>* card_deck = ServiceLocator::getInstance()->getCardService()->generateRandomizedCardDeck(number_of_decks);

		while (card_deck->getSize() > drawing_deck_stack_size)
		{
			for (int i = 0; i < number_of_play_stacks; i++)
			{			

				if (card_deck->getSize() <= drawing_deck_stack_size) break;
				addCardInPlayStack(i, card_deck->pop());
			}
		}

		while (!card_deck->isEmpty())
		{
			addCardInDrawingStack(card_deck->pop());
		}

		delete (card_deck);
	}

	void LevelModel::addCardInPlayStack(int stack_index, CardController* card_controller)
	{
		if (stack_index >= 0 && stack_index < number_of_play_stacks)
		{
			removeEmptyCard(play_stacks[stack_index]);
			play_stacks[stack_index]->push(card_controller);
		}
	}

	void LevelModel::addCardInSolutionStack(int stack_index, CardController* card_controller)
	{
		if (stack_index >= 0 && stack_index < number_of_solution_stacks)
		{
			solution_stacks[stack_index]->push(card_controller);
		}
	}

	void LevelModel::addCardInDrawingStack(CardController* card_controller)
	{
		drawing_stack->push(card_controller);
	}

	std::vector<IStack<CardController*>*> Gameplay::LevelModel::getPlayStacks()
	{
		return play_stacks;
	}

	std::vector<IStack<CardController*>*> Gameplay::LevelModel::getSolutionStacks()
	{
		return solution_stacks;
	}

	IStack<CardController*>* Gameplay::LevelModel::getDrawingStack()
	{
		return drawing_stack;
	}

	IStack<Card::CardController*>* LevelModel::getEmptySolutionStack()
	{
		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			if (solution_stacks[i]->getSize() == 0) return solution_stacks[i];
		}

		return nullptr;
	}

	IStack<Card::CardController*>* LevelModel::findPlayStack(Card::CardController* card_controller)
	{
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			if (play_stacks[i]->contains(card_controller))
			{
				return play_stacks[i];
			}
		}

		return nullptr;
	}

	void LevelModel::addEmptyCard(IStack<Card::CardController*>* stack)
	{
		CardController* empty_card = ServiceLocator::getInstance()->getCardService()->generateCard(Card::Rank::DEFAULT, Card::Suit::DEFAULT);
		stack->push(empty_card);
	}

	void LevelModel::removeEmptyCard(IStack<Card::CardController*>* stack)
	{
		if (stack->isEmpty()) return;

		if (stack->peek()->getCardData()->rank == Card::Rank::DEFAULT)
		{
			CardController* card_controller = stack->pop();
			delete (card_controller);
		}
	}

	void LevelModel::deleteAllStackElemets()
	{
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			deleteStackElements(play_stacks[i]);
		}

		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			deleteStackElements(solution_stacks[i]);
		}

		deleteStackElements(drawing_stack);
	}

	void LevelModel::deleteStackElements(IStack<Card::CardController*>* stack)
	{
		while (!stack->isEmpty())
		{
			CardController* card_controller = stack->pop();
			delete card_controller;
		}
	}	
	void LevelModel::openTopPlayStackCards()
	{
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			play_stacks[i]->peek()->setCardState(State::OPEN);

		}
	}

	void LevelModel::destroy()
	{
		deleteAllStackElemets();

		for (int i = 0; i < number_of_play_stacks; i++)
		{
			delete (play_stacks[i]);
		}

		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			delete (solution_stacks[i]);
		}

		delete (drawing_stack);
	}
}