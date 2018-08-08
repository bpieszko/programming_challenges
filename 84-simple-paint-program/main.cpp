#include <iostream>
#include <SFML/Graphics.hpp>

void paint(sf::Image & canvas, int x, int y, int r, sf::Color color) {
	for (int b = std::max(y - r, 0); b < y + r && b < 600; ++b)
		for (int a = std::max(x - r, 0); a < x + r && a < 800; ++a)
			if ((a - x) * (a - x) + (b - y) * (b - y) <= r * r)
				canvas.setPixel(a, b, color);
}

int main () {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Paint Program", sf::Style::Titlebar | sf::Style::Close);
	window.setMouseCursorVisible(false);

	sf::Image canvas;
	canvas.create(800, 700, sf::Color::White);

	sf::CircleShape cursor;
	cursor.setRadius(1);
	cursor.setFillColor(sf::Color::Black);

	int bPaint = 0;

	while (window.isOpen()) {
		cursor.setPosition(sf::Mouse::getPosition(window).x - cursor.getRadius(), sf::Mouse::getPosition(window).y - cursor.getRadius());
		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (event.key.code == sf::Keyboard::Add)
					cursor.setRadius(std::min((int)cursor.getRadius() + 1, 50));
				else if (event.key.code == sf::Keyboard::Subtract)
					cursor.setRadius(std::max((int)cursor.getRadius() - 1, 1));
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					bPaint |= 1;
				if (event.mouseButton.button == sf::Mouse::Button::Right)
					bPaint |= 2;
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					bPaint &= ~1;
				else if (event.mouseButton.button == sf::Mouse::Button::Right)
					bPaint &= ~2;
			}
		}

		if (bPaint & 1)
			paint(canvas, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, cursor.getRadius(), sf::Color::Black);
		else if (bPaint & 2)
			paint(canvas, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, cursor.getRadius(), sf::Color::White);

		sf::Texture texture;
		texture.loadFromImage(canvas);
		sf::Sprite sprite(texture);
		sprite.setPosition(0, 0);

		window.clear();
		window.draw(sprite);
		window.draw(cursor);
		window.display();
	}

	return 0;
}