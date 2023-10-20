#include "../../header/Gameplay/LevelModel.h"

namespace Gameplay
{
	using namespace ArrayStack;
	using namespace Card;

	LevelModel::LevelModel() = default;

	LevelModel::~LevelModel() = default;

	void LevelModel::initialize() { }

	void LevelModel::addPlayStack(ArrayStack::Stack<Card::CardController*>* stack)
	{
		play_stacks.push_back(stack);
	}

	void LevelModel::addSolutionStack(ArrayStack::Stack<Card::CardController*>* stack)
	{
		solution_stacks.push_back(stack);
	}

	void LevelModel::setDrawingStack(ArrayStack::Stack<Card::CardController*>* stack)
	{
		drawing_stack = stack;
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
}