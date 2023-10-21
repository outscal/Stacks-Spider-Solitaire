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
        const float cards_vertical_spacing = 25.f;

        const float play_deck_top_offset = 90.f;

        const float drawing_deck_top_offset = 700.f;
        const float drawing_deck_left_offset = 1550.f;
        const float drawing_deck_horizontal_spacing = 50.f;

        const float solution_deck_top_offset = 700.f;
        const float solution_deck_left_offset = 200.f;
        const float solution_deck_horizontal_spacing = 50.f;

        float card_width;
        float card_height;

        LevelController* level_controller;
        UIElement::ImageView* background_image;

        void createImage();
        void initializeImage();

        void updatePlayStacksView();
        void updatePlayStackCards(LinkedListStack::Stack<Card::CardController*>& stack, int stack_position);

        void updateSolutionStacksView();      
        void updateDrawingStackView();

        void renderPlayStacks();
        void renderPlayStackCards(LinkedListStack::Stack<Card::CardController*>& stack);

        void renderSolutionStacks();
        void renderDrawnigStack();

        void calculateCardExtents();
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