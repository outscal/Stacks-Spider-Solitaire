#pragma once
#include "../../header/UI/UIElement/ButtonView.h"

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

        sf::String getCardTexturePath(CardData* card_type);
        void initializeButton();
        void cardButtonCallback();

    public:
        CardView();
        ~CardView();

        void initialize(float width, float height, CardController* controller);
        void update();
        void render();

        void updateCardTexture();
    };
}