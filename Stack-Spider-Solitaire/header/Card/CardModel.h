#pragma once
#include "../../header/Card/CardConfig.h"
#include <sfml/Graphics.hpp>

namespace Card
{
    struct CardType
    {
        CardType(Rank card_rank, Suit card_suit, State card_state)
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
        CardType* card_type;
        sf::Vector2f position;

    public:
        CardModel(Rank rank, Suit suit);
        ~CardModel();

        void setPosition(sf::Vector2f card_position);
        sf::Vector2f getPosition();

        CardType* getCardType();
    };
}