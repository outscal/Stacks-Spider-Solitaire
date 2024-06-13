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
		for (float i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			updateSinglePlayStackView(*(level_controller->getPlayStacks()[i]), i);
		}
	}

	void LevelView::updateSinglePlayStackView(IStack<CardController*>& stack_to_update, int stack_index)
	{
		ArrayStack::Stack<CardController*> temp_stack;
		int stack_size = stack_to_update.getSize();
		int card_stack_position = 0;

		while (!stack_to_update.isEmpty())
		{
			sf::Vector2f card_position = level_controller->calculatePlayCardPosition(stack_index, stack_size, card_stack_position);

			CardController* card_controller = stack_to_update.pop();
			temp_stack.push(card_controller);

			card_controller->setCardPosition(card_position);
			card_controller->update();
			card_stack_position++;
		}

		while (!temp_stack.isEmpty())
		{
			stack_to_update.push(temp_stack.pop());
		}
	}

	void LevelView::updateSolutionStacksView() 
	{
		for (float i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->isEmpty()) continue;

			float x_position = LevelModel::solution_deck_left_offset + (i * LevelModel::solution_deck_horizontal_spacing);
			float y_position = LevelModel::solution_deck_top_offset;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			card_controller->update();
		}
	}

	void LevelView::updateDrawingStackView() 
	{ 
		ArrayStack::Stack<CardController*> temp_stack;
		int number_of_draws = level_controller->getDrawingStack()->getSize() / LevelModel::number_of_play_stacks;

		for (int i = 0; i < number_of_draws; i++)
		{
			CardController* card_controller = level_controller->getDrawingStack()->pop();
			temp_stack.push(card_controller);

			float x_position = LevelModel::drawing_deck_left_offset - (i * LevelModel::drawing_deck_horizontal_spacing);
			float y_position = LevelModel::drawing_deck_top_offset;

			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			card_controller->update();
		}

		while (!temp_stack.isEmpty())
		{
			level_controller->getDrawingStack()->push(temp_stack.pop());
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
		int number_of_draws = level_controller->getDrawingStack()->getSize() / LevelModel::number_of_play_stacks;

		for (int i = 0; i < number_of_draws; i++)
		{
			CardController* card_controller = level_controller->getDrawingStack()->pop();
			temp_stack.push(card_controller);
			card_controller->render();
		}

		while (!temp_stack.isEmpty())
		{
			level_controller->getDrawingStack()->push(temp_stack.pop());
		}
	}

	void LevelView::destroy()
	{
		delete (background_image);
	}
}