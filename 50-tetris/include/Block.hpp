#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <sys/time.h>
#include "Utils.hpp"
#include "config.hpp"
#include "Board.hpp"

struct Position {
	unsigned x, y;
};

class Block {
private:
	struct Tile {
		Position position;
		Tile(const unsigned x, const unsigned y) {
			position = {x, y};
		}
	};
	
	std::vector<std::vector<Tile>> BLOCK_SHAPES;
	Position position;

	std::vector<Tile> tiles;

	// SFML
	sf::Color color;

public:
	Block() = delete;
	Block(const unsigned, const unsigned);
	
	unsigned destroyBottomLayer();
	bool isOnTop() const;

	void draw(sf::RenderWindow &);

	void moveLeft();
	void moveRight();
	void moveDown();

	friend class Board;
};

#endif // BLOCK_HPP