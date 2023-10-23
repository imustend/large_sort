#include <stdio.h>

namespace Sorting {
	FILE* openFile(char* fileName, char* mode);
	
	
	
	class Chunk {
		int position;
		char* data;
		
		void save_to_file(char* fileName);
		void sort();
	};
}

