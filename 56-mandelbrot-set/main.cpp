#include <iostream>
#include <complex>
#include <vector>
#include <chrono>
#include <functional>

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
			std::cout << progress << "%" << std::endl;
		}
	}
}

void fractal(window<int> & scr, window<double> & fract, int iter_max, std::vector<int> & colors,
	const std::function<Complex(Complex, Complex)> & func, const char * fname, bool smooth_color) {
	auto start = std::chrono::steady_clock::now();
	get_number_iterations(scr, fract, iter_max, colors, func);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time to generate " << fname << " = " << std::chrono::duration<double, std::milli> (end - start).count() << "[ms]" << std::endl;

	plot(scr, colors, iter_max, fname, smooth_color);
}

void mandelbrot() {

	// CONFIG BEGIN

	double X, Y, R;
	X = -6.490308e-1;
	Y = -4.455151e-1;
	R = 1.7E-6;
	int iter_max = 550;
	const char *fname = "mandelbrot7.png";
	bool smooth_color = true;

	// CONFIG END

	window<int> scr(0, 512, 0, 512);
	window<double> fract(X, X + R, Y, Y + R);

	auto func = [](Complex z, Complex c) -> Complex { return z * z + c; };

	std::vector<int> colors(scr.size());

	fractal(scr, fract, iter_max, colors, func, fname, smooth_color);
}

int main () {
	mandelbrot();

	return 0;
}