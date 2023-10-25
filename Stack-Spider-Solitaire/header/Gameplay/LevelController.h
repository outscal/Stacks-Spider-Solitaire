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

        float elapsed_time;
        int score;

        void updateElapsedTime();
        void reset();

    public:
        LevelController();
        ~LevelController();

        void initialize();
        void update();
        void render();

        void startLevel();
        
        float getCardWidth();
        float getCardHeight();
        float getElapsedTime();
        int getScore();

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();
    };
}