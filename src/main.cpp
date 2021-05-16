#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(text) std::cout << text << '\n'
#endif // !LOGA_MACRO

#define GET(text, referenceStore) std::cout << text; std::cin >> &referenceStore;

#include "kslibs.h" // MUST BE ABOVE EVERYTHING

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// EXTERNAL DEPENDENCIES



// sha1sum src/something Get-FileHash src/something -Algorithm sha1  
// that is for knowing if a file changed. 
int main(int argc, char* argv[])
{
	std::vector<std::string> cmdArgsVec(argv, argv + argc);

	std::unique_ptr<kslibs> program = std::make_unique<kslibs>(cmdArgsVec);


//	std::cout << "Test \n"; 
    return 0;
} 
