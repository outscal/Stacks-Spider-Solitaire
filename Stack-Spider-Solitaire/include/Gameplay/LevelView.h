#pragma once
#include "Card/CardController.h"
#include "Stack/ArrayStack.h"
#include "Stack/LinkedListStack.h"
#include "UI/UIElement/ImageView.h"

namespace Gameplay
{
	inline float length(const sf::Vector2f& vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	inline sf::Vector2f normalize(const sf::Vector2f& vector)
	{
		float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
		if (length != 0)
		{
			return sf::Vector2f(vector.x / length, vector.y / length);
		}
		return vector; // Avoid division by zero
	}

	class LevelController;

	class LevelView
	{
	  private:
		const float height_to_width_ratio = 1.45f;
		const float cards_horrizontal_spacing = 40.f;
		const float closed_cards_vertical_spacing = 25.f;
		const float open_cards_vertical_spacing = 60.f;

		const float play_deck_top_offset = 180.f;
		const float play_deck_left_offset = 60.f;

		const float drawing_deck_top_offset = 770.f;
		const float drawing_deck_left_offset = 1670.f;
		const float drawing_deck_horizontal_spacing = 40.f;

		const float solution_deck_top_offset = 700.f;
		const float solution_deck_left_offset = 200.f;
		const float solution_deck_horizontal_spacing = 40.f;

		const int max_number_of_open_cards = 8;

		const float animation_speed = 1000.0;

		float card_width;
		float card_height;

		bool initial_draw{true};

		sf::Vector2f prev_mouse_pos{};
		sf::Vector2f velocity{};

		sf::RenderWindow* game_window;
		sf::Vector2i mouse_position{};
		sf::Vector2f current_mouse_coord{};

		LevelController* level_controller;
		UIElement::ImageView* background_image;

		void createImage();
		void initializeImage();

		void updatePlayStacksView();
		void updatePlayStackCardsView(LinkedListStack::Stack<Card::CardController*>& stack, int stack_position);

		void updateSolutionStacksView();
		void updateDrawingStackView();

		void renderPlayStacks();
		void renderPlayStackCards(LinkedListStack::Stack<Card::CardController*>& stack);

		void renderSolutionStacks();
		void renderDrawnigStack();

		void calculateCardExtents();
		float getCardVerticalSpacing(Card::State state, int number_of_open_cards);
		void destroy();

	  public:
		LevelView();
		~LevelView();

		void initialize(LevelController* controller);
		void update();
		void render();

		float getCardWidth();
		float getCardHeight();
	};
} // namespace Gameplay