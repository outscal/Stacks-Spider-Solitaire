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
        void deleteAllStackElemets();
        void deleteStackElements(IStack<Card::CardController*>* stack);

        void addCardInPlayStack(int stack_index, Card::CardController* card_controller);
        void addCardInSolutionStack(int stack_index, Card::CardController* card_controller);
        void addCardInDrawingStack(Card::CardController* card_controller);


    public:
        static const int number_of_play_stacks = 10;
        static const int number_of_solution_stacks = 8;

        const int number_of_decks = 4;
        const int drawing_deck_stack_size = 50;

        LevelModel();
        ~LevelModel();

        void initialize();
        void reset();

        void populateCardPiles();

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();

        void openTopPlayStackCards();

        static constexpr float cards_horrizontal_spacing = 40.f;
        static constexpr float cards_vertical_spacing = 25.f;

        static constexpr float play_deck_top_offset = 110.f;
        static constexpr float drawing_deck_top_offset = 800.f;
        static constexpr float drawing_deck_left_offset = 1670.f;

        static constexpr float solution_deck_top_offset = 770.f;
        static constexpr float solution_deck_left_offset = 200.f;
        static constexpr float solution_deck_spacing = 40.f;
        static constexpr float drawing_deck_horizontal_spacing = 40.f;


    };
}