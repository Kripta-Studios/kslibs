#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(text) std::cout << text << '\n'
#endif // !LOGA_MACRO

#define GET(text, referenceStore) std::cout << text; std::cin >> &referenceStore;


#include "kslibs.h"
#include "fileManager.h"
#include "cmdEditor.h"

// Constructors and destructors
kslibs::~kslibs()
{
	std::cout << "Destructor called \n";	
}
kslibs::kslibs(std::vector<string>& cmdrgs)
{
	// TODO: the part that create and execute the command should be inside the run func.
	boolArgs["run"] = false;
	boolArgs["clean"] = false;
	boolArgs["compile"] = false;
	boolArgs["edit"] = false;

	cmdArgs = cmdrgs;
	argsParser(cmdArgs);
	fileManager fileManager;
	string path = fileManager.getPath();
	std::map<string, string> infoFromFile = fileManager.getInfoMAP();
	/*
	string CMDCompile = createCommand(infoFromFile);
	
	//system(CMDCompile.c_str());
	//LOG(CMDCompile);
	string testingWitTheBASH = "./.silentCMD \'" + CMDCompile + "\' > /dev/null";
	system(testingWitTheBASH.c_str());
	*/
	if (boolArgs["run"]) runCommand(infoFromFile);
	else if (boolArgs["clean"]) cleanCommand(boolArgs);
	else if (boolArgs["compile"]) compileCommand(infoFromFile);
	else if (boolArgs["edit"]) editCommand(infoFromFile, path);
	else printHelp(infoFromFile);
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
void kslibs::runCommand(std::map<string, string>& infoFromFile)
{
	std::remove(infoFromFile["OutputName"].c_str());
	string CMDCompile = createCommand(infoFromFile);
	string testingWitTheBASH = "./.silentCMD \'" + CMDCompile + "\' > /dev/null";
	system(testingWitTheBASH.c_str());
	printf("\n");
	system(infoFromFile["OutputName"].c_str());
	//LOG(testingWitTheBASH);
}

void kslibs::cleanCommand(std::map<string, bool>& boolArgs)
{


}
	
void kslibs::compileCommand(std::map<string, string>& infoFromFile)
{
	std::remove(infoFromFile["OutputName"].c_str());
	string CMDCompile = createCommand(infoFromFile);
	string testingWitTheBASH = "./.silentCMD \'" + CMDCompile + "\' > /dev/null";
	system(testingWitTheBASH.c_str());
	printf("\n");
}
	
void kslibs::editCommand(std::map<string, string>& infoFromFile, string& pathToConfig)
{
	cmdEditor cmdEdit(infoFromFile, pathToConfig);
	cmdEdit.printActualCMD();
	cmdEdit.editCMD();
}

string kslibs::createCommand(std::map<string, string>& infoAboutProj)
{
	// TODO: add the object files and all that stuff

	string cmd;
	//cmd = "g++ -o \"" + infoAboutProj["ProjectName"] + "\" " + 
	//infoAboutProj["SourcePath"] + "* -I" + infoAboutProj["LibPath"] 
	//+ "include" + " -L" + infoAboutProj["LibPath"] + "lib -l";
	//LOG(infoAboutProj["OutputName"]);
	cmd = "g++ -o \"" + infoAboutProj["OutputName"] + "\" ";
	if (infoAboutProj["SourcePath"] != ".")
	{
		string copy;
		infoAboutProj["SourcePath"] += ';';
		
		for (uint8_t it = 0; it < infoAboutProj["SourcePath"].length() -1; ++it)
		{
			string newSrcPath;
			if (it == 0)
			{
				newSrcPath.clear();
				for (uint8_t ij = it; infoAboutProj["SourcePath"][ij] != ';'; ++ij)
				{
					if (infoAboutProj["SourcePath"][ij+1] == ';')
					{
						newSrcPath += infoAboutProj["SourcePath"][ij];
						if (newSrcPath.find(".cpp") == string::npos)
						{
								newSrcPath += "*.cpp";
							
						}
					} 
					else newSrcPath += infoAboutProj["SourcePath"][ij];
				}
				copy+= newSrcPath + ';';
			}
			if (infoAboutProj["SourcePath"][it] == ';')
			{
				newSrcPath.clear();
				for (uint8_t ij = it+1;(infoAboutProj["SourcePath"][ij] != ';'); ++ij)
				{
					if (infoAboutProj["SourcePath"][ij+1] == ';')
					{
						newSrcPath += infoAboutProj["SourcePath"][ij];
						if (newSrcPath.find(".cpp") == string::npos)
						{
								newSrcPath += "*.cpp";
							
						}
					} 
					else newSrcPath += infoAboutProj["SourcePath"][ij];
				}
				copy+= newSrcPath + ';';
			}
		}
		infoAboutProj["SourcePath"] = copy;

		for (auto& v : infoAboutProj["SourcePath"])
		{
			if (v == ';') {cmd.push_back(' ');}
			else cmd.push_back(v);
		}
		/*
		if ((infoAboutProj["SourcePath"][infoAboutProj["SourcePath"].length() - 1] != 'p') &&
				(infoAboutProj["SourcePath"][infoAboutProj["SourcePath"].length() - 2] != 'p') &&
				(infoAboutProj["SourcePath"][infoAboutProj["SourcePath"].length() - 3] != 'c') &&
				(infoAboutProj["SourcePath"][infoAboutProj["SourcePath"].length() - 1] != '.'))
				cmd += infoAboutProj["SourcePath"] + "*.cpp";
			else cmd += infoAboutProj["SourcePath"];
		
		for (auto& v : infoAboutProj["LibNames"])
		{
			if (v == ';') {cmd.push_back(' '); cmd.push_back('-'); cmd.push_back('l');}
			else cmd.push_back(v);
		}
		*/

	} 
	else cmd += ".";

	// TODO: check correctly if the paths without extensions are the same, and then use the -I flag or not
	/*
	if (infoAboutProj["HeadersPath"] != infoAboutProj["SourcePath"])
	{
		if ((infoAboutProj["HeadersPath"][infoAboutProj["HeadersPath"].length() - 1] != 'h') &&
			(infoAboutProj["HeadersPath"][infoAboutProj["HeadersPath"].length() - 2] != '.'))
			cmd += " -I" + infoAboutProj["HeadersPath"] + "*.h";
		else cmd += " -I" + infoAboutProj["HeadersPath"];

	} 
	else ;
	*/

	if (infoAboutProj["LibPath"] != "NULL/")
		cmd += " -I" + infoAboutProj["LibPath"] + "include" + " -L" + infoAboutProj["LibPath"] + "lib -l";
	else cmd += " -l";

	if (infoAboutProj["LibNames"] != "NULL")
	{
		for (auto& v : infoAboutProj["LibNames"])
		{
			if (v == ';') {cmd.push_back(' '); cmd.push_back('-'); cmd.push_back('l');}
			else cmd.push_back(v);
		}
	}
	else cmd += " ";
	
	string importantModifiers = " -O2 -Wall -Wregister -std=c++17 -g -Wall -Wdisabled-optimization -Wuninitialized -Wextra";
	for (auto& x : importantModifiers) cmd.push_back(x);
	LOG(cmd);
	return cmd;
}

void kslibs::printHelp(std::map<string, string>& infoFromFile)
{
	std::cout 	<< "Options availables:\n"
				<< "RUN project:\t\t-r\n"
				<< "CLEAN project:\t\t-cln\n"
				<< "COMPILE project:\t-c\n"
				<< "EDIT configuration:\t-ed\n"
				<< "\n"
				<< "ACTUAL INFORMATION OF THE PROJECT";
	printf("\nProject Name:\t");
    printf(infoFromFile["ProjectName"].c_str());
    printf("\nOutput Name:\t");
    printf(infoFromFile["OutputName"].c_str());
    printf("\nSource Path:\t");
    printf(infoFromFile["SourcePath"].c_str());
    printf("\nHeaders Path:\t");
    printf(infoFromFile["HeadersPath"].c_str());
    printf("\nLib Path:\t");
    printf(infoFromFile["LibPath"].c_str());
    printf("\nLib Names:\t");
    printf(infoFromFile["LibNames"].c_str());
}