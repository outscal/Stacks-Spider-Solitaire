#include "../../header/Gameplay/LevelController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Global/TimeService.h"

namespace Gameplay
{
	using namespace Card;
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

	void LevelController::populateCardPiles(IStack<CardController*>* temp_card_deck)
	{
		level_model->populateCardPiles(temp_card_deck);
	}

	void LevelController::processCard(CardController* card_to_process)
	{
		IStack<CardController*>* drawingDeck = level_model->getDrawingStack();
		
		if (drawingDeck->peek() == card_to_process)
			drawingDeck->pop();
	}

	float LevelController::getTotalCardSpacingWidth()
	{
		return level_view->getTotalCardSpacingWidth();
	}

	int LevelController::getNumberOfPlaystacks()
	{
		return level_model->number_of_play_stacks;
	}

	float LevelController::getElapsedTime()
	{
		return elapsed_time;
	}

	int LevelController::getScore()
	{
		return score;
	}
	
	std::vector<IStack<CardController*>*> LevelController::getPlayStacks()
	{
		return level_model->getPlayStacks();
	}

	std::vector<IStack<CardController*>*> LevelController::getSolutionStacks()
	{
		return level_model->getSolutionStacks();
	}

	IStack<CardController*>* LevelController::getDrawingStack()
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