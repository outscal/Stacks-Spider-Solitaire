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

        float elapsed_time;
        int score;

        void updateElapsedTime();
        void updatePlayStacks();
        void updateSolutionStacks();
        void updateDrawingStack();
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

        std::vector<LinkedListStack::Stack<Card::CardController*>*> getPlayStacks();
        std::vector<ArrayStack::Stack<Card::CardController*>*> getSolutionStacks();
        ArrayStack::Stack<Card::CardController*>* getDrawingStack();
    };
}