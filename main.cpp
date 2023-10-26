#include <iostream>
#include "sorter/sorter.h"

int main(int argc, char* argv[])
{
	char* in = "input.txt";
	char* out = "output.txt";
	int size = 1000000;
    //TODO: better logging and arguments
	auto sorter = new Sorting::Sorter(in, out, size);
    sorter->generate_and_sort_chunks();
    sorter->merge_sort();
//    sorter->delete_temp_files();
	return 0;
}
