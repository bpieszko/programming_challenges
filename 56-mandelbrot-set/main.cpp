// STD
#include <iostream>
#include <complex>
#include <vector>
#include <chrono>
#include <functional>
#include <thread>
#include <stack>
#include <mutex>
#include <bitset>

// SFML
#include <SFML/Graphics.hpp>

// Own
#include "window.hpp"
#include "save_image.hpp"
#include "utils.hpp"
#include "config.hpp"

using Complex = std::complex<double>;

std::mutex image_mutex;

Complex scale(window<int> & scr, window<double> & fr, Complex c) {
	Complex aux(c.real() / (double)scr.width() * fr.width() + fr.x_min(), c.imag() / (double)scr.height() * fr.height() + fr.y_min());
	return aux;
}

int escape(Complex c, int iter_max, const std::function<Complex(Complex, Complex)> & func) {
	Complex z(0);
	int iter = 0;
	while (abs(z) < 2.0 && iter < iter_max) {
		z = func(z, c);
		++iter;
	}
	return iter;
}

void get_number_iterations(window<int> &scr, window<double> &fract, int iter_max, std::vector<int> &colors,
	const std::function<Complex( Complex, Complex)> &func) {
	int k = 0, progress = -1;
	for (int i = scr.y_min(); i < scr.y_max(); ++i) {
		for (int j = scr.x_min(); j < scr.x_max(); ++j) {
			Complex c((double)j, (double)i);
			c = scale(scr, fract, c);
			colors[k] = escape(c, iter_max, func);
			++k;
		}
	}
}

void fractal(window<int> & scr, window<double> & fract, int iter_max, std::vector<int> & colors,
	const std::function<Complex(Complex, Complex)> & func, const char * fname, bool smooth_color) {
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	plot(scr, colors, iter_max, fname, smooth_color);
}

void fillSprite(sf::Texture & texture, sf::Sprite & sprite) {
	texture.loadFromFile(FNAME);
	sprite.setTexture(texture);
}

void fillSelection(const sf::Vector2i & selection_start, const sf::Vector2i & selection_end, sf::RectangleShape & selection) {
	selection.setSize(sf::Vector2f(0, 0));
	selection.setFillColor(sf::Color::Transparent);
	selection.setOutlineColor(sf::Color::White);
	selection.setOutlineThickness(1);
	selection.setPosition(sf::Vector2f(selection_start.x, selection_start.y));
}

void fillApproximation(sf::Font & font, sf::Text & approximation) {
	try {
		if (!font.loadFromFile("International.ttf"))
			throw "Cannot load font file.";
		approximation.setFont(font);
		approximation.setString("1");
		approximation.setCharacterSize(APPROX_SIZE);
		approximation.setColor(sf::Color::White);
		approximation.setPosition(sf::Vector2f(APPROX_X, APPROX_Y));
	}
	catch (const std::string & e) {
		std::cerr << e << std::endl;
	}
}

void fillElements(sf::Texture & texture, sf::Sprite & sprite,
				  const sf::Vector2i & selection_start, const sf::Vector2i & selection_end, sf::RectangleShape & selection,
				  sf::Font & font, sf::Text & approximation) {
	fillSprite(texture, sprite);
	fillSelection(selection_start, selection_end, selection);
	fillApproximation(font, approximation);
}

void updateSprite(sf::Texture & texture, sf::Sprite & sprite, std::vector<bool> & flags) {
	if (image_mutex.try_lock()) {
		if (flags[1]) {
			std::cerr << "Trying to load image... ";
			texture.loadFromFile(FNAME);
			sprite.setTexture(texture);
			flags[1] = false;
			std::cerr << "ok" << std::endl;
		}
		image_mutex.unlock();
	}
}

void updateSelection(const sf::RenderWindow & render, const sf::Vector2i & selection_start, sf::RectangleShape & selection) {
	selection.setSize(sf::Vector2f(std::abs(sf::Mouse::getPosition(render).x - selection_start.x), std::abs(sf::Mouse::getPosition(render).y - selection_start.y)));
	selection.setPosition(sf::Vector2f(std::min(selection_start.x, sf::Mouse::getPosition(render).x), std::min(selection_start.y, sf::Mouse::getPosition(render).y)));
}

void updateApproximation(sf::Text & approximation, const std::stack<std::tuple<double, double, double>> & zoom_coords) {
	approximation.setString(std::to_string(4.0 / std::get<2>(zoom_coords.top())));
}

void updateElements(const sf::RenderWindow & render,
					sf::Texture & texture, sf::Sprite & sprite,
					const sf::Vector2i & selection_start, const sf::Vector2i & selection_end, sf::RectangleShape & selection,
					sf::Text & approximation,
					const std::stack<std::tuple<double, double, double>> & zoom_coords,
					std::vector<bool> & flags) {
	updateSprite(texture, sprite, flags);
	updateSelection(render, selection_start, selection);
	updateApproximation(approximation, zoom_coords);
}

