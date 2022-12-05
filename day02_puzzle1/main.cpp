/* ~~~~~~~~~~~~RULES~~~~~~~~~~~~~
 * Rock			:	A or X and 1 points
 * Paper		:	B or Y and 2 points
 * Scissors	:	C or Z and 3 points
 *
 * Lose	: 0 points
 * Draw	: 3 points
 * Win	: 6 points
 * ~~~~~~~~~~~~RULES~~~~~~~~~~~~~
 */

#include <array>

std::array<char, 2> RockShapes	 		= {'A', 'X'};
std::array<char, 2> PaperShapes 		= {'B', 'Y'};
std::array<char, 2> ScissorsShapes 	= {'C', 'Z'};

const int lose 	= 0;
const int draw 	= 3;
const int win		= 6;

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

enum Shape
{
	None 			= 0,
	Rock 			= 1,
	Paper 		= 2,
	Scissors 	= 3
};

int _play(Shape opponent, Shape self)
{
	if(opponent == self)
	{
		return self + draw;
	}
	int score = self;
	switch (self)
	{
		case Rock:
			switch (opponent)
			{
				case Paper:
					score += lose;
					break;
				case Scissors:
					score += win;
					break;
			}
			break;
		case Paper:
			switch (opponent)
			{
				case Rock:
					score += win;
					break;
				case Scissors:
					score += lose;
					break;
			}
			break;
		case Scissors:
			switch (opponent)
			{
				case Rock:
					score += lose;
					break;
				case Paper:
					score += win;
					break;
			}
			break;
	}
	return score;
}

template <typename T, size_t size>
bool in(const std::array<T, size>& shapes, char shape_raw)
{
	for(const T& shape: shapes)
	{
		if(shape == shape_raw)
		{
			return true;
		}
	}
	return false;
}

Shape getShape(char c)
{
	if(in(RockShapes, c))
	{
		return Rock;
	}
	if(in(PaperShapes, c))
	{
		return Paper;
	}
	if(in(ScissorsShapes, c))
	{
		return Scissors;
	}
	throw std::runtime_error("Invalid type");
}

void getShapes(std::string line, Shape& opponent, Shape& self)
{
	char _opponent 	= 0;
	char _self 			= 0;
	std::sscanf(line.c_str(), "%c %c", &_opponent, &_self);

	opponent 	= getShape(_opponent);
	self		 	= getShape(_self);
}

int play(const std::string& line)
{
	Shape opponent 	= None;
	Shape self 			= None;
	getShapes(line, opponent, self);
	return _play(opponent, self);
}

int main()
{
	std::ifstream input("./input.txt");
	std::string line;

	int score = 0;

	while(std::getline(input, line))
	{
		score += play(line);
	}
	input.close();

	std::cout << "Score: " << score << '\n';
	return EXIT_SUCCESS;
}

