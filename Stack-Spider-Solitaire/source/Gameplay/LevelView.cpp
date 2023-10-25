#include "../../header/Gameplay/LevelView.h"
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GraphicService.h"
#include "../../header/Gameplay/LevelController.h"
#include "../../header/Card/CardController.h"
#include "../../header/Stack/ArrayStack/ArrayStack.h"
#include <vector>

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
		calculateCardExtents();
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
			updatePlayStackCardsView(*(level_controller->getPlayStacks()[i]), i);
		}
	}

	void LevelView::updatePlayStackCardsView(IStack<CardController*>& stack, int stack_position)
	{
		ArrayStack::Stack<CardController*> temp_stack;
		float stack_size = stack.size();
		float card_stack_position = 0;
		float vertical_spacing = 0;
		int number_of_open_cards = 0;

		while (!stack.empty())
		{
			if (stack.peek()->getCardState() == Card::State::OPEN || 
				stack.peek()->getCardState() == Card::State::SELECTED) number_of_open_cards++;

			temp_stack.push(stack.pop());
		}

		while (!temp_stack.empty())
		{
			float x_position = (stack_position * card_width) + ((stack_position + 1) * cards_horrizontal_spacing);
			float y_position = play_deck_top_offset + vertical_spacing;

			CardController* card_controller = temp_stack.pop();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));

			stack.push(card_controller);
			card_stack_position++;
			vertical_spacing += getCardVerticalSpacing(card_controller->getCardState(), number_of_open_cards);
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
		}
	}

	void LevelView::updateDrawingStackView() 
	{ 
		ArrayStack::Stack<CardController*> temp_stack;
		int number_of_draws = getNumberOfDrawsRemaining();

		for (int i = 0; i < number_of_draws; i++)
		{
			CardController* card_controller = level_controller->getDrawingStack()->pop();
			temp_stack.push(card_controller);

			float x_position = drawing_deck_left_offset - (i * drawing_deck_horizontal_spacing);
			float y_position = drawing_deck_top_offset;

			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
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

	void LevelView::renderPlayStackCards(IStack<Card::CardController*>& stack)
	{
		ArrayStack::Stack<CardController*> temp_stack;

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
		int number_of_draws = getNumberOfDrawsRemaining();

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

	int LevelView::getNumberOfDrawsRemaining()
	{
		float drawing_stack_size = static_cast<float>(level_controller->getDrawingStack()->size());
		float play_stacks_count = static_cast<float>(LevelModel::number_of_play_stacks);
		
		return static_cast<int>(std::ceil(drawing_stack_size / play_stacks_count));
	}

	void LevelView::calculateCardExtents()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		float total_width = game_window->getSize().x;
		float total_spacing_width = (LevelModel::number_of_play_stacks + 1) * cards_horrizontal_spacing;

		card_width = (total_width - total_spacing_width) / LevelModel::number_of_play_stacks;
		card_height = card_width * height_to_width_ratio;
	}

	float LevelView::getCardVerticalSpacing(Card::State state, int number_of_open_cards)
	{
		float vertical_spacing_adjustment_ratio = static_cast<float>(max_number_of_open_cards) / static_cast<float>(number_of_open_cards);

		switch (state)
		{
		case::Card::State::OPEN:
			return open_cards_vertical_spacing * std::min(1.f, vertical_spacing_adjustment_ratio);
		case::Card::State::CLOSE:
			return closed_cards_vertical_spacing;
		case::Card::State::SELECTED:
			return open_cards_vertical_spacing * std::min(1.f, vertical_spacing_adjustment_ratio);
		}
	}

	void LevelView::destroy()
	{
		delete (background_image);
	}
}