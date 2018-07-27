#include "Block.hpp"

Block::Block(const unsigned x, const unsigned y) {
	BLOCK_SHAPES.resize(9);
	BLOCK_SHAPES[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
	BLOCK_SHAPES[1] = {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
	BLOCK_SHAPES[2] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
	BLOCK_SHAPES[3] = {{0, 0}, {1, 0}, {1, 1}};
	BLOCK_SHAPES[4] = {{0, 1}, {1, 0}, {1, 1}};
	BLOCK_SHAPES[5] = {{0, 0}};
	BLOCK_SHAPES[6] = {{0, 0}, {1, 0}};
	BLOCK_SHAPES[7] = {{0, 0}, {1, 0}, {2, 0}};
	BLOCK_SHAPES[8] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};

	struct timeval time;
	gettimeofday(&time, 0);
	srand(time.tv_sec * 1000 + time.tv_usec % 1000);

	position = {x, y};
	color = BLOCK_COLORS[random(0, BLOCK_COLORS.size() - 1)];
	tiles = BLOCK_SHAPES[random(0, BLOCK_SHAPES.size() - 1)];
}

unsigned Block::destroyBottomLayer() {
	unsigned mostBottomLayer = 0;
	unsigned count = 0;
	for (std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		mostBottomLayer = std::max(mostBottomLayer, it->position.y);
	}
	for (std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		if (it->position.y == mostBottomLayer) {
			tiles.erase(it);
			++count;
		}
	}
	return count;
}

bool Block::isOnTop() const {
	for (const auto & tile : tiles)
		if (tile.position.y + position.y == 0)
			return true;
	return false;
}

void Block::draw(sf::RenderWindow & window) {
	for (const auto & tile : tiles) {
		sf::RectangleShape sf_tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));

		sf_tile.setPosition(position.x + TILE_SIZE * tile.position.x, position.y + TILE_SIZE * tile.position.y);
		sf_tile.setFillColor(color);
		sf_tile.setOutlineColor(TILE_OUT_COLOR);
		sf_tile.setOutlineThickness(1);
		window.draw(sf_tile);
	}
}

void Block::moveLeft() {
	position.x -= (position.x >= TILE_SIZE) ? TILE_SIZE : 0;
}

void Block::moveRight() {
	unsigned tmp = 0;
	for (auto & i : tiles)
		tmp = std::max(tmp, i.position.x);
	position.x += (position.x < BOARD_WIDTH - TILE_SIZE - TILE_SIZE * tmp) ? TILE_SIZE : 0;
}

void Block::moveDown() {
	unsigned tmp = 0;
	for (auto & i : tiles)
		tmp = std::max(tmp, i.position.y);
	position.y += (position.y < BOARD_HEIGHT - TILE_SIZE - TILE_SIZE * tmp) ? TILE_SIZE : 0;
}