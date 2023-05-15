#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Character.h"

static std::vector<std::string> initOptions = {"Load", "New"};
static std::vector<std::string> runOptions = {"Strike", "Cast", "Save", "Skill", "Add_Weapon", "Change_Armor", "Harm", "Heal", "Gain_Experience", "Print", "Quit"};
static std::vector<std::string> addOptions = {"Add_Another", "Finished"};
static std::vector<std::string> multipleAttackPenaltyOptions = {"First", "Second", "Third"};

void Character::ApplyFlaws(std::vector<std::string> &flaws)
{
    for(auto flaw : flaws)
    {
        _attributes[Attributes::stringToAttribute(flaw)] -= 2;
    }
}

void Character::ApplyBoosts(std::vector<std::string> &boosts)
{
    std::vector<std::string> availableBoosts;
    for(auto attribute : Attributes::All)
    {
        bool push = true;
        for(auto boost : boosts)
        {
            if(Attributes::stringToAttribute(boost) == attribute)
            {
                push = false;
            }
        }
        if(push)
        {
            availableBoosts.emplace_back(Attributes::attributeToString(attribute));
        }
    }
    
    for(auto boost : boosts)
    {
        if(strcasecmp(boost.c_str(),"Free") == 0)
        {
            std::cout << "Choosing Free Boost.\n";
            int boostIndex = VectorManip::ChooseFromVector(availableBoosts, "boost");
            _attributes[Attributes::stringToAttribute(availableBoosts[boostIndex])] += 2;
            availableBoosts.erase(availableBoosts.begin()+boostIndex);
        }
        else
        {
            std::cout << "Boosting " << boost << "!\n";
            _attributes[Attributes::stringToAttribute(boost)] += 2;
        }
        
    }
}

Character::Character()
{
    for(auto attribute : Attributes::All)
    {
        _attributes[attribute] = 10;
        _mods[attribute] = 0;
    }
    for(auto save : Saves::All)
    {
        _saveTraining[save] = Training::Untrained; 
        _saves[save] = _saveTraining[save] + _mods[Saves::attributeForSave(save)];
    }
    for(auto skill : Skills::All)
    {
        _skillTraining[skill] = Training::Untrained;
        _skills[skill] = _skillTraining[skill] + _mods[Skills::attributeForSkill(skill)];
    }
}

void Character::PrintCharacter()
{
    std::cout << "Name: " << _name << "\n";
    std::cout << "Ancestry: " << _ancestry << "\tBackground: " << _background << "\tClass: " << _class << "\tSpell Tradition: " << 
        SpellTraditions::traditionToString(_spellTradition) << "\n";
    std::cout << "HP: " << _currenthp << "/" << _maxhp << "\tSpeed: " << _speed << "\tLevel: " << _level << "\tExperience: " << _experience << "\n";
    std::cout << std::right;
    for(auto save : Saves::All)
    {
        std::cout << Saves::saveToString(save) << ": " << Training::trainingToString(_saveTraining[save]) << " " << _saves[save] << std::setw(15);
    }
    std::cout << "\n";
    std::cout << std::left << std::setw(10) << "Weapon"
        << std::left << std::setw(10) << WeaponProficiency::proficiencyToString(_weaponProficiency)
        << std::left << std::setw(10) << Training::trainingToString(_weaponTraining)
        << std::left << std::setw(10) << "Armor"
        << std::left << std::setw(10) << ArmorCategories::categoryToString( _armorCategory)
        << std::left << std::setw(10) << Training::trainingToString(_armorTraining) 
        << std::left << std::setw(10) << "Class DC" 
        << std::left << std::setw(10) << Training::trainingToString(_classdc) << "\n";
    std::cout << std::left << "AC " << _ac << " in " << _armor->name << "\n";
    for(auto attribute : Attributes::All)
    {
        std::cout << std::left << std::setw(15) << Attributes::attributeToString(attribute) << std::left << std::setw(15) << _attributes[attribute] 
            << std::left << std::setw(5) << _mods[attribute] << "\n";
    }
    std::cout << std::left << std::setw(15) << "Perception" << std::left << std::setw(15) << 
        Training::trainingToString(_perceptionTraining) << std::left << std::setw(15) << _perception << "\n";
    for(auto skill : Skills::All)
    {
        std::cout << std::left << std::setw(15) << Skills::skillToString(skill) << std::left << std::setw(15) << 
            Attributes::attributeToString(Skills::attributeForSkill(skill)) << std::left << std::setw(15) << 
            Training::trainingToString(_skillTraining[skill]) << std::left << std::setw(5) << _skills[skill] << "\n";
    }
    for(int i = 0; i < _weaponNames.size(); i++)
    {
        std::cout << std::left << std::setw(20) << _weaponNames[i] << std::setw(10) << WeaponType::typeToString(_weapons[i]->type) <<
            std::setw(4) << _weapons[i]->attackModifier << "  d" << _weapons[i]->damage << " " << _weapons[i]->damageModifier << "  " << _weapons[i]->damageType << "\n";
    }
    for(int i = 0; i < _spellNames.size(); i++)
    {
        std::cout << std::left << std::setw(20) << _spellNames[i] << std::setw(6) << _spells[i]->range << "  Against " << std::setw(10) << 
            SpellDefenses::defenseToString(_spells[i]->against) << "  ";
        if(_spells[i]->damageDie != 0)
        {
            std::cout << _spells[i]->numberOfDie << "d" << _spells[i]->damageDie << " ";
        }
        if(_spells[i]->abilityModifier)
        {
            std::cout << _mods[_keyAbility] << " ";
        }
        if(_spells[i]->flatDamage)
        {
            std::cout << _spells[i]->flatDamage << " ";
        }
        std::cout << _spells[i]->damageType << "\n";
    }
}

