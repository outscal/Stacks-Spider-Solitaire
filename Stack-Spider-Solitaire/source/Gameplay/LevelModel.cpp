#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Card/CardService.h"
#include "../../header/Global/ServiceLocator.h"

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
			play_stacks.push_back(new Stack<CardController*>());
		}
	}

	void LevelModel::createSolutionStacks()
	{
		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			solution_stacks.push_back(new Stack<CardController*>());
		}
	}

	void LevelModel::createDrawingStack()
	{
		drawing_stack = new Stack<CardController*>();
	}

	void LevelModel::initialize() 
	{
		initializeStacks();
	}

	void LevelModel::initializeStacks()
	{
		Stack<CardController*>* card_deck = ServiceLocator::getInstance()->getCardService()->generateSequentialCardDeck();

		for (int i = 0; i < number_of_play_stacks; i++)
		{
			addCardInPlayStack(i, card_deck->pop());
		}

		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			addCardInSolutionStack(i, card_deck->pop());
		}

		while (!card_deck->empty())
		{
			addCardInDrawingStack(card_deck->pop());
		}

		delete (card_deck);
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

	std::vector<Stack<CardController*>*> Gameplay::LevelModel::getPlayStacks()
	{
		return play_stacks;
	}

	std::vector<Stack<CardController*>*> Gameplay::LevelModel::getSolutionStacks()
	{
		return solution_stacks;
	}

	ArrayStack::Stack<CardController*>* Gameplay::LevelModel::getDrawingStack()
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