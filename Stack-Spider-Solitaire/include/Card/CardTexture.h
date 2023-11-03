#pragma once
#include "Card/CardConfig.h"
#include <SFML/Graphics.hpp>

#include <stdexcept>

namespace Card
{
	class CardTexture
	{
	  public:
		static sf::String getCardTexturePath(Type card_type, Rank rank, Suit suit, State state)
		{
			if (state == State::CLOSE)
			{
				return sf::String("assets/textures/cards/card_53.png");
			}

			if (card_type != Card::Type::DEFAULT)
			{
				switch (card_type)
				{
				case Type::SORT:
					return "assets/textures/cards/card_sort.png";

				case Type::VISION:
					return "assets/textures/cards/card_vision.png";

				case Type::SWAP:
					return "assets/textures/cards/card_swap.png";

				case Type::TIME:
					return "assets/textures/cards/card_time.png";

				case Type::DEFAULT:
					throw std::logic_error("Impossible code path reached: CardTexture.h");
					break;

				default:
					break;
				};
			}

			int card_number = static_cast<int>(rank) + (static_cast<int>(suit) * number_of_ranks);
			sf::String path = "assets/textures/cards/card_" + std::to_string(card_number) + ".png";
			return path;
		}
	};
} // namespace Card