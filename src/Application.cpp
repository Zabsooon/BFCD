#include "File/Reader.hpp"
#include "File/File.hpp"

int main()
{
	BFCD::File file2("../TestFiles/TestFileOpen.txt");
	BFCD::Reader reader2(file2);
	reader2.readData();
	reader2.getFile()->print();
	return 0;
}