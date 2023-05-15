#include "Constants.h"
#include <iomanip>
#include <cstring>

Attributes::Attribute Attributes::stringToAttribute(std::string name)
{
    for(int i = 0; i < Attributes::Size; i++)
    {
        if(strcasecmp(AttributeName[i].c_str(),name.c_str()) == 0)
        {
            return All[i];
        }
    }    
    return Unknown;
}

std::string Attributes::attributeToString(Attribute attribute)
{
    return AttributeName[attribute];
}

std::string Training::trainingToString(Training training)
{
    return TrainingName[training/2];
}

Training::Training Training::stringToTraining(std::string training)
{
    for(int i = 0; i < Size; i++)
    {
        if(strcasecmp(TrainingName[i].c_str(),training.c_str()) == 0 )
        {
            return All[i];
        }        
    }
    return Unknown;
}

std::string Skills::skillToString(Skill skill)
{
    return SkillName[skill];
}

Skills::Skill Skills::stringToSkill(std::string skill)
{
    for(int i = 0; i < Skills::Size; i++)
    {
        if(strcasecmp(SkillName[i].c_str(),skill.c_str()) == 0)
        {
            return All[i];
        }
    }
    return Unknown;
}

Attributes::Attribute Skills::attributeForSkill(Skill skill)
{
    return SkillAttributes[skill];
}

std::string Saves::saveToString(Save save)
{
    return SaveName[save];
}

Saves::Save Saves::stringToSave(std::string save)
{
    for(int i = 0; i < Saves::Size; i++)
    {
        if(strcasecmp(SaveName[i].c_str(),save.c_str()) == 0 )
        {
            return All[i];
        }
    }
    return Unknown;
}

Attributes::Attribute Saves::attributeForSave(Save save)
{
    return SaveAttribute[save];
}

std::string WeaponType::typeToString(WeaponType::Type type)
{
    return TypeName[type];
}

WeaponType::Type WeaponType::stringToType(std::string type)
{
    for(int i = 0; i < WeaponType::Size; i++)
    {
        if(strcasecmp(TypeName[i].c_str(), type.c_str()) == 0)
        {
            return All[i];
        }
    }
    return Unknown;
}

std::string WeaponProficiency::proficiencyToString(WeaponProficiency::Proficiency proficiency)
{
    return ProficiencyName[proficiency];
}

WeaponProficiency::Proficiency WeaponProficiency::stringToProficiency(std::string proficiency)
{
    for(int i = 0; i < WeaponProficiency::Size; i++)
    {
        if(strcasecmp(ProficiencyName[i].c_str(), proficiency.c_str()) == 0)
        {
            return All[i];
        }
    }
    return Unknown;
}

std::string SpellTraditions::traditionToString(SpellTraditions::Tradition tradition)
{
    return TraditionNames[tradition];
}

SpellTraditions::Tradition SpellTraditions::stringToTradition(std::string tradition)
{
    for(int i = 0; i < SpellTraditions::Size; i++)
    {
        if(strcasecmp(TraditionNames[i].c_str(),tradition.c_str()) == 0)
        {
            return All[i];
        }
    }
    return None;
}

std::string SpellDefenses::defenseToString(SpellDefenses::Defense defense)
{
    return DefenseNames[defense];
}

SpellDefenses::Defense SpellDefenses::stringToDefense(std::string defense)
{
    for(int i = 0; i < SpellDefenses::Size; i++)
    {
        if(strcasecmp(DefenseNames[i].c_str(), defense.c_str()) == 0)
        {
            return All[i];
        }
    }
    return Unknown;
}

std::string ArmorCategories::categoryToString(ArmorCategories::ArmorCategory category)
{
    return ArmorCategoryNames[category];
}
ArmorCategories::ArmorCategory ArmorCategories::stringToCategory(std::string category)
{
    for(int i = 0; i < ArmorCategories::Size; i++)
    {
        if(strcasecmp(ArmorCategoryNames[i].c_str(), category.c_str()) == 0)
        {
            return All[i];
        }
    }
    return Unknown;
}