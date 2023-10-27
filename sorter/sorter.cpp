#include "sorter.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define CLEAR "                                                                    "
#define PBWIDTH 60
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define NC "\e[0m"

void printProgress(double percentage)
{
	fflush(stdout);
	int val = (int) (percentage * 100) + 1;
	int lpad = (int) (percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r" CYN "%3d%% [%.*s%*s]" NC, val, lpad, PBSTR, rpad, "");
}

void Sorting::Sorter::generate_and_sort_chunks()
{
	unsigned int current_chunk = 0;
	int current_chunk_size;
	int line;
	std::ifstream in(this->input_file_name);
	
	std::cout << "Generating chunks: \n";
	
	while (!in.eof())
	{
		current_chunk_size = 0;
		this->chunks.emplace_back(current_chunk, this->size_of_chunks);
		
		while (this->size_of_chunks > current_chunk_size && in >> line)
		{
			//FIXME: here if character is newline this shit crashes, gotta fix it
			this->chunks[current_chunk].push_pack(line);
			current_chunk_size++;
			this->size_of_everything++;
		}
		this->chunks[current_chunk].size = current_chunk_size;
		
		this->chunks[current_chunk].sort();
		
		this->chunks[current_chunk].save_to_file();
		
		this->chunks[current_chunk].remove_data();
		
		printf("\r" CYN "Generated chunk number: %d" NC, current_chunk);
		std::cout.flush();
		
		current_chunk++;
	}
	printf(GRN "\rDone!" NC CLEAR);
	std::cout.flush();
	std::cout << "\n";
	this->number_of_chunks = current_chunk;
}

bool is_all_empty(const std::vector<std::ifstream> &files)
{
	bool ret = true;
	for (auto &file: files)
	{
		ret = ret && file.eof();
	}
	return ret;
}

void Sorting::Sorter::merge_sort() const
{
	std::ofstream out(this->output_file_name);
	
	std::vector<std::optional<int>> temp;
	std::vector<std::ifstream> files;
	
	std::cout << "Merging chunks: \n";
	
	for (int i = 0; i < number_of_chunks; ++i)
	{
		files.emplace_back(std::to_string(i) + ".temp");
	}
	
	for (auto &file: files)
	{
		if (file.good())
		{
			int n;
			file >> n;
			temp.push_back(n);
		} else
		{
			temp.push_back(std::nullopt);
		}
	}
	int index = 0;
	
	int sorting_progress = 0;
	int pck = -1;
	
	while (!is_all_empty(files))
	{
		for (int i = 0; i < temp.size(); i++)
		{
//			if ((temp[i] < temp[index] && !files[i].eof()) || (files[index].eof() && !files[i].eof()))
			if (temp[i] < temp[index] )
				index = i;
		}
		out << *temp[index] << std::endl;
		files[index] >> *temp[index];
		
		if ((int) ((float) sorting_progress / (float) (this->size_of_everything) * 100) != pck)
		{
			printProgress((float) sorting_progress / (float) (this->size_of_everything));
			pck = sorting_progress;
		}
		sorting_progress++;
	}
	printf(GRN "\rDone!" NC CLEAR);
	std::cout.flush();
	std::cout << "\n";
}

Sorting::Sorter::Sorter(char *inputFileName, char *outputFileName, int sizeOfChunks) : input_file_name(
		inputFileName), output_file_name(outputFileName), size_of_chunks(sizeOfChunks)
{}

void Sorting::Sorter::delete_temp_files()
{
	int progress = 0;
	std::cout << "Removing temporary files: \n";
	for (const auto &chunk: chunks)
	{
		chunk.remove_file();
		printProgress((float) progress / (float) (this->number_of_chunks));
		progress++;
	}
	printf(GRN "\rDone!" NC CLEAR);
	std::cout.flush();
	std::cout << "\n";
}
