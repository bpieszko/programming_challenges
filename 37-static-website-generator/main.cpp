#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main (int argc, char * argv[]) {
	if (argc != 4){ 
		std::cout << "Usage: ./static_website_generator scheme.html data.txt website.html" << std::endl;
		return 1;
	}

	std::ifstream scheme_f;
	std::ifstream data_f;

	scheme_f.open(argv[1]);
	data_f.open(argv[2]);

	std::map<std::string, std::string> data_m;

	std::string line_s;
	while (std::getline(data_f, line_s)) {
		if (line_s[0] == '#')
			continue;
		std::string lhs_s, rhs_s;
		std::string::iterator line_it = line_s.begin();
		for (; *line_it != '='; ++line_it)
			lhs_s += *line_it;
		line_it++;
		for (; line_it != line_s.end(); ++line_it)
			rhs_s += *line_it;
		lhs_s = "[%" + lhs_s + "%]";
		data_m[lhs_s] = rhs_s;
	}

	data_f.close();

	std::ofstream website_f;
	website_f.open(argv[3]);

	while (std::getline(scheme_f, line_s)) {
		bool read = false;
		char prev_c = 0;
		std::string new_line_s, hash_s;
		for (std::string::iterator line_it = line_s.begin(); line_it != line_s.end(); ++line_it) {
			if (!read && prev_c == '[' && *line_it == '%')
				read = true;
			else if (read && prev_c == '%' && *line_it == ']') {
				new_line_s += data_m[hash_s + ']'];
				hash_s = "";
				read = false;
				continue;
			}
			if (read) {
				if (hash_s.empty())
					hash_s += '[';
				hash_s += *line_it;
			}
			else if (*line_it != '[' || (line_it + 1) == line_s.end() || *(line_it + 1) != '%')
				new_line_s += *line_it;
			prev_c = *line_it;
		}
		website_f << new_line_s << std::endl;
	}

	scheme_f.close();
	website_f.close();
	return 0;
}