#include <iostream>
#include <SFML/Graphics.hpp>

int main (int argc, char * argv[]) {
	if (argc != 2) {
		std::cout << "Usage: ./app.e image.jpg" << std::endl;
		return 1;
	}

	sf::Texture texture;
	if (!texture.loadFromFile(argv[1])) {
		std::cout << "Cannot open file!" << std::endl;
		return 1;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::RenderWindow window(sf::VideoMode(texture.getSize().x, texture.getSize().y), "Image viewer", sf::Style::Titlebar | sf::Style::Close);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
		
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}