#pragma once
#include "../../header/UI/UIElement/ButtonView.h"

namespace Card
{
    class CardController;

    class CardView
    {
    private:
        const float normal_alpha = 255.f;
        const float highlighted_alpha = 200.f;

        CardController* card_controller;

        float card_width;
        float card_height;

        UIElement::ButtonView* card_button_view;

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