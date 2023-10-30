#include <iostream>
#include "sorter/sorter.h"


int main(int argc, char *argv[])
{
	char *in = "input.txt";
	char *out = "output.txt";
	int size = 1000000;
	
	if (argc >= 2)
	{
		if (std::string(argv[1]) == "help" or std::string(argv[1]) == "h" or std::string(argv[1]) == "-help" or
			std::string(argv[1]) == "--help")
		{
			std::cout << "Usage: bignsort\n"
						 "  or:  bignsort SOURCE\n"
						 "  or:  bignsort SOURCE DEST\n"
						 "  or:  bignosrt SOURCE DEST CHUNKSIZE\n"
						 "Sort SOURCE to DEST with chunk size of CHUNKSIZE\n\n"
						 "Deafults\n"
						 "      SOURCE: input.txt\n"
						 "        DEST: output.txt\n"
						 "   CHUNKSIZE: 1000000\n";
			return 0;
		} else
		{
			in = argv[1];
		}
	}
	
	if (argc >= 3)
	{
		out = argv[2];
	}
	
	if (argc >= 4)
	{
		size = atoi(argv[3]);
	}
	
	auto sorter = new Sorting::Sorter(in, out, size);
	sorter->generate_and_sort_chunks();
	sorter->merge_sort();
	sorter->delete_temp_files();
	return 0;
}