void Character::ApplySkills(const std::vector<std::string> &skills, std::vector<std::string> &availableSkills)
{
    int skillIndex;
    int skillsRemaining = skills.size();
    for(auto skill : skills)
    {
        skillsRemaining--;
        std::cout << "Setting skill: " << skill << " " << skillsRemaining << "\tskills to choose after this\n";
        if(skill.find('/') != std::string::npos)
        {
            std::cout << skill << " / found, choosing skill option\n";
            std::vector<std::string> skillOptions = split(skill, '/');
            for(auto skillOption : skillOptions)
            {
                if(!VectorManip::IsValueInVector(availableSkills, skillOption))
                {
                    VectorManip::RemoveFromVector(skillOptions, skillOption);
                }
            }
            if(skillOptions.size() > 1)
            {
                skillIndex = VectorManip::ChooseFromVector(skillOptions, "skill");
                _skillTraining[Skills::stringToSkill(skillOptions[skillIndex])] = Training::Trained;
                VectorManip::RemoveFromVector(availableSkills, skillOptions[skillIndex]);
                continue;
            }  
            else if (skillOptions.size() == 1)
            {
                skill = skillOptions[0];
            }
                
        }
        if(VectorManip::IsValueInVector(availableSkills, skill))
        {
            _skillTraining[Skills::stringToSkill(skill)] = Training::Trained;
            VectorManip::RemoveFromVector(availableSkills, skill);
        }
        else
        {
            skillIndex = VectorManip::ChooseFromVector(availableSkills, "skill");
            _skillTraining[Skills::stringToSkill(availableSkills[skillIndex])] = Training::Trained;
            VectorManip::RemoveFromVector(availableSkills, availableSkills[skillIndex]);
        }
    }
}

void Character::UpdateAttributes()
{
    for(auto attribute : Attributes::All)
    {
        _mods[attribute] = (_attributes[attribute] - 10) / 2;
    }
    _maxhp = _ancestryHP + (_classhp + _mods[Attributes::Constitution]) * _level;
    _currenthp = _maxhp;
    _speed = _baseSpeed;
}

void Character::UpdateSaves()
{
    for(auto save : Saves::All)
    {
        _saves[save] = _mods[Saves::attributeForSave(save)] + _saveTraining[save] + _level;
    }
}

