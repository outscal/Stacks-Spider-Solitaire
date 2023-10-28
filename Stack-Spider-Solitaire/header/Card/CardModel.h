#pragma once
#include "Card/CardConfig.h"
#include <SFML/Graphics.hpp>

namespace Card
{
    enum class CardVisibility
    {
        VISIBLE,
        HIDDEN,
    };

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

        CardVisibility card_visibility;
        float hide_duration;

    public:
        CardModel(Rank rank, Suit suit);
        ~CardModel();

        void setPosition(sf::Vector2f card_position);
        sf::Vector2f getPosition();

        void setCardState(State card_state);
        CardType* getCardType();

        void setCardVisibility(CardVisibility visibility);
        CardVisibility getCardVisibility();

        void setHideDuration(float duration);
        float getHideDuration();
    };
}