#include <iostream>
#include <string>
#include <algorithm>

int main () {
	std::string s;
	std::cin >> s;
	std::reverse(s.begin(), s.end());
	std::cout << s;
	return 0;
}