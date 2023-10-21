#pragma once
#include "../../header/UI/UIElement/ImageView.h"

namespace Gameplay
{
    class LevelController;

    class LevelView
    {
    private:
        const float height_to_width_ratio = 1.37f;
        const float cards_horrizontal_spacing = 30.f;

        const float play_deck_top_offset = 70.f;
        const float drawing_deck_top_offset = 700.f;
        const float drawing_deck_left_offset = 1550.f;

        const float solution_deck_top_offset = 700.f;
        const float solution_deck_left_offset = 200.f;
        const float solution_deck_spacing = 50.f;

        float card_width;
        float card_height;

        LevelController* level_controller;
        UIElement::ImageView* background_image;

        void createImage();
        void initializeImage();

        void updatePlayStacksView();
        void updateSolutionStacksView();
        void updateDrawingStackView();

        void renderPlayStacks();
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