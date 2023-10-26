#include "chunk.h"

#include <utility>

Sorting::Chunk::Chunk(int _position, int _size)
{
	position = _position;
	size = _size;
    this->data.clear();
}

Sorting::Chunk::Chunk(int file_)
{
	std::ifstream in(std::to_string(file_) + ".temp");
	size = std::count(std::istreambuf_iterator<char>(in),
					  std::istreambuf_iterator<char>(), '\n');

    this->data.clear();

    in.close();
}

void swap(std::vector<int>& v, int x, int y);

void quicksort(std::vector<int> &vec, int L, int R) {
    int i, j, mid, piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid];

    while (i<R || j>L) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksort(vec, i, R);
            if (j > L)
                quicksort(vec, L, j);
            return;
        }
    }
}

void swap(std::vector<int>& v, int x, int y) {
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;

}

void Sorting::Chunk::sort()
{
    quicksort(this->data, 0, this->size-1);
}

void Sorting::Chunk::save_to_file() const
{
	std::ofstream o(std::to_string(this->position) + ".temp");
	
	for (auto i : this->data)
	{
		o << std::to_string(i) << '\n';
	}

    std::cout << "saved chunk to file: " << std::to_string(this->position) + ".temp" << "\n";
	
	o.close();
}


void Sorting::Chunk::load(std::vector<int> _data) {
    this->data = std::move(_data);
}

void Sorting::Chunk::remove_data()
{
    this->data.clear();
    std::destroy(this->data.begin(), this->data.end());
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

Sorting::Chunk::~Chunk() {
    this->data.clear();
    std::destroy(this->data.begin(), this->data.end());
}

void Sorting::Chunk::push_pack(int i) {
    this->data.push_back(i);
}
