#include <iostream>

int main () {
	int turns;
	std::cout << "Number of turns: ";
	std::cin >> turns;
	
	int i = 1;
	while (turns--) {
		if (i % 3 == 0) {
			std::cout << "Fizz";
			if (i % 5 == 0)
				std::cout << "Buzz";
		}
		else if (i % 5 == 0)
			std::cout << "Buzz";
		else
			std::cout << i;
		std::cout << std::endl;
		++i;
	}

	return 0;
}