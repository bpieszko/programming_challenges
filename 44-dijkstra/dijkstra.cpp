#include <iostream>
#include <vector>
#include <queue>

using graph_t = std::vector<std::vector<std::pair<int, long long>>>;

std::vector<long long> dijkstra(const graph_t& graph, int start_vertex)
{
	std::priority_queue<std::pair<long long, int> > pq;
	std::vector<long long> result(graph.size(), 1LL << 60);
	result[start_vertex] = 0;
	pq.push({0, start_vertex});
	while (!pq.empty())
	{
		std::pair<long long, int> w = pq.top();
		pq.pop();

		if (result[w.second] != 1LL << 60 && w.second != start_vertex)
			continue;

		result[w.second] = -w.first;

		for (const auto i : graph[w.second])
			if (result[w.second] + i.second < result[i.first])
				pq.push({-result[w.second] - i.second, i.first});
	}
	return result;
}

int main ()
{
	graph_t v(5);

	v[0].push_back({1, 3});
	v[1].push_back({0, 3});

	v[1].push_back({2, 5});
	v[2].push_back({1, 5});
	
	v[1].push_back({4, 7});
	v[4].push_back({1, 7});
	
	v[2].push_back({3, 10});
	v[3].push_back({2, 10});
	
	v[4].push_back({3, 1});
	v[3].push_back({4, 1});

	std::vector<long long> result(dijkstra(v, 0)); // z pomoca konstruktora kopiujacego
	for (const auto i : result)
		std::cout << i << std::endl;

	return 0;
}