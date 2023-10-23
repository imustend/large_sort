#include "sorting.h"

Sorting::Chunk::Chunk(int _poistion, int _size, int* _data)
{
	position = _poistion;
	size = _size;
	data = _data;
}

Sorting::Chunk::Chunk(int file_)
{
	std::ifstream in(std::to_string(file_) + ".temp");
	size = std::count(std::istreambuf_iterator<char>(in),
					  std::istreambuf_iterator<char>(), '\n');
	position = file_;
	for (int i = 0; i < size; ++i)
	{
		in >> data[i];
	}
}

void swap(int a, int b) {
	int c = b;
	b = a;
	a = c;
}

void Sorting::Chunk::sort()
{
	int i, j;
	for (i = 0; i < this->size - 1; i++)
		for (j = 0; j < this->size - i - 1; j++)
			if (this->data[j] > this->data[j + 1])
				swap(this->data[j], this->data[j + 1]);
}

void Sorting::Chunk::save_to_file()
{
	std::ofstream o(std::to_string(this->position) + ".temp");
	
	for (int i = 0; i < this->size; ++i)
	{
		o << std::to_string(this->data[i]) << std::endl;
	}
	
	o.close();
}
