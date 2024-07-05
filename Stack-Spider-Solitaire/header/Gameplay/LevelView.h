#pragma once
#include "../../header/UI/UIElement/ImageView.h"

namespace Gameplay
{
    class LevelController;

    class LevelView
    {
    private:

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

        float getTotalCardSpacingWidth();

        
    };
}