#include "../../header/Gameplay/LevelView.h"
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GraphicService.h"
#include "../../header/Gameplay/LevelController.h"
#include <vector>

namespace Gameplay
{
	using namespace UIElement;
	using namespace Global;

	LevelView::LevelView()
	{
		createImage();
	}

	LevelView::~LevelView()
	{
		destroy();
	}

	void LevelView::initialize(LevelController* controller)
	{
		level_controller = controller;
		initializeImage();
	}

	void LevelView::createImage()
	{
		background_image = new ImageView();
	}

	void LevelView::initializeImage()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		background_image->initialize(Config::level_background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0,0));
	}

	void LevelView::update()
	{
		background_image->update();
	}

	void LevelView::render()
	{
		background_image->render();
	}

	void LevelView::calculateCardExtents()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		float total_width = game_window->getSize().x;
		float total_spacing_width = (LevelModel::number_of_play_stacks + 1) * cards_horrizontal_spacing;

		card_width = (total_width - total_spacing_width) / LevelModel::number_of_play_stacks;
		card_height = card_width * height_to_width_ratio;
	}

	void LevelView::destroy()
	{
		delete (background_image);
	}
}