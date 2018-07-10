#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <functional>

template<class T>
int binary_search(std::vector<T>& v, const T& elem, const std::function<bool(const std::vector<T>&, const int, const T&)> f)
{
	sort(v.begin(), v.end());
	int p = 0, k = v.size() - 1;
	while (p < k)
	{
		int m = (p + k) / 2;
		if (f(v, m, elem))
			k = m;
		else
			p = m + 1;
	}
	return p;
};

int main ()
{
	struct timeval time;
	gettimeofday(&time, 0);
	srand(time.tv_sec * 1000 + time.tv_usec % 1000);

	const int n = 10;
	const int mn = 0;
	const int mx = 1000;
	
	std::vector<int> v(n, 0);
	
	std::for_each(v.begin(), v.end(),
		[](int& i)
		{
			i = rand() % (mx - mn + 1) + mn;
		}
	);

	std::cout << binary_search<int>(v, 500, 
		[](const std::vector<int>& v, const int m, const int& elem) -> bool
		{ 
			return (v[m] < elem) ? false : true;
		}) << std::endl;
	return 0;
}