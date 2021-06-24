#include "kslibs.h"

// Constructors and destructors
kslibs::~kslibs()
{
	RANGL(rang::fg::red, rang::style::blink, "\nDestructor called\n");	
}
kslibs::kslibs(std::vector<string>& cmdrgs)
{
	// TODO: the part that create and execute the command should be inside the run func.
	boolArgs["run"] = false;
	boolArgs["clean"] = false;
	boolArgs["compile"] = false;
	boolArgs["edit"] = false;
	boolArgs["show"] = false;
	boolArgs["download"] = false;

	cmdArgs = cmdrgs;
	argsParser(cmdArgs);
	fileManager fileManager;
	string path = fileManager.getPath();
	std::map<string, string> infoFromFile = fileManager.getInfoMAP();

	if (boolArgs["run"]) runCommand(infoFromFile);
	else if (boolArgs["clean"]) cleanCommand(boolArgs);
	else if (boolArgs["compile"]) compileCommand(infoFromFile);
	else if (boolArgs["edit"]) editCommand(infoFromFile, path);
	else if (boolArgs["show"]) showCommand(infoFromFile);
	else if (boolArgs["download"]) downloadCommand(cmdArgs, cmdArgs[2]);
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
		else if (v == "-cmd") boolArgs["show"] = true;
		else if ((v == "-dowl") && (cmdArgs.size() >= 3)) boolArgs["download"] = true;
		else if ((v == "-dowl") && (cmdArgs.size() < 3)) RANGL(rang::style::reversed, rang::fg::red, "Not enough arguments to the option -dowl. REQUIRED: 3; GIVEN: ", cmdArgs.size())
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

void kslibs::showCommand(std::map<string, string>& infoFromFile)
{
	string showCMD = createCommand(infoFromFile);
	RANGL(rang::style::bold, rang::fg::green, "\nThe following cmd is used to compile the project:\n--> ", showCMD.c_str() );
}

void kslibs::downloadCommand(const std::vector<std::string>& cmdArgs, const string& libName)
{
	// TODO: IMPLEMENT THE YAML PARSER FOR THE URL
	string DB = consultDB();
	dataParser dataParse(DB); // use this to get the url of the libName
	//dataParse.printDataLib();

	string nameFile;
	string url = libName; // the second comand argument is waht gets downloaded
	//#warning URL IS NOT DEFINED LACK A YAML PARSER	
	for (uint8_t i = url.size() - 1; i > 0; --i)
	{
		if ((url[i] == '/') || (url[i] == '\\'))
		{
			++i;
			do
			{
				nameFile.push_back(url[i]);
				++i;
			} while(i < url.size());
			break;
		}
	}
	HTTPDownloader downloader;
	FILE* out;
	downloader.download(url, out, nameFile);
}

string kslibs::createCommand(std::map<string, string>& infoAboutProj)
{
	// TODO: add the object files and all that stuff

	string cmd;
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
	} 
	else cmd += ".";

	if ((infoAboutProj["HeadersPath"] != "."))
	{
		string copy;
		infoAboutProj["HeadersPath"] += ';';
		
		for (uint8_t it = 0; it < infoAboutProj["HeadersPath"].length() -1; ++it)
		{
			string newHeadPath;
			if (it == 0)
			{
				newHeadPath.clear();
				for (uint8_t ij = it; infoAboutProj["HeadersPath"][ij] != ';'; ++ij)
				{
					if (infoAboutProj["HeadersPath"][ij+1] == ';')
					{
						newHeadPath += infoAboutProj["HeadersPath"][ij];
						if ((newHeadPath.find(".h") == string::npos) && (newHeadPath.find(".hpp") == string::npos))
						{
							// TODO: ADD A *.hpp IDK HOW TO DO IT, THINK ABOUT IT
							newHeadPath += "*.h";
						}
					} 
					else newHeadPath += infoAboutProj["HeadersPath"][ij];
				}
				copy+= newHeadPath + ';';
			}
			if (infoAboutProj["HeadersPath"][it] == ';')
			{
				newHeadPath.clear();
				for (uint8_t ij = it+1;(infoAboutProj["HeadersPath"][ij] != ';'); ++ij)
				{
					if (infoAboutProj["HeadersPath"][ij+1] == ';')
					{
						newHeadPath += infoAboutProj["HeadersPath"][ij];
						if ((newHeadPath.find(".h") == string::npos) || (newHeadPath.find(".hpp") == string::npos))
						{
							// TODO: ADD A *.hpp IDK HOW TO DO IT, THINK ABOUT IT
							//newHeadPath += "*.h";
							continue;	
						}
					} 
					else newHeadPath += infoAboutProj["HeadersPath"][ij];
				}
				copy+= newHeadPath + ';';
			}
		}
		infoAboutProj["HeadersPath"] = copy;
	} 
	else ;

	for (uint8_t i = infoAboutProj["HeadersPath"].length() - 1; i > 0; --i)
	{
		if ( ((infoAboutProj["HeadersPath"][i] == 'p') && (infoAboutProj["HeadersPath"][i-1] == 'p') && (infoAboutProj["HeadersPath"][i-2] == 'h') && (infoAboutProj["HeadersPath"][i-3] == '.'))  || ((infoAboutProj["HeadersPath"][i] == 'h') && (infoAboutProj["HeadersPath"][i-1] == '.')))
		{
			 while (infoAboutProj["HeadersPath"][i] != '.')
			 {
				infoAboutProj["HeadersPath"][i] = ' ';
				--i;
			 }
			 infoAboutProj["HeadersPath"][i] = ' ';
		}
	}
	for (uint8_t i = infoAboutProj["HeadersPath"].length() - 1; i > 0; --i)
	{
		if (infoAboutProj["HeadersPath"][i] == '*')
			infoAboutProj["HeadersPath"][i] = ' ';
	}

	if ((cmd[cmd.length() - 3] != ' ') && (cmd[cmd.length() - 3] != '-') && (cmd[cmd.length() - 1] != 'I'))
		cmd += " -I";

	if (infoAboutProj["HeadersPath"] != ".")
	{
		for (auto& v : infoAboutProj["HeadersPath"])
		{
			// TODO: UN FOR CLASSIC PARA SABER SI EL SIGUIENTE ES HPP
			if (v == ';') {cmd.push_back(' '); cmd.push_back('-'); cmd.push_back('I');}
			// TODO: CON FOR CLASSIC MIRAR SI ES HPP O BUSCAR FORMA DE ELIMINAR LOS HPP
			else if ((v == '.' ) || (v == 'h' ) || (v == '.' ) || (v == '.' )) continue;
			else cmd.push_back(v);
		}
	}
	cmd.push_back(' ');
	for (uint8_t i = 0; i < cmd.length(); ++i)
	{
		if ((cmd[i] == 'I') && (cmd[i-1] == '-') && (cmd[i+1] == ' '))
		{
			cmd[i] = ' ';
			cmd[i - 1] = ' ';
			cmd[i + 1] = ' ';
		}
	}

	if (infoAboutProj["LibPath"] != "NULL/")
		cmd += " -I" + infoAboutProj["LibPath"] + "include" + " -L" + infoAboutProj["LibPath"] + "lib -l";
	else;

	if (infoAboutProj["LibNames"] != "NULL")
	{
		cmd += " -l";
		for (auto& v : infoAboutProj["LibNames"])
		{
			if (v == ';') {cmd.push_back(' '); cmd.push_back('-'); cmd.push_back('l');}
			else cmd.push_back(v);
		}
	}
	else cmd += " ";
	uint8_t passedQuote = 0;
	string formattedCmd;
	for (uint8_t i = 0; i < cmd.length(); ++i)
	{
		if (cmd[i] == '\"') ++passedQuote;
		if ((passedQuote >= 2) && (cmd[i-1] == ' ') && (cmd[i] == ' ') )
			continue;
		else formattedCmd += cmd[i];
	}

	cmd = formattedCmd;

	string importantModifiers = " -O2 -Wall -Wregister -std=c++17 -g -Wall -Wdisabled-optimization -Wuninitialized -Wextra";
	for (auto& x : importantModifiers) cmd.push_back(x);

	return cmd;
}

