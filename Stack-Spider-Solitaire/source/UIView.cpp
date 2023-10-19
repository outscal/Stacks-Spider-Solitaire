#include "../header/UIView.h"
#include "../header/ServiceLocator.h"
#include "../header/GraphicService.h"

UIView::UIView() = default;

UIView::~UIView() = default;

void UIView::initialize()
{
	game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
	ui_state = UIState::VISIBLE;
}

void UIView::update() { }

void UIView::render() { }

void UIView::show()
{
	ui_state = UIState::VISIBLE;
}

void UIView::hide()
{
	ui_state = UIState::HIDDEN;
}