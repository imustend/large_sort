#include <iostream>
#include "sorter/sorter.h"

int main(int argc, char* argv[])
{
    //TODO: better logging and arguments
	auto sorter = new Sorting::Sorter("input.txt", "output.txt", 1000000);
    sorter->generate_and_sort_chunks();
//    sorter->delete_temp_files();
    std::cout << sorter->number_of_chunks << std::endl;
	return 0;
}
