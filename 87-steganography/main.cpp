#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>

using uint = unsigned;


const std::vector<uint> color_bit{0, 1, 8, 9, 16, 17, 24, 25};

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
			uint color = image.getPixel(x, y).toInteger();
			for (int i = 0; i < 8; ++i)
				(data[it_data] & (1 << i)) ? color |= (1 << (color_bit[i])) : color &= ~(1 << (color_bit[i]));
			image.setPixel(x, y, sf::Color(color));
			++x;
			if (x >= max_x) {
				x = 0;
				y++;
				if (y >= max_y) {
					std::cout << "Error: Data length is too long or image is too small." << std::endl;
					return 1;
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
		bool read_flag = false;

		for (uint y = 0; y < max_y; ++y) {
			for (uint x = 0; x < max_x; ++x) {
				std::bitset<8> bit_c;
				uint color = image.getPixel(x, y).toInteger();
				for (int i = 0; i < 8; ++i)
					if (color & (1 << color_bit[i])) 
						bit_c.set(i);
				unsigned long l = bit_c.to_ulong();
				unsigned char c = static_cast<unsigned char>(l);
				if (c == '~')
					read_flag ^= 1;
				else if (read_flag)
					data += c;
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