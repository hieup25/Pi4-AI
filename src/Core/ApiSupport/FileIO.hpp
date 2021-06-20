#pragma once
#include <fstream>
#include <vector>
#include <iostream>

class FileIO
{
    private:
        /* data */
    public:
        FileIO(/* args */);
        ~FileIO();
        int loadLabel(std::string path, std::vector<std::string>& vec_labels);
};

FileIO::FileIO(/* args */)
{
}

FileIO::~FileIO()
{
}
int FileIO::loadLabel(std::string path, std::vector<std::string>& vec_labels)
{
    int countLine = 0;
	std::ifstream fileLabel(path);
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
            vec_labels.push_back(line);
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