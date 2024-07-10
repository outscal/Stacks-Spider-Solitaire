#include "../../header/Gameplay/LevelView.h"
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Gameplay/LevelController.h"
#include "../../header/Card/CardController.h"
#include "../../header/Stack/ArrayStack/ArrayStack.h"
#include <vector>
#include <iostream>

namespace Gameplay
{
	using namespace ArrayStack;
	using namespace UI::UIElement;
	using namespace Global;
	using namespace Card;

	LevelView::LevelView()
	{
		createImage();
	}

	LevelView::~LevelView()
	{
		destroy();
	}

	void LevelView::initialize(LevelController* controller)
	{
		level_controller = controller;
		initializeBackgroudImage();
		
	}

	void LevelView::createImage()
	{
		background_image = new ImageView();
	}

	void LevelView::initializeBackgroudImage()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		background_image->initialize(Config::level_background_texture_path, 
									game_window->getSize().x, 
									game_window->getSize().y, 
									sf::Vector2f(0,0));

		background_image->setImageAlpha(background_alpha);
	}

	void LevelView::update()
	{
		background_image->update();
		updatePlayStacksView();
		updateSolutionStacksView();
		updateDrawingStackView();
	}

	void LevelView::render()
	{
		background_image->render();
		renderPlayStacks();
		renderSolutionStacks();
		renderDrawnigStack();
	}

	void LevelView::updatePlayStacksView() 
	{ 
		float card_width = ServiceLocator::getInstance()->getCardService()->getCardWidth();

		for (float i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			updatePlayStackCardsView(*(level_controller->getPlayStacks()[i]), i);
		}
	}

	void LevelView::updatePlayStackCardsView(IStack<CardController*>& stack, int stack_position)
	{
		ArrayStack::Stack<CardController*> temp_stack;
		float stack_size = stack.getSize();
		float card_stack_position = 0;
		float vertical_spacing = 0;
		int number_of_open_cards = 0;

		while (!stack.isEmpty())
		{

			if (stack.peek()->getCardData()->state == Card::State::OPEN ||
				stack.peek()->getCardData()->state == Card::State::SELECTED) number_of_open_cards++;

			temp_stack.push(stack.pop());
		}

		while (!temp_stack.isEmpty())
		{
			float x_position = (stack_position * card_width) + ((stack_position + 1) * LevelModel::cards_horrizontal_spacing);
			float y_position = LevelModel::play_deck_top_offset + vertical_spacing;

			CardController* card_controller = temp_stack.pop();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));

			stack.push(card_controller);
			card_stack_position++;
			vertical_spacing += getCardVerticalSpacing(card_controller->getCardData()->state, number_of_open_cards);
		}
		
	}

	void LevelView::updateSolutionStacksView() 
	{
		for (float i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->isEmpty()) continue;

			float x_position = LevelModel::solution_deck_left_offset + (i * LevelModel::solution_deck_spacing);
			float y_position = LevelModel::solution_deck_top_offset;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
		}
	}

	void LevelView::updateDrawingStackView() 
	{ 
		ArrayStack::Stack<CardController*> temp_stack;
		int number_of_draws = getNumberOfDrawsRemaining();

		for (int i = 0; i < number_of_draws; i++)
		{
			CardController* card_controller = level_controller->getDrawStackButtons()->pop();
			temp_stack.push(card_controller);

			float x_position = LevelModel::drawing_deck_left_offset - (i * LevelModel::drawing_deck_horizontal_spacing);
			float y_position = LevelModel::drawing_deck_top_offset;

			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
		}

		while (!temp_stack.isEmpty())
		{
			level_controller->getDrawStackButtons()->push(temp_stack.pop());
		}
	}

	void LevelView::renderPlayStacks()
	{
		for (int i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			renderPlayStackCards(*(level_controller->getPlayStacks()[i]));
		}
	}

	void LevelView::renderPlayStackCards(IStack<Card::CardController*>& stack)
	{
		ArrayStack::Stack<CardController*> temp_stack;

		while (!stack.isEmpty())
		{
			temp_stack.push(stack.pop());
		}

		while (!temp_stack.isEmpty())
		{
			temp_stack.peek()->render();
			stack.push(temp_stack.pop());
		}
	}

	void LevelView::renderSolutionStacks()
	{
		for (int i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->isEmpty()) continue;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->render();
		}
	}

	void LevelView::renderDrawnigStack()
	{
		ArrayStack::Stack<CardController*> temp_stack;
		int number_of_draws = getNumberOfDrawsRemaining();

		for (int i = 0; i < number_of_draws; i++)
		{
			CardController* card_controller = level_controller->getDrawStackButtons()->pop();
			temp_stack.push(card_controller);
						
				card_controller->render();
						
		}

		while (!temp_stack.isEmpty())
		{
			level_controller->getDrawStackButtons()->push(temp_stack.pop());
		}
		
	}

	int LevelView::getNumberOfDrawsRemaining()
	{
		float drawing_stack_size = static_cast<float>(level_controller->getDrawingStack()->getSize());
		float play_stacks_count = static_cast<float>(LevelModel::number_of_play_stacks);

		return static_cast<int>(std::ceil(drawing_stack_size / play_stacks_count));
	}

	float LevelView::getTotalCardSpacingWidth()
	{
		return (LevelModel::number_of_play_stacks + 1)* LevelModel::cards_horrizontal_spacing;

	}


	void LevelView::setCardDimensions(float height, float width)
	{
		card_height = height;
		card_width = width;
	}

	float LevelView::getCardVerticalSpacing(Card::State state, int number_of_open_cards)
	{
		float vertical_spacing_adjustment_ratio = static_cast<float>(LevelModel::max_number_of_open_cards) / static_cast<float>(number_of_open_cards);

		switch (state)
		{
		case::Card::State::OPEN:
			return LevelModel::open_cards_vertical_spacing * std::min(1.f, vertical_spacing_adjustment_ratio);
		case::Card::State::CLOSE:
			return LevelModel::closed_cards_vertical_spacing;
		case::Card::State::SELECTED:
			return LevelModel::open_cards_vertical_spacing * std::min(1.f, vertical_spacing_adjustment_ratio);
		}
	}

	void LevelView::destroy()
	{
		delete (background_image);
	}
}