void Character::UpdateSkills()
{
    _perception = _mods[Attributes::Wisdom] + _perceptionTraining;
    for(auto skill : Skills::All)
    {
        _skills[skill] = _mods[Skills::attributeForSkill(skill)] + _skillTraining[skill];
        if(_skillTraining[skill] != Training::Untrained)
        {
            _skills[skill] += _level;
        }
    }
}

void Character::UpdateWeapons()
{
    bool dexterityHigher = _mods[Attributes::Dexterity] > _mods[Attributes::Strength];
    for(int i = 0; i < _weaponNames.size(); i++)
    {
        if(_weapons[i]->type == WeaponType::Ranged)
        {
            _weapons[i]->attackModifier = _mods[Attributes::Dexterity];
            if(VectorManip::IsValueInVector(_weapons[i]->traits, "Thrown"))
            {
                _weapons[i]->damageModifier = _mods[Attributes::Strength];
            }
            else if(VectorManip::IsValueInVector(_weapons[i]->traits, "Propulsive"))
            {
                _weapons[i]->damageModifier = _mods[Attributes::Strength] / 2;
            }
            else
            {
                _weapons[i]->damageModifier = 0;
            }            
        }
        else if(dexterityHigher && VectorManip::IsValueInVector(_weapons[i]->traits, "Finesse"))
        {
            _weapons[i]->attackModifier = _mods[Attributes::Dexterity];
            _weapons[i]->damageModifier = _mods[Attributes::Strength];
        }
        else
        {
            _weapons[i]->attackModifier = _mods[Attributes::Strength];            
            _weapons[i]->damageModifier = _mods[Attributes::Strength];
        }
        if(_weapons[i]->proficiency <= _weaponProficiency)
        {
            _weapons[i]->attackModifier += _weaponTraining + _level;
        }
        if(VectorManip::IsValueInVector(_weapons[i]->traits, "Thrown"))
        {
            _weapons[i]->damageModifierThrown = _mods[Attributes::Strength];
            _weapons[i]->attackModifierThrown = _mods[Attributes::Dexterity];
            if(_weapons[i]->proficiency <= _weaponProficiency)
            {
                _weapons[i]->attackModifierThrown += _weaponTraining + _level;
            }
        }
    }
}

void Character::UpdateSpells()
{
    for(int i = 0; i < _spellNames.size(); i++)
    {
        _spells[i]->numberOfDie = (_level - 1) / (_spells[i]->heightenedSpellLevel * 2);
        if(_spells[i]->damageDie == _spells[i]->heightenedDamageDie)
        {
            _spells[i]->numberOfDie++;
        }
        if(_spells[i]->damageDie == 0 && _spells[i]->numberOfDie > 0)
        {
            _spells[i]->damageDie = _spells[i]->heightenedDamageDie;
        }
    }
}

void Character::UpdateArmor()
{
    UpdateAttributes();
    UpdateSkills();
    _ac = _armor->AC + std::min(_mods[Attributes::Dexterity],_armor->dexCap) + 10;
    if(_armor->category <= _armorCategory)
    {
        _ac += _armorTraining + _level;
    }
    if(_attributes[Attributes::Strength] < _armor->strength)
    {
        _speed = _baseSpeed + _armor->speedPenalty;
        for(auto skill : Skills::All)
        {
            if(Skills::attributeForSkill(skill) == Attributes::Strength || Attributes::Dexterity)
            {
                _skills[skill] += _armor->checkPenalty;
            }
        }
    }
    else
    {
        if(_armor->speedPenalty < -5)
        {
            _speed = _baseSpeed + _armor->speedPenalty + 5;
        }
        if(VectorManip::IsValueInVector(_armor->traits, "Noisy"))
        {
            _skills[Skills::Stealth] += _armor->checkPenalty;
        }
    }    
}

void Character::UpdateStats()
{
    UpdateAttributes();
    UpdateSaves();
    UpdateSkills();
    UpdateWeapons();
    UpdateArmor();
    UpdateSpells();
}

