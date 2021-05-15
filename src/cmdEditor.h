#ifndef CMDEDITOR_H
#define CMDEDITOR_H

#include <string>
#include <map>
#include <iostream>
#include <stdio.h>
#include "fileManager.h"

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
