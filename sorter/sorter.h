#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include "../chunk/chunk.h"

namespace Sorting {
    class Sorter {
    public:


        char* input_file_name;
        char* output_file_name;
        int size_of_chunks;
        unsigned int number_of_chunks = 0;
        int size_of_everything = 1;
        std::vector<Chunk> chunks;

        Sorter(char *inputFileName, char *outputFileName, int sizeOfChunks);

        void generate_and_sort_chunks();
        void merge_sort() const;
        void delete_temp_files();

    };
}

