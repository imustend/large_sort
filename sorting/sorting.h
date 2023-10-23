#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>

namespace Sorting {
	FILE* openFile(char* fileName, char* mode);
	
	
	
	class Chunk {
	public:
		Chunk(int _poistion, int _size, int* data);
		Chunk(int file);
		~Chunk();
		
		
		int position;
		int size;
		int* data;
		
		void save_to_file();
		void sort();
	};
}

