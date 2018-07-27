#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>

// board
#define BOARD_HEIGHT 	510
#define BOARD_WIDTH 	300
#define BOARD_BG_COLOR 	sf::Color::Black

#define TURN_TIME 		250 // as milliseconds
#define DRAW_TIME 		100 // as milliseconds

// tiles
#define TILE_SIZE 		30
#define TILE_OUT_COLOR	sf::Color::Black

// blocks

static const std::vector<sf::Color> BLOCK_COLORS = {
	sf::Color::Red,
	sf::Color::Green,
	sf::Color::Blue,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Cyan
	};

#endif // CONFIG_HPP