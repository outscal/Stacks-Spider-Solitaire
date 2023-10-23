#pragma once
#include "../../header/UI/UIElement/ButtonView.h"
#include "../../header/UI/UIElement/ImageView.h"

namespace Card
{
    class CardController;

    class CardView
    {
    private:
        CardController* card_controller;

        float card_width;
        float card_height;

        UIElement::ButtonView* card_button_view;
        UIElement::ImageView* card_highlight;

        void initializeButton();
        void initializeImage();

        void updateCardView();
        void registerButtonCallback();
        void cardButtonCallback();
        sf::String getCardTexturePath();

    public:
        CardView();
        ~CardView();

        void initialize(float width, float height, CardController* controller);
        void update();
        void render();

        void updateCardTexture();
        void setCardHighLight(bool b_highlight);
    };
}