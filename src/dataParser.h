#include "rang.hpp"
#include "macroUtils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using std::string;

class dataParser
{
private:
    string nameFile, stringWithContent;
    std::ifstream file;
    std::vector<char> buffer;
    std::pair<uint32_t, uint32_t> indexes;
    std::map<string, string> dataLib;

    std::vector<char>& initFile();
    void parseTokens(const std::vector<char>& buffer);
    void tokenizer(const std::vector<char>& buffer, std::pair<uint32_t, uint32_t> indexes);

public:
    dataParser(const string& nameFile, size_t& sizeOfFile);
    dataParser(const string& stringWithContent);
    ~dataParser();
    
    void printBuffer() const;
    void printDataLib() const;

    std::map<string, string> getDataLib() const {return dataLib;}

};
