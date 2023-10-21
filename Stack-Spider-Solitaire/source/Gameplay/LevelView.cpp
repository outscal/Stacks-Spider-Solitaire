#include "../../header/Gameplay/LevelView.h"
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GraphicService.h"
#include "../../header/Gameplay/LevelController.h"
#include "../../header/Card/CardController.h"
#include <vector>

namespace Gameplay
{
	using namespace LinkedListStack;
	using namespace ArrayStack;
	using namespace UIElement;
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
		initializeImage();
		calculateCardExtents();
	}

	void LevelView::createImage()
	{
		background_image = new ImageView();
	}

	void LevelView::initializeImage()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		background_image->initialize(Config::level_background_texture_path, 
									game_window->getSize().x, 
									game_window->getSize().y, 
									sf::Vector2f(0,0));
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
			updatePlayStackCards(*(level_controller->getPlayStacks()[i]), i);
		}
	}

	void LevelView::updatePlayStackCards(LinkedListStack::Stack<CardController*>& stack, int stack_position)
	{
		LinkedListStack::Stack<CardController*> temp_stack;
		float stack_size = stack.size();
		float card_stack_position = 0;

		while (!stack.empty())
		{
			float x_position = (stack_position * card_width) + ((stack_position + 1) * cards_horrizontal_spacing);
			float y_position = play_deck_top_offset + ((stack_size - card_stack_position) * cards_vertical_spacing);

			CardController* card_controller = stack.pop();
			temp_stack.push(card_controller);

			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			card_controller->update();
			card_stack_position++;
		}

		while (!temp_stack.empty())
		{
			stack.push(temp_stack.pop());
		}
	}

	void LevelView::updateSolutionStacksView() 
	{
		for (float i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->empty()) continue;

			float x_position = solution_deck_left_offset + (i * solution_deck_horizontal_spacing);
			float y_position = solution_deck_top_offset;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			card_controller->update();
		}
	}

	void LevelView::updateDrawingStackView() 
	{ 
		ArrayStack::Stack<CardController*> temp_stack;
		int number_of_draws = level_controller->getDrawingStack()->size() / LevelModel::number_of_play_stacks;

		for (int i = 0; i < number_of_draws; i++)
		{
			CardController* card_controller = level_controller->getDrawingStack()->pop();
			temp_stack.push(card_controller);

			float x_position = drawing_deck_left_offset - (i * drawing_deck_horizontal_spacing);
			float y_position = drawing_deck_top_offset;

			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			card_controller->update();
		}

		while (!temp_stack.empty())
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

	void LevelView::renderPlayStackCards(LinkedListStack::Stack<Card::CardController*>& stack)
	{
		LinkedListStack::Stack<CardController*> temp_stack;

		while (!stack.empty())
		{
			CardController* card_controller = stack.pop();
			temp_stack.push(card_controller);
		}

		while (!temp_stack.empty())
		{
			temp_stack.peek()->render();
			stack.push(temp_stack.pop());
		}
	}

	void LevelView::renderSolutionStacks()
	{
		for (int i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->empty()) continue;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->render();
		}
	}

	void LevelView::renderDrawnigStack()
	{
		ArrayStack::Stack<CardController*> temp_stack;
		int number_of_draws = level_controller->getDrawingStack()->size() / LevelModel::number_of_play_stacks;

		for (int i = 0; i < number_of_draws; i++)
		{
			CardController* card_controller = level_controller->getDrawingStack()->pop();
			temp_stack.push(card_controller);
			card_controller->render();
		}

		while (!temp_stack.empty())
		{
			level_controller->getDrawingStack()->push(temp_stack.pop());
		}
	}

	float LevelView::getCardWidth()
	{
		return card_width;
	}

	float LevelView::getCardHeight()
	{
		return card_height;
	}

	void LevelView::calculateCardExtents()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		float total_width = game_window->getSize().x;
		float total_spacing_width = (LevelModel::number_of_play_stacks + 1) * cards_horrizontal_spacing;

		card_width = (total_width - total_spacing_width) / LevelModel::number_of_play_stacks;
		card_height = card_width * height_to_width_ratio;
	}

	void LevelView::destroy()
	{
		delete (background_image);
	}
}