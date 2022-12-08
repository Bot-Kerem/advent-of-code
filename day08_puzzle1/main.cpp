#include <fstream>
#include <iostream>
#include <vector>
#include <string>

bool check_row(const std::string& row, int x)
{
	bool left = false;
	bool right = false;
	for(int i = x - 1; i >= 0; i--)
	{
		if(row[x] <= row[i])
		{
			left = true;
			break;
		}
	}
	for(int i = x + 1; i < row.size(); i++)
	{
		if(row[x] <= row[i])
		{
			right = true;
			break;
		}
	}
	return left && right;
}

bool check_column(const std::vector<std::string>& column, int x, int y)
{
	bool top = false;
	bool bottom = false;
	for(int i = y - 1; i >= 0; i--)
	{
		if(column[y][x] <= column[i][x])
		{
			top = true;
			break;
		}
	}
	for(int i = y + 1; i < column.size(); i++)
	{
		if(column[y][x] <= column[i][x])
		{
			bottom = true;
			break;
		}
	}
	return top && bottom;
}

int solution(const std::vector<std::string>& grid)
{
	int total_tree = grid.size() * grid[0].size();
	int total_unvisible_tree = 0;

	for(int y = 1; y < grid.size() - 1; y++)
	{
		for(int x = 1; x < grid[y].size() - 1; x++)
		{
			if(check_row(grid[y], x) && check_column(grid, x, y))
			{
				total_unvisible_tree++;
			}
		}
	}
	
	return total_tree - total_unvisible_tree;
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

