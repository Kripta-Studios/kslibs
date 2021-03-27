#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>

using std::string;

class fileManager
{
private:
    std::ifstream* fileIn = new std::ifstream(".config.kslibs");
    
public:
    fileManager(/* args */);
    ~fileManager();
    void notExistFile();
};









#endif // !FILEMANAGER_H