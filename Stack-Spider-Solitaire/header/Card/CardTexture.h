#pragma once
#include "Card/CardConfig.h"
#include <SFML/Graphics.hpp>

namespace Card
{
	class CardTexture
	{
	  public:
		static sf::String getCardTexturePath(Rank rank, Suit suit, State state)
		{
			if (state == State::CLOSE)
			{
				return sf::String("assets/textures/cards/card_53.png");
			}

			int card_number = static_cast<int>(rank) + (static_cast<int>(suit) * number_of_ranks);
			sf::String path = "assets/textures/cards/card_" + std::to_string(card_number) + ".png";
			return path;
		}
	};
} // namespace Card