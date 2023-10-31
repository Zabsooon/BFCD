#include "File/Reader.hpp"
#include "File/File.hpp"
#include "File/Compression/Huffman.hpp"

int main()
{
	BFCD::File file("../TestFiles/TestFileOpen.txt");
	BFCD::Reader reader(std::make_shared<BFCD::File>(file));
	reader.readData(&file);
	reader.getFile()->print();
	file.print();

	{
		BFCD::Huffman huffman(&file);
	}
	auto data = file.getData();

	for(auto d : data)
	{
		std::cout << d;
	}

	return 0;
}
