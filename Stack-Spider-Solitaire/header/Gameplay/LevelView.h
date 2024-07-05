#pragma once
#include "../../header/UI/UIElement/ImageView.h"
#include "../../header/Stack/IStack.h"
#include "../../header/Card/CardController.h"

namespace Gameplay
{
    using namespace Stack;
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
        void updateSinglePlayStackView(IStack<Card::CardController*>& stack, int stack_position);

        void updateSolutionStacksView();      
        void updateDrawingStackView();

        void renderPlayStacks();
        void renderPlayStackCards(IStack<Card::CardController*>& stack);

        void renderSolutionStacks();
        void renderDrawnigStack();

        int getNumberOfDrawsRemaining();

        

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