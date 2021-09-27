#include "dataParser.h"

dataParser::dataParser(const string& nameFile, size_t& sizeOfFile)
{
    size_t size = sizeOfFile;
    this->nameFile = nameFile;
    this->file.open(nameFile);
    buffer = initFile();
}

dataParser::dataParser(const string& stringWithContent)
{
    this->stringWithContent = stringWithContent;
    this->buffer.reserve(stringWithContent.size()+1);
    for (auto& v : stringWithContent) this->buffer.push_back(v);
    parseTokens(buffer);
}

dataParser::~dataParser()
{
    this->file.close();
}

std::vector<char>& dataParser::initFile()
{
    if (this->file)
    {
        /*
            * Get the size of the file
            */
        this->file.seekg(0,std::ios::end);
        std::streampos length = this->file.tellg();
        this->file.seekg(0,std::ios::beg);

        /*
            * Use a vector as the buffer.
            * It is exception safe and will be tidied up correctly.
            * This constructor creates a buffer of the correct length.
            * Because char is a POD data type it is not initialized.
            *
            * Then read the whole file into the buffer.
            */
        std::vector<char> buffer(length);
        file.read(&buffer[0],length);
    }
    else if (!this->file) {std::cout << "ERROR: FILE NOT FOUND!!!\n";}
}

void dataParser::parseTokens(const std::vector<char>& buffer)
{
    bool sector = false;
    for (uint32_t i = 0; i < buffer.size(); ++i)
    {
        if ((buffer[i] == '-') && (buffer[i+1] == '|') && (buffer[i+2] == '-') && (sector == false))
        {
            sector = true;
            i += 2;
            indexes.first = i;
            //LOG(indexes.first);
        }
        else if ((buffer[i] == '-') && (buffer[i+1] == '/') && (buffer[i+2] == '-') && (sector == true))
        {
            sector = false;
            i += 2;
            indexes.second = i;
            //LOG(indexes.second);
            tokenizer(buffer, indexes);
        }
    }
}

void dataParser::tokenizer(const std::vector<char>& buffer, std::pair<uint32_t, uint32_t> indexes)
{
    // TODO: use the ';' delimiter to read the lines 
    for (uint32_t i = indexes.first; i < indexes.second; ++i)
    {

        string line;
        for (int i = 0; i < indexes.second; ++i)
            //LOG(stringWithContent.c_str()[i]);
            //LOG(line);
            if (stringWithContent.c_str()[i] == 'l' && stringWithContent.c_str()[i+1] == 'i'
                && stringWithContent.c_str()[i+2] == 'b' && stringWithContent.c_str()[i+3] == 'N'
                && stringWithContent.c_str()[i+4] == 'a' && stringWithContent.c_str()[i+5] == 'm'
                && stringWithContent.c_str()[i+6] == 'e' && stringWithContent.c_str()[i+7] == ':')
            {
                i += 8;
                string Var;
                if (stringWithContent.c_str()[i-1] == ':' && stringWithContent.c_str()[i] == ' ')
                {
                    
                    for (int j = i+1; stringWithContent.c_str()[j] != ';'; j++)
                        Var.push_back(stringWithContent.c_str()[j]);
                }                    
                if (dataLib["libName"].find(Var) == std::string::npos) 
                    dataLib["libName"] += Var + ' ';
            } 
    }
}

void dataParser::printBuffer() const
{
    LOG("buffer:");
    for (auto& v : this->buffer)
        std::cout << v;
}
void dataParser::printDataLib() const
{
    LOG("dataLib:");
    for (auto& v : this->dataLib)
        std::cout << v.first << '\t' << v.second;
}