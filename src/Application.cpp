#include "File/File.hpp"
#include "File/FileHandler.hpp"
#include "File/Compression/Huffman.hpp"

int main()
{
    BFCD::FileHandler handle("../TestFiles/TestFileOpen.txt");

    std::cout << (*handle.getFilePtr()).getPath() << "\n";

    for(char c : handle.getFilePtr()->getData())
    {
        std::cout << c;
    }

    BFCD::Huffman huffman(handle.getFilePtr());
	return 0;
}
