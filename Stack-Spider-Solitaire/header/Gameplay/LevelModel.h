#pragma once
#include <vector>
#include "../../header/Stack/IStack.h"
#include "../../header/Card/CardController.h"

namespace Gameplay
{

   
    using namespace Stack;
    using namespace Card;

    struct CardMovement {
        IStack<Card::CardController*>* sourceStack;
        IStack<Card::CardController*>* targetStack;
        std::vector<Card::CardController*> movedCards;
        bool wasTopCardOpen;
        Card::CardController* openedCard;  // Track the card that was opened

        CardMovement(IStack<Card::CardController*>* src, IStack<Card::CardController*>* tgt, std::vector<Card::CardController*> cards, bool topCardOpen, Card::CardController* openedCard)
            : sourceStack(src), targetStack(tgt), movedCards(cards), wasTopCardOpen(topCardOpen), openedCard(openedCard) {}
    };


    class LevelModel
    {
    private:
        

        std::vector<IStack<Card::CardController*>*> play_stacks;
        std::vector<IStack<Card::CardController*>*> solution_stacks;
        IStack<Card::CardController*>* drawing_stack;
        IStack<Card::CardController*>* draw_stack_buttons;
        

        void createPlayStacks();
        void createSolutionStacks();
        void createDrawingStack();
        void createDrawStackButtons();
        void createMoveHistoryStack();

        void destroy();
        void deleteAllStackElemets();
        void deleteStackElements(IStack<Card::CardController*>* stack);

        


    public:
        static const int number_of_play_stacks = 10;
        static const int number_of_solution_stacks = 8;

        static const int initial_score = 500;
        static const int suit_complete_score = 50;

        static const int max_number_of_open_cards = 7;
        
        static constexpr float card_hide_duration = 0.15f;

        const int number_of_decks = 4;
        const int drawing_deck_stack_size = 50;

        static constexpr float cards_horrizontal_spacing = 40.f;
        static constexpr float closed_cards_vertical_spacing = 25.f;
        static constexpr float open_cards_vertical_spacing = 60.f;

        static constexpr float play_deck_top_offset = 110.f;

        static constexpr float drawing_deck_top_offset = 820.f;
        static constexpr float drawing_deck_left_offset = 1670.f;
        static constexpr float drawing_deck_horizontal_spacing = 40.f;

        static constexpr float solution_deck_top_offset = 820.f;
        static constexpr float solution_deck_left_offset = 200.f;
        static constexpr float solution_deck_spacing = 40.f;

        IStack<CardMovement*>* moveHistory;

        LevelModel();
        ~LevelModel();

        void initialize();
        void reset();

        void populateCardPiles();

        void addEmptyCard(IStack<Card::CardController*>* stack);
        void removeEmptyCard(IStack<Card::CardController*>* stack);

        IStack<Card::CardController*>* findPlayStack(Card::CardController* card_controller);

        IStack<Card::CardController*>* getEmptySolutionStack();
        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();
        IStack<Card::CardController*>* getDrawStackButtons();

        void openTopPlayStackCards();

        void addCardInPlayStack(int stack_index, Card::CardController* card_controller);
        void addCardInSolutionStack(int stack_index, Card::CardController* card_controller);
        void addCardInDrawingStack(Card::CardController* card_controller);
        void addDrawStackButtons(Card::CardController* card_controller);

        
        


    };
}