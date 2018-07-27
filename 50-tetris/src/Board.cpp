#include "Board.hpp"
#include <iostream>

Board::Board() {
	paused = false;
	result = 0;
	bottomLayerPosition.resize(BOARD_WIDTH / TILE_SIZE, BOARD_HEIGHT);
}

void Board::pause() {
	paused = true;
}

void Board::resume() {
	paused = false;	
}

bool Board::isPaused() {
	return paused;
}

void Board::restart() {
	moveable.clear();
	unmoveable.clear();
	paused = false;
	result = 0;
	bottomLayerPosition.clear();
}

void Board::destroyBottomLayer() {
	for (auto & block : unmoveable)
		result += block.destroyBottomLayer();
}

void Board::addBlock(const unsigned x) {
	moveable.push_back(Block(x, 0));
}

unsigned Board::getResult() {
	return result;
}

bool Board::isOnTop() {
	for (const auto & block : unmoveable)
		if (block.isOnTop())
			return true;
	return false;
}

void Board::draw(sf::RenderWindow & window) {
	background.setSize(sf::Vector2f(BOARD_HEIGHT, BOARD_WIDTH));
	background.setFillColor(BOARD_BG_COLOR);
	background.setPosition(0, 0);

	window.draw(background);

	for (auto & block : unmoveable)
		block.draw(window);

	for (auto & block : moveable)
		block.draw(window);
}

bool Board::isMoveable() {
	return moveable.size() != 0;
}

void Board::nextTurn() {
	for (std::vector<Block>::iterator block = moveable.begin(); block != moveable.end(); ) {
		if (checkBlockPosition(*block)) {
			unmoveable.push_back(*block);
			updateBottomLayerPosition(*block);
			block = moveable.erase(block);
		}
		else {
			block->position.y += TILE_SIZE;
			++block;
		}
	}
}

bool Board::checkBlockPosition(Block & block) {
	for (auto & i : block.tiles) {
		if (block.position.y + i.position.y * TILE_SIZE + TILE_SIZE >= bottomLayerPosition[(block.position.x + i.position.x * TILE_SIZE) / TILE_SIZE])
			return true;
	}
	return false;
}

void Board::updateBottomLayerPosition(Block & block) {
	for (auto & i : block.tiles)
		bottomLayerPosition[(block.position.x + i.position.x * TILE_SIZE) / TILE_SIZE] =
			std::min(block.position.y + i.position.y * TILE_SIZE, 
					 bottomLayerPosition[(block.position.x + i.position.x * TILE_SIZE) / TILE_SIZE]);
}

void Board::moveLeft() {
	moveable.back().moveLeft();
}

void Board::moveRight() {
	moveable.back().moveRight();
}

void Board::moveDown() {
	moveable.back().moveDown();
}