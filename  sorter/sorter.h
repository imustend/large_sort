#include <vector>
#include "../chunk/chunk.h"

namespace Sorting {
    class Sorter {
    public:
        char* input_file_name;
        char* output_file_name;
        unsigned int num_of_chunks;
        std::vector<Chunk> chunks;

        void generate_and_sort_chunks();
        void merge_sort();

    };
}

