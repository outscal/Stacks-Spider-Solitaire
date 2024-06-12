#pragma once
#include <vector>
#include "../../header/Stack/IStack.h"
#include "../../header/Card/CardController.h"

namespace Gameplay
{
    using namespace Stack;
    using namespace Card;

    class LevelModel
    {
    private:
        std::vector<IStack<Card::CardController*>*> play_stacks;
        std::vector<IStack<Card::CardController*>*> solution_stacks;
        IStack<Card::CardController*>* drawing_stack;

        void createPlayStacks();
        void createSolutionStacks();
        void createDrawingStack();
        void destroy();

    public:
        static const int number_of_play_stacks = 10;
        static const int number_of_solution_stacks = 8;

        LevelModel();
        ~LevelModel();

        void initialize();

        void populateCardPiles(IStack<CardController*>* temp_card_deck);
        void addCardInPlayStack(int stack_index, Card::CardController* card_controller);
        void addCardInSolutionStack(int stack_index, Card::CardController* card_controller);
        void addCardInDrawingStack(Card::CardController* card_controller);

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();
    };
}