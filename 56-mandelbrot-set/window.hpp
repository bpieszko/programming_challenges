#ifndef WINDOW_HPP
#define WINDOW_HPP

template <typename T>
class window {
	T _x_min, _x_max, _y_min, _y_max;

public:
	window(T x_min, T x_max, T y_min, T y_max)
		: _x_min(x_min), _x_max(x_max), _y_min(y_min), _y_max(y_max)
	{}

	T size() const {
		return (width() * height());
	}

	T width() const {
		return (_x_max - _x_min);
	}

	T height() const {
		return (_y_max - _y_min);
	}

	T x_min() const {
		return _x_min;
	}

	void x_min(T x_min) {
		_x_min = x_min;
	}

	T x_max() const {
		return _x_max;
	}

	void x_max(T x_max) {
		_x_max = x_max;
	}		

	T y_min() const {
		return _y_min;
	}

	void y_min(T y_min) {
		_y_min = y_min;
	}		

	T y_max() const {
		return _y_max;
	}

	void y_max(T y_max) {
		_y_max = y_max;
	}

	void reset(T x_min, T x_max, T y_min, T y_max) {
		_x_min = x_min;
		_x_max = x_max;
		_y_min = y_min;
		_y_max = y_max;
	}
};

#endif // WINDOW_HPP