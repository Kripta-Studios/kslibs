#ifndef KSLIBS_H
#define KSLIBS_H

#include <vector>
#include <string>
#include <map>

using std::string;
// TODO: Commands MANAGERS Functions
class kslibs
{
private:
	std::vector<string> cmdArgs;
	std::vector<string> libs;
	string output;
	int numFiles;
	std::vector<string> nameFiles; 
	std::map<string, bool> boolArgs;
	
	// The PARSER
	void argsParser(std::vector<string>& cmdArgs);

	// Commands MANAGERS
	void runCommand(std::map<string, string>& infoFromFile);
	void cleanCommand(std::map<string, bool>& boolArgs);
	void compileCommand(std::map<string, string>& infoFromFile);
	void editCommand(std::map<string, string>& infoFromFile, string& pathToConfig);
	string createCommand(std::map<string, string>& infoAboutProj);
	void printHelp(std::map<string, string>& infoFromFile);

public:
	~kslibs();
	kslibs(std::vector<string>& cmdrgs);
	
};

#endif // !KSLIBS_H

