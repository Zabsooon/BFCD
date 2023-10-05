#include "File/Reader.hpp"
#include "File/File.hpp"
#include "File/Compression/Huffman.hpp"
int main()
{
	BFCD::File file("../TestFiles/TestFileOpen.txt");
	BFCD::Reader reader(file);
	reader.readData();
	reader.getFile()->print();

	{
		BFCD::Huffman(file);
	}

	return 0;
}