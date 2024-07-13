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

	LevelModel::LevelModel()
	{
		createPlayStacks();
		createSolutionStacks();
		createDrawingStack();
		createDrawStackButtons();
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

	void LevelModel::createDrawStackButtons()
	{
		draw_stack_buttons = new ArrayStack::Stack<CardController*>();
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
		ServiceLocator* locator = ServiceLocator::getInstance();
		IStack<CardController*>* card_deck = locator->getCardService()->generateRandomizedCardDeck(number_of_decks);

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

		for (int i = 0; i < 5; i++)
		{
			addDrawStackButtons(locator->getCardService()->generateCard(Card::Rank::ACE, Card::Suit::HEARTS));

		}
	}

	void LevelModel::addCardInPlayStack(int stack_index, CardController* card_controller)
	{
		if (stack_index >= 0 && stack_index < number_of_play_stacks)
		{
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

	void LevelModel::addDrawStackButtons(Card::CardController* card_controller)
	{
		draw_stack_buttons->push(card_controller);
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

	IStack<Card::CardController*>* LevelModel::getDrawStackButtons()
	{
		return draw_stack_buttons;
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
		deleteStackElements(draw_stack_buttons);
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
		delete (draw_stack_buttons);
	}
}