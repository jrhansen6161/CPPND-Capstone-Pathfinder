#include <iomanip>
#include "DataParser.h"
#include "VectorManip.h"

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> fields;
    std::stringstream strstream(str);
    std::string field;
    while(std::getline(strstream, field, delimiter))
    {
        fields.emplace_back(field);
    }
    return fields;
}

bool IsStringInArray(const std::string stringArray[], int size, std::string &str)
{
    for(int i = 0; i < size; i++)
    {
        if(stringArray[i] == str)
        {
            return true;
        }
    }
    return false;
}

int GetPositiveIntegerAmount(std::string option)
{
    std::string input;
    while(true)
    {
        std::cout << "Please enter the amount of " << option << ":\n";
        std::cin >> input;
        if(input.find_first_not_of("0123456789") == std::string::npos)
        {
            return std::stoi(input);
        }
        std::cout << "Invalid amount, please give a positve integer\n";
    }
}

/*std::vector<std::string> ListDirectory(std::string path)
{
    std::vector<std::string> files;
    for(const auto & filename : std::filesystem::directory_iterator(path))
    {
        files.emplace_back(filename.path());
    }
    return files;
}*/

void Ancestry::PrintAncestry()
{
    std::cout << name << " HP: " << hp << " Speed: " << speed << "\n";
    std::cout << "\tBoosts: ";
    for(auto boost : boosts)
    {
        std::cout << boost << " ";
    }
    std::cout << "\n";
    std::cout << "\tFlaws: ";
    for(auto flaw : flaws)
    {
        std::cout << flaw << " ";
    }
    std::cout <<"\n";
}

std::vector<std::unique_ptr<Ancestry>> parseAncestry()
{
    std::string line, str;
    std::vector<std::string> boosts;
    std::vector<std::string> flaws;
    std::vector<std::unique_ptr<Ancestry>> ancestries;
    std::ifstream filestream(kAncestryPath);
    if(filestream.is_open())
    {
        while(std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            std::unique_ptr<Ancestry> ancestry = std::make_unique<Ancestry>() ;
            while(linestream >> str)
            {
                if(str == "Ancestry")
                {
                    linestream >> ancestry->name; 
                }
                else if(str == "HP")
                {                               
                    linestream >> str;
                    ancestry->hp = std::stoi(str);
                }
                else if(str == "Speed")
                {
                    linestream >> str;
                    ancestry->speed = std::stoi(str);
                }
                else if(str == "Boost")
                {
                    linestream >> str;
                    ancestry->boosts.emplace_back(str);
                }
                else if(str == "Flaw")
                {
                    linestream >> str;
                    ancestry->flaws.emplace_back(str);
                }
            }
           ancestries.emplace_back(std::move(ancestry));
        }
    }
    return ancestries;
}

void Background::PrintBackground()
{
    std::cout << name << " Available Boosts: ";
    for(auto boost : boosts)
    {
        std::cout << boost << " ";
    }
    std::cout << "Skill: " << skill << "\n";
}

std::vector<std::unique_ptr<Background>> parseBackground()
{
    std::string line, name, str;
    std::vector<std::string> boosts;
    std::vector<std::unique_ptr<Background>> backgrounds;
    std::ifstream filestream(kBackgroundPath);
    if(filestream.is_open())
    {
        while(std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            std::unique_ptr<Background> background = std::make_unique<Background>() ;
            while(linestream >> str){
                if(str == "Background")
                {
                    linestream >> background->name;
                }
                else if(str == "Boost")
                {
                    linestream >> str;
                    background->boosts.emplace_back(str);
                }
                else if(str == "Skill")
                {
                    linestream >> background->skill;
                }
            }
            backgrounds.emplace_back(move(background));
        }
    }
    return backgrounds;
}

void Class::PrintClass()
{
    std::cout << name << " Key Ability " << key << " HP " << hp << " Spell Casting: " << spellTradition << "\n";
    std::cout << "\tPerception: " << perception << "\t";
    for(int i = 0; i < saves.size(); i++)
    {
        std::cout << saves[i] << ": " << saveTraining[i] << "\t";
    }
    std::cout << "\n";
    std::cout << "\tTrained in ";
    int freeSkills = 0;
    for(auto skill : skills)
    {
        if(skill == "Free")
        {
            freeSkills++;
        }
        else
        {
            std::cout << skill << " ";
        }      
    }
    if(freeSkills == skills.size())
    {
        std::cout << freeSkills << " skills.  ";
    }
    else
    {
        std::cout << "and " << freeSkills << " other skills.  ";
    }     
    std::cout << weaponTraining << " in " << weaponType << ".  " << armorTraining << " in " << armorType << ".  " << dc << " in class DC.\n";
}

