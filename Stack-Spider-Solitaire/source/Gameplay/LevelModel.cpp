#pragma once
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Card/CardService.h"
#include "../../header/Card/CardController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Stack/ArrayStack/ArrayStack.h"
#include "../../header/Stack/IStack.h"

namespace Gameplay
{
	using namespace ArrayStack;
	using namespace Card;
	using namespace Global;

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
			IStack<CardController*>* stack = new ArrayStack::Stack<CardController*>();
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

	void LevelModel::initialize() { }

	void LevelModel::populateCardPiles(IStack<CardController*>* temp_card_deck)
	{
		// Adding one card in play stacks for visualization purpose. 
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			addCardInPlayStack(i, temp_card_deck->pop());
		}

		while (!temp_card_deck->isEmpty())
		{
			addCardInDrawingStack(temp_card_deck->pop());
		}

		delete (temp_card_deck);
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

	void LevelModel::drawCard()
	{
		drawing_stack->pop();
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

	void LevelModel::destroy()
	{
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