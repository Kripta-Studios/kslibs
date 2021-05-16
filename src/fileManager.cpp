#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(text) std::cout << text << '\n'
#endif // !LOGA_MACRO

#define GET(text, referenceStore) std::cout << text; std::cin >> referenceStore;


#include "fileManager.h"


fileManager::fileManager(string pathConfigFile)
{
    this->pathToConfigKslibs = pathConfigFile;
    this->fileIn = new std::ifstream(pathToConfigKslibs);
    existFile = fileIn->is_open();  // IF result == 0 THE THE FILE DOESN'T EXIST
    if (existFile == 0) fileManager::notExistFile();
    else configFileParser(&pathToConfigKslibs);
}

fileManager::fileManager()
{
    this->pathToConfigKslibs = ".config.kslibs";
    this->fileIn = new std::ifstream(pathToConfigKslibs);
    existFile = fileIn->is_open();  // IF result == 0 THE THE FILE DOESN'T EXIST
    if (existFile == 0) fileManager::notExistFile();
    else configFileParser(&pathToConfigKslibs);
}

fileManager::~fileManager()
{
    fileIn->close();
    delete fileIn;
}
// TODO:
void fileManager::notExistFile()
{
    LOG("In the current  directory doesn't exist a \'.config.kslibs\' file.\n");
trollerInpath:
    GET("Enter the path to your \'.config.kslibs\' file \nor enter \'newkslibs\' to create a new one or \'exit\': ", pathToConfigKslibs);

    if (pathToConfigKslibs == "exit") {return;}
    if (pathToConfigKslibs == "newkslibs") {newConfigFile(); return;}
    else
    {
        configFileParser(&pathToConfigKslibs);
    }
    delete fileIn;
    fileIn = new std::ifstream(pathToConfigKslibs);
 
    existFile = fileIn->is_open();
    if (!existFile) goto trollerInpath;
}

void fileManager::newConfigFile()
{
    // TODO: Add more options and info such as output path, object path, and library downloading

    // Clean the sreen in POSIX and in Win10
    system("cls||clear");
    LOG("###########################################################################");
    LOG("#                  WELCOME TO THE KSLIBS PROJECTS CREATOR                 #");
    LOG("###########################################################################\n");
    string defaultPath{".config.kslibs"};
    std::ofstream newFile{defaultPath};
    
    // Variable about the data of the project
    string projName, outputNameAndPath, srcPath, headPath, libPath, libNames;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Insert the name of the project: ";
    std::getline(std::cin, projName);
    std::cout << "Insert the name and path of the output file (Ex. folder/exec ): ";
    std::getline(std::cin, outputNameAndPath);
    GET("Insert the path of the source files (Ex: .) (Ex: src/;fs/main.cpp): ", srcPath);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    GET("Insert the path of the header files (Ex: .) (Ex: head/;fs/headf.h): ", headPath);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    GET("Insert the path of the library (don't write the include/ or lib/ path)(Ex: ../extern/SFML/)(NULL): ", libPath);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Insert the name of the library/ies without the \'-l\'. Use the \';\' as separtor \n(Ex for boost::thread: boost_thread ; boost_system)(NULL): " ;
    std::getline(std::cin, libNames);

    // Writing to the file
    newFile << "ProjectName: " + projName;
    newFile.flush();
    newFile << "\nOutputName: " + outputNameAndPath;
    newFile.flush();
    newFile << "\nSourcePath: " + srcPath;
    newFile.flush();
    newFile << "\nHeadersPath: " + headPath;
    newFile.flush();
    newFile << "\nLibPath: " + libPath;
    newFile.flush();
    newFile << "\nLibNames: " + libNames;
    newFile.flush();
    newFile.close();
    pathToConfigKslibs = defaultPath;
    configFileParser(&defaultPath);

}

