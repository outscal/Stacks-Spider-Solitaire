#pragma once
#include <vector>
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Gameplay/LevelView.h"
#include "../../header/Stack/IStack.h"
#include "../Card/CardController.h"

namespace Gameplay
{
    using namespace Stack;
    using namespace Card;
    
    class LevelController
    {
    private:
        LevelModel* level_model;
        LevelView* level_view;
        Card::CardController* previously_selected_card_controller;
        Card::CardController* flagged_card_to_process_input;

        float elapsed_time = 0.0f;
        float delay_time = 0.0f;
        int score;
        bool canDrawCard = false;
        int cards_popped = 0;

        void updateElapsedTime();
        void updateDelayTime();
        void updateStacks();
        void updatePlayStacks();
        void updateSolutionStacks();
        void updateDrawingStack();
        void updateStackCards(IStack<Card::CardController*>* stack);

        void processCardControllerInput();
        void processButtonInput(Card::CardController* selected_card_controller);
        void processCardSelection(Card::CardController* selected_card_controller);
        void processCardDraw(Card::CardController* selected_card_controller);
        void processCardMove(Card::CardController* selected_card_controller);
        void processSuitCompletion(IStack<Card::CardController*>* stack);
        void drawCards();

        void selectCards(Card::CardController* card_controller);
        void unselectCards(Card::CardController* card_controller);
        void moveCards(Card::CardController* selected_card_controller);
        std::vector<Card::CardController*> moveCardsBetweenStacks(IStack<Card::CardController*>* source_stack, IStack<Card::CardController*>* target_stack, Card::CardController*& openedCard);
        void openTopCardOfStack(IStack<Card::CardController*>* stack);

        bool isValidSelection(Card::CardController* selected_card_controller);
        bool isValidMove(Card::CardController* selected_card_controller);
        bool isSequential(IStack<Card::CardController*>* stack, Card::CardController* last_card_to_check);

        bool isSuitComplete(IStack<Card::CardController*>* stack);
        bool isLevelComplete();
        bool isGameOver();

        void undo();

        void reduceScore(int val);
        void increaseScore(int val);
        void processGameOver();
        void clearMoveHistory();
        void reset();

    public:
        LevelController();
        ~LevelController();

        void initialize();
        void update();
        void render();

        void startLevel();

        void setCardToProcessInput(Card::CardController* selected_card_controller);
        
        float getElapsedTime();
        int getScore();

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();
        IStack<Card::CardController*>* getDrawStackButtons();

        float getTotalCardSpacingWidth();
        int getNumberOfPlaystacks();
        sf::Vector2f calculatePlayCardPosition(int stack_index, int stack_size, int card_stack_position);
    };
}