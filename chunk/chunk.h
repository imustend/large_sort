#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>

namespace Sorting {
    class Chunk {
	public:
		Chunk(int _position, int _size);
		Chunk(int file);
		~Chunk();
		
		
		int position = 0;
		long size = 0;
		int* data{};
		
		void save_to_file() const;
		void load() const;
		void remove_data();
		void sort() const;
        void remove_file() const;
	};
}

