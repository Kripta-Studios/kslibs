#ifndef FILEMANAGER_H
#define FILEMANAGER_H

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
    fileManager(/* args */);
    ~fileManager();
    
    // GETTERS
    string getPath() {return pathToConfigKslibs;}
    std::map<string, string> getInfoMAP() {return containerConfigData;};
    
};




#endif // !FILEMANAGER_H