#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/time.h>

void lowercase(std::string& s)
{
	for (auto& i : s)
		if (i >= 'A' && i <= 'Z')
			i += 'a' - 'A';
}

void print_intro()
{
	std::cout << "Password generator - bpieszko" << std::endl;
	std::cout << "Written as a part of /g/'s programming challenges." << std::endl << std::endl;
}

char r(const int a, const int b)
{
	return (rand() % (b - a + 1)) + a;
}

std::vector<int> get_input()
{
	std::vector<int> options(4, 0);
	const std::vector<std::string> yesno_opt = {"y", "n", "yes", "no"};
	
	try
	{
		std::cout << "Input length of password (max 256): ";
		std::cin >> options[0];

		if (options[0] > 256 || options[0] <= 0)
		{
			std::cout << "Invalid length of password!" << std::endl;
			throw;
		}

		std::string tmp;
		std::cout << "Use uppercase letters [(y)es/(n)o]: ";
		std::cin >> tmp;
		lowercase(tmp);

		if (std::find(yesno_opt.begin(), yesno_opt.end(), tmp) == yesno_opt.end())
		{
			std::cout << "Invalid option for uppercase letters!" << std::endl;
			throw;
		}
		options[1] = (tmp == "y" || tmp == "yes") ? 1 : 0;

		std::cout << "How many numbers? (max " << options[0] << "): ";
		std::cin >> options[2];

		if (options[2] < 0 || options[2] > options[0])
		{
			std::cout << "Invalid number of numbers in password!" << std::endl;
			throw;
		}

		std::cout << "Use special characters [(y)es/(n)o]: ";
		std::cin >> tmp;
		lowercase(tmp);

		if (std::find(yesno_opt.begin(), yesno_opt.end(), tmp) == yesno_opt.end())
		{
			std::cout << "Invalid option for special characters!" << std::endl;
			throw;
		}
		options[3] = (tmp == "y" || tmp == "yes") ? 1 : 0;
	}
	catch (...)
	{
		options.clear();
	}
	return options;
}

std::string generator(const std::vector<int>& options)
{
	std::string password(options[0], 0);
	const std::vector<char> specials = {',', '.', '<', '>', '?', ';', ':', '\'', '\"', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '`', '~', '[', ']', '{', '}'};
	int i;
	for (i = 0; i < options[2]; i++)
		password[i] = r('0', '9');
	for (; i < options[0]; i++)
	{
		int x = r(0, 2);
		if (x == 0)
			password[i] = r('a', 'z');
		else if (x == 1 && options[1])
			password[i] = r('A', 'Z');
		else if (x == 2 && options[3])
			password[i] = specials[r(0, specials.size() - 1)];
		else
			i--;
	}
	std::random_shuffle(password.begin(), password.end());
	return password;
}


int main ()
{
	struct timeval time;
	gettimeofday(&time, 0);
	srand(time.tv_sec * 1000 + time.tv_usec % 1000);
	
	print_intro();
	std::vector<int> options = get_input();
	if (options.empty())
		return 1;

	std::cout << generator(options) << std::endl;
	return 0;
}