void Character::SaveCharacter()
{
    std::ofstream CharacterFile("../saves/" + _name);
    CharacterFile << "Name " << _name << "\n";
    CharacterFile << "Ancestry " << _ancestry << "\n";
    CharacterFile << "Background " << _background << "\n";
    CharacterFile << "Class " << _class << "\n";
    CharacterFile << "SpellTradition " << SpellTraditions::traditionToString(_spellTradition) << "\n";
    CharacterFile << "HP " << _currenthp << " " << _maxhp << " " << _classhp << " " << _ancestryHP << "\n";
    CharacterFile << "Speed " << _speed << " " << _baseSpeed << "\n";
    CharacterFile << "Level " << _level << "\n";
    CharacterFile << "Experience " << _experience << "\n";
    CharacterFile << "WeaponProficiency " << WeaponProficiency::proficiencyToString(_weaponProficiency) << " " << Training::trainingToString(_weaponTraining) << "\n";
    CharacterFile << "ArmorProficiency " << _armorCategory << " " << Training::trainingToString(_armorTraining) << "\n";
    CharacterFile << "Armor " << _armor->name << " AC " << _ac << "\n";
    CharacterFile << "ClassDC " << Attributes::attributeToString(_keyAbility) << " " << Training::trainingToString(_classdc) << "\n";
    for(auto save : Saves::All)
    {
        CharacterFile << Saves::saveToString(save) << " " << Training::trainingToString(_saveTraining[save]) << " " << _saves[save] << "\n";
    }
    for(auto attribute : Attributes::All)
    {
        CharacterFile << Attributes::attributeToString(attribute) << " " << _attributes[attribute] << " " << _mods[attribute] << "\n";
    }
    CharacterFile << "Perception " << Training::trainingToString(_perceptionTraining) << " " << _perception << "\n";
    for(auto skill : Skills::All)
    {
        CharacterFile << Skills::skillToString(skill) << " " << Training::trainingToString(_skillTraining[skill]) << " " << _skills[skill] << "\n";
    }
    for(int i = 0; i < _weaponNames.size(); i++)
    {
        CharacterFile << "Weapon " << _weaponNames[i] << " " << _weapons[i]->type << " d" << _weapons[i]->damage << " " << _weapons[i]->damageType << "\n";
    }
    for(int i = 0; i < _spellNames.size(); i++)
    {
        CharacterFile << "Spell " << _spellNames[i] << " " << _spells[i]->range << " ";
        if(_spells[i]->damageDie != 0)
        {
            CharacterFile << "1d" << _spells[i]->damageDie << " ";
        }
        if(_spells[i]->abilityModifier)
        {
            CharacterFile << "Ability Modifer ";
        }
        if(_spells[i]->flatDamage != 0)
        {
            CharacterFile << "+ " << _spells[i]->flatDamage << " ";
        }
        CharacterFile << _spells[i]->damageType << "\n";
    }
    CharacterFile.close();
}

