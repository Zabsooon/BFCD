#include "File/Reader.hpp"
#include "File/File.hpp"

int main()
{
	BFCD::File file("Z:/Dev/BFCD/TestFiles/TestFileOpen.txt");
	BFCD::Reader reader(file);
	// reader.open();
	reader.read();
	reader.getFile()->print();
	return 0;
}