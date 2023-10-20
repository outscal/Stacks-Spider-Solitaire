#pragma once
#include "../../header/Stack/ArrayStack.h"
#include "../../header/Card/CardController.h"
#include <vector>

namespace Gameplay
{
    class LevelModel
    {
    private:
        std::vector<ArrayStack::Stack<Card::CardController*>*> play_stacks;
        std::vector<ArrayStack::Stack<Card::CardController*>*> solution_stacks;
        ArrayStack::Stack<Card::CardController*>* drawing_stack;

    public:
        static const int number_of_play_stacks = 10;
        static const int number_of_solution_stacks = 4;

        LevelModel();
        ~LevelModel();

        void initialize();

        void addPlayStack(ArrayStack::Stack<Card::CardController*>* stack);
        void addSolutionStack(ArrayStack::Stack<Card::CardController*>* stack);
        void setDrawingStack(ArrayStack::Stack<Card::CardController*>* stack);

        std::vector<ArrayStack::Stack<Card::CardController*>*> getPlayStacks();
        std::vector<ArrayStack::Stack<Card::CardController*>*> getSolutionStacks();
        ArrayStack::Stack<Card::CardController*>* getDrawingStack();
    };
}