#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cassert>

char getShared(const std::string& compartment1, const std::string& compartment2)
{
	for(const auto& item: compartment1)
	{
		for(const auto& compare_item: compartment2)
		{
			if(item == compare_item)
			{
				return item;
			}
		}
	}
	throw std::runtime_error("Shared item not found!");
}

int getPrioriy(const std::string& backpack)
{
	assert(!(backpack.size() % 2) && "Backpack size must be even!");
	std::string compartment1 = backpack.substr(0, backpack.size() / 2);
	std::string compartment2 = backpack.substr(backpack.size() / 2, backpack.size() / 2);

	char shared = getShared(compartment1, compartment2);

	return isupper(shared) ? (shared - 'A') + 27 : (shared - 'a') + 1;
}

int main()
{
	std::ifstream input("./input.txt");
	std::string line;

	int total_priorty = 0;
	while(std::getline(input, line))
	{
		total_priorty += getPrioriy(line);
	}

	std::cout << "Total: " << total_priorty << '\n';

	return EXIT_SUCCESS;
}

