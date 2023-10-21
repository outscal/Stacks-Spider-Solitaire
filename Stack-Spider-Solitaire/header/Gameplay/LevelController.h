#pragma once
#include <vector>
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Gameplay/LevelView.h"
#include "../../header/Stack/ArrayStack.h"

namespace Gameplay
{
    class LevelController
    {
    private:
        LevelModel* level_model;
        LevelView* level_view;

        void updatePlayStacks();
        void updateSolutionStacks();
        void updateDrawingStack();

    public:
        LevelController();
        ~LevelController();

        void initialize();
        void update();
        void render();

        float getCardWidth();
        float getCardHeight();

        std::vector<ArrayStack::Stack<Card::CardController*>*> getPlayStacks();
        std::vector<ArrayStack::Stack<Card::CardController*>*> getSolutionStacks();
        ArrayStack::Stack<Card::CardController*>* getDrawingStack();
    };
}