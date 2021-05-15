#include "cmdEditor.h"

#ifndef LOGA_MACRO
#define LOGA_MACRO
#define LOG(text) std::cout << text << '\n'
#endif // !LOGA_MACRO

cmdEditor::cmdEditor(std::map<string, string>& infoFromFile, string& pathToConfig)
{
    this->infoFromFile = infoFromFile;
    this->pathToConfig = pathToConfig;
}

cmdEditor::~cmdEditor()
{
    
}

void cmdEditor::printActualCMD()
{
    printf("\n1- Project Name: ");
    printf(this->infoFromFile["ProjectName"].c_str());
    printf("\n2- Output Name: ");
    printf(this->infoFromFile["OutputName"].c_str());
    printf("\n3- Source Path: ");
    printf(this->infoFromFile["SourcePath"].c_str());
    printf("\n4- Headers Path: ");
    printf(this->infoFromFile["HeadersPath"].c_str());
    printf("\n5- Lib Path: ");
    printf(this->infoFromFile["LibPath"].c_str());
    printf("\n6- Lib Names: ");
    printf(this->infoFromFile["LibNames"].c_str());

}

void cmdEditor::editCMD()
{
    string newData{};
    int dataMod = 0;
    
    do{    
        printf("\nInsert the number of the value to modify (type \"255\" to finish): ");
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	    std::cin >> dataMod;
        LOG(dataMod);
        switch (dataMod)
        {
        case 1:
            printf("Insert the new value for the Project Name: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newData);
            this->infoFromFile["ProjectName"] = newData;
            break;
        
        case 2:
            printf("Insert the new value for the Output Name: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newData);
            this->infoFromFile["OutputName"] = newData;
            break;

        case 3:
            printf("Insert the new value for the Source Path: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newData);
            this->infoFromFile["SourcePath"] = newData;
            break;

        case 4:
            printf("Insert the new value for the Headers Path: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newData);
            this->infoFromFile["HeadersPath"] = newData;
            LOG(this->infoFromFile["HeadersPath"]);
            break;

        case 5:
            printf("Insert the new value for the Lib Path: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newData);
            this->infoFromFile["LibPath"] = newData;
            break;

        case 6:
            printf("Insert the new value for the Lib Names: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newData);
            this->infoFromFile["LibNames"] = newData;
            break;

        default:
            break;
        }
        printActualCMD();
    }while (dataMod != 255);
    string newSTR;
    newSTR.clear();
    for (uint8_t i = 0; i < this->infoFromFile["SourcePath"].length(); ++i)
    {
        if (this->infoFromFile["SourcePath"][i] == ' ')
            continue;
        else newSTR += this->infoFromFile["SourcePath"][i];
    }
    newSTR.clear();
    for (uint8_t i = 0; i < this->infoFromFile["HeadersPath"].length(); ++i)
    {
        if (this->infoFromFile["HeadersPath"][i] == ' ')
            continue;
        else newSTR += this->infoFromFile["HeadersPath"][i];
    }
    newSTR.clear();
    for (uint8_t i = 0; i < this->infoFromFile["LibNames"].length(); ++i)
    {
        if (this->infoFromFile["LibNames"][i] == ' ')
            continue;
        else newSTR += this->infoFromFile["LibNames"][i];
    }
    updateDataConfig();
}

void cmdEditor::updateDataConfig()
{
    fileManager FILE(this->pathToConfig);
    FILE.resetFile(this->infoFromFile);
}
