#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class LoadFromFile
{
public:

    std::string LoadAPIKey()
    {
        std::fstream myFile;
        myFile.open(".\\API.txt");

        if (myFile.is_open())
        {
            getline(myFile, API_KEY);
            myFile.close();
        }

        return API_KEY;
    }

private:

    std::string API_KEY;
};