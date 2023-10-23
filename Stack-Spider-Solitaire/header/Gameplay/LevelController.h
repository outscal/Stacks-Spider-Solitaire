#pragma once
#include <vector>
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Gameplay/LevelView.h"
#include "../../header/Stack/ArrayStack.h"
#include "../../header/Stack/LinkedListStack.h"

namespace Gameplay
{
    class LevelController
    {
    private:
        LevelModel* level_model;
        LevelView* level_view;
        Card::CardController* previously_selected_card_controller;
        Card::CardController* flagged_card_to_process_input;

        float elapsed_time;
        int score;

        void updateElapsedTime();
        void updateStacks();
        void updatePlayStacks();
        void updateSolutionStacks();
        void updateDrawingStack();
        void updateArrayStackCards(ArrayStack::Stack<Card::CardController*>* stack);
        void updateLinkedListStackCards(LinkedListStack::Stack<Card::CardController*>* stack);

        void processCardControllerInput();
        void processButtonInput(Card::CardController* selected_card_controller);
        void processCardSelection(Card::CardController* selected_card_controller);
        void processCardDraw(Card::CardController* selected_card_controller);
        void processCardMove(Card::CardController* selected_card_controller);
        void drawCards();

        void selectCards(Card::CardController* card_controller);
        void unselectCards(Card::CardController* card_controller);
        void moveCards(Card::CardController* selected_card_controller);
        void openTopCardOfStack(LinkedListStack::Stack<Card::CardController*>* stack);

        bool isValidSelection(Card::CardController* selected_card_controller);
        bool isValidMove(Card::CardController* selected_card_controller);

        void addEmptyCard(LinkedListStack::Stack<Card::CardController*>* stack);
        void removeEmptyCard(LinkedListStack::Stack<Card::CardController*>* stack);
        void reset();

    public:
        LevelController();
        ~LevelController();

        void initialize();
        void update();
        void render();

        void startLevel();

        void setCardToProcessInput(Card::CardController* selected_card_controller);
        float getCardWidth();
        float getCardHeight();
        float getElapsedTime();
        int getScore();

        std::vector<LinkedListStack::Stack<Card::CardController*>*> getPlayStacks();
        std::vector<ArrayStack::Stack<Card::CardController*>*> getSolutionStacks();
        ArrayStack::Stack<Card::CardController*>* getDrawingStack();
    };
}