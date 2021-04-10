#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(text) std::cout << text << '\n'
#endif // !LOGA_MACRO

#define GET(text, referenceStore) std::cout << text; std::cin >> referenceStore;


#include "fileManager.h"


fileManager::fileManager(/* args */) : pathToConfigKslibs(".config.kslibs"), fileIn(new std::ifstream(pathToConfigKslibs))
{
    
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
    LOG("In the current doesn't exist a \'.config.kslibs\' file.\n");
trollerInpath:
    GET("Enter the path to your \'.config.kslibs\' file \nor enter \'newkslibs\' to use create a new one: ", pathToConfigKslibs);
    
    if (pathToConfigKslibs == "newkslibs") {newConfigFile(); return;}

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
    std::map<int, double> a;
    // Variable about the data of the project
    string projName, srcPath, headPath, libPath, libNames;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Insert the name of the project: ";
    std::getline(std::cin, projName);
    GET("Insert the path of the source files (Ex: .) (Ex: src/): ", srcPath);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    GET("Insert the path of the header files (Ex: .) (Ex: hed/): ", headPath);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    GET("Insert the path of the library (don't write the include/ or lib/ path)(Ex: ../extern/SFML/)(NULL): ", libPath);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Insert the name of the library/ies without the \'-l\'. Use the \';\' as separtor \n(Ex for boost::thread: boost_thread ; boost_system)(NULL): " ;
    std::getline(std::cin, libNames);

    // Writing to the file
    newFile << "ProjectName: " + projName;
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

        if (line.find("SourcePath: ") != std::string::npos)
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
            containerConfigData["SourcePath"] = Var;
        }

        if (line.find("HeadersPath: ") != std::string::npos)
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
        || (containerConfigData.find("LibPath")  == containerConfigData.end())    || ((containerConfigData.find("LibNames"))  == containerConfigData.end())
        || (containerConfigData["ProjectName"].empty()) || (containerConfigData["SourcePath"].empty()) || (containerConfigData["HeadersPath"].empty())
        || (containerConfigData["LibPath"].empty())     || (containerConfigData["LibNames"].empty()))
    {
        LOG("The file \'.confg.kslibs\' is corrupt or empty. You should create a new one.");
        notExistFile();
    }

}