void beginSelection(sf::Vector2i & selection_start, std::vector<bool> & flags, const sf::RenderWindow & render) {
	selection_start = sf::Mouse::getPosition(render);
	flags[0] = true;
}

void endSelection(sf::Vector2i & selection_start, sf::Vector2i & selection_end, std::vector<bool> & flags, const sf::RenderWindow & render) {
	selection_end = sf::Mouse::getPosition(render);
	flags[0] = false;
}

void zoomIn(sf::Vector2i & selection_start, sf::Vector2i & selection_end, std::stack<std::tuple<double, double, double>> & zoom_coords) {
	try {
		if (selection_start.x < 0 || selection_start.x >= WIN_SIZE ||
			selection_start.y < 0 || selection_start.y >= WIN_SIZE)
			throw "Position of beginning of selection is outside window!";
		if (selection_end.x < 0 || selection_end.x >= WIN_SIZE ||
			selection_end.y < 0 || selection_end.y >= WIN_SIZE)
			throw "Position of end of selection is outside window!";

		double x0 = std::get<0>(zoom_coords.top());
		double y0 = std::get<1>(zoom_coords.top());
		double r  = std::get<2>(zoom_coords.top());

		double new_x0 = x0 + r * selection_start.x / WIN_SIZE;
		double new_y0 = y0 - r * selection_start.y / WIN_SIZE;

		double tmp = x0 + r * selection_end.x / WIN_SIZE;
		r = tmp - new_x0;

		zoom_coords.push({new_x0, new_y0, r});
	}
	catch (const std::string & e) {
		std::cerr << e << std::endl;
	}
}

void zoomOut(std::stack<std::tuple<double, double, double>> & zoom_coords) {
	if (zoom_coords.size() > 1)
		zoom_coords.pop(); 
}

void threadRenderImage(const double a, const double z, const double r, std::vector<bool> & flags) {
	std::cerr << "Trying to render image... ";
	window<int> scr(0, WIN_SIZE, 0, WIN_SIZE);
	window<double> fract(a, a + r, z - r, z);

	auto func = [](Complex z, Complex c) -> Complex { return z * z + c; };
	std::vector<int> colors(scr.size());

	image_mutex.lock();
	fractal(scr, fract, MAX_ITER, colors, func, FNAME, SMOOTH);
	image_mutex.unlock();
	flags[1] = true;
	std::cerr << "ok" << std::endl;
	std::cerr << "    a=" << a << " z=" << z << " r=" << r << std::endl;
}

void renderImage(std::stack<std::tuple<double, double, double>> & zoom_coords, std::vector<bool> & flags) {
	std::thread t(threadRenderImage, std::get<0>(zoom_coords.top()), std::get<1>(zoom_coords.top()), std::get<2>(zoom_coords.top()), std::ref(flags));
	t.detach();
}

int main () {
	sf::RenderWindow render(sf::VideoMode(WIN_SIZE, WIN_SIZE), TITLE, sf::Style::Close);
	render.setFramerateLimit(60);

	std::vector<bool> flags(2, false);
	std::stack<std::tuple<double, double, double>> zoom_coords;
	zoom_coords.push({-2, 2, 4});

	std::mutex image_mutex;

	sf::Texture 		texture;
	sf::Sprite			sprite;
	sf::Vector2i		selection_start;
	sf::Vector2i		selection_end;
	sf::RectangleShape	selection;
	sf::Font			font;
	sf::Text 			approximation;
	sf::Event			event;

	fillElements(texture, sprite, selection_start, selection_end, selection, font, approximation);

	renderImage(zoom_coords, flags);

	while (render.isOpen()) {
		while (render.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					render.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Escape:
							render.close();
							break;
						default:
							break;
					}
					break;
				case sf::Event::MouseButtonPressed:
					switch (event.mouseButton.button) {
						case sf::Mouse::Button::Left:
							beginSelection(selection_start, flags, render);
							break;
						case sf::Mouse::Button::Right:
							zoomOut(zoom_coords);
							break;
						default:
							break;
					}
					break;
				case sf::Event::MouseButtonReleased:
					switch (event.mouseButton.button) {
						case sf::Mouse::Button::Left:
							endSelection(selection_start, selection_end, flags, render);
							zoomIn(selection_start, selection_end, zoom_coords);
							renderImage(zoom_coords, flags);
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		updateElements(render, texture, sprite, selection_start, selection_end, selection, approximation, zoom_coords, flags);
		
		render.clear();
		render.draw(sprite);
		if (flags[0])
			render.draw(selection);
		render.draw(approximation);
		render.display();
	}
	return 0;
}