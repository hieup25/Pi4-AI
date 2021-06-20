#pragma once
class FileIO
{
private:
    /* data */
public:
    FileIO(/* args */);
    ~FileIO();
    void loadLabel(std::string path, std::vector<std::string>& vec_labels);
};

FileIO::FileIO(/* args */)
{
}

FileIO::~FileIO()
{
}
#include <fstream>
#include <vector>
#include <iostream>

int FileIO::loadLabel(std::string path, std::vector<std::string>& vec_labels)
{
    int countLine = 0;
	std::ifstream fileLabel(nameFile);
	if(!fileLabel)
    {
        printf("Reading file label error \n");
        return -1;
    }
    while(fileLabel.is_open())
    {
        std::string line;
        while (std::getline(fileLabel, line)) 
        {
            labels.push_back(line);
            countLine++;
        }
        fileLabel.close();
    }
    if( countLine < 1)
    {
        printf("There is no class in file label\n");
        return -1;
    }
	return 0;
}