#include <cstdlib>
#include <iostream>

int main(int argc,const char* argv[])
{
	std::string cmd;	
	if (argc == 1) return 0;
	for (int i = 1; i < argc; ++i)
		std::cout << argv[i];
	std::cout << '\n';
	system(argv[1]);
	return 1;
}
