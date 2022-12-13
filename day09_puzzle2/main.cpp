#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <utility>
#include <vector>
#include <set>

struct vec2
{
	int32_t x = 0;
	int32_t y = 0;

	inline bool operator<(const vec2& v) const noexcept
	{
		int32_t v1[2] = {this->x, this->y};
		int32_t v2[2] = {v.x, v.y};

		uint64_t* c1 = (uint64_t*)v1;
		uint64_t* c2 = (uint64_t*)v2;
		
		return *c1 < *c2;
	}
};

auto extract(const std::string& line) -> std::pair<char, int>
{
	char direction = '0';
	int count = 0;
	std::sscanf(line.c_str(), "%c %i", &direction, &count);
	return {direction, count};
}

int32_t sign(int32_t i)
{
	return (0 < i) - (i < 0);
}

void _simulate(const vec2& head, vec2& tail)
{
	if(std::abs(head.x - tail.x) >= 2 || std::abs(head.y - tail.y) >= 2)
	{
		tail.x += sign(head.x - tail.x);
		tail.y += sign(head.y - tail.y);
	}
}

void simulate(std::vector<vec2>& rope, const std::pair<char, int>& c, std::set<vec2>& pos)
{
	vec2 dir{0,0};
	switch (c.first)
	{
		case 'R':
			dir.x = 1;
			break;
		case 'L':
			dir.x = -1;
			break;
		case 'U':
			dir.y = 1;
			break;
		case 'D':
			dir.y = -1;
			break;
	}
	for(int _ = 0; _ < c.second; _++)
	{
		rope[0].x += dir.x;
		rope[0].y += dir.y;

		for(int i = 1; i < rope.size(); i++)
		{
			_simulate(rope[i - 1], rope[i]);
		}
		pos.insert(rope[9]);
	}
}

int solution(std::ifstream& input)
{
	std::vector<vec2> rope{10, {0, 0}};
	std::string line;
	std::set<vec2> positions;

	while(std::getline(input, line))
	{
		auto move = extract(line);
		simulate(rope, move, positions);
	}

	return positions.size();
}

int main()
{
	std::ifstream input("input.txt");
	int result = solution(input);
	input.close();

	std::cout << "Result: " << result << '\n';

	return EXIT_SUCCESS;
}

