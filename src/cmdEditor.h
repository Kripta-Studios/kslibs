#ifndef CMDEDITOR_H
#define CMDEDITOR_H

#include "rang.hpp"
#include "fileManager.h"
#include "macroUtils.h"

#include <string>
#include <map>
#include <iostream>
#include <stdio.h>

using std::string;

class cmdEditor
{
private:
    std::map<string, string> infoFromFile;
    string pathToConfig;
    // PRIVATE METHODS
    

public:
    // PUBLIC METHODS

    void printActualCMD();
    void editCMD();
    void updateDataConfig();
    cmdEditor(std::map<string, string>& infoFromFile, string& pathToConfig);
    ~cmdEditor();

};


#endif // !CMDEDITOR_H
