#pragma once
#include "../../header/UI/UIElement/ImageView.h"

namespace Gameplay
{
    class LevelController;

    class LevelView
    {
    private:
        const float height_to_width_ratio = 1.37f;
        const float cards_horrizontal_spacing = 10;

        float card_width;
        float card_height;

        LevelController* level_controller;
        UIElement::ImageView* background_image;

        void createImage();
        void initializeImage();

        void calculateCardExtents();
        void destroy();

    public:
        LevelView();
        ~LevelView();

        void initialize(LevelController* controller);
        void update();
        void render();
    };
}