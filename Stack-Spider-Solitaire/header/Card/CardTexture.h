#pragma once
#include "Card/CardConfig.h"
#include <SFML/Graphics.hpp>

namespace Card
{
	class CardTexture
	{
	  public:
		static sf::String getCardTexturePath(CardTypeEnum card_type, Rank rank, Suit suit, State state)
		{
			if (state == State::CLOSE)
			{
				return sf::String("assets/textures/cards/card_53.png");
			}

			if (card_type != Card::CardTypeEnum::DEFAULT)
			{
				switch (card_type)
				{
				case CardTypeEnum::SORT:
					return "assets/textures/cards/card_sort.png";

				case CardTypeEnum::VISION:
					return "assets/textures/cards/card_vision.png";

				case CardTypeEnum::SWAP:
					return "assets/textures/cards/card_swap.png";

				case CardTypeEnum::TIME:
					return "assets/textures/cards/card_time.png";

				case CardTypeEnum::DEFAULT:
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