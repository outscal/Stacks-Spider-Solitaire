#include "../../header/Gameplay/LevelController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Time/TimeService.h"

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
		CardService* card_service = ServiceLocator::getInstance()->getCardService();
		card_service->calculateCardExtends(level_view->getTotalCardSpacingWidth(), level_model->number_of_play_stacks);
		
		//init view and model
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


	void LevelController::processCardClick(CardController* card_to_process)
	{
		IStack<Card::CardController*>* card_deck = level_model->getDrawingStack();
		
		if (card_deck->contains(card_to_process))
		{
			for (int i = 0; i < LevelModel::number_of_play_stacks; i++)
			{
				if (card_deck->isEmpty()) return;
				CardController* card_controller = card_deck->pop();

				card_controller->setCardState(Card::State::OPEN);

			}
		}
	
	}

	float LevelController::getTotalCardSpacingWidth()
	{
		return (level_model->number_of_play_stacks + 1) * level_model->cards_horrizontal_spacing;
	}

	int LevelController::getNumberOfPlaystacks()
	{
		return level_model->number_of_play_stacks;
	}

	sf::Vector2f LevelController::calculatePlayCardPosition(int stack_index, int stack_size, int card_stack_position)
	{
		float card_width_offset = (stack_index * ServiceLocator::getInstance()->getCardService()->getCardWidth());
		float card_spacing_offset = ((stack_index + 1) * level_model->cards_horrizontal_spacing);
		float x_position = +card_width_offset + card_spacing_offset;

		float card_position_offset = ((stack_size - card_stack_position) * level_model->cards_vertical_spacing);
		float y_position = level_model->play_deck_top_offset + card_position_offset;

		return sf::Vector2f(x_position, y_position);
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