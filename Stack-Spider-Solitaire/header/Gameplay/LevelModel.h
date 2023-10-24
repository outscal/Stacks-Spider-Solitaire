#pragma once
#include "../../header/Stack/IStack.h"
#include "../../header/Card/CardController.h"
#include <vector>

namespace Gameplay
{
    using namespace Stack;

    class LevelModel
    {
    private:
        std::vector<IStack<Card::CardController*>*> play_stacks;
        std::vector<IStack<Card::CardController*>*> solution_stacks;
        IStack<Card::CardController*>* drawing_stack;

        void createPlayStacks();
        void createSolutionStacks();
        void createDrawingStack();
        void initializeStacks();
        void destroy();

    public:
        static const int number_of_play_stacks = 10;
        static const int number_of_solution_stacks = 8;

        LevelModel();
        ~LevelModel();

        void initialize();

        void addCardInPlayStack(int stack_index, Card::CardController* card_controller);
        void addCardInSolutionStack(int stack_index, Card::CardController* card_controller);
        void addCardInDrawingStack(Card::CardController* card_controller);

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();
    };
}