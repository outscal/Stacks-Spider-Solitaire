#pragma once
#include "../../header/UI/UIElement/ImageView.h"
#include "../../header/Stack/ArrayStack.h"
#include "../../header/Stack/LinkedListStack.h"
#include "../../header/Card/CardController.h"

namespace Gameplay
{
    class LevelController;

    class LevelView
    {
    private:
        const float height_to_width_ratio = 1.45f;
        const float cards_horrizontal_spacing = 40.f;
        const float closed_cards_vertical_spacing = 25.f;
        const float open_cards_vertical_spacing = 60.f;

        const float play_deck_top_offset = 110.f;

        const float drawing_deck_top_offset = 770.f;
        const float drawing_deck_left_offset = 1670.f;
        const float drawing_deck_horizontal_spacing = 40.f;

        const float solution_deck_top_offset = 770.f;
        const float solution_deck_left_offset = 200.f;
        const float solution_deck_horizontal_spacing = 40.f;

        const int max_number_of_open_cards = 7;

        float card_width;
        float card_height;

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

        int getNumberOfDrawsRemaining();
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
}