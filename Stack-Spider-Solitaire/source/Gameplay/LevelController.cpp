#include "../../header/Gameplay/LevelController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Global/TimeService.h"
#include "../../header/Card/CardConfig.h"
#include "../../header/Stack/LinkedListStack/LinkedListStack.h"

namespace Gameplay
{
	using namespace LinkedListStack;
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
		updateStacks();
		processCardControllerInput();
	}

	void LevelController::render()
	{
		level_view->render();
	}

	void LevelController::startLevel()
	{
		reset();
	}

	void LevelController::processCardControllerInput()
	{
		if (flagged_card_to_process_input != nullptr)
		{
			processButtonInput(flagged_card_to_process_input);
			flagged_card_to_process_input = nullptr;
		}
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
	}

	void LevelController::processCardSelection(Card::CardController* selected_card_controller)
	{
		unselectCards(selected_card_controller);
	}

	void LevelController::processCardDraw(CardController* selected_card_controller)
	{
		if(previously_selected_card_controller) unselectCards(previously_selected_card_controller);

		if (getDrawingStack()->contains(selected_card_controller))
		{
			drawCards();
		}
	}

	void LevelController::processCardMove(Card::CardController* selected_card_controller)
	{
		if (previously_selected_card_controller == nullptr && isValidSelection(selected_card_controller))
		{
			previously_selected_card_controller = selected_card_controller;
			selectCards(selected_card_controller);
			return;
		}

		if (previously_selected_card_controller == nullptr) return;

		if (isValidMove(selected_card_controller)) moveCards(selected_card_controller);
		else unselectCards(previously_selected_card_controller);
	}

	void LevelController::drawCards()
	{
		IStack<Card::CardController*>* card_deck = getDrawingStack();

		for (int i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			if (card_deck->empty()) return;
			CardController* card_controller = card_deck->pop();
			
			card_controller->hideCard(static_cast<float>(i) * LevelModel::card_hide_duration_multiplyer);
			card_controller->setCardState(Card::State::OPEN);
			level_model->addCardInPlayStack(i, card_controller);
		}
	}

	void LevelController::selectCards(Card::CardController* card_controller)
	{
		IStack<Card::CardController*>* stack = level_model->findPlayStack(card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;
		card_controller->setCardState(Card::State::SELECTED);

		while (!stack->empty() && stack->peek() != card_controller)
		{
			CardController* card_controller = stack->pop();
			card_controller->setCardState(Card::State::SELECTED);
			temp_stack.push(card_controller);
		}

		while (!temp_stack.empty())
		{
			stack->push(temp_stack.pop());
		}
	}

	void LevelController::unselectCards(Card::CardController* card_controller)
	{
		IStack<Card::CardController*>* stack = level_model->findPlayStack(card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;

		while (!stack->empty() && stack->peek()->getCardState() == Card::State::SELECTED)
		{
			CardController* card_controller = stack->pop();
			card_controller->setCardState(Card::State::OPEN);
			temp_stack.push(card_controller);
		}

		while (!temp_stack.empty())
		{
			stack->push(temp_stack.pop());
		}

		previously_selected_card_controller = nullptr;
	}

	void LevelController::moveCards(Card::CardController* card_controller)
	{
		IStack<Card::CardController*>* previously_selected_card_stack = level_model->findPlayStack(previously_selected_card_controller);
		IStack<Card::CardController*>* currently_selected_card_stack = level_model->findPlayStack(card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;
		removeEmptyCard(currently_selected_card_stack);

		while (previously_selected_card_stack->peek() != previously_selected_card_controller)
		{
			CardController* controller = previously_selected_card_stack->pop();
			controller->setCardState(Card::State::OPEN);
			temp_stack.push(controller);
		}

		temp_stack.push(previously_selected_card_stack->pop());
		while (!temp_stack.empty()) currently_selected_card_stack->push(temp_stack.pop());
		
		openTopCardOfStack(previously_selected_card_stack);
		previously_selected_card_controller->setCardState(Card::State::OPEN);
		previously_selected_card_controller = nullptr;
		reduceScore(1);
	}

	void LevelController::openTopCardOfStack(IStack<Card::CardController*>* stack)
	{
		if (stack->empty())
		{
			addEmptyCard(stack);
		}

		stack->peek()->setCardState(Card::State::OPEN);
	}

	bool LevelController::isValidSelection(Card::CardController* selected_card_controller)
	{
		IStack<Card::CardController*>* currently_selected_card_stack = level_model->findPlayStack(selected_card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;

		Card::Suit card_suit = selected_card_controller->getCardType()->suit;
		int previous_card_rank = static_cast<int>(currently_selected_card_stack->peek()->getCardType()->rank) - 1;
		bool is_valid_selection = true;

		while (currently_selected_card_stack->peek() != selected_card_controller)
		{
			CardController* card_controller = currently_selected_card_stack->pop();
			temp_stack.push(card_controller);

			if (static_cast<int>(card_controller->getCardType()->rank) != ++previous_card_rank
				|| card_controller->getCardType()->suit != card_suit)
			{
				is_valid_selection = false;
				break;
			}
		}

		while (!temp_stack.empty())
		{
			currently_selected_card_stack->push(temp_stack.pop());
		}

		return is_valid_selection;
	}

	bool LevelController::isValidMove(Card::CardController* selected_card_controller)
	{
		IStack<Card::CardController*>* previously_selected_card_stack = level_model->findPlayStack(previously_selected_card_controller);
		IStack<Card::CardController*>* currently_selected_card_stack = level_model->findPlayStack(selected_card_controller);

		if (currently_selected_card_stack->peek() != selected_card_controller) return false;

		Card::Rank previous_card_rank = previously_selected_card_controller->getCardType()->rank;
		Card::Rank current_card_rank = selected_card_controller->getCardType()->rank;

		return (static_cast<int>(previous_card_rank) + 1 == static_cast<int>(current_card_rank));
	}

	void LevelController::updateElapsedTime()
	{
		elapsed_time += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}

	void LevelController::updateStacks()
	{
		updatePlayStacks();
		updateSolutionStacks();
		updateDrawingStack();
	}

	void LevelController::updatePlayStacks()
	{
		for (float i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			updateStackCards(getPlayStacks()[i]);
		}
	}

	void LevelController::updateSolutionStacks()
	{
		for (float i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			updateStackCards(getSolutionStacks()[i]);
		}
	}

	void LevelController::updateDrawingStack()
	{
		updateStackCards(getDrawingStack());
	}

	void LevelController::updateStackCards(IStack<Card::CardController*>* stack)
	{
		LinkedListStack::Stack<CardController*> temp_stack;

		while (!stack->empty())
		{
			CardController* card_controller = stack->pop();
			card_controller->update();
			temp_stack.push(card_controller);
		}

		while (!temp_stack.empty())
		{
			stack->push(temp_stack.pop());
		}
	}

	void LevelController::setCardToProcessInput(Card::CardController* selected_card_controller)
	{
		flagged_card_to_process_input = selected_card_controller;
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

	void LevelController::addEmptyCard(IStack<Card::CardController*>* stack)
	{
		CardController* empty_card = ServiceLocator::getInstance()->getCardService()->generateCard(Card::Rank::DEFAULT, Card::Suit::DEFAULT);
		stack->push(empty_card);
	}

	void LevelController::removeEmptyCard(IStack<Card::CardController*>* stack)
	{
		if (stack->peek()->getCardType()->rank == Card::Rank::DEFAULT)
		{
			CardController* card_controller = stack->pop();
			delete (card_controller);
		}
	}

	void LevelController::reduceScore(int val)
	{
		score -= val;
	}

	void LevelController::increaseScore(int val)
	{
		score += val;
	}

	void LevelController::reset()
	{
		elapsed_time = 0;
		score = LevelModel::initial_score;
		previously_selected_card_controller = nullptr;
		flagged_card_to_process_input = nullptr;
		level_model->reset();
	}
}