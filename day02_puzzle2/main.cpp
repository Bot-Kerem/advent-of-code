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

std::array<char, 1> RockShapes	 		= {'A'};
std::array<char, 1> PaperShapes 		= {'B'};
std::array<char, 1> ScissorsShapes 	= {'C'};

std::array<char, 1> LoseShapes	 		= {'X'};
std::array<char, 1> DrawShapes 			= {'Y'};
std::array<char, 1> WinShapes 			= {'Z'};

const int lose 	= 0;
const int draw 	= 3;
const int win		= 6;

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

enum GameElement
{
	None 			= 0,
	Rock 			= 1,
	Paper 		= 2,
	Scissors 	= 3,
	Lose			= 4,
	Draw			= 5,
	Win				= 6
};

int _play(GameElement opponent, GameElement condition)
{
	if(condition == Draw)
	{
		return draw + opponent;
	}
	int score = 0;
	switch (opponent)
	{
		case Rock:
			switch (condition)
			{
				case Lose:
					score += lose + Scissors;
					break;
				case Win:
					score += win + Paper;
					break;
				default:
					throw std::runtime_error("Invalid condition!");
					break;
			}
			break;
		case Paper:
			switch (condition)
			{
				case Lose:
					score += lose + Rock;
					break;
				case Win:
					score += win + Scissors;
					break;
				default:
					throw std::runtime_error("Invalid condition!");
					break;
			}
			break;
		case Scissors:
			switch (condition)
			{
				case Lose:
					score += lose + Paper;
					break;
				case Win:
					score += win + Rock;
					break;
				default:
					throw std::runtime_error("Invalid condition!");
					break;
			}
			break;
		default:
			throw std::runtime_error("Invalid shape!");
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

GameElement getShape(char c)
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
	if(in(LoseShapes, c))
	{
		return Lose;
	}
	if(in(DrawShapes, c))
	{
		return Draw;
	}
	if(in(WinShapes, c))
	{
		return Win;
	}
	throw std::runtime_error("Invalid element");
}

void getShapes(std::string line, GameElement& opponent, GameElement& self)
{
	char _opponent 	= 0;
	char _self 			= 0;
	std::sscanf(line.c_str(), "%c %c", &_opponent, &_self);

	opponent 	= getShape(_opponent);
	self		 	= getShape(_self);
}

int play(const std::string& line)
{
	GameElement opponent 	= None;
	GameElement self 			= None;
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

	std::cout << "Score: " << score << '\n';
	return EXIT_SUCCESS;
}

