#include <iostream>
#include "Character.h"

int main() {
    std::vector<std::string> yesno = {"Yes", "No"};
    
    Character character;
    character.InitializeCharacter(); 
    character.Run();  
    //character.PrintCharacter();

    std::cout << "Would you like to save the character?\n";
    std::cout << "Note that the filename will be the character name and it will be saved in the saves directory\n";
    if(VectorManip::ChooseFromVector(yesno, "whether to save") == 0)
    {
        character.SaveCharacter();
    }
    return 0;
}