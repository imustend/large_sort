#include "sorter.h"

void Sorting::Sorter::generate_and_sort_chunks() {
    unsigned int current_chunk = 0;
    int current_chunk_size;

    char ch;
    int line;
    std::ifstream in(this->input_file_name);

    while (!in.eof()) {
        current_chunk_size = 0;
        this->chunks.emplace_back(current_chunk, this->size_of_chunks);

        while (this->size_of_chunks > current_chunk_size && in >> line) {
            this->chunks[current_chunk].pushpack(line);
            current_chunk_size++;
            line = 0;
        }
        this->chunks[current_chunk].size = current_chunk_size;

        this->chunks[current_chunk].sort();

        std::cout << "created chunk: " << current_chunk << std::endl;
        this->chunks[current_chunk].save_to_file();

        this->chunks[current_chunk].remove_data();


        current_chunk++;
    }

}

void Sorting::Sorter::merge_sort() {
    //TODO: this shit
}


Sorting::Sorter::Sorter(char *inputFileName, char *outputFileName, int sizeOfChunks) : input_file_name(
        inputFileName), output_file_name(outputFileName), size_of_chunks(sizeOfChunks) {}

void Sorting::Sorter::delete_temp_files() {
    for (auto chunk: chunks) {
        chunk.remove_file();
    }
}
