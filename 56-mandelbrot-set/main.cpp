#include <iostream>
#include <complex>
#include <vector>
#include <chrono>
#include <functional>
#include <SFML/Graphics.hpp>
#include <thread>

#include "window.hpp"
#include "save_image.hpp"
#include "utils.hpp"

using Complex = std::complex<double>;

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
		if (progress < (int)(i * 100.0 / scr.y_max())) {
			progress = (int)(i * 100.0 / scr.y_max());
			//std::cout << progress << "%" << std::endl;
		}
	}
}

void fractal(window<int> & scr, window<double> & fract, int iter_max, std::vector<int> & colors,
	const std::function<Complex(Complex, Complex)> & func, const char * fname, bool smooth_color) {
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	//std::cout << "Time to generate " << fname << " = " << std::chrono::duration<double, std::milli> (end - start).count() << "[ms]" << std::endl;

	plot(scr, colors, iter_max, fname, smooth_color);
}

void f_thread() {
	int iter_max1 = 5000;
	const char *fname1 = "mandelbrot.png";
	bool smooth_color1 = true;
	window<int> scr1(0, 512, 0, 512);
	window<double> fract1(-2, 2, -2, 2);
	auto func1 = [](Complex z, Complex c) -> Complex { return z * z + c; };
	std::vector<int> colors1(scr1.size());
	fractal(scr1, fract1, iter_max1, colors1, func1, fname1, smooth_color1);
}


void f_thread2(sf::RenderWindow & ren, double & a, double & z, double & r, bool & ok) {
	while (ren.isOpen()) {
		int iter_max = 5000;
		const char *fname = "mandelbrot.png";
		bool smooth_color = true;

		window<int> scr(0, 512, 0, 512);
		window<double> fract(a, a + r, z - r, z);

		auto func = [](Complex z, Complex c) -> Complex { return z * z + c; };
		std::vector<int> colors(scr.size());
		if (ok == true)
			continue;
		else {
			ok = true;
			fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
			ok = false;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

double A = 0, B = 512, a = -2, b = 2, x, y, r, z;

int main () {
	sf::RenderWindow render(sf::VideoMode(512, 512), "Mandelbrot set", sf::Style::Titlebar | sf::Style::Close);
	render.setFramerateLimit(60);

	bool ok = false;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2i start, end;


	std::thread first(f_thread);
	first.join();

	a = -2;
	z = 2;
	r = 4;

	std::thread second(f_thread2, std::ref(render), std::ref(a), std::ref(z), std::ref(r), std::ref(ok));

	texture.loadFromFile("mandelbrot.png");
	sprite.setTexture(texture);
	bool pressed = false;
	while (render.isOpen()) {
		//std::cout << sf::Mouse::getPosition(render).x << " " << sf::Mouse::getPosition(render).y << std::endl;
		sf::Event event;
		while (render.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				render.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					render.close();
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					std::cout << "Pressed! ";
					std::cout << sf::Mouse::getPosition(render).x << " " << sf::Mouse::getPosition(render).y << std::endl;
					start = sf::Mouse::getPosition(render);
					pressed = true;
				}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					if (sf::Mouse::getPosition(render).x >= 0 && sf::Mouse::getPosition(render).x < 512 &&
						sf::Mouse::getPosition(render).y >= 0 && sf::Mouse::getPosition(render).x < 512 &&
						start.x >= 0 && start.x < 512 && start.y >= 0 && start.y < 512) {
						pressed = false;
						std::cout << "Released!" << std::endl;
						std::cout << start.x << " " << start.y << std::endl;
						std::cout << sf::Mouse::getPosition(render).x << " " << sf::Mouse::getPosition(render).y << std::endl;

						end = sf::Mouse::getPosition(render);

						double na = a + (b - a) * (double)start.x / (double)512;
						double nb = a + (b - a) * (double)end.x / (double)512;

						r = nb - na;

						z = z - (b - a) * (double)start.y / (double)512;

						a = na;
						b = nb;

						std::cout << "x: " << a << " " << a + r << " y: " << z - r << " " << z << std::endl;
					}
				}
			}
		}

		if (!ok) {
			ok = true;
			texture.loadFromFile("mandelbrot.png");
			sprite.setTexture(texture);
			ok = false;
		}

		sf::RectangleShape rect;
		if (pressed == true) {
			rect.setSize(sf::Vector2f(sf::Mouse::getPosition(render).x - start.x, sf::Mouse::getPosition(render).y - start.y));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::White);
			rect.setOutlineThickness(1);
			rect.setPosition(start.x, start.y);
		}

		render.clear();
		render.draw(sprite);
		render.draw(rect);
		render.display();
	}

	second.join();

	return 0;
}