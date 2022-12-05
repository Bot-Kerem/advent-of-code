#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <array>

template <size_t size>
void place(std::array<int, size>& top, int cal)
{
	for(int i = 0; i < size; i++)
	{
		if(cal > top[i])
		{
			top[i] = cal;
			break;
		}
	}
}

template <size_t size>
int sum(std::array<int, size> arr)
{
	int total = 0;
	for(int i = 0; i < size; i++)
	{
		total += arr[i];
	}
	return total;
}

int main()
{
	std::ifstream input("./input.txt");

	std::string line;
	int current = 0;
	std::array<int, 3> top;
	while(std::getline(input, line))
	{
		if(line.length() == 0)
		{
			place(top, current);
			current = 0;
		}
		current += std::atoi(line.c_str());
	}
	input.close();
	place(top, current);

	int top_sum = sum(top);
	std::cout << "Total " << top_sum << " calories that 3 elves carrying\n";

	return EXIT_SUCCESS;
}