void Character::LoadCharacter(std::string name)
{
    std::string line, str, strSpare;;
    std::ifstream filestream("../saves/" + name);
    if(filestream.is_open())
    {
        while(std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            while(linestream >> str)
            {
                if(str == "Name")
                {
                    linestream >> _name;
                }
                else if(str == "Ancestry")
                {
                    linestream >> _ancestry;
                }
                else if(str == "Background")
                {
                    linestream >> _background;
                }
                else if(str == "Class")
                {
                    linestream >> _class;                   
                }
                else if(str == "SpellTradition")
                {
                    linestream >> str;
                    _spellTradition = SpellTraditions::stringToTradition(str);
                    _allSpells.ParseSpells(_spellTradition);
                }
                else if(str == "HP")
                {
                   linestream >> _currenthp;
                   linestream >> _maxhp;
                   linestream >> _classhp;
                   linestream >> _ancestryHP;
                }
                else if(str == "Speed")
                {
                    linestream >> _speed;
                    linestream >> _baseSpeed;
                }
                else if(str == "Level")
                {
                    linestream >> _level;
                }
                else if (str == "Experience")
                {
                    linestream >> _experience;
                }
                else if(str == "WeaponProficiency")
                {
                    linestream >> str;
                    _weaponProficiency = WeaponProficiency::stringToProficiency(str);
                    linestream >> str;
                    _weaponTraining = Training::stringToTraining(str);
                }
                else if(str == "ArmorProficiency")
                {
                    linestream >> str;
                    _armorCategory = ArmorCategories::stringToCategory(str);
                    linestream >> str;
                    _armorTraining = Training::stringToTraining(str);
                }
                else if(str == "ClassDC")
                {
                    linestream >> str;
                    _keyAbility = Attributes::stringToAttribute(str);
                    linestream >> str;
                    _classdc = Training::stringToTraining(str);
                }
                else if(VectorManip::IsValueInVector(Saves::SaveName, str))
                {
                    linestream >> strSpare;
                    _saveTraining[Saves::stringToSave(str)] = Training::stringToTraining(strSpare);
                }
                else if(VectorManip::IsValueInVector(Attributes::AttributeName, str))
                {
                    linestream >> _attributes[Attributes::stringToAttribute(str)];
                }
                else if(str == "Perception")
                {
                    linestream >> str;
                    _perceptionTraining = Training::stringToTraining(str);
                }
                else if(VectorManip::IsValueInVector(Skills::SkillName, str))
                {
                    linestream >> strSpare;
                    _skillTraining[Skills::stringToSkill(str)] = Training::stringToTraining(strSpare);
                }
                else if(str == "Weapon")
                {
                    linestream >> str;
                    if(_allWeapons.DoesWeaponExist(str))
                    {
                        _weaponNames.emplace_back(str);
                        _weapons.emplace_back(_allWeapons.SelectWeapon(str));
                    }
                }
                else if(str == "Armor")
                {
                    linestream >> str;
                    if(_allArmors.DoesArmorExist(str))
                    {
                        _armor = _allArmors.SelectArmor(str);
                    }
                }
                else if(str == "Spell")
                {
                    linestream >> str;
                    if(_allSpells.DoesSpellExist(str))
                    {
                        _spellNames.emplace_back(str);
                        _spells.emplace_back(_allSpells.SelectSpell(str));
                    }
                }
            }
        }
    }
    UpdateStats();
}

void Character::InitializeCharacter()
{
    _allWeapons.ParseWeapons();
    _allArmors.ParseArmors();
    _armor = _allArmors.SelectArmor("Clothing");
    std::cout << "Would you like to load a charater or create a new character?\n";
    if(VectorManip::ChooseFromVector(initOptions, "load or new") == 0)
    {
        std::string name;
        while(true)
        {
            std::cout << "Please give a valid filename from the saves directory.\n";
            std::cout << "Note that capitalization matters and the character file will not be checked for whether it is legal.\n";
            std::cin >> name;
            std::ifstream filestream("../saves/" + name);
            if(filestream.is_open())
            {
                filestream.close();
                break;
            }
        }
        std::cout << "Character found\n";
        LoadCharacter(name);
    }
    else
    {
        CreateCharacter();
    }
}

int Character::Strike(int numberOfAttacks, int difficulty = 0)
{
    int attackRoll, attackTotal;
    bool thrown = false;
    std::vector<std::string> options;
    std::vector<int> weaponIndex;
    for(int i = 0; i < _weaponNames.size(); i++)
    {
        options.emplace_back(_weaponNames[i]);
        weaponIndex.emplace_back(i);
        if(VectorManip::IsValueInVector(_weapons[i]->traits, "Thrown") && ! _weapons[i]->type == WeaponType::Ranged)
        {
            options.emplace_back(_weaponNames[i]+"_Thrown");
            weaponIndex.emplace_back(i);
        }
    }
    int choice = VectorManip::ChooseFromVector(options, "strike");
    int multipleAttackPenaltyPerAttack = -5;
    if(VectorManip::IsValueInVector(_weapons[weaponIndex[choice]]->traits, "Agile"))
    {
        multipleAttackPenaltyPerAttack = -4;
    }
    int multipleAttackPenalty = multipleAttackPenaltyPerAttack * numberOfAttacks;
    attackRoll = Dice::RollDice(20);
    if(options[choice].find("Thrown") != std::string::npos)
    {
        thrown = true;
        attackTotal = attackRoll + _weapons[weaponIndex[choice]]->attackModifierThrown + multipleAttackPenalty;
        std::cout << "Attack " << attackRoll << " + " << _weapons[weaponIndex[choice]]->attackModifierThrown + multipleAttackPenalty << " = " << attackTotal << "\n";
    }
    else
    {
        attackTotal = attackRoll + _weapons[weaponIndex[choice]]->attackModifier + multipleAttackPenalty;
        std::cout << "Attack " << attackRoll << " + " << _weapons[weaponIndex[choice]]->attackModifier + multipleAttackPenalty << " = " << attackTotal << "\n";
    }
    if(attackTotal >= difficulty)
    {
        std::cout << "Strike hit\n";
        return Damage(_weapons[weaponIndex[choice]], thrown);
    }
    else
    {
        std::cout << "Strike did not hit\n";
        return 0;
    }   
}

