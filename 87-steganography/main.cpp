#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using uint = unsigned;

int main (int argc, char ** argv) {
	if (argc == 1 || (argv[1] != std::string("--encode") && argv[1] != std::string("--decode")) || 
		(argv[1] == "--encode" && argc != 5) ||
		(argv[1] == "--decode" && argc != 4)) {
		std::cout << "Usage:" << std::endl;
		std::cout << "    to encode: ./app.e --encode image.png data.txt output.png" << std::endl;
		std::cout << "    to decode: ./app.e --decode image.png output.txt" << std::endl;
		return 1;
	}

	if (argv[1] == std::string("--encode")) {
		std::string data;

		data += " ~";

		std::ifstream istr_data(argv[3]);
		if (istr_data.is_open()) {
			std::string line;
			while (std::getline(istr_data, line))
				data += line + "\n";
			istr_data.close();
			data += "~";
		}
		else {
			std::cout << "Error: Cannot open data file." << std::endl;
			return 1;
		}

		sf::Image image;
		image.loadFromFile(argv[2]);

		const uint max_x = image.getSize().x;
		const uint max_y = image.getSize().y;

		uint x = 0, y = 0;

		for (uint it_data = 0; it_data < data.size(); ++it_data) {
			for (uint bit = 1 << 7; bit > 0; bit >>= 1) {
				uint color = image.getPixel(x, y).toInteger();
				(data[it_data] & bit) ? color |= 1 << 7 : color &= ~(1 << 7);
				image.setPixel(x, y, sf::Color(color));
				x++;
				if (x >= max_x) {
					x = 0;
					y++;
					if (y >= max_y) {
						std::cout << "Error: Data length is too long or image is too small." << std::endl;
						return 1;
					}
				}
			}
		}
		image.saveToFile(argv[4]);
	}
	else { // --decode
		sf::Image image;
		image.loadFromFile(argv[2]);

		const uint max_x = image.getSize().x;
		const uint max_y = image.getSize().y;

		std::string data;

		uint cnt = 0;
		unsigned char c = 1;

		bool read = false;

		for (uint y = 0; y < max_y; ++y) {
			for (uint x = 0; x < max_x; ++x) {
				c |= (image.getPixel(x, y).toInteger() & (1 << 7)) >> cnt;
				cnt++;
				if (cnt > 8) {
					if (c == '~')
						read ^= 1;
					else if (read)
						data += (unsigned char)(c);

					cnt = 1;
					c = 0;
				}
			}
		}
		std::ofstream ostr_output(argv[3], std::ios::out);
		if (ostr_output.is_open()) {
			ostr_output << data;
			ostr_output.close();
		}
	}

	
	return 0;
}