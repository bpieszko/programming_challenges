#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sys/time.h>
#include <functional>

template<class A, class R>
A ternary_search(const std::function<R(A)> f, A left, A right, const A& precision)
{
	while (1)
	{
		if (std::abs(right - left) < precision)
			return (left + right) / 2;

		const A leftThird = left + (right - left) / 3;
		const A rightThird = right - (right - left) / 3;

		if (f(leftThird) < f(rightThird))
			left = leftThird;
		else
			right = rightThird;
	}
}

inline const double f(const double& x)
{
	return (-17.5356 * x * x) + (134.56 * x) + 53.7788;
}

int main ()
{
	const double max_x = ternary_search<double, double>(f, -1000000.0, 1000000.0, 0.00001);
	std::cout << "f_max(" << max_x << ") = " << f(max_x) << std::endl;
	return 0;
}