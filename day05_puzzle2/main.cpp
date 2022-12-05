#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <string> // std::string, std::getline
#include <vector> // std::vector
#include <cstdio> // std::sscanf
#include <cassert> // std::assert

struct Procedure
{
	int pieces;
	int from;
	int to;
};

int get_stack_count(const std::string& str)
{
	int count = 0;
	std::stringstream seg(str);

	std::string w;
	while(std::getline(seg, w, ' '))
	{
		if(!w.empty())
			count++;
	}
	return count;
}

void place_crates(auto& raw_crates, auto& stacks)
{
	for(int i = raw_crates.size() - 1; i >= 0; i--)
	{
		size_t p = 1;
		const int j = 4;
		for(int _ = 0; _ < stacks.size(); _++)
		{
			if(raw_crates[i][p] != ' ')
			{
				stacks[_].push_back(raw_crates[i][p]);
			}
			p += j;
		}
	}

}

std::vector<std::vector<char>> create_stacks(std::vector<std::string>& raw_crates)
{

	int stack_count = get_stack_count(raw_crates[raw_crates.size() - 1]);
	raw_crates.pop_back();


	std::vector<std::vector<char>> stacks(stack_count);

	place_crates(raw_crates, stacks);
	
	return stacks;
}

void get_raw(auto& input, auto& raw_crates, auto& raw_procedures)	
{
	std::string line;
	bool crates_end = false;
	while(std::getline(input, line))
	{
		if(line.empty())
		{ crates_end = true; }
		else
		{ (crates_end ? raw_procedures : raw_crates).push_back(line); }
	}
}

std::vector<Procedure> create_procedures(const auto& raw_procedures)
{
	std::vector<Procedure> procedures;

	for(const auto& raw_procedure: raw_procedures)
	{
		Procedure procedure{};
		std::sscanf(raw_procedure.c_str(), "move %i from %i to %i", &procedure.pieces, &procedure.from, &procedure.to);
		procedure.from -= 1;
		procedure.to -= 1;
		procedures.push_back(procedure);
	}

	return procedures;
}

void process_procedures(auto& stacks, const auto& procedures)
{
	for(const auto& procedure: procedures)
	{
		assert(procedure.pieces <= stacks[procedure.from].size() && "Move size cannot be bigger than stack size!");

		for(int i = procedure.pieces; i > 0; i--)
		{
			stacks[procedure.to].push_back(stacks[procedure.from][stacks[procedure.from].size() - i]);
		}
		for(int i = procedure.pieces; i > 0; i--)
		{
			stacks[procedure.from].pop_back();
		}
	}
}

std::string process(std::ifstream& input)
{
	std::vector<std::string> raw_crates{};
	std::vector<std::string> raw_procedures{};

	get_raw(input, raw_crates, raw_procedures);

	auto stacks = create_stacks(raw_crates);
	auto procedures = create_procedures(raw_procedures);

	process_procedures(stacks, procedures);

	std::string result = "";
	int max = 0;

	for(const std::vector<char>& stack: stacks)
	{
		result += stack.at(stack.size() - 1);
		if(stacks.size() > max)
		{
			max = stacks.size();
		}
	}

	return result;
}

int main()
{
	std::ifstream input("./input.txt");
	auto result = process(input);
	input.close();

	std::cout << "Result: " << result << '\n';

	return EXIT_SUCCESS;
}

