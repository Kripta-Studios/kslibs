#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "rang.hpp" // MUST BE ABOVE EVERYTHING
#include "macroUtils.h"

#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <map>

using std::string;

class fileManager
{
private:
    bool existFile;
    string pathToConfigKslibs;
    std::ifstream* fileIn;
    std::map<string, string> containerConfigData;

    // Functions 
    void notExistFile();
    void newConfigFile();
    void configFileParser(string* pathToAConfigFile);

public:
    fileManager(string pathConfigFile);
    fileManager();
    ~fileManager();
    
    // GETTERS functions
    string getPath() {return pathToConfigKslibs;}
    std::map<string, string> getInfoMAP() {return containerConfigData;};
    void resetFile(std::map<string, string> newDataToFile);
    
};




#endif // !FILEMANAGER_H