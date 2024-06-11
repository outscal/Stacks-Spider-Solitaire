#include "../../header/Gameplay/LevelView.h"
#include "../../header/Gameplay/LevelModel.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Gameplay/LevelController.h"
#include "../../header/Card/CardController.h"
#include <vector>
#include <iostream>

namespace Gameplay
{
	using namespace UI::UIElement;
	using namespace Global;
	using namespace Card;

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
		initializeBackgroudImage();
	}

	void LevelView::createImage()
	{
		background_image = new ImageView();
	}

	void LevelView::initializeBackgroudImage()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

		background_image->initialize(Config::level_background_texture_path, 
									game_window->getSize().x, 
									game_window->getSize().y, 
									sf::Vector2f(0,0));

		background_image->setImageAlpha(background_alpha);
	}

	void LevelView::update()
	{
		background_image->update();
		updatePlayStacksView();
		updateSolutionStacksView();
		updateDrawingStackView();
	}

	void LevelView::render()
	{
		background_image->render();
		renderPlayStacks();
		renderSolutionStacks();
		renderDrawnigStack();
	}

	void LevelView::updatePlayStacksView() 
	{ 
		for (float i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			if (level_controller->getPlayStacks()[i]->isEmpty()) continue;

			float x_position = (i * ServiceLocator::getInstance()->getCardService()->getCardWidth()) + ((i + 1) * cards_horrizontal_spacing);
			float y_position = play_deck_top_offset;

			CardController* card_controller = level_controller->getPlayStacks()[i]->peek();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			card_controller->update();
		}
	}

	void LevelView::updateSolutionStacksView() 
	{
		for (float i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->isEmpty()) continue;

			float x_position = solution_deck_left_offset + (i * solution_deck_spacing);
			float y_position = solution_deck_top_offset;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->setCardPosition(sf::Vector2f(x_position, y_position));
			card_controller->update();
		}
	}

	void LevelView::updateDrawingStackView() 
	{ 
		if (level_controller->getDrawingStack()->isEmpty()) return;

		CardController* card_controller = level_controller->getDrawingStack()->peek();
		card_controller->setCardPosition(sf::Vector2f(drawing_deck_left_offset, drawing_deck_top_offset));
		card_controller->update();
	}

	void LevelView::renderPlayStacks()
	{
		for (int i = 0; i < LevelModel::number_of_play_stacks; i++)
		{
			if (level_controller->getPlayStacks()[i]->isEmpty()) continue;

			CardController* card_controller = level_controller->getPlayStacks()[i]->peek();

			card_controller->render();
		}
	}

	void LevelView::renderSolutionStacks()
	{
		for (int i = 0; i < LevelModel::number_of_solution_stacks; i++)
		{
			if (level_controller->getSolutionStacks()[i]->isEmpty()) continue;

			CardController* card_controller = level_controller->getSolutionStacks()[i]->peek();
			card_controller->render();
		}
	}

	void LevelView::renderDrawnigStack()
	{
		if (level_controller->getDrawingStack()->isEmpty()) return;

		CardController* card_controller = level_controller->getDrawingStack()->peek();
		card_controller->render();
	}

	float LevelView::getTotalCardSpacingWidth()
	{
		return (LevelModel::number_of_play_stacks + 1)* cards_horrizontal_spacing;
	}

	void LevelView::destroy()
	{
		delete (background_image);
	}
}