std::vector<std::unique_ptr<Class>> parseClass()
{
    std::string line, str;
    std::vector<std::string> boosts;
    std::vector<std::string> flaws;
    std::vector<std::unique_ptr<Class>> classes;
    std::ifstream filestream(kClassPath);
    if(filestream.is_open())
    {
        while(std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            std::unique_ptr<Class> clss = std::make_unique<Class>() ;
            while(linestream >> str){
                if(str == "Class")
                {
                    linestream >> clss->name; 
                }
                else if(str == "Key")
                {
                    linestream >> clss->key;
                }
                else if(str == "HP")
                {
                    linestream >> str;
                    clss->hp = std::stoi(str);
                }
                else if(str == "Perception")
                {
                    linestream >> clss->perception;
                }
                else if(str == "Save")
                {
                    linestream >> str;
                    clss->saves.emplace_back(str);
                    linestream >> str;
                    clss->saveTraining.emplace_back(str);                    
                }
                else if(str == "Skill")
                {
                    linestream >> str;
                    clss->skills.emplace_back(str);
                }
                else if(str == "Skills")
                {
                    linestream >> str;
                    for(int i = 0; i < std::stoi(str); i++)
                    {
                        clss->skills.emplace_back("Free");
                    }
                }
                else if(str == "Attacks")
                {
                    linestream >> clss->weaponType;
                    linestream >> clss->weaponTraining;
                }
                else if(str == "Defenses")
                {
                    linestream >> clss->armorType;
                    linestream >> clss->armorTraining;
                }
                else if(str == "DC")
                {
                    linestream >> clss->dc;
                }
                else if(str == "SpellTradition")
                {
                    linestream >> clss->spellTradition;
                }
                else if(str == "SpellsKnown")
                {
                    linestream >> clss->spellsKnown;
                }
            }
            if(clss->spellTradition == SpellTraditions::traditionToString(SpellTraditions::None))
            {
                clss->spellsKnown = 0;
            }
            classes.emplace_back(std::move(clss));
        }        
    }
    return classes;
}

void Weapon::PrintWeapon()
{
    std::cout << std::left << std::setw(20) << name << std::setw(9) << WeaponType::typeToString(type) << std::setw(10) 
        << WeaponProficiency::proficiencyToString(proficiency) << std::setw(5) << price << "  1d" << std::setw(3) << damage 
        << std::setw(20) << damageType << std::setw(3) << bulk << "bulk " <<  hands << std::setw(8) << " hands" << std::setw(15) << group << 
        std::setw(10) << range << "  Traits: ";
    for(auto trait : traits)
    {
        std::cout << trait << " ";
    }  
    std::cout << "\n";
}

void Weapons::ParseWeapons()
{
    std::string line, str;
    std::ifstream filestream(kWeaponPath);
    if(filestream.is_open())
    {
        while(std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>() ;
            while(linestream >> str){
                if(str == "Weapon")
                {
                    linestream >> weapon->name;
                }
                else if(str == "Type")
                {
                    linestream >> str;
                    weapon->type = WeaponType::stringToType(str);
                }
                else if(str == "Proficiency")
                {
                    linestream >> str;
                    weapon->proficiency = WeaponProficiency::stringToProficiency(str);
                }
                else if(str == "Price")
                {
                    linestream >> weapon->price;
                }
                else if(str == "Damage")
                {
                    linestream >> weapon->damage;
                }
                else if(str == "DamageType")
                {
                    linestream >> weapon->damageType;                    
                }
                else if(str == "Bulk")
                {
                    linestream >> weapon->bulk;
                }
                else if(str == "Hands")
                {
                    linestream >> weapon->hands;
                }
                else if(str == "Group")
                {
                    linestream >> weapon->group;
                }
                else if(str == "Range")
                {
                    linestream >> weapon->range;
                }
                else if(str == "Traits")
                {
                    linestream >> str;
                    weapon->traits = split(str, ',');
                }
            }
            if(weapon->type == WeaponType::Melee && ! VectorManip::IsValueInVector(weapon->traits, "Thrown"))
            {
                if(VectorManip::IsValueInVector(weapon->traits, "Reach"))
                {
                    weapon->range = 10;
                }
                else
                {
                    weapon->range = 5;
                }                
            }
            _weaponNames.emplace_back(weapon->name);
            _weapons.emplace_back(std::move(weapon));
        }
    }
}

