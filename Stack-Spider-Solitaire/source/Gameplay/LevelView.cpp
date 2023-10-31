#include "Gameplay/LevelView.h"
#include "Card/CardController.h"
#include "Gameplay/LevelController.h"
#include "Gameplay/LevelModel.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Main/GraphicService.h"

#include <cmath>
#include <iostream>
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
		this->game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
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
									 sf::Vector2f(0, 0));
	}

	void LevelView::update()
	{
		// Get the mouse position
		this->mouse_position = sf::Mouse::getPosition(*game_window);
		this->current_mouse_coord = game_window->mapPixelToCoords(mouse_position);

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

	void LevelView::updatePlayStackCardsView(LinkedListStack::Stack<CardController*>& stack, int stack_position)
	{
		LinkedListStack::Stack<CardController*> temp_stack;
		// float card_stack_position = 0;
		float vertical_spacing = 0;
		int number_of_open_cards = 0;
		auto num_selected_cards = 0;

		while (!stack.empty())
		{
			if (stack.peek()->getCardState() == Card::State::OPEN)
			{
				number_of_open_cards++;
			}
			if (stack.peek()->getCardState() == Card::State::SELECTED)
			{
				num_selected_cards++;
			}

			temp_stack.push(stack.pop());
		}

		while (!temp_stack.empty())
		{
			float x_position = play_deck_left_offset + (stack_position * card_width) + ((stack_position + 1) * cards_horrizontal_spacing);
			float y_position = play_deck_top_offset + vertical_spacing;

			CardController* card_controller = temp_stack.pop();

			if (card_controller->shouldFollowMouse())
			{
				sf::Vector2f mouse_delta = current_mouse_coord - this->prev_mouse_pos;

				// Apply acceleration
				this->velocity += 0.08f * static_cast<sf::Vector2f>(mouse_delta);

				// Calculate the new card position with or without vertical spacing

				sf::Vector2f cardpos = sf::Vector2f{current_mouse_coord.x, (num_selected_cards <= 1) ? (current_mouse_coord.y) : (current_mouse_coord.y + vertical_spacing - play_deck_top_offset)};
				cardpos += velocity;

				// Apply acceleration to card position
				card_controller->setCardPosition(cardpos);

				this->prev_mouse_pos = current_mouse_coord;
				velocity *= 0.99f;
			}
			else
			{
				card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			}

			stack.push(card_controller);
			// card_stack_position++;
			vertical_spacing += getCardVerticalSpacing(card_controller->getCardState(), number_of_open_cards);
		}
	}

	void LevelView::updateSolutionStacksView()
	{
		for (float i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->empty())
				continue;

			float x_position = solution_deck_left_offset + (i * solution_deck_horizontal_spacing);
			float y_position = solution_deck_top_offset;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
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

			auto target_position = sf::Vector2f(x_position, y_position);

			// FIXME
			if (this->initial_draw)
			{
				// Update sprite position for animation
				sf::Vector2f currentPosition = card_controller->getCardPosition();
				sf::Vector2f direction = target_position - currentPosition;

				// Calculate the distance to move this frame based on animationSpeed
				float distance_to_move = this->animation_speed * ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

				// If the sprite hasn't reached the target position yet, move it
				if (direction != sf::Vector2f(0, 0))
				{
					this->initial_draw = false;
					if (distance_to_move >= length(direction))
					{
						card_controller->setCardPosition(target_position);
					}
					else
					{
						sf::Vector2f step = normalize(direction) * distance_to_move;

						sf::Vector2f pos = card_controller->getCardPosition();
						card_controller->setCardPosition({pos.x + step.x, pos.y + step.y});
					}
				}
			}
			else
			{
				card_controller->setCardPosition(target_position);
			}
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
			if (level_controller->getSolutionStacks()[i]->empty())
				continue;

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

	float LevelView::getCardVerticalSpacing(Card::State state, int number_of_open_cards)
	{
		float vertical_spacing_adjustment_ratio = static_cast<float>(max_number_of_open_cards) / static_cast<float>(number_of_open_cards);

		switch (state)
		{
		case ::Card::State::OPEN:
			return open_cards_vertical_spacing * std::min(1.f, vertical_spacing_adjustment_ratio);
		case ::Card::State::CLOSE:
			return closed_cards_vertical_spacing;
		case ::Card::State::SELECTED:
			return open_cards_vertical_spacing * std::min(1.f, vertical_spacing_adjustment_ratio);
		}
	}

	void LevelView::destroy()
	{
		delete (background_image);
	}
} // namespace Gameplay