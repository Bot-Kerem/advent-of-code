#include <cctype>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cassert>
#include <array>
#include <set>

const size_t group_size = 3;

template<size_t size>
bool in(const std::array<std::string, size>& strlist, char c)
{
	int count = 0;

	for(const auto& str: strlist)
	{
		for(int i = 0; i < str.size(); i++)
		{
			if(str[i] == c)
			{
				count++;
				break;
			}
		}
	}
	return count == size;
}

template <size_t size>
char getShared(const std::array<std::string, size>& backpacks)
{
	std::set<char> candidates{backpacks[0].begin(), backpacks[0].end()};
	std::set<char> eliminations;

	for(const auto& candidate: candidates)
	{
		if(in(backpacks, candidate))
		{
			return candidate;
		}
	}
	throw std::runtime_error("No shared elemnt");
}

template <size_t size>
int getPrioriy(const std::array<std::string, size>& backpacks)
{
	char shared = getShared(backpacks);
	return isupper(shared) ? (shared - 'A') + 27 : (shared - 'a') + 1;
}

int main()
{
	std::ifstream input("./input.txt");
	std::string line;

	int total_priorty = 0;

	std::array<std::string, group_size> group;
	size_t group_index = 0;
	while(std::getline(input, line))
	{
		if(!(group_index < group_size))
		{
			group_index = 0;
			total_priorty += getPrioriy(group);
		}
			group[group_index++] = line;
	}
	input.close();
	total_priorty += getPrioriy(group);

	std::cout << "Total: " << total_priorty << '\n';

	return EXIT_SUCCESS;
}

