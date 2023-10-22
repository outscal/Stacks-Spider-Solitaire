#include "../../header/Gameplay/LevelController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Global/TimeService.h"

namespace Gameplay
{
	using namespace Card;
	using namespace ArrayStack;
	using namespace Global;

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
		updateElapsedTime();
		updatePlayStacks();
		updateSolutionStacks();
		updateDrawingStack();
		level_view->update();
	}

	void LevelController::render()
	{
		level_view->render();
	}

	void LevelController::startLevel()
	{
		reset();
	}

	void LevelController::updateElapsedTime()
	{
		elapsed_time += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
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

	float LevelController::getElapsedTime()
	{
		return elapsed_time;
	}

	int LevelController::getScore()
	{
		return score;
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

	void LevelController::reset()
	{
		elapsed_time = 0;
		score = 0;
		level_model->reset();
	}
}