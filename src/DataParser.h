#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include "Constants.h"

const std::string kAncestryPath{"../data/Ancestry.txt"};
const std::string kBackgroundPath{"../data/Background.txt"};
const std::string kClassPath{"../data/Class.txt"};
const std::string kWeaponPath{"../data/Weapons.txt"};
const std::string kSpellPath{"../data/Spells.txt"};
const std::string kArmorPath{"../data/Armor.txt"};

std::vector<std::string> split(const std::string &str, char delimiter);
bool IsStringInArray(const std::string stringArray[], int size, std::string &str);
int GetPositiveIntegerAmount(std::string option);
//std::vector<std::string> ListDirectory(std::string path);

class Ancestry
{
public:
    void PrintAncestry();
    std::string name;
    int hp;
    int speed;
    std::vector<std::string> boosts;
    std::vector<std::string> flaws;
};

std::vector<std::unique_ptr<Ancestry>> parseAncestry();

class Background
{
public:
    void PrintBackground();
    std::string name;
    std::vector<std::string> boosts;
    std::string skill;
};

std::vector<std::unique_ptr<Background>> parseBackground();

class Class
{
public:
    void PrintClass();
    std::string name;
    int hp;
    std::string key;
    std::string perception;
    std::vector<std::string> saves;
    std::vector<std::string> saveTraining;
    std::vector<std::string> skills;    
    std::string weaponType;
    std::string weaponTraining;
    std::string armorType;
    std::string armorTraining;
    std::string dc;
    std::string spellTradition;
    int spellsKnown;
};

std::vector<std::unique_ptr<Class>> parseClass();

class Weapon
{
public:
    void PrintWeapon();
    std::string name;
    WeaponType::Type type;
    WeaponProficiency::Proficiency proficiency;
    float price;
    int damage;
    std::string damageType;
    char bulk;
    int hands;
    std::string group;
    std::vector<std::string> traits;
    int range;
    int attackModifier;
    int damageModifier;
    int attackModifierThrown;
    int damageModifierThrown;
};

class Weapons
{
public:
    void ParseWeapons();
    void PrintWeapons();
    std::shared_ptr<Weapon> SelectWeapon();
    std::shared_ptr<Weapon> SelectWeapon(std::string name);
    bool DoesWeaponExist(std::string name);
private:
    std::vector<std::shared_ptr<Weapon>> _weapons;
    std::vector<std::string> _weaponNames;
};

class Spell
{
public:
void PrintSpell();
    std::string name;
    std::vector<SpellTraditions::Tradition> traditions;
    int range;
    std::string shape;
    int targets;
    int damageDie;
    bool abilityModifier;
    int flatDamage;
    std::string damageType;
    SpellDefenses::Defense against;
    int actions;
    std::string components;
    int heightenedDamageDie;
    int heightenedSpellLevel;
    int numberOfDie{0};
    std::string description;
};

class Spells
{
public:
    void ParseSpells(SpellTraditions::Tradition tradition);
    void PrintSpells();
    std::shared_ptr<Spell> SelectSpell();
    std::shared_ptr<Spell> SelectSpell(std::string name);
    bool DoesSpellExist(std::string name);
private:
    std::vector<std::shared_ptr<Spell>> _spells;
    std::vector<std::string> _spellNames;
};

class Armor
{
public:
    void PrintArmor();
    std::string name;
    ArmorCategories::ArmorCategory category;
    float price;
    int AC;
    int dexCap;
    int checkPenalty;
    int speedPenalty;
    int strength;
    char bulk;
    std::string group;
    std::vector<std::string> traits;
};

class Armors
{
public:
    void ParseArmors();
    void PrintArmors();
    std::shared_ptr<Armor> SelectArmor();
    std::shared_ptr<Armor> SelectArmor(std::string name);
    bool DoesArmorExist(std::string name);
private:
    std::vector<std::shared_ptr<Armor>> _armors;
    std::vector<std::string> _armorNames;
};

#endif