void kslibs::printHelp(std::map<string, string>& infoFromFile)
{
	RANGL(rang::style::underline, rang::style::reversed, rang::fg::cyan,"\nOptions availables:");
	RANGL(rang::style::bold, rang::fg::yellow,"RUN project:\t\t\t",rang::style::reversed        ,rang::fg::black,"-r");
	RANGL(rang::style::bold, rang::fg::yellow,"CLEAN project:\t\t\t",rang::style::reversed      ,rang::fg::black,"-cln");
	RANGL(rang::style::bold, rang::fg::yellow,"COMPILE project:\t\t",rang::style::reversed      ,rang::fg::black,"-c");
	RANGL(rang::style::bold, rang::fg::yellow,"EDIT configuration:\t\t",rang::style::reversed   ,rang::fg::black,"-ed");
	RANGL(rang::style::bold, rang::fg::yellow,"SHOW command to compile:\t",rang::style::reversed,rang::fg::black,"-cmd");
	RANGL(rang::style::bold, rang::fg::yellow,"DOWNLOAD an available lib:\t",rang::style::reversed,rang::fg::black,"-dowl {NAME_OF_LIB}");
	RANGL(rang::style::bold, rang::fg::yellow," ");
	RANGL(rang::style::reversed, rang::fg::red,"ACTUAL INFORMATION OF THE PROJECT:");
	
	printf("Project Name:\t");
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

string kslibs::consultDB()
{
	HTTPDownloader downloader;
	string downloaded = downloader.download("https://raw.githubusercontent.com/Kripta-Studios/kripta-studios.github.io/master/assets/kslibsDB/ListOfAvailableLibs");
	return downloaded;
}