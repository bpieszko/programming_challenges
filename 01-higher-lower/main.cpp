#include <iostream>
#include <string>
#include <sys/time.h>

int main () {
	struct timeval time;
	gettimeofday(&time, 0);
	srand(time.tv_sec * 1000 + time.tv_usec % 1000);

	int correct = 1 + rand() % 1000000;
	int counter = 0;

	int n;

	std::cout << "Guess number (1, 1000000): ";
	do {
		++counter;
		std::cin >> n;
		if (n < correct)
			std::cout << "Higher: ";
		if (n > correct)
			std::cout << "Lower: ";
	} while (correct != n);

	std::cout << "Shots: " << counter << std::endl;

	return 0; 
}