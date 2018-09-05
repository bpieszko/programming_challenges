#include <iostream>
#include <string>
#include <stack>

bool isNumber(const std::string & s) {
	for (auto i : s)
		if ((i < '0' || i > '9') && i != '.')
			return false;
	return true;
}

int main () {
	std::stack<double> s;

	std::string str;
	while (std::cin >> str) {
		if (isNumber(str))
			s.push(std::stod(str));
		else {
			double a = s.top(); s.pop();
			double b = s.top(); s.pop();
			if (str == "+")
				s.push(b + a);
			else if (str == "-") 
				s.push(b - a);
			else if (str == "*")
				s.push(b * a);
			else if (str == "/")
				s.push(b / a);
		}
	}	

	std::cout << s.top() << std::endl;

	return 0;
}