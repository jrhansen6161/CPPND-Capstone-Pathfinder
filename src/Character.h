#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "DataParser.h"
#include "VectorManip.h"
#include "Dice.h"
#include "Constants.h"

class Character
{
public:
    Character();
    void LoadCharacter(std::string filename);
    void CreateCharacter();
    void PrintCharacter();
    void UpdateStats();
    void SaveCharacter();
    void InitializeCharacter();
    void Run();
    int Save();
    int Skill();
    int Strike(int numberOfAttacks, int difficulty);
    int Cast();
    void Heal(int amount);
    bool Harm(int amount);
    void GainExperience(int amount);
    void AddWeapon();
    void ChangeArmor();
    void AddSpell(int spellsToLearn);
    void RemoveWeapon();
private:
    int _attributes[6];
    int _mods[6];
    Training::Training _skillTraining[16];
    int _skills[16];
    int _saves[3];
    Training::Training _saveTraining[3];
    std::string _name;    
    int _level{1};
    int _experience{0};
    int _maxhp{0};
    int _currenthp{0};
    int _classhp{0};
    int _ancestryHP{0};
    int _speed{0};
    int _baseSpeed{0};
    int _ac{10};
    Training::Training _perceptionTraining{Training::Untrained};
    int _perception{0};
    WeaponProficiency::Proficiency _weaponProficiency{WeaponProficiency::Unarmed};
    Training::Training _weaponTraining{Training::Untrained};
    ArmorCategories::ArmorCategory _armorCategory{ArmorCategories::Unarmored};
    Training::Training _armorTraining{Training::Untrained};
    Training::Training _classdc{Training::Untrained};
    Attributes::Attribute _keyAbility{Attributes::Constitution};
    std::string _ancestry;
    std::string _background;
    std::string _class;
    SpellTraditions::Tradition _spellTradition{SpellTraditions::None};
    int _spellsKnown{0};
    Weapons _allWeapons;
    std::vector<std::shared_ptr<Weapon>> _weapons;
    std::vector<std::string> _weaponNames;
    Spells _allSpells;
    std::vector<std::shared_ptr<Spell>> _spells;
    std::vector<std::string> _spellNames;
    Armors _allArmors;
    std::shared_ptr<Armor> _armor;
    void ApplyFlaws(std::vector<std::string> &flaws);
    void ApplyBoosts(std::vector<std::string> &boosts);
    void ApplySkills(const std::vector<std::string> &skills, std::vector<std::string> &availableSkills);
    void UpdateAttributes();
    void UpdateSaves();
    void UpdateSkills();
    void UpdateWeapons();
    void UpdateSpells();
    void UpdateArmor();  
    int Damage(std::shared_ptr<Weapon> weapon, bool thrown);
};

#endif