int Character::Cast()
{
    int totalDamage = 0;
    int damageModifier = 0;
    int damageRoll;
    int choice = VectorManip::ChooseFromVector(_spellNames, "spell");
    int attackRoll;
    int totalAttack;
    if(_spells[choice]->against == SpellDefenses::AC)
    {
        attackRoll = Dice::RollDice(20);
        totalAttack = attackRoll + _mods[_keyAbility] + _classdc + _level;
        std::cout << "Attack: " << attackRoll << " + " << _mods[_keyAbility] + _classdc + _level << " = " << totalAttack << "\n";
    }
    else
    {
        std::cout << "Target makes a " << SpellDefenses::defenseToString(_spells[choice]->against) << " save\n";
    }
    std::cout << "Damage: ";
    for(int i = 0; i < _spells[choice]->numberOfDie; i++)
    {
        damageRoll = Dice::RollDice(_spells[choice]->damageDie);
        std::cout << damageRoll << " + ";
        totalDamage += damageRoll;
    }
    if(_spells[choice]->abilityModifier)
    {
        damageModifier += _mods[_keyAbility];
    }
    if(_spells[choice]->flatDamage != 0)
    {
        damageModifier += _spells[choice]->flatDamage;
    }
    totalDamage += damageModifier;
    std::cout << damageModifier << " = " << totalDamage << " of " << _spells[choice]->damageType << "\n";
    return totalDamage;    
}

int Character::Damage(std::shared_ptr<Weapon> weapon, bool thrown)
{
    int total;
    int damageRoll = Dice::RollDice(weapon->damage);
    std::cout << "Damage ";
    if(thrown)
    {
        total = damageRoll + weapon->damageModifierThrown;
        std::cout << damageRoll << " + " << weapon->damageModifierThrown << " = " << total << "\n";
    }
    else
    {
        total = damageRoll + weapon->damageModifier;
        std::cout << damageRoll << " + " << weapon->damageModifier << " = " << total << "\n";        
    }
    return total;
}

int Character::Save()
{
    int save = VectorManip::ChooseFromVector(Saves::SaveName, "save");
    int roll = Dice::RollDice(20);
    int total = roll + _saves[save];
    std::cout << roll << " + " << _saves[save] << " = " << total << "\n";
    return total;
}

int Character::Skill()
{
    int skill = VectorManip::ChooseFromVector(Skills::SkillName, "skill");
    int roll = Dice::RollDice(20);
    int total = roll + _skills[skill];
    std::cout << roll << " + " << _skills[skill] << " = " << total << "\n";
    return total;
}

void Character::AddSpell(int spellsToLearn)
{
    int choice;
    while(spellsToLearn != 0)
    {
        _spells.emplace_back(_allSpells.SelectSpell());
        spellsToLearn--;
    }
    _spellNames.clear();
    for(auto& spell : _spells)
    {
        _spellNames.emplace_back(spell->name);
    }
}

