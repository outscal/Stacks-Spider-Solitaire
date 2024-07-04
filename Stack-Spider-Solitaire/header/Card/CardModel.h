#pragma once
#include "../../header/Card/CardConfig.h"
#include <sfml/Graphics.hpp>

namespace Card
{
    struct CardData
    {
        CardData(Rank card_rank, Suit card_suit, State card_state)
        {
            rank = card_rank;
            suit = card_suit;
            state = card_state;
        }

        Rank rank;
        Suit suit;
        State state;
    };

    class CardModel
    {
    private:
        CardData* card_data;
        sf::Vector2f position;

    public:
        CardModel(Rank rank, Suit suit);
        ~CardModel();

        void setPosition(sf::Vector2f card_position);
        sf::Vector2f getPosition();

        void setCardState(State card_state);
        CardData* getCardData();
        void setCardState(State card_state);
    };
}