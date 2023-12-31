#include "sorter.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define CLEAR "                                                                    "
#define PBWIDTH 60
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define NC "\e[0m"

void printProgress(double percentage)
{
	int val = (int) (percentage * 100);
	int lpad = (int) (percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r" CYN "%3d%% [%.*s%*s]" NC, val, lpad, PBSTR, rpad, "");
	fflush(stdout);
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
		
		while (this->size_of_chunks > current_chunk_size && !in.eof())
		{
			in >> line;
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

void Sorting::Sorter::merge_sort() const
{
	std::ofstream out(this->output_file_name);
	
	std::vector<int> temp;
	std::vector<std::ifstream *> files;
	
	std::cout << "Merging chunks: \n";
	
	if (this->chunks.size() == 1)
	{
		std::ifstream in("0.temp");
		int i;
		while (in.eof())
		{
			in >> i;
			out << i;
		}
		return;
	}
	
	for (int i = 0; i < this->number_of_chunks; ++i)
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
	
	int sorting_progress = 0;
	int ckp = -1;
	
	int smallest_not_eof = 0;
	while (true)
	{
		int smallest_current = smallest_not_eof;
		
		for (int i = 1; i < files.size(); i++)
		{
			if (temp[i] < temp[smallest_current] && !files[i]->eof())
			{
				smallest_current = i;
			}
		}
		
		out << temp[smallest_current] << '\n';
		
		*files[smallest_current] >> temp[smallest_current];
		
		bool all_eof = true;
		
		for (int i = 0; i < files.size(); i++)
		{
			if (!files[i]->eof())
			{
				smallest_not_eof = i;
				all_eof = false;
				break;
			}
		}
		
		if (all_eof)
		{
			break;
		}
		
		if ((int) ((float) sorting_progress / (float) (this->size_of_everything) * 100) != ckp)
		{
			printProgress((float) sorting_progress / (float) (this->size_of_everything));
			ckp = (int) ((float) sorting_progress / (float) (this->size_of_everything) * 100);
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
