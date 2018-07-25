#include <SFML/Graphics.hpp>
#include <iostream>
#include <sys/time.h>

#define IMG_SIZE 1000
#define SIZE 200
#define SPACE 3

bool is_prime(int value) {
	for (int i = 2; i * i <= value; ++i)
		if (value % i == 0)
			return false;
	return true;
}

inline int r(const int a, const int b) { return a + rand() % (b - a + 1); }

void draw(sf::Image& img, const int size, const int x, const int y) {
	if (size == 1) {
		img.setPixel(x, y, sf::Color::White);
	}
	else if (size == 2) {
		img.setPixel(x, y, sf::Color::White);
		img.setPixel(x + 1, y, sf::Color::White);
		img.setPixel(x - 1, y, sf::Color::White);
		img.setPixel(x, y + 1, sf::Color::White);
		img.setPixel(x, y - 1, sf::Color::White);
	}
	else if (size == 3) {
		img.setPixel(x, y, sf::Color::White);
		img.setPixel(x + 1, y, sf::Color::White);
		img.setPixel(x - 1, y, sf::Color::White);
		img.setPixel(x, y + 1, sf::Color::White);
		img.setPixel(x, y - 1, sf::Color::White);

		img.setPixel(x + 1, y + 1, sf::Color::White);
		img.setPixel(x - 1, y + 1, sf::Color::White);
		img.setPixel(x + 1, y - 1, sf::Color::White);
		img.setPixel(x - 1, y - 1, sf::Color::White);

		img.setPixel(x + 2, y, sf::Color::White);
		img.setPixel(x - 2, y, sf::Color::White);
		img.setPixel(x, y + 2, sf::Color::White);
		img.setPixel(x, y - 2, sf::Color::White);
	}
}

int main()
{
	struct timeval time;
	gettimeofday(&time, 0);
	srand(time.tv_sec * 1000 + time.tv_usec % 1000);

	int x = 0, y = 0;
    sf::Image img;
   	img.create(IMG_SIZE, IMG_SIZE, sf::Color::Black);

  	int a[SIZE][SIZE];

   	int i, k = 0, l = 0, index = 1;
   	int n = SIZE, m = SIZE;

   	while (k < m && l < n) {
   		for (i = l; i < n; ++i)
   			a[k][i] = index++;
   		++k;
   		for (i = k; i < m; ++i)
   			a[i][n - 1] = index++;
   		n--;
   		if (k < m) {
   			for (i = n - 1; i >= l; --i)
   				a[m - 1][i] = index++;
   			--m;
   		}
   		if (l < n) {
   			for (i = m - 1; i >= k; --i)
   				a[i][l] = index++;
   			l++;
   		}
   	}

   	for (int i = 0; i < SIZE; ++i, x += SPACE) {
   		y = 0;
   		for (int j = 0; j < SIZE; ++j, y += SPACE) {
   			if (is_prime(a[i][j])) {
   				int v = r(1, 100);
   				if (v <= 90)
   					draw(img, 1, i + IMG_SIZE / 2 - SIZE * (SPACE + 1) / 2 + x, j + IMG_SIZE / 2 - SIZE * (SPACE + 1) / 2 + y);
   				else if (v <= 98)
   					draw(img, 2, i + IMG_SIZE / 2 - SIZE * (SPACE + 1) / 2 + x, j + IMG_SIZE / 2 - SIZE * (SPACE + 1) / 2 + y);
   				else
   					draw(img, 3, i + IMG_SIZE / 2 - SIZE * (SPACE + 1) / 2 + x, j + IMG_SIZE / 2 - SIZE * (SPACE + 1) / 2 + y);
   			}
   		}
   	}

   	if (!img.saveToFile("result.png"))
   		return -1;
   	
    return 0;
}