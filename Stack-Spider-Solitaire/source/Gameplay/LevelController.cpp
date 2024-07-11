#include "../../header/Gameplay/LevelController.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Time/TimeService.h"
#include "../../header/Card/CardConfig.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Main/GameService.h"
#include "../../header/Stack/LinkedListStack/LinkedListStack.h"

namespace Gameplay
{
	using namespace Main;
	using namespace LinkedListStack;
	using namespace Card;
	using namespace Global;
	using namespace Sound;

	

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
		level_view->setCardDimensions(card_service->getCardHeight(), card_service->getCardWidth());
		score = LevelModel::initial_score;
		
		//init view and model
		level_view->initialize(this);
		level_model->initialize();
	}

	void LevelController::update()
	{
		updateElapsedTime();
		updateDelayTime();
		level_view->update();
		updateStacks();
		processCardControllerInput();

		if (ServiceLocator::getInstance()->getEventService()->isCtrlZPressed())
		{
			undo();
		}
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
		switch (selected_card_controller->getCardData()->state)
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
		if (previously_selected_card_controller) unselectCards(previously_selected_card_controller);
		
		if (getDrawStackButtons()->contains(selected_card_controller))
		{
			canDrawCard = true;
			
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

		if (isValidMove(selected_card_controller))
		{
			moveCards(selected_card_controller);
			if (isGameOver()) processGameOver();
		}
		else unselectCards(previously_selected_card_controller);
	}

	void LevelController::processSuitCompletion(IStack<Card::CardController*>* stack)
	{
		IStack<Card::CardController*>* solution_stack = level_model->getEmptySolutionStack();

		if (solution_stack)
		{
			for (int i = 1; i < static_cast<int>(Card::Rank::DEFAULT); i++) solution_stack->push(stack->pop());
		}

		openTopCardOfStack(stack);
		clearMoveHistory();
		increaseScore(LevelModel::suit_complete_score);

		if (isLevelComplete()) processGameOver();
	}

	void LevelController::drawCards()
	{

		if (cards_popped < LevelModel::number_of_play_stacks)
		{
			IStack<Card::CardController*>* card_deck = getDrawingStack();
			
			if (card_deck->isEmpty()) return;

			CardController* card_controller = card_deck->pop();
			level_model->addCardInPlayStack(cards_popped, card_controller);

			if (isSuitComplete(level_model->getPlayStacks()[cards_popped])) processSuitCompletion(level_model->getPlayStacks()[cards_popped]);
			card_controller->setCardState(Card::State::OPEN);

			cards_popped++;
			delay_time = 0;
		}
		else {
			canDrawCard = false;
			cards_popped = 0;
			clearMoveHistory();
		}
	}


	void LevelController::selectCards(Card::CardController* card_controller)
	{
		IStack<Card::CardController*>* stack = level_model->findPlayStack(card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;
		card_controller->setCardState(Card::State::SELECTED);

		while (!stack->isEmpty() && stack->peek() != card_controller)
		{
			CardController* card_controller = stack->pop();
			card_controller->setCardState(Card::State::SELECTED);
			temp_stack.push(card_controller);
		}

		while (!temp_stack.isEmpty())
		{
			stack->push(temp_stack.pop());
		}

	}

	void LevelController::unselectCards(Card::CardController* card_controller)
	{
		IStack<Card::CardController*>* stack = level_model->findPlayStack(card_controller);
		LinkedListStack::Stack<Card::CardController*> temp_stack;

		while (!stack->isEmpty() && stack->peek()->getCardData()->state == Card::State::SELECTED)
		{
			CardController* card_controller = stack->pop();
			card_controller->setCardState(Card::State::OPEN);
			temp_stack.push(card_controller);
		}

		while (!temp_stack.isEmpty())
		{
			stack->push(temp_stack.pop());
		}

		previously_selected_card_controller = nullptr;
	}

	void LevelController::moveCards(Card::CardController* card_controller)
	{
		IStack<Card::CardController*>* previously_selected_card_stack = level_model->findPlayStack(previously_selected_card_controller);
		IStack<Card::CardController*>* currently_selected_card_stack = level_model->findPlayStack(card_controller);

		if (!previously_selected_card_stack || !currently_selected_card_stack) return;

		level_model->removeEmptyCard(currently_selected_card_stack);
		
		Card::CardController* openedCard = nullptr;
		std::vector<Card::CardController*> movedCards = moveCardsBetweenStacks(previously_selected_card_stack, currently_selected_card_stack, openedCard);
		bool wasTopCardOpen = openedCard && openedCard->getCardData()->state == Card::State::CLOSE;


		// Create a new CardMovement object and push its pointer onto the stack
		CardMovement* move = new CardMovement(previously_selected_card_stack, currently_selected_card_stack, movedCards, wasTopCardOpen, openedCard);
		level_model->moveHistory->push(move);

		openTopCardOfStack(previously_selected_card_stack);

		previously_selected_card_controller->setCardState(Card::State::OPEN);
		previously_selected_card_controller = nullptr;

		if (isSuitComplete(currently_selected_card_stack)) processSuitCompletion(currently_selected_card_stack);
		reduceScore(1);
	}

	std::vector<Card::CardController*> LevelController::moveCardsBetweenStacks(IStack<Card::CardController*>* source_stack, IStack<Card::CardController*>* target_stack, Card::CardController*& openedCard)
	{
		LinkedListStack::Stack<Card::CardController*> temp_stack;
		std::vector<Card::CardController*> movedCards;
		openedCard = nullptr;

		while (source_stack->peek() != previously_selected_card_controller)
		{
			Card::CardController* controller = source_stack->pop();
			controller->setCardState(Card::State::OPEN);
			temp_stack.push(controller);
			movedCards.push_back(controller);
		}

		Card::CardController* selectedController = source_stack->pop();
		temp_stack.push(selectedController);
		movedCards.push_back(selectedController);

		while (!temp_stack.isEmpty()) {
			target_stack->push(temp_stack.pop());
		}

		// If there are still cards left in the source stack, the top card needs to be checked for state
		if (!source_stack->isEmpty()) {
			openedCard = source_stack->peek();
		}

		return movedCards;
	}

	void LevelController::openTopCardOfStack(IStack<Card::CardController*>* stack)
	{
		if (stack->isEmpty())
		{
			level_model->addEmptyCard(stack);

		}

		stack->peek()->setCardState(Card::State::OPEN);
	}

	bool LevelController::isValidSelection(Card::CardController* selected_card_controller)
	{

		if (selected_card_controller->getCardData()->rank == Card::Rank::DEFAULT) return false;

		IStack<Card::CardController*>* currently_selected_card_stack = level_model->findPlayStack(selected_card_controller);
		return (currently_selected_card_stack != nullptr) && isSequential(currently_selected_card_stack, selected_card_controller);
	}

	bool LevelController::isValidMove(Card::CardController* selected_card_controller)
	{
		IStack<Card::CardController*>* previously_selected_card_stack = level_model->findPlayStack(previously_selected_card_controller);
		IStack<Card::CardController*>* currently_selected_card_stack = level_model->findPlayStack(selected_card_controller);

		if (!previously_selected_card_stack || !currently_selected_card_stack) return false;
		if (currently_selected_card_stack->peek() != selected_card_controller) return false;

		Card::Rank previous_card_rank = previously_selected_card_controller->getCardData()->rank;
		Card::Rank current_card_rank = selected_card_controller->getCardData()->rank;

		if (current_card_rank == Card::Rank::DEFAULT) {
			return true;
		}

		return (static_cast<int>(previous_card_rank) + 1 == static_cast<int>(current_card_rank));
	}

	bool LevelController::isSequential(IStack<Card::CardController*>* stack, Card::CardController* last_card_to_check)
	{
		LinkedListStack::Stack<Card::CardController*> temp_stack;

		Card::Suit card_suit = last_card_to_check->getCardData()->suit;
		int previous_card_rank = static_cast<int>(stack->peek()->getCardData()->rank) - 1;
		bool is_sequential = true;

		while (!stack->isEmpty())

		{
			Card::CardController* card_controller = stack->pop();
			temp_stack.push(card_controller);

			if (static_cast<int>(card_controller->getCardData()->rank) != ++previous_card_rank ||
				card_controller->getCardData()->suit != card_suit)
			{
				is_sequential = false;
			}

			if (card_controller == last_card_to_check) break;
		}

		while (!temp_stack.isEmpty()) stack->push(temp_stack.pop());
		return is_sequential;
	}

	bool LevelController::isSuitComplete(IStack<Card::CardController*>* stack)
	{
		if (stack->getSize() + 1 < static_cast<int>(Card::Rank::DEFAULT)) return false;
		LinkedListStack::Stack<Card::CardController*> temp_stack;

		for (int i = 1; i < static_cast<int>(Card::Rank::DEFAULT); i++)
		{
			temp_stack.push(stack->pop());
		}

		CardController* last_card_to_check = temp_stack.peek();
		while (!temp_stack.isEmpty()) stack->push(temp_stack.pop());

		return isSequential(stack, last_card_to_check);
	}

	bool LevelController::isLevelComplete()
	{
		return (level_model->getEmptySolutionStack() == nullptr);
	}

	bool LevelController::isGameOver()
	{
		return score <= 0;
	}


	void LevelController::updateElapsedTime()
	{
		elapsed_time += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
	}

	void LevelController::updateDelayTime()
	{
		delay_time += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (canDrawCard)
		{
			if (delay_time > level_model->card_hide_duration)
			{

				drawCards();
				
			}			

		}
		
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
		updateStackCards(getDrawStackButtons());
	}

	void LevelController::updateStackCards(IStack<Card::CardController*>* stack)
	{
		LinkedListStack::Stack<CardController*> temp_stack;

		while (!stack->isEmpty())
		{
			CardController* card_controller = stack->pop();
			card_controller->update();
			temp_stack.push(card_controller);
		}

		while (!temp_stack.isEmpty())
		{
			stack->push(temp_stack.pop());
		}
	}

	void LevelController::setCardToProcessInput(Card::CardController* selected_card_controller)
	{

			flagged_card_to_process_input = selected_card_controller;
	
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

		float card_position_offset = ((stack_size - card_stack_position) * level_model->open_cards_vertical_spacing);
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

	IStack<Card::CardController*>* LevelController::getDrawStackButtons()
	{
		return level_model->getDrawStackButtons();
	}

	void LevelController::addEmptyCard(IStack<Card::CardController*>* stack)
	{
		if (stack->isEmpty())
		{
			CardController* empty_card = ServiceLocator::getInstance()->getCardService()->generateCard(Card::Rank::DEFAULT, Card::Suit::DEFAULT);
			empty_card->setCardState(State::OPEN);
			empty_card->setCardVisibility(CardVisibility::VISIBLE);
			stack->push(empty_card);
		}
		
	}

	void LevelController::removeEmptyCard(IStack<Card::CardController*>* stack)
	{
		if (stack->isEmpty()) return;

		if (stack->peek()->getCardData()->rank == Card::Rank::DEFAULT)
		{
			CardController* card_controller = stack->pop();
			delete (card_controller);
		}
	}

	void LevelController::undo()
	{
		if (level_model->moveHistory->isEmpty()) return;

		if (previously_selected_card_controller) unselectCards(previously_selected_card_controller);
		// Get the last move and remove it from the stack
		CardMovement* lastMove = level_model->moveHistory->peek();
		level_model->moveHistory->pop();

		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);

		removeEmptyCard(lastMove->sourceStack);

		// Move cards back to the original stack
		for (auto it = lastMove->movedCards.rbegin(); it != lastMove->movedCards.rend(); ++it) {
			lastMove->targetStack->pop();
			lastMove->sourceStack->push(*it);
		}

		removeEmptyCard(lastMove->targetStack);
		addEmptyCard(lastMove->targetStack);

		// Close the card that was opened
		if (lastMove->openedCard && lastMove->wasTopCardOpen && (lastMove->openedCard->getCardData()->rank != Card::Rank::DEFAULT)) {

				lastMove->openedCard->setCardState(Card::State::CLOSE);
			
		}

		

		

		// Delete the dynamically allocated CardMovement object
		delete lastMove;
	}

	void LevelController::reduceScore(int val)
	{
		score -= val;
	}

	void LevelController::increaseScore(int val)
	{
		score += val;
	}

	void LevelController::processGameOver()
	{
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::LEVEL_COMPLETE);
		GameService::setGameState(GameState::CREDITS);
	}

	void LevelController::clearMoveHistory()
	{
		while (!level_model->moveHistory->isEmpty()) {
			CardMovement* move = level_model->moveHistory->peek();
			level_model->moveHistory->pop();
			delete move;
		}
	}

	void LevelController::reset()
	{
		elapsed_time = 0;
		delay_time = 0;
		score = LevelModel::initial_score;
		previously_selected_card_controller = nullptr;
		flagged_card_to_process_input = nullptr;
		clearMoveHistory();
		level_model->reset();
	}
}