#include "Gameplay/LevelModel.h"
#include "Card/CardService.h"
#include "Global/ServiceLocator.h"

namespace Gameplay
{
	using namespace ArrayStack;
	using namespace LinkedListStack;
	using namespace Card;
	using namespace Global;

	const float LevelModel::card_hide_duration_multiplyer = 0.1f;

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
			play_stacks.push_back(new LinkedListStack::Stack<CardController*>());
		}
	}

	void LevelModel::createSolutionStacks()
	{
		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			solution_stacks.push_back(new ArrayStack::Stack<CardController*>());
		}
	}

	void LevelModel::createDrawingStack()
	{
		drawing_stack = new ArrayStack::Stack<CardController*>();
	}

	void LevelModel::initialize() 
	{
		initializeStacks();
		openPlayStacksTopCard();
	}

	void LevelModel::reset()
	{
		deleteStackElements();
		initialize();
	}

	void LevelModel::initializeStacks()
	{
		ArrayStack::Stack<CardController*>* card_deck = ServiceLocator::getInstance()->getCardService()->generateRandomizedCardDeck(number_of_decks);

		while (card_deck->size() > drawing_deck_stack_size)
		{
			for (int i = 0; i < number_of_play_stacks; i++)
			{
				if (card_deck->size() < drawing_deck_stack_size) break;
				addCardInPlayStack(i, card_deck->pop());
			}
		}

		while (!card_deck->empty())
		{
			addCardInDrawingStack(card_deck->pop());
		}

		delete (card_deck);
	}

	void LevelModel::openPlayStacksTopCard()
	{
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			play_stacks[i]->peek()->setCardState(State::OPEN);
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

	std::vector<LinkedListStack::Stack<CardController*>*> Gameplay::LevelModel::getPlayStacks()
	{
		return play_stacks;
	}

	std::vector<ArrayStack::Stack<CardController*>*> Gameplay::LevelModel::getSolutionStacks()
	{
		return solution_stacks;
	}

	ArrayStack::Stack<CardController*>* Gameplay::LevelModel::getDrawingStack()
	{
		return drawing_stack;
	}

	LinkedListStack::Stack<Card::CardController*>* LevelModel::findPlayStack(Card::CardController* card_controller)
	{
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			if (play_stacks[i]->search(card_controller))
			{
				return play_stacks[i];
			}
		}

		return nullptr;
	}

	void LevelModel::deleteStackElements()
	{
		for (int i = 0; i < number_of_play_stacks; i++)
		{
			deleteLinkedListStackElements(play_stacks[i]);
		}

		for (int i = 0; i < number_of_solution_stacks; i++)
		{
			deleteArrayStackElements(solution_stacks[i]);
		}

		deleteArrayStackElements(drawing_stack);
	}

	void LevelModel::deleteLinkedListStackElements(LinkedListStack::Stack<Card::CardController*>* stack)
	{
		while (!stack->empty())
		{
			CardController* card_controller = stack->pop();
			delete card_controller;
		}
	}

	void LevelModel::deleteArrayStackElements(ArrayStack::Stack<Card::CardController*>* stack)
	{
		while (!stack->empty())
		{
			CardController* card_controller = stack->pop();
			delete card_controller;
		}
	}

	void LevelModel::destroy()
	{
		deleteStackElements();

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