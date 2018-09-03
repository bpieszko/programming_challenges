#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <set>
#include <sys/time.h>

inline int r(int a, int b) { return a + rand() % (b - a + 1); }

int main () {
	struct timeval time;
	gettimeofday(&time, 0);
	srand(time.tv_sec * 1000 + time.tv_usec % 1000);

	sf::RenderWindow window(sf::VideoMode(600, 400), "Snake", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	std::vector<sf::RectangleShape> snake(1);
	snake[0].setSize(sf::Vector2f(10, 10));
	snake[0].setOutlineColor(sf::Color::Black);
	snake[0].setOutlineThickness(1);
	snake[0].setFillColor(sf::Color::White);
	snake[0].setPosition(300, 200);

	sf::RectangleShape apple;
	apple.setSize(sf::Vector2f(10, 10));
	apple.setOutlineColor(sf::Color::Black);
	apple.setOutlineThickness(1);
	apple.setFillColor(sf::Color::Green);
	apple.setPosition(r(0, 59)*10, r(0, 39)*10);

	#define LEFT std::pair<int, int>{-10, 0}
	#define RIGHT std::pair<int, int>{10, 0}
	#define UP std::pair<int, int>{0, -10}
	#define DOWN std::pair<int, int>{0, 10}

	std::pair<int, int> direction = RIGHT;

	std::deque<std::pair<int, int>> directions;

	std::deque<std::pair<sf::Vector2f, int>> awaiting_snake;

	int time_cnt = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Up:
							if (direction != DOWN)
								direction = UP;
							break;
						case sf::Keyboard::Down:
							if (direction != UP)
								direction = DOWN;
							break;
						case sf::Keyboard::Left:
							if (direction != RIGHT)
								direction = LEFT;
							break;
						case sf::Keyboard::Right:
							if (direction != LEFT)
								direction = RIGHT;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		if (apple.getPosition() == snake[0].getPosition()) {			
			awaiting_snake.push_back({snake.front().getPosition(), (time_cnt + snake.size() + awaiting_snake.size()) % 1000000007});
			apple.setPosition(r(0, 59)*10, r(0, 39)*10);
		}

		while (!awaiting_snake.empty() && awaiting_snake.front().second <= time_cnt) {
			snake.push_back(sf::RectangleShape());
			snake.back().setSize(sf::Vector2f(10, 10));
			snake.back().setOutlineColor(sf::Color::Black);
			snake.back().setOutlineThickness(1);
			snake.back().setFillColor(sf::Color::White);
			snake.back().setPosition(awaiting_snake.front().first);
			awaiting_snake.pop_front();
		}

		directions.push_front(direction);
		while (directions.size() > snake.size())
			directions.pop_back();

		std::set<std::pair<int, int> > s;
		for (int i = 0; i < directions.size(); ++i) {
			snake[i].setPosition(snake[i].getPosition().x + directions[i].first, snake[i].getPosition().y + directions[i].second);
			if (snake[i].getPosition().x < 0)
				snake[i].setPosition(590, snake[i].getPosition().y);
			if (snake[i].getPosition().x > 590)
				snake[i].setPosition(0, snake[i].getPosition().y);
			if (snake[i].getPosition().y < 0)
				snake[i].setPosition(snake[i].getPosition().x, 390);
			if (snake[i].getPosition().y > 390)
				snake[i].setPosition(snake[i].getPosition().x, 0);
			if (s.find({snake[i].getPosition().x, snake[i].getPosition().y}) != s.end())
				return 0;
			s.insert({snake[i].getPosition().x, snake[i].getPosition().y});
		}

		window.clear();
		window.draw(apple);
		for (auto i : snake)
			window.draw(i);
		window.display();

		sf::sleep(sf::milliseconds(80));

		time_cnt = (time_cnt + 1) % 1000000007;
	}

	return 0;
}