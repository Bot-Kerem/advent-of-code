#include <fstream> // std::ifstream
#include <iostream> // std::cout
#include <iterator>
#include <string> // std::string and std::getline
#include <utility> // std::pair
#include <cstdio> // std::sscanf

bool between(const std::pair<std::pair<int, int>, std::pair<int, int>>& pair)
{
	return pair.first.first <= pair.second.first && pair.first.second >= pair.second.second;
}

std::pair<std::pair<int, int>, std::pair<int, int>> extract(const std::string& line)
{
	std::pair<std::pair<int, int>, std::pair<int, int>> pair;
	std::sscanf(line.c_str(), "%i-%i,%i-%i", &pair.first.first, &pair.first.second, &pair.second.first, &pair.second.second);
	return pair;
}

bool contains(const std::string& line)
{
	auto pair = extract(line);
	return between(pair) || between({pair.second, pair.first});
}

int main()
{
	std::ifstream input("./input.txt");
	std::string line;

	int count = 0;
	
	while(std::getline(input, line))
	{
		contains(line) ? count++ : NULL;
	}
	input.close();

	std::cout << "Count: " << count << '\n';

	return EXIT_SUCCESS;
}