std::shared_ptr<Weapon> Weapons::SelectWeapon()
{
    return _weapons[VectorManip::ChooseFromVector(_weaponNames, "weapon")];
}

std::shared_ptr<Weapon> Weapons::SelectWeapon(std::string name)
{
    for(int i = 0; i < _weaponNames.size(); i++)
    {
        if(strcasecmp(_weaponNames[i].c_str(), name.c_str()) == 0)
        {
            return _weapons[i];
        }
    }
}

bool Weapons::DoesWeaponExist(std::string name)
{
    for(auto weapon : _weaponNames)
    {
        if(strcasecmp(weapon.c_str(), name.c_str()) == 0)
        {
            return true;
        }
    }
    return false;
}

void Weapons::PrintWeapons()
{
    for(auto& weapon : _weapons)
    {
        weapon->PrintWeapon();
    }
}

void Spell::PrintSpell()
{
    std::cout << name << ": " << description << "\n";
    std::cout << "\tRange: " << std::setw(5) << range;
    if(shape == "Target")
    {
        std::cout << std::setw(10) << " Targets " << targets;
    }
    else
    {
        std::cout << std::setw(12) << shape;
    }
    std::cout << " Against " << std::setw(11) << SpellDefenses::defenseToString(against) << "  ";
    if(damageDie != 0)
    {
        std::cout << "1d" << damageDie << " ";
    }
    if(abilityModifier)
    {
        std::cout << "Ability Modifer ";
    }
    if(flatDamage != 0)
    {
        std::cout << "+ " << flatDamage << " ";
    }
    std::cout << damageType << " " << actions << " actions " << components << " components Heightened every " << heightenedSpellLevel 
        << " spell level for and extra d" << heightenedDamageDie << "\n";   
}

void Spells::ParseSpells(SpellTraditions::Tradition tradition)
{
    std::string line, str;
    std::ifstream filestream(kSpellPath);
    std::vector<std::string> values;
    if(filestream.is_open())
    {
        while(std::getline(filestream, line))
        {
            if(line.find(SpellTraditions::traditionToString(tradition)) == std::string::npos)
            {
                continue;
            }
            std::istringstream linestream(line);
            std::shared_ptr<Spell> spell = std::make_shared<Spell>() ;
            while(linestream >> str){
                if(str == "Spell")
                {
                    linestream >> spell->name;
                }
                else if(str == "Tradition")
                {
                    linestream >> str;
                    values = split(str, '/');
                    for(auto value : values)
                    {
                        spell->traditions.emplace_back(SpellTraditions::stringToTradition(value));
                    }
                }
                else if(str == "Range")
                {
                    linestream >> spell->range;
                }
                else if(str == "Shape")
                {
                    linestream >> spell->shape >> spell->targets;
                }
                else if(str == "Damage")
                {
                    linestream >> spell->damageDie >> str >> spell->flatDamage;
                    if(str == "Ability")
                    {
                        spell->abilityModifier = true;
                    }
                    else
                    {
                        spell->abilityModifier = false;
                    }
                }
                else if(str == "DamageType")
                {
                    linestream >> spell->damageType;
                }
                else if(str == "Against")
                {
                    linestream >> str;
                    spell->against = SpellDefenses::stringToDefense(str);
                }
                else if(str == "Actions")
                {
                    linestream >> spell->actions;
                }
                else if(str == "Components")
                {
                    linestream >> spell->components;
                }
                else if(str == "Heightened")
                {
                    linestream >> spell->heightenedSpellLevel >> spell->heightenedDamageDie;
                }
                else if(str == "Description")
                {
                    linestream >> str;
                    spell->description = str;
                    while(linestream >> str)
                    {
                        spell->description = spell->description + " " + str;
                    }
                }
            }
            _spellNames.emplace_back(spell->name);
            _spells.emplace_back(std::move(spell));
        }
    }
}

