#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow render(sf::VideoMode(512, 512), "Mandelbrot set", sf::Style::Titlebar | sf::Style::Close);	
	while (render.isOpen()) {
		//std::cout << sf::Mouse::getPosition(render).x << " " << sf::Mouse::getPosition(render).y << std::endl;
		sf::Event event;
		while (render.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				render.close();
		}

		
		render.clear();
		render.display();
	}
	return 0;
}