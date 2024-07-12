#pragma once
#include "../../header/Card/CardModel.h"
#include "../../header/Card/CardView.h"

namespace Card
{
    class CardController
    {
    private:
        CardModel* card_model;
        CardView* card_view;
        
    public:
        CardController(Rank rank, Suit suit);
        ~CardController();

        void initialize(float card_width, float card_height, float hide_duration = 0);
        void update();
        void render();

        
        CardData* getCardData();
        void setCardState(State card_state);

        sf::Vector2f getCardPosition();
        void setCardPosition(sf::Vector2f card_position);

        CardVisibility getCardVisibility();
        void setCardVisibility(Card::CardVisibility visibility);
        bool positionSet = false;

    };
}