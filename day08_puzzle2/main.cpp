#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int get_view_score_row(const std::string& row, int x)
{
	int left = 0;
	int right = 0;
	for(int i = x - 1; i >= 0; i--)
	{
		left++;
		if(row[x] <= row[i])
		{
			break;
		}
	}
	for(int i = x + 1; i < row.size(); i++)
	{
		right++;
		if(row[x] <= row[i])
		{
			break;
		}
	}
	return left * right;
}

int get_view_score_column(const std::vector<std::string>& column, int x, int y)
{
	int top = 0;
	int bottom = 0;
	for(int i = y - 1; i >= 0; i--)
	{
		top++;
		if(column[y][x] <= column[i][x])
		{
			break;
		}
	}
	for(int i = y + 1; i < column.size(); i++)
	{
		bottom++;
		if(column[y][x] <= column[i][x])
		{
			break;
		}
	}
	return top * bottom;
}

int solution(const std::vector<std::string>& grid)
{
	int highest = 0;
	for(int y = 1; y < grid.size() - 1; y++)
	{
		for(int x = 1; x < grid[y].size() - 1; x++)
		{
			highest = std::max(get_view_score_row(grid[y], x) * get_view_score_column(grid, x, y), highest);
		}
	}
	
	return highest;
}

int main()
{
	std::ifstream input("input.txt");
	std::string line;

	std::vector<std::string> grid;
	while(std::getline(input, line))
	{
		grid.push_back(line);
	}

	int result = solution(grid);

	std::cout << "Result: " << result << '\n';

	return EXIT_SUCCESS;
}

