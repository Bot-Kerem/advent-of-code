#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

bool compare(const std::string& str, int start, int i)
{
	for(int j = 0; j < i; j++)
	{
		for(int k = 1; k < (i - j); k++)
		{
			if(str[start + j] == str[start + k + j])
			{
				return false;
			}
		}
	}
	return true;
}

int find_marker(const std::string& line, int marker_size, int start = 0)
{
	for(int i = start; i < line.size() - marker_size; i++)
	{
		if(compare(line, i, marker_size))
		{
			return i + marker_size;
		}
	}
	throw std::runtime_error("No marker found");
}

int solution(const std::string& line)
{
	int packet_marker = find_marker(line, 4);

	return find_marker(line, 14, packet_marker - 1);
}

int main()
{
	std::ifstream input("input.txt");
	std::string line;
	std::getline(input, line);
	input.close();
	int result = solution(line);

	std::cout << "Result: " << result << '\n';

	return 0;
}

