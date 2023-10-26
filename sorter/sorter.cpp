#include "sorter.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define NC "\e[0m"

void printProgress(double percentage) {
    int val = (int) (percentage * 100) + 1;
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf(CYN "\r%3d%% [%.*s%*s]" NC, val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void Sorting::Sorter::generate_and_sort_chunks() {
    unsigned int current_chunk = 0;
    int current_chunk_size;
    int line;
    std::ifstream in(this->input_file_name);

    std::cout << "Generating chunks: \n";

    while (!in.eof()) {
        current_chunk_size = 0;
        this->chunks.emplace_back(current_chunk, this->size_of_chunks);

        while (this->size_of_chunks > current_chunk_size && in >> line) {
			this->chunks[current_chunk].push_pack(line);
            current_chunk_size++;
            this->size_of_everything++;
        }
        this->chunks[current_chunk].size = current_chunk_size;

        this->chunks[current_chunk].sort();

        this->chunks[current_chunk].save_to_file();

        this->chunks[current_chunk].remove_data();

//        std::cout << "\rGenerated chunk number: " << current_chunk;
        printf(CYN "\rGenerated chunk number: %d" NC, current_chunk);
        std::cout.flush();

        current_chunk++;
    }
    printf(GRN "\rDone!" NC);
    std::cout.flush();
    std::cout << "\n";
    this->number_of_chunks = current_chunk;
}

bool is_all_empty(const std::vector<std::ifstream*>& files) {
	bool ret = true;
	for (auto file: files)
	{
		ret = ret and file->eof();
	}
    return ret;
}

void Sorting::Sorter::merge_sort() {
    std::ofstream out(this->output_file_name);
	
	std::vector<int> temp;
	std::vector<std::ifstream*> files;

    std::cout << "Merging chunks: \n";
	
	for (int i = 0; i < number_of_chunks; ++i)
	{
		auto *file = new std::ifstream(std::to_string(i) + ".temp");
		files.push_back(file);
	}
	
	for (auto file: files)
	{
		int n;
		*file >> n;
		temp.push_back(n);
	}
	int index = 0;

    int sorting_progress = 0;


	while (!is_all_empty(files)) {
		for (int i = 0; i < temp.size(); i++)
		{
			if ((temp[i] < temp[index] and !files[i]->eof()) or (files[index]->eof() and !files[i]->eof()))
				index = i;
		}
		out << temp[index] << std::endl;
		int temp_num;
		*files[index] >> temp_num;
		temp[index] = temp_num;


        printProgress((float)sorting_progress / (float)(this->size_of_everything));
        sorting_progress++;
	}
    printf(GRN "\rDone!" NC);
    std::cout.flush();
    std::cout << "\n";
}

Sorting::Sorter::Sorter(char *inputFileName, char *outputFileName, int sizeOfChunks) : input_file_name(
        inputFileName), output_file_name(outputFileName), size_of_chunks(sizeOfChunks) {}

void Sorting::Sorter::delete_temp_files() {
    int progress = 0;
    std::cout << "Removing temporary files: \n";
    for (const auto& chunk: chunks) {
        chunk.remove_file();
        printProgress((float)progress / (float)(this->number_of_chunks));
        progress++;
    }
    printf(GRN "\rDone!" NC);
    std::cout.flush();
    std::cout << "\n";
}