void Spells::PrintSpells()
{
    for(auto& spell : _spells)
    {
        spell->PrintSpell();
    }
}

std::shared_ptr<Spell> Spells::SelectSpell()
{
    int choice = VectorManip::ChooseFromVector(_spellNames, "spell");
    std::shared_ptr<Spell> spell = _spells[choice];
    _spells.erase(_spells.begin() + choice);
    _spellNames.erase(_spellNames.begin() + choice);
    return spell;
}

std::shared_ptr<Spell> Spells::SelectSpell(std::string name)
{
    std::shared_ptr<Spell> spell;
    for(int i = 0; i < _spellNames.size(); i++)
    {
        if(strcasecmp(_spellNames[i].c_str(), name.c_str()) == 0)
        {
            spell = _spells[i];
            _spells.erase(_spells.begin() + i);
            _spellNames.erase(_spellNames.begin() + i);
            return spell;
        }
    }
    return spell;
}

bool Spells::DoesSpellExist(std::string name)
{
    for(auto spell : _spellNames)
    {
        if(strcasecmp(spell.c_str(), name.c_str()) == 0)
        {
            return true;
        }
    }
    return false;
}

void Armor::PrintArmor()
{
    std::cout << std::left << std::setw(15) << name << std::right << std::setw(7) << price << std::setw(4) << AC << std::setw(9) << dexCap << std::setw(15) <<
        checkPenalty << std::setw(15) << speedPenalty << std::setw(10) << strength << std::setw(6) << bulk << std::setw(12) << group << "   ";
    for(auto trait : traits)
    {
        std::cout << trait << " ";
    }
    std::cout << "\n";
}

void Armors::ParseArmors()
{
    std::string line, str;
    std::ifstream filestream(kArmorPath);
    std::vector<std::string> values;
    if(filestream.is_open())
    {
        while(std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            std::shared_ptr<Armor> armor = std::make_shared<Armor>() ;
            while(linestream >> str){
                if(str == "Armor")
                {
                    linestream >> armor->name;
                }
                else if(str == "Category")
                {
                    linestream >> str;
                    armor->category = ArmorCategories::stringToCategory(str);
                }
                else if(str == "Price")
                {
                    linestream >> armor->price;
                }
                else if(str == "AC")
                {
                    linestream >> armor->AC;
                }
                else if(str == "DexCap")
                {
                    linestream >> armor->dexCap;
                }
                else if(str == "CheckPenalty")
                {
                    linestream >> armor->checkPenalty;
                }
                else if(str == "SpeedPenalty")
                {
                    linestream >> armor->speedPenalty;
                }
                else if(str == "Strength")
                {
                    linestream >> armor->strength;
                }
                else if(str == "Bulk")
                {
                    linestream >> armor->bulk;
                }
                else if(str == "Group")
                {
                    linestream >> armor->group;
                }
                else if(str == "Traits")
                {
                    linestream >> str;
                    armor->traits = split(str, ',');
                }
            }
            _armorNames.emplace_back(armor->name);
            _armors.emplace_back(armor);
        }
    }
}

void Armors::PrintArmors()
{
    std::cout << std::left << std::setw(15) << "Armor" << std::right << std::setw(7) << "Price" << std::setw(4) << "AC" << std::setw(9) << "Dex Cap" << 
        std::setw(15) << "Check Penalty" << std::setw(15) << "Speed Penalty" << std::setw(10) << "Strength" << std::setw(6) << "Bulk" << std::setw(12) 
        << "Group" << "   Traits\n";
    for(auto& armor : _armors)
    {
        armor->PrintArmor();
    }
}

std::shared_ptr<Armor> Armors::SelectArmor()
{
    return _armors[VectorManip::ChooseFromVector(_armorNames, "armor")];
}

std::shared_ptr<Armor> Armors::SelectArmor(std::string name)
{
    for(int i = 0; i < _armorNames.size(); i++)
    {
        if(strcasecmp(_armorNames[i].c_str(), name.c_str()) == 0)
        {
            return _armors[i];
        }
    }
}

bool Armors::DoesArmorExist(std::string name)
{
    for(auto armor : _armorNames)
    {
        if(strcasecmp(armor.c_str(), name.c_str()) == 0)
        {
            return true;
        }
    }
    return false;
}
