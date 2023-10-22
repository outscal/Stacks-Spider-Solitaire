#pragma once
#include "../../header/Stack/ArrayStack.h"
#include "../../header/Stack/LinkedListStack.h"
#include "../../header/Card/CardController.h"
#include <vector>

namespace Gameplay
{
    class LevelModel
    {
    private:
        const int number_of_decks = 4;
        const int drawing_deck_stack_size = 50;

        std::vector<LinkedListStack::Stack<Card::CardController*>*> play_stacks;
        std::vector<ArrayStack::Stack<Card::CardController*>*> solution_stacks;
        ArrayStack::Stack<Card::CardController*>* drawing_stack;

        void createPlayStacks();
        void createSolutionStacks();
        void createDrawingStack();

        void initializeStacks();
        void openPlayStacksTopCard();

        void destroy();
        void deleteStackElements();
        void deleteLinkedListStackElements(LinkedListStack::Stack<Card::CardController*>* stack);
        void deleteArrayStackElements(ArrayStack::Stack<Card::CardController*>* stack);

    public:
        static const int number_of_play_stacks = 10;
        static const int number_of_solution_stacks = 4;

        LevelModel();
        ~LevelModel();

        void initialize();
        void reset();

        void addCardInPlayStack(int stack_index, Card::CardController* card_controller);
        void addCardInSolutionStack(int stack_index, Card::CardController* card_controller);
        void addCardInDrawingStack(Card::CardController* card_controller);

        LinkedListStack::Stack<Card::CardController*>* findPlayStack(Card::CardController* card_controller);

        std::vector<LinkedListStack::Stack<Card::CardController*>*> getPlayStacks();
        std::vector<ArrayStack::Stack<Card::CardController*>*> getSolutionStacks();
        ArrayStack::Stack<Card::CardController*>* getDrawingStack();
    };
}