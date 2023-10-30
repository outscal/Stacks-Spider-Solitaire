#pragma once
#include "Card/CardModel.h"
#include "Card/CardView.h"

namespace Card
{
	class CardController
	{
	  private:
		CardModel* card_model;
		CardView* card_view;

		bool card_follow_mouse{false};
		sf::Vector2f prev_card_position{0.0f, 0.0f};
		sf::Vector2f last_mouse_coord{0.0f, 0.0f};

		void updateCardVisibility();

	  public:
		CardController(Rank rank, Suit suit);
		~CardController();

		void initialize(float card_width, float card_height,
						float hide_duration = 0);
		void update();
		void render();

		CardType* getCardType();
		State getCardState();
		void setCardState(State card_state);

		sf::Vector2f getCardPosition() const;
		void setCardPosition(sf::Vector2f card_position);

		CardVisibility getCardVisibility();
		void hideCard(float duration);

		void followMouse();
		void stopFollowingMouse();

		bool shouldFollowMouse();
		void setModelPosition(const sf::Vector2f& pos);
	};
} // namespace Card