void Character::AddWeapon()
{
    int choice;
    _allWeapons.PrintWeapons();
    _weapons.emplace_back(_allWeapons.SelectWeapon());
    while(true)
    {
        choice = VectorManip::ChooseFromVector(addOptions, "option");
        if(choice == 0)
        {
            _allWeapons.PrintWeapons();
            _weapons.emplace_back(_allWeapons.SelectWeapon());
        }
        else
        {
            break;
        }        
    }
    _weaponNames.clear();
    for(auto& weapon : _weapons)
    {
        _weaponNames.emplace_back(weapon->name);
    }
    UpdateWeapons();
}

void Character::ChangeArmor()
{
    _allArmors.PrintArmors();
    _armor = _allArmors.SelectArmor();
    UpdateArmor();
}

bool Character::Harm(int amount)
{
    if(amount == -1)
    {
        amount = GetPositiveIntegerAmount("damage");
    }
    if(amount >= 2 * _maxhp)
    {
        std::cout << _name << " is dead\n";
        _currenthp = 0;
        return false;
    }
    if(_currenthp - amount <= 0)
    {
        std::cout << _name << " is unconscious\n";
        _currenthp = 0;
        return true;
    }
    _currenthp -= amount;
    std::cout << "Current HP: " << _currenthp << "\n";
    return true;
}

void Character::Heal(int amount)
{
    if(amount == -1)
    {
        amount = GetPositiveIntegerAmount("healing");
    }
    _currenthp = std::min(_maxhp,_currenthp + amount);
    std::cout << "Current HP: " << _currenthp << "\n";
}

void Character::GainExperience(int amount)
{
    if(amount == -1)
    {
        amount = GetPositiveIntegerAmount("experience");
    }
    _experience += amount;
    while(_experience >= 1000)
    {
        _level++;
        _experience -= 1000;
        UpdateStats();
    }
}

