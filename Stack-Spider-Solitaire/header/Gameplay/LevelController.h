#pragma once
#include <vector>
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Gameplay/LevelView.h"
#include "../../header/Stack/IStack.h"

namespace Gameplay
{
    using namespace Stack;

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

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();
    };
}