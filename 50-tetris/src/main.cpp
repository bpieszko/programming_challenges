#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "config.hpp"
#include "Utils.hpp"

int main () {
	sf::RenderWindow window(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Tetris by bpieszko", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	Board board;

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;

		if (!board.isMoveable())
			board.addBlock(5);


		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Left:
							board.moveLeft();
							break;
						case sf::Keyboard::Right:
							board.moveRight();
							break;
						case sf::Keyboard::Down:
							board.moveDown();
							break;
						case sf::Keybaord::Space:
							board.rotate();
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		if (clock.getElapsedTime().asMilliseconds() >= TURN_TIME) {
			board.nextTurn();
			clock.restart();
		}

		window.clear(sf::Color::Black);
		board.draw(window);
		window.display();


		sf::sleep(sf::milliseconds(DRAW_TIME));
	}
	return 0;
}