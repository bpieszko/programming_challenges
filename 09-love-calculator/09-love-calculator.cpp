#include <iostream>
#include <vector>
#include <algorithm>

void print_intro()
{
	std::cout << "Love calculator - bpieszko" << std::endl;
	std::cout << "Written as a part of /g/'s programming challenges." << std::endl << std::endl;
}


const long long prime = 31;
const long long mod = 1000000007;

int hash(const std::string& s)
{
	long long result = 0;
	for (auto i : s)
		result = (result + prime * (i - (i >= 'a') ? 'a' : 'A')) % mod;
	return result;
}

int main ()
{
	print_intro();

	std::string first_name, second_name;
	std::cout << "Enter first name: ";
	std::cin >> first_name;
	std::cout << "Enter second name: ";
	std::cin >> second_name;

	const int love = (hash(first_name) ^ hash(second_name)) % 101;

	if(love > 90)
		std::cout << "Wow! That's a lot of love! (" << love << ")" << std::endl;
	else if(love > 70)
		std::cout << "That's quite a lot of love! (" << love << ")" << std::endl;
	else if(love > 50)
		std::cout << "It's still quite a bunch. (" << love << ")" << std::endl;
	else if(love > 30)
		std::cout << "It's still love after all. (" << love << ")" << std::endl;
	else if(love > 10)
		std::cout << "It could have been better... (" << love << ")" << std::endl;
	else
		std::cout << "Oh... (" << love << ")" << std::endl;

	return 0;
}