void Character::Run()
{
    int choice;
    PrintCharacter();
    if(_spellTradition == SpellTraditions::None)
    {
        VectorManip::RemoveFromVector(runOptions, "Cast");
    }
    while(true)
    {        
        choice = VectorManip::ChooseFromVector(runOptions, "activity");
        if(strcasecmp(runOptions[choice].c_str(), "Strike") == 0)
        {
            Strike(VectorManip::ChooseFromVector(multipleAttackPenaltyOptions, "multiple attack penalty"));
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Cast") == 0)
        {
            Cast();
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Save") == 0)
        {
            Save();
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Skill") == 0)
        {
            Skill();
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Add_Weapon") ==0)
        {
            AddWeapon();
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Change_Armor") ==0)
        {
            ChangeArmor();
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Harm") == 0)
        {
            Harm(-1);
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Heal") == 0)
        {
            Heal(-1);
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Gain_Experience") == 0)
        {
            GainExperience(-1);
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Print") == 0)
        {
            PrintCharacter();
        }
        else if(strcasecmp(runOptions[choice].c_str(), "Quit") == 0)
        {
            std::cout << "Quitting\n";
            break;
        }
    }
}

void Character::CreateCharacter()
{
    std::vector<std::unique_ptr<Ancestry>> ancestries = parseAncestry();
    std::vector<std::string> ancestryNames;
    std::vector<std::unique_ptr<Background>> backgrounds = parseBackground();
    std::vector<std::string> backgroundNames;
    std::vector<std::unique_ptr<Class>> classes = parseClass();
    std::vector<std::string> classNames;
    std::vector<std::string> boosts;
    std::vector<std::string> availableSkills;
    std::vector<std::string> keyAbility;
    std::vector<std::string> traditions;

    for(auto skill : Skills::SkillName)
    {
        availableSkills.emplace_back(skill);
    }
    std::cout << "Please give character name (one word only): ";
    std::cin >> _name;
    for(auto& ancestry : ancestries)
    {
        ancestryNames.emplace_back(ancestry->name);
        ancestry->PrintAncestry();
    }
    int ancestryIndex = VectorManip::ChooseFromVector(ancestryNames, "ancestry");
    _ancestry = ancestries[ancestryIndex]->name;
    _ancestryHP = ancestries[ancestryIndex]->hp;
    _baseSpeed = ancestries[ancestryIndex]->speed;
    ApplyFlaws(ancestries[ancestryIndex]->flaws);
    ApplyBoosts(ancestries[ancestryIndex]->boosts);
    for(auto& background : backgrounds)
    {
        backgroundNames.emplace_back(background->name);
        background->PrintBackground();
    }
    int backgroundIndex = VectorManip::ChooseFromVector(backgroundNames, "background");
    _background = backgrounds[backgroundIndex]->name;
    std::cout << "Training Background skill " << backgrounds[backgroundIndex]->skill << "\n";
    _skillTraining[Skills::stringToSkill(backgrounds[backgroundIndex]->skill)] = Training::Trained;
    VectorManip::RemoveFromVector(availableSkills,backgrounds[backgroundIndex]->skill);
    boosts.emplace_back(backgrounds[backgroundIndex]->boosts[VectorManip::ChooseFromVector(backgrounds[backgroundIndex]->boosts, "boost")]);
    boosts.emplace_back("Free");
    ApplyBoosts(boosts);
    for(auto& clss : classes)
    {
        classNames.emplace_back(clss->name);
        clss->PrintClass();
    }
    int classIndex = VectorManip::ChooseFromVector(classNames, "class");
    _class = classes[classIndex]->name;
    _classhp = classes[classIndex]->hp;
    _perceptionTraining = Training::stringToTraining(classes[classIndex]->perception);
    _weaponProficiency = WeaponProficiency::stringToProficiency(classes[classIndex]->weaponType);
    _weaponTraining = Training::stringToTraining(classes[classIndex]->weaponTraining);
    _armorCategory = ArmorCategories::stringToCategory( classes[classIndex]->armorType);
    _armorTraining = Training::stringToTraining(classes[classIndex]->armorTraining);
    _classdc = Training::stringToTraining(classes[classIndex]->dc);
    for(int i = 0; i < classes[classIndex]->saves.size(); i++)
    {
        _saveTraining[Saves::stringToSave(classes[classIndex]->saves[i])] = Training::stringToTraining(classes[classIndex]->saveTraining[i]);
    }
    if(classes[classIndex]->spellTradition.find('/') != std::string::npos)
    {
        traditions = split(classes[classIndex]->spellTradition, '/');
        _spellTradition = SpellTraditions::stringToTradition(traditions[VectorManip::ChooseFromVector(traditions, "spell tradition")]);
    }
    else
    {
        _spellTradition = SpellTraditions::stringToTradition(classes[classIndex]->spellTradition);
    }  
    _spellsKnown = classes[classIndex]->spellsKnown;  
    if(classes[classIndex]->key.find('/') != std::string::npos)
    {
        boosts.clear();
        boosts = split(classes[classIndex]->key, '/');
        keyAbility.emplace_back(boosts[VectorManip::ChooseFromVector(boosts, "key ability")]);
    }
    else
    {
        keyAbility.emplace_back(classes[classIndex]->key);
    }
    _keyAbility = Attributes::stringToAttribute(keyAbility[0]);
    ApplyBoosts(keyAbility);
    boosts.clear();
    boosts = {"Free","Free","Free","Free"};
    ApplyBoosts(boosts);
    UpdateAttributes();
    UpdateSaves();
    if(_mods[Attributes::Intelligence] == -1)
    {
        classes[classIndex]->skills.pop_back();
    }
    else
    {
        for(int i = 0; i < _mods[Attributes::Intelligence]; i++)
        {   
            std::cout << "Adding skill from int\n";
            classes[classIndex]->skills.emplace_back("Free");
        }
    }
    ApplySkills(classes[classIndex]->skills,availableSkills);
    UpdateSkills();
    PrintCharacter();
    _weapons.emplace_back(_allWeapons.SelectWeapon("Fist"));
    _weaponNames.emplace_back("Fist");
    AddWeapon();
    ChangeArmor();
    if(_spellTradition != SpellTraditions::None)
    {
        _allSpells.ParseSpells(_spellTradition);
        _allSpells.PrintSpells();
        AddSpell(_spellsKnown);
        UpdateSpells();
    }
}

