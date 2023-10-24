#include "chunk.h"

Sorting::Chunk::Chunk(int _position, int _size)
{
	position = _position;
	size = _size;
	data = nullptr;
}

Sorting::Chunk::Chunk(int file_)
{
	std::ifstream in(std::to_string(file_) + ".temp");
	size = std::count(std::istreambuf_iterator<char>(in),
					  std::istreambuf_iterator<char>(), '\n');
	
	data = nullptr;

    in.close();
}

void swap(int a, int b) {
	int c = b;
	b = a;
	a = c;
}

void Sorting::Chunk::sort() const
{
	int i, j;
	for (i = 0; i < this->size - 1; i++)
		for (j = 0; j < this->size - i - 1; j++)
			if (this->data[j] > this->data[j + 1])
				swap(this->data[j], this->data[j + 1]);
}

void Sorting::Chunk::save_to_file() const
{
	std::ofstream o(std::to_string(this->position) + ".temp");
	
	for (int i = 0; i < this->size; ++i)
	{
		o << std::to_string(this->data[i]) << std::endl;
	}

    std::cout << "saved chunk to file: " << std::to_string(this->position) + ".temp" << "\n";
	
	o.close();
}

void Sorting::Chunk::load() const
{
	std::ifstream in(std::to_string(this->position) + ".temp");
	
	for (int i = 0; i < this->size; ++i)
	{
		in >> data[i];
	}
}

void Sorting::Chunk::remove_data()
{
	delete this->data;
	this->data = nullptr;
}

void Sorting::Chunk::remove_file() const
{
    try {
            if (std::filesystem::remove(std::to_string(this->position) + ".temp"))
            std::cout << "file " << std::to_string(this->position) + ".temp" << " deleted.\n";
            else
            std::cout << "file " << std::to_string(this->position) + ".temp" << " not found.\n";
    }
    catch(const std::filesystem::filesystem_error& err) {
        std::cout << "filesystem error: " << err.what() << '\n';
    }
}
