#pragma once
#include "../../header/UI/UIElement/ImageView.h"

namespace Gameplay
{
    class LevelController;

    class LevelView
    {
    private:
        const float cards_horrizontal_spacing = 30.f;

        const float play_deck_top_offset = 70.f;
        const float drawing_deck_top_offset = 700.f;
        const float drawing_deck_left_offset = 1550.f;

        const float solution_deck_top_offset = 700.f;
        const float solution_deck_left_offset = 200.f;
        const float solution_deck_spacing = 50.f;

        const float background_alpha = 85.f;

        LevelController* level_controller;
        UI::UIElement::ImageView* background_image;

        void createImage();
        void initializeBackgroudImage();

        void updatePlayStacksView();
        void updateSolutionStacksView();
        void updateDrawingStackView();

        void renderPlayStacks();
        void renderSolutionStacks();
        void renderDrawnigStack();

        void destroy();

    public:
        LevelView();
        ~LevelView();

        void initialize(LevelController* controller);
        void update();
        void render();

        float getTotalSpacingWidth();
    };
}