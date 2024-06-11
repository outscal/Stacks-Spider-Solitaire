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

    public:
        LevelController();
        ~LevelController();

        void initialize();
        void update();
        void render();

        void populateCardPiles(IStack<CardController*>* temp_card_deck);
        void processCard(CardController* card_to_process);

        std::vector<IStack<Card::CardController*>*> getPlayStacks();
        std::vector<IStack<Card::CardController*>*> getSolutionStacks();
        IStack<Card::CardController*>* getDrawingStack();

        float getTotalCardSpacingWidth();
        int getNumberOfPlaystacks();
    };
}