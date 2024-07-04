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
        const int drawing_deck_stack_size = 50;

        std::vector<IStack<Card::CardController*>*> play_stacks;
        std::vector<IStack<Card::CardController*>*> solution_stacks;
        IStack<Card::CardController*>* drawing_stack;

        void createPlayStacks();
        void createSolutionStacks();
        void createDrawingStack();
        void openPlayStacksTopCard();
        void destroy();
        void deleteAllStackElemets();
        void deleteStackElements(IStack<Card::CardController*>* stack);

        void addCardInPlayStack(int stack_index, Card::CardController* card_controller);
        void addCardInSolutionStack(int stack_index, Card::CardController* card_controller);
        void addCardInDrawingStack(Card::CardController* card_controller);

    public:
        static const int number_of_play_stacks = 10;
        static const int number_of_solution_stacks = 8;

        // Spacings:
        static constexpr float cards_horrizontal_spacing = 40.f;
        static constexpr float cards_vertical_spacing = 25.f;

        // Offsets:
        static constexpr float play_deck_top_offset = 90.f;

        static constexpr float drawing_deck_top_offset = 770.f;
        static constexpr float drawing_deck_left_offset = 1670.f;
        static constexpr float drawing_deck_horizontal_spacing = 40.f;

        static constexpr float solution_deck_top_offset = 700.f;
        static constexpr float solution_deck_left_offset = 200.f;
        static constexpr float solution_deck_horizontal_spacing = 40.f;

        LevelModel();
        ~LevelModel();

        void initialize();
        void reset();

        void populateCardPiles(IStack<CardController*>* temp_card_deck);

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();

        void openTopPlayStackCards();

        static constexpr float cards_horrizontal_spacing = 40.f;

        static constexpr float play_deck_top_offset = 110.f;
        static constexpr float drawing_deck_top_offset = 800.f;
        static constexpr float drawing_deck_left_offset = 1670.f;

        static constexpr float solution_deck_top_offset = 770.f;
        static constexpr float solution_deck_left_offset = 200.f;
        static constexpr float solution_deck_spacing = 40.f;

        static constexpr float background_alpha = 85.f;

    };
}