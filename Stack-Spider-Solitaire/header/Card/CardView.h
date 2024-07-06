#pragma once
#include "../../header/UI/UIElement/ButtonView.h"
#include "../../header/UI/UIElement/ImageView.h"
#include <SFML/Graphics.hpp>


namespace Card
{
    class CardController;
    class CardData;

    class CardView
    {
    private:
        CardController* card_controller;

        float card_width;
        float card_height;

        UI::UIElement::ButtonView* card_button_view;
        UI::UIElement::ImageView* card_highlight;

        void initializeButton();
        void initializeImage();
        
        sf::String getCardTexturePath(CardData* card_type);

        void cardButtonCallback();


    public:
        CardView();
        ~CardView();

        void initialize(float width, float height, CardController* controller);
        void update();
        void render();

        void updateCardTexture();
        void setCardHighLight(bool b_highlight);
        void setCardPosition(sf::Vector2f card_position);

        

    };
}