#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>

void print_intro()
{
	std::cout << "Calculate age in seconds with leap years - bpieszko" << std::endl;
	std::cout << "Written as a part of /g/'s programming challenges." << std::endl << std::endl;
}

int main ()
{
	print_intro();

	std::string birth_date;
	std::cout << "Enter your birth date (DD.MM.RRRR ex.: 01.01.1970): ";
	std::cin >> birth_date;

	int b_day = (birth_date[0] - '0') * 10 + birth_date[1] - '0';
	int b_mon = (birth_date[3] - '0') * 10 + birth_date[4] - '0';
	int b_yea = (birth_date[6] - '0') * 1000 + (birth_date[7] - '0') * 100 + (birth_date[8] - '0') * 10 + birth_date[9] - '0';

	struct tm timeinfo = {0};
	timeinfo.tm_mday = b_day;
	timeinfo.tm_mon = b_mon - 1;
	timeinfo.tm_year = b_yea - 1900;
	timeinfo.tm_isdst = -1;
	
	time_t birth_time = mktime(&timeinfo);
	time_t now_time = time(0);
	time_t in_seconds = now_time - birth_time;

	std::cout << in_seconds << std::endl; 

	return 0;
}