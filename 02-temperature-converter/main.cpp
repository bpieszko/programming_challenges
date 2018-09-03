#include <iostream>
#include <string>
#include <map>

int main () {
	std::string from, to;
	double n;

	std::cout << "From (C|F|K|R|De|N|Re|Ro): ";
	std::cin >> from;
	std::cout << "Number: ";
	std::cin >> n;
	std::cout << "To (C|F|K|R|De|N|Re|Ro): ";
	std::cin >> to;

	std::map<std::string, double(*)(const double)> from_C;
	from_C["C"] = [](const double n) -> double { return n; };
	from_C["F"] = [](const double n) -> double { return n * 9 / 5 + 32; };
	from_C["K"] = [](const double n) -> double { return n + 273.15; };
	from_C["R"] = [](const double n) -> double { return (n + 273.15) * 9 / 5; };
	from_C["De"] = [](const double n) -> double { return (100 - n) * 3 / 2; };
	from_C["N"] = [](const double n) -> double { return n * 33 / 100; };
	from_C["Re"] = [](const double n) -> double { return n * 4 / 5; };
	from_C["Ro"] = [](const double n) -> double { return n * 21 / 40 + 7.5; };

	std::map<std::string, double(*)(const double)> to_C;
	to_C["C"] = [](const double n) -> double { return n; };
	to_C["F"] = [](const double n) -> double { return (n - 32) * 5 / 9; };
	to_C["K"] = [](const double n) -> double { return n - 273.15; };
	to_C["R"] = [](const double n) -> double { return (n - 491.67) * 5 / 9; };
	to_C["De"] = [](const double n) -> double { return 100 - n * 2 / 3; };
	to_C["N"] = [](const double n) -> double { return n * 100 / 33; };
	to_C["Re"] = [](const double n) -> double { return n * 5 / 4; };
	to_C["Ro"] = [](const double n) -> double { return (n - 7.5) * 40 / 21; };

	std::cout << "Result: " << from_C[to](to_C[from](n)) << " " << to << std::endl;

	return 0;
}