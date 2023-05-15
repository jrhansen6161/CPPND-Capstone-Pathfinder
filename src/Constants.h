#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>

namespace Attributes
{
    static const std::vector<std::string> AttributeName
    {
        "Strength",
        "Dexterity",
        "Constitution",
        "Intelligence",
        "Wisdom",
        "Charisma"        
    };

    enum Attribute
    {
        Strength,
        Dexterity,
        Constitution,
        Intelligence,
        Wisdom,
        Charisma,
        Unknown = 99
    };

    Attribute stringToAttribute(std::string);
    std::string attributeToString(Attribute);

    static const int Size = 6;
    static const std::vector<Attribute> All = {Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma};
}

namespace Training
{
    enum Training
    {
        Untrained = 0,
        Trained = 2,
        Expert = 4,
        Master = 6,
        Legend = 8,
        Unknown = 99
    };
    static const std::vector<std::string> TrainingName
    {
        "Untrained",
        "Trained",
        "Expert",
        "Master",
        "Legend"
    };
    std::string trainingToString(Training training);
    Training stringToTraining(std::string training);
    static const int Size = 5;
    static const std::vector<Training> All = {Untrained, Trained, Expert, Master, Legend};
};

namespace Skills
{
    static const std::vector<std::string> SkillName
    {
        "Acrobatics",
        "Arcana",
        "Athletics",
        "Crafting",
        "Deception",
        "Diplomacy",
        "Intimidation",
        "Medicine",
        "Nature",
        "Occultism",
        "Performance",
        "Religion",
        "Society",
        "Stealth",
        "Survival",
        "Thievery"
    };

    enum Skill
    {
        Acrobatics,
        Arcana,
        Athletics,
        Crafting,
        Deception,
        Diplomacy,
        Intimidation,
        Medicine,
        Nature,
        Occultism,
        Performance,
        Religion,
        Society,
        Stealth,
        Survival,
        Thievery,
        Unknown = 99
    };

    static const std::vector<Attributes::Attribute> SkillAttributes 
    {
        Attributes::Dexterity, 
        Attributes::Intelligence,
        Attributes::Strength,
        Attributes::Intelligence,
        Attributes::Charisma,
        Attributes::Charisma,
        Attributes::Charisma,
        Attributes::Wisdom,
        Attributes::Wisdom,
        Attributes::Intelligence,
        Attributes::Charisma,
        Attributes::Wisdom,
        Attributes::Intelligence,
        Attributes::Dexterity,
        Attributes::Wisdom,
        Attributes::Dexterity
    };

    std::string skillToString(Skill skill);
    Skill stringToSkill(std::string);
    Attributes::Attribute attributeForSkill(Skill skill);

    static const int Size = 16;
    static const std::vector<Skill> All = {Acrobatics, Arcana, Athletics, Crafting, Deception, Diplomacy, Intimidation, Medicine, Nature, Occultism, Performance, 
        Religion, Society, Stealth, Survival, Thievery};
}

namespace Saves
{
    enum Save
    {
        Fortitude,
        Reflex,
        Will,
        Unknown = 99
    };

    static const std::vector<std::string> SaveName =
    {
        "Fortitude",
        "Reflex",
        "Will"
    };

    static const std::vector<Attributes::Attribute> SaveAttribute 
    {
        Attributes::Constitution,
        Attributes::Dexterity,
        Attributes::Wisdom
    };

    std::string saveToString(Save save);
    Save stringToSave(std::string save);
    Attributes::Attribute attributeForSave(Save save);

    static const int Size = 3;
    static const std::vector<Save> All = {Fortitude, Reflex, Will};
}

namespace WeaponType
{
    enum Type
    {
        Melee,
        Ranged,
        Unknown = 99
    };

    static const std::vector<std::string> TypeName
    {
        "Melee",
        "Ranged"
    };

    std::string typeToString(Type type);
    Type stringToType(std::string type);

    static const int Size = 2;
    static const std::vector<Type> All = {Melee, Ranged};
}

namespace WeaponProficiency
{
    enum Proficiency
    {
        Unarmed,
        Simple,
        Martial,
        Unknown = 99
    };

    static const std::vector<std::string> ProficiencyName
    {
        "Unarmed",
        "Simple",
        "Martial"
    };

    std::string proficiencyToString(Proficiency proficiency);
    Proficiency stringToProficiency(std::string proficiency);

    static const int Size = 3;
    static const std::vector<Proficiency> All = {Unarmed, Simple, Martial};
}

namespace SpellTraditions
{
    enum Tradition
    {
        None,
        Arcane,
        Divine,
        Occult,
        Primal
    };

    static const std::vector<std::string> TraditionNames
    {
        "None",
        "Arcane",
        "Divine",
        "Occult",
        "Primal"
    };

    std::string traditionToString(Tradition tradition);
    Tradition stringToTradition(std::string tradition);

    static const int Size = 5;
    static const std::vector<Tradition> All = {None, Arcane, Divine, Occult, Primal};
}

namespace SpellDefenses
{
    enum Defense
    {
        Fortitude,
        Reflex,
        Will,
        AC,
        Unknown = 99
    };

    static const std::vector<std::string> DefenseNames
    {
        "Fortitude",
        "Reflex",
        "Will",
        "AC"
    };

    std::string defenseToString(Defense defense);
    Defense stringToDefense(std::string defense);

    static const int Size = 4;
    static const std::vector<Defense> All = {Fortitude, Reflex, Will, AC};
}

namespace ArmorCategories
{
    enum ArmorCategory
    {
        Unarmored,
        Light,
        Medium,
        Heavy,
        Unknown = 99
    };

    static const std::vector<std::string> ArmorCategoryNames
    {
        "Unarmored",
        "Light",
        "Medium",
        "Heavy"
    };

    std::string categoryToString(ArmorCategory category);
    ArmorCategory stringToCategory(std::string category);

    static const int Size = 4;
    static const std::vector<ArmorCategory> All = {Unarmored, Light, Medium, Heavy};
}



#endif