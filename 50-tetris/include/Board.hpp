#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Utils.hpp"
#include "config.hpp"
#include "Block.hpp"

class Block;

class Board {
private:
	bool paused;
	unsigned result;
	
	std::vector<Block> unmoveable;
	std::vector<Block> moveable;

	std::vector<unsigned> bottomLayerPosition;
	// SFML
	sf::RectangleShape background;

public:
	Board();

	void pause();
	void resume();
	void restart();
	void destroyBottomLayer();
	void addBlock(const unsigned);
	void nextTurn();

	bool checkBlockPosition(Block &);
	void updateBottomLayerPosition(Block &);

	unsigned getResult();
	bool isPaused();
	bool isOnTop();
	bool isMoveable();

	void draw(sf::RenderWindow &);

	void moveLeft();
	void moveRight();
	void moveDown();
	void rotate();
};

#endif // BOARD_HPP