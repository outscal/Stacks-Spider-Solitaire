#include "../../header/Gameplay/LevelController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Global/TimeService.h"
#include "../../header/Card/CardConfig.h"

namespace Gameplay
{
	using namespace Card;
	using namespace ArrayStack;
	using namespace LinkedListStack;
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

	void LevelController::processButtonInput(CardController* selected_card_controller)
	{
		switch (selected_card_controller->getCardState())
		{
		case::Card::State::OPEN:
			processCardMove(selected_card_controller);
			break;
		case::Card::State::CLOSE:
			processCardDraw(selected_card_controller);
			break;
		case::Card::State::SELECTED:
			processCardSelection(selected_card_controller);
			break;
		}

		LinkedListStack::Stack<Card::CardController*>* stack = level_model->findPlayStack(selected_card_controller);
	}

	void LevelController::processCardSelection(Card::CardController* selected_card_controller)
	{
		unselectCards(selected_card_controller);
	}

	void LevelController::processCardDraw(CardController* selected_card_controller)
	{
		if (getDrawingStack()->search(selected_card_controller))
		{
			drawCards();
		}
	}

	void LevelController::processCardMove(Card::CardController* selected_card_controller)
	{
		if (previously_selected_card_controller == nullptr)
		{
			previously_selected_card_controller = selected_card_controller;
			selectCards(selected_card_controller);
		}
		else
		{
			//moveCards(selected_card_controller);
		}
	}

	void LevelController::drawCards()
	{
		ArrayStack::Stack<Card::CardController*>* card_deck = getDrawingStack();

		for (int i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			if (card_deck->empty()) return;
			CardController* card_controller = card_deck->pop();
			
			card_controller->setCardState(Card::State::OPEN);
			level_model->addCardInPlayStack(i, card_controller);
		}
	}

	void LevelController::selectCards(Card::CardController* card_controller)
	{
		LinkedListStack::Stack<Card::CardController*>* stack = level_model->findPlayStack(card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;

		card_controller->setCardState(Card::State::SELECTED);
		card_controller->setCardHighLight(true);

		while (!stack->empty() && stack->peek() != card_controller)
		{
			CardController* card_controller = stack->pop();
			card_controller->setCardState(Card::State::SELECTED);
			card_controller->setCardHighLight(true);
			temp_stack.push(card_controller);
		}

		while (!temp_stack.empty())
		{
			stack->push(temp_stack.pop());
		}
	}

	void LevelController::unselectCards(Card::CardController* card_controller)
	{
		LinkedListStack::Stack<Card::CardController*>* stack = level_model->findPlayStack(card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;

		while (!stack->empty() && stack->peek()->getCardState() == Card::State::SELECTED)
		{
			CardController* card_controller = stack->pop();
			card_controller->setCardState(Card::State::OPEN);
			card_controller->setCardHighLight(false);
			temp_stack.push(card_controller);
		}

		while (!temp_stack.empty())
		{
			stack->push(temp_stack.pop());
		}
	}

	void LevelController::moveCards(Card::CardController* card_controller)
	{
		LinkedListStack::Stack<Card::CardController*>* previously_selected_card_stack = level_model->findPlayStack(previously_selected_card_controller);
		LinkedListStack::Stack<Card::CardController*>* currently_selected_card_stack = level_model->findPlayStack(card_controller);

		while (currently_selected_card_stack->peek() != card_controller)
		{
			CardController* controller = currently_selected_card_stack->pop();
			controller->setCardState(Card::State::OPEN);
			previously_selected_card_stack->push(controller);
		}

		previously_selected_card_stack->push(currently_selected_card_stack->pop());
	}

	void LevelController::updateElapsedTime()
	{
		elapsed_time += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}

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
		previously_selected_card_controller = nullptr;
		level_model->reset();
	}
}