#include <cstdint>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>

enum Direction: char
{
	Right = 'R',
	Left	= 'L',
	Up		= 'U',
	Down	= 'D'
};


struct vec2 {
	int16_t x;
	int16_t y;
};

auto extract(const std::string& line)
{
	char Dir = ' ';
	int Repeat = 0;
	std::sscanf(line.c_str(), "%c %i", &Dir, &Repeat);
	return std::pair<Direction, int>(static_cast<Direction>(Dir), Repeat);
}

void simulate(vec2& Head, vec2& Tail, Direction Dir)
{
	switch (Dir)
	{
		case Right:
			Head.x += 1;
			break;
		case Left:
			Head.x -= 1;
			break;
		case Up:
			Head.y += 1;
			break;
		case Down:
			Head.y -= 1;
			break;
		default:
			throw std::runtime_error("Error!");
	}

	if(std::sqrt(std::pow<float>(Head.x - Tail.x, 2) + std::pow<float>(Head.y - Tail.y, 2)) >= 2)
	{
		switch (Dir)
		{
			case Right:
				Tail.x = Head.x - 1;
				Tail.y = Head.y;
				break;
			case Left:
				Tail.x = Head.x + 1;
				Tail.y = Head.y;
				break;
			case Up:
				Tail.y = Head.y - 1;
				Tail.x = Head.x;
				break;
			case Down:
				Tail.y = Head.y + 1;
				Tail.x = Head.x;
				break;
		}
	}
}

void insert(std::vector<vec2>& pos, vec2 p)
{
	for(const auto& _p: pos)
	{
		if(_p.x == p.x && _p.y == p.y)
		{
			return;
		}
	}
	pos.push_back(p);
}

int solution(std::fstream& input)
{
	std::vector<vec2> map;
	std::string line;

	while(std::getline(input, line))
	{
		static vec2 Tail = vec2{0, 0};
		static vec2 Head = vec2{0, 0};

		auto [Dir, Repeat] = extract(line);
		for(int _ = 0; _ < Repeat; _++)
		{
			simulate(Head, Tail, Dir);	
			insert(map, Tail);
		}
	}

	return map.size();
}

int main()
{
	std::fstream input("input.txt");
	int result = solution(input);
	input.close();

	std::cout << "Result: " << result << '\n';

	return EXIT_SUCCESS;
}

