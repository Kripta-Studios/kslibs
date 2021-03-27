#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(a) std::cout << a << '\n'
#endif // !LOGA_MACRO

#include "fileManager.h"
#include <iostream>


fileManager::fileManager(/* args */)
{
    
    bool existFile = fileIn->is_open();  // IF result == 0 THE THE FILE DOESN'T EXIST
    
    if (existFile == 0) fileManager::notExistFile();
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

    

}