#include "VectorManip.h"

int VectorManip::ChooseFromVector(const std::vector<std::string> &choices, std::string option)
{
    std::cout << "Choose " << option << " (number or name works):\n";
    int i;
    std::string choice;
    for(i = 0; i < choices.size(); i++)
    {
        std::cout << i << ": " << choices[i] << "\n";
    }
    i = -1;
    while(true)
    {
        std::cin >> choice;
        if((choice.find_first_not_of("0123456789") == std::string::npos) == true)
        {
            i = std::stoi(choice);
            if(i >= 0 && i < choices.size())
            {
                std::cout << choices[i] << " has been chosen.\n";
                return i;
            }          
        }
        else
        {
            for(i = 0; i < choices.size(); i++)
            {
                if(strcasecmp(choice.c_str(),choices[i].c_str()) == 0)
                {
                    std::cout << choices[i] << " has been chosen.\n";
                    return i;
                }
            }
        }
        std::cout << "Please enter a valid " << option << ".\n";
    }
}

void VectorManip::RemoveFromVector(std::vector<std::string> &vec, std::string option)
{
    int index = -1;
    for(int i = 0; i < vec.size(); i++)
    {
        if(strcasecmp(vec.at(i).c_str(), option.c_str()) == 0)
        {
            index = i;
            break;
        }
    }
    if(!(index == -1))
    {
        vec.erase(vec.begin()+index);
    }
}

bool VectorManip::IsValueInVector(const std::vector<std::string> &vec, const std::string &value)
{
    for(auto str : vec)
    {
        if(strcasecmp(str.c_str(),value.c_str()) == 0)
        {
            return true;
        }
    }
    return false;
}

