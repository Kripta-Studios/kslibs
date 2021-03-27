#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(a) std::cout << a << '\n'
#endif // !LOGA_MACRO

#include "kslibs.h"
#include "fileManager.h"
#include <iostream>

// Constructors and destructors
kslibs::~kslibs()
{
	std::cout << "Destructor called \n";	
}
kslibs::kslibs(std::vector<string>& cmdrgs)
{
	boolArgs["run"] = false;
	boolArgs["clean"] = false;
	boolArgs["compile"] = false;
	boolArgs["edit"] = false;

	cmdArgs = cmdrgs;
	argsParser(cmdArgs);

	fileManager a;

	if (boolArgs["run"]) runCommand(boolArgs);
	if (boolArgs["clean"]) cleanCommand(boolArgs);
	if (boolArgs["compile"]) compileCommand(boolArgs);
	if (boolArgs["edit"]) editCommand(boolArgs);
}

void kslibs::argsParser(std::vector<string>& cmdArgs)
{
	for (auto& v : cmdArgs)
	{
		if (v == "-r") boolArgs["run"] = true;
		else if (v == "-cln") boolArgs["clean"] = true;
		else if (v == "-c") boolArgs["compile"] = true;
		else if (v == "-ed") boolArgs["edit"] = true;
 	}
}
// TODO: all the functions for the commands
void kslibs::runCommand(std::map<string, bool>& boolArgs)
{


}

void kslibs::cleanCommand(std::map<string, bool>& boolArgs)
{


}
	
void kslibs::compileCommand(std::map<string, bool>& boolArgs)
{


}
	
void kslibs::editCommand(std::map<string, bool>& boolArgs)
{


}