#include "../../header/Gameplay/LevelController.h"

namespace Gameplay
{
	using namespace Card;
	using namespace ArrayStack;

	LevelController::LevelController()
	{
		level_model = new LevelModel();
		level_view = new LevelView();
	}

	LevelController::~LevelController()
	{
		delete level_model;
		delete level_view;
	}

	void LevelController::initialize()
	{
		level_view->initialize(this);
		level_model->initialize();
	}

	void LevelController::update()
	{
		updatePlayStacks();
		updateSolutionStacks();
		updateDrawingStack();
		level_view->update();
	}

	void LevelController::render()
	{
		level_view->render();
	}

	void LevelController::updatePlayStacks() { }

	void LevelController::updateSolutionStacks() { }

	void LevelController::updateDrawingStack() { }

	float LevelController::getCardWidth()
	{
		return level_view->getCardWidth();
	}

	float LevelController::getCardHeight()
	{
		return level_view->getCardHeight();
	}

	std::vector<LinkedListStack::Stack<CardController*>*> LevelController::getPlayStacks()
	{
		return level_model->getPlayStacks();
	}

	std::vector<ArrayStack::Stack<CardController*>*> LevelController::getSolutionStacks()
	{
		return level_model->getSolutionStacks();
	}

	ArrayStack::Stack<CardController*>* LevelController::getDrawingStack()
	{
		return level_model->getDrawingStack();
	}
}