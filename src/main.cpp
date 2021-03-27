#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(a) std::cout << a << '\n'
#endif // !LOGA_MACRO

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "kslibs.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> cmdArgsVec(argv, argv + argc);

	std::unique_ptr<kslibs> program = std::make_unique<kslibs>(cmdArgsVec);


//	std::cout << "Test \n"; 
    return 0;
} 