void fileManager::configFileParser(string* pathToAConfigFile)
{
    string line;
    std::ifstream fileToParse{*pathToAConfigFile};
    while(std::getline(fileToParse, line))
    {
        if (line.find("ProjectName: ") != std::string::npos)
        {
            string Var;
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i-1] == ':' && line[i] == ' ')
                {
                    for (int j = i+1; j < line.length(); j++)
                        Var.push_back(line[j]);
                }
            }
            containerConfigData["ProjectName"] = Var;
        }

        if (line.find("OutputName: ") != std::string::npos)
        {
            string Var;
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i-1] == ':' && line[i] == ' ')
                {
                    for (int j = i+1; j < line.length(); j++)
                        Var.push_back(line[j]);
                }
            }
            containerConfigData["OutputName"] = Var;
        }

        if (line.find("SourcePath: ") != std::string::npos)
        {
            string Var;
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i-1] == ':' && line[i] == ' ')
                {
                /*  for (int j = i+1; j < line.length(); j++)
                        Var.push_back(line[j]);             */
                    for (int j = i+1; j < line.length(); j++)
                    {
                        if ((j == i) && (line[j] == ';')) continue;
                        if ( (line[line.length() -1] == ';') && (j == line.length() - 1) ) break; 
                        if (line[j] != ' ')
                            Var.push_back(line[j]);
                        
                    }
                    
                }
            }
            if (Var[Var.length() - 1] != '/' && Var[Var.length() - 1] != 'p' 
                && Var[Var.length() - 2] != 'p' && Var[Var.length() - 3] != 'c'
                && Var[Var.length() - 4] != '.') Var.push_back('/');
            containerConfigData["SourcePath"] = Var;
        }

        if (line.find("HeadersPath: ") != std::string::npos)
        {
            string Var;
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i-1] == ':' && line[i] == ' ')
                {
                /*  for (int j = i+1; j < line.length(); j++)
                        Var.push_back(line[j]);                */
                    for (int j = i+1; j < line.length(); j++)
                    {
                        if ((j == i) && (line[j] == ';')) continue;
                        if ( (line[line.length() -1] == ';') && (j == line.length() - 1) ) break; 
                        if (line[j] != ' ')
                            Var.push_back(line[j]);
                        
                    }

                }
            }
            if (Var[Var.length() - 1] != '/' && Var[Var.length() - 1] != 'h'
                && Var[Var.length() - 2] != '.' && Var[Var.length() - 1] != 'p' 
                && Var[Var.length() - 2] != 'p' && Var[Var.length() - 3] != 'h'
                && Var[Var.length() - 4] != '.') Var.push_back('/');
            containerConfigData["HeadersPath"] = Var;
        }

        if (line.find("LibPath: ") != std::string::npos)
        {
            string Var;
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i-1] == ':' && line[i] == ' ')
                {
                    for (int j = i+1; j < line.length(); j++)
                        Var.push_back(line[j]);
                }
            }
            if (Var[Var.length() - 1] != '/') Var.push_back('/');
            containerConfigData["LibPath"] = Var;
        }

        if (line.find("LibNames: ") != std::string::npos)
        {
            string Var;
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i-1] == ':' && line[i] == ' ')
                {
                    for (int j = i+1; j < line.length(); j++)
                    {
                        if ((j == i) && (line[j] == ';')) continue;
                        if ( (line[line.length() -1] == ';') && (j == line.length() - 1) ) break; 
                        if (line[j] != ' ')
                            Var.push_back(line[j]);
                        
                    }
                }
            }
            containerConfigData["LibNames"] = Var;
        }
    }

    if ((containerConfigData.empty() == true) || (containerConfigData.find("ProjectName") == containerConfigData.end()) 
        || (containerConfigData.find("SourcePath")  == containerConfigData.end()) || (containerConfigData.find("HeadersPath")== containerConfigData.end()) 
        || (containerConfigData.find("LibPath")  == containerConfigData.end())    || ((containerConfigData.find("LibNames"))  == containerConfigData.end())  || ((containerConfigData.find("OutputName"))  == containerConfigData.end())
        || (containerConfigData["ProjectName"].empty()) || (containerConfigData["SourcePath"].empty()) || (containerConfigData["HeadersPath"].empty())
        || (containerConfigData["LibPath"].empty())     || (containerConfigData["LibNames"].empty()) || (containerConfigData["OutputName"].empty()))
    {
        LOG("The file \'.confg.kslibs\' is corrupt or empty. You should create a new one.");
        notExistFile();
    }

}

void fileManager::resetFile(std::map<string, string> newDataToFile)
{
    std::ofstream newFile;
    newFile.open(this->pathToConfigKslibs, std::ofstream::out | std::ofstream::trunc);
    newFile.close();
    newFile.open(this->pathToConfigKslibs);
    // Writing to the file
    newFile << "ProjectName: " + newDataToFile["ProjectName"];
    newFile.flush();
    newFile << "\nOutputName: " + newDataToFile["OutputName"];
    newFile.flush();
    newFile << "\nSourcePath: " + newDataToFile["SourcePath"];
    newFile.flush();
    newFile << "\nHeadersPath: " + newDataToFile["HeadersPath"];
    newFile.flush();
    newFile << "\nLibPath: " + newDataToFile["LibPath"];
    newFile.flush();
    newFile << "\nLibNames: " + newDataToFile["LibNames"];
    newFile.flush();

    newFile.close();
}