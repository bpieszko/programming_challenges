#include <iostream>
#include <SFML/Graphics.hpp>
#include <sys/time.h>

inline int r(const int a, const int b) { return a + rand() % (b - a + 1); }

int main () {
	struct timeval time;
	gettimeofday(&time, 0);
	srand(time.tv_sec * 1000 + time.tv_usec % 1000);

	sf::Image img;
	img.create(400, 400);
	for (int i = 0; i < 400; ++i) {
		for (int j = 0; j < 400; ++j) {
			img.setPixel(i, j, sf::Color(r(0, 255), r(0, 255), r(0, 255)));
		}
	}
	img.saveToFile("output.jpg");

	return 0;
}