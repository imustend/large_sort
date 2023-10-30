#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <vector>

namespace Sorting
{
	class Chunk
	{
	public:
		Chunk(int _position, int _size);
		
		Chunk(int file);
		
		~Chunk();
		
		
		int position = 0;
		int size = 0;
		std::vector<int> data{};
		
		void save_to_file() const;
		
		void load_file();
		
		void load(std::vector<int> _data);
		
		void remove_data();
		
		void sort();
		
		void push_pack(int i);
		
		void remove_file() const;
		
		int get_num();
	};
}

