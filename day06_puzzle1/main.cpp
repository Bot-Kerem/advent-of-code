#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

bool compare(const std::string& str, int start, int i = 4)
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

int solution(const std::string& line)
{
	for(int i = 0; i < line.size() - 4; i++)
	{
		if(compare(line, i))
		{
			return i + 4;
		}
	}
	throw std::runtime_error("No marker found");
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

