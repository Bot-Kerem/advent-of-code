#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>

#define VISUALIZE

struct File
{
	File(const std::string& _name, int _size) { name = _name; size = _size; }
	std::string name;
	int size = 0;
};

struct Directory
{
	Directory(const std::string& _name) { name = _name; }
	std::string name;
	std::vector<File> files;
	std::vector<Directory> directories;
	Directory* parent = nullptr;

	void insert(Directory dir)
	{
		for(auto& d: directories)
		{
			if(d.name == dir.name)
			{
				std::cout << "Folder exists!\n";
				return;
			}
		}
		dir.parent = this;
		directories.push_back(dir);
	}
	void insert(File file)
	{
		for(auto& f: directories)
		{
			if(f.name == file.name)
			{
				return;
			}
		}
		files.push_back(file);
	}
	std::string getFullPath() const
	{
		std::string full_path = "";
		const Directory* _parent = this;
		while(_parent->parent)
		{
			full_path = _parent->name + '/' + full_path ;
			_parent = _parent->parent;
		}
		full_path = _parent->name + full_path;
		return full_path;
	}

	int getSize() const
	{
		int size = 0;
		for(const auto& file: files)
		{
			size += file.size;
		}
		for(const auto& dir: directories)
		{
			size += dir.getSize();
		}
		return size;
	}
};

class Filesystem
{
	const int device_space = 70000000;
	Directory* current_dir = &main_dir;
	private:
		Directory main_dir{"/"};

	public:
		Filesystem() = default;

		template <typename T>
		void add(T item)
		{
			current_dir->insert(item);
		}

		void cd(const std::string& path)
		{
			if(path == "/")
			{
				current_dir = &main_dir;
			}
			else if(path == ".." && current_dir->parent)
			{
				current_dir = current_dir->parent;
			}
			else
			{
				for(auto& dir: current_dir->directories)
				{
					if(dir.name == path)
					{
						current_dir = &dir;
						return;
					}
				}
				add<Directory>(path);
				for(auto& dir: current_dir->directories)
				{
					if(dir.name == path)
					{
						current_dir = &dir;
						return;
					}
				}
			}
		}
		
		int size;

		void writeSize(const Directory& dir, std::map<std::string, int>& map)
		{
			map[dir.getFullPath()] = dir.getSize();

			for(const auto& d: dir.directories)
			{
				writeSize(d, map);
			}
		}

		void visualize(const Directory& dir) const
		{
			std::cout << dir.getFullPath() << " (dir): " << dir.getSize() << '\n';
			for(const auto& file: dir.files)
			{
				std::cout << dir.getFullPath() << file.name << " " << file.size << '\n';
			}
			for(const auto& d: dir.directories)
			{
				visualize(d);
			}
		}

		int getSolution(int size)
		{
			std::map<std::string, int> map;
			writeSize(main_dir, map);

			int result = RAND_MAX;

			int required_space = std::abs(device_space - (size + main_dir.getSize()));

			for(auto const& [key, val]: map)
			{
				if(val >= required_space && val < result)
				{
					result = val;
				}
			}

#ifdef VISUALIZE
			visualize(main_dir);
#endif

			return result;
		}
};

class Device
{
	private:
		Filesystem filesystem;

		enum Command
		{
			CMD_CD, CMD_LS, CMD_NULL
		};

		Command current_command = CMD_NULL;

		void cmd_cd(std::stringstream& args)
		{
			std::string where;
			std::getline(args, where, ' ');
			filesystem.cd(where);
		}

		void cmd_ls(std::stringstream& args) {  }

		void process_command(const std::string& command)
		{
			std::stringstream cmd{command};

			std::string cmd_type;
			std::getline(cmd, cmd_type, ' '); // skip $

			std::getline(cmd, cmd_type, ' ');

			if(cmd_type == "cd")
			{
				current_command = CMD_CD;
				cmd_cd(cmd);
			}
			else if(cmd_type == "ls")
			{
				current_command = CMD_LS;
				cmd_ls(cmd);
			}

		}
	
		void process_cmd_ls(std::stringstream&& output)
		{
			std::string T;
			std::string name;
			std::getline(output, T, ' ');
			std::getline(output, name, ' ');
			if(T == "dir")
			{
				filesystem.add<Directory>(name);
			}
			else
			{
				filesystem.add<File>({name, std::atoi(T.c_str())});
			}
		}

		void process_command_output(const std::string& output)
		{
			switch (current_command)
			{
				case CMD_LS:
					process_cmd_ls(std::stringstream{output});
					break;
				case CMD_CD:
					break;
				case CMD_NULL:
					break;
			}
		}
		
	public:
		Device() = default;
		void process(const std::string& line)
		{
			if(line[0] == '$')
			{
				process_command(line);
			}
			else
			{
				process_command_output(line);
			}
		}
		int getSolution()
		{
			return filesystem.getSolution(30000000);
		}
};


int solution(std::ifstream& input)
{
	static Device device{};
	std::string line;
	while(std::getline(input, line))
	{
		device.process(line);
	}
	return device.getSolution();
}

int main()
{
	std::ifstream input("input.txt");
	int result = solution(input);
	input.close();

	std::cout << "Result: " << result << '\n';

	return EXIT_SUCCESS;
}

