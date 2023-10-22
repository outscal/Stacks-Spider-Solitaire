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

        void initialize(float card_width, float card_height);
        void update();
        void render();

        CardType* getCardType();
        State getCardState();
        void setCardState(State card_state);

        void setCardHighLight(bool b_highlight);

        sf::Vector2f getCardPosition();
        void setCardPosition(sf::Vector2f card_position);
    };
}