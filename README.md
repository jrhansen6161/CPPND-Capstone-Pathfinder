# CPPND: Capstone Pathfinder Repo

This is the repo for the Pathfinder Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

Pathfinder is a text interface for creating, storing, and using basic Pathfinder 2nd edition characters.

You start off by creating a new character or loading an existing character from the "saves' directory.  You must give the filename for a character to load, you will be prompted to reenter the name if it was not found.  Creating a character will walk you through naming your character, choosing an ancestery, background, and class as well as applying boosts (raise an attribute by 2) and choosing skills.  At the end you will choose weapons and then go to the dice roller.

The dice roller will print your character and then give you a menu of ativities.  Note that most activities roll a 20 sided die and add modifiers determined by your stats.  Only the strike and cast action's damage uses a die other than the 20 sided.
Strike is attacking with a weapon you have
Cast is casting a spell you have (only availabe for a class with spell casting)
Save is make a saving throw based on your stats
Skill is rolling a skill check based on your stats
Adding a weapon can expand your options while striking
Change armor switches the armor you are wearing
Harm deals damage to the character and informs you if you are unconscious (< 0 HP) or dead (you took more than 2x your max HP in damage)
Heal restores current HP up to the max HP
Gain experience increases your experience by an amount, every 1000 experience your level will increase.  
  Note that most of your stats will increase with level (any skill, weapon, armor, or save you are at least trained in as well as your spells and HP)
Print reprints the character sheet
Quit exits the dice roller 

Once you quit, you can save your character based on its name.  Note that it will overwrite without warning.

Rubric Points.
Loops, Functions, I/O
  The project is clearly organized into functions.
  The ancesteries, backgrounds, classes, weapons, armor, and spells are all read from files.  Additionally the characters can be saved and loaded from files.
  The project accepts input from the user at every step of the program.
Object Oriented Programming
  The project is orgranized into classes to hold data and perform tasks.  There are data classes for ancestery, background, class, weapons, armor, and spells.  Additionally the Character class holds the data and runs the dice.
  All class member functions document their effects through function names and do not change the program state in undocumented ways.
Memory Management
  References are heavily used in VectorManip namespace as well as the Character class.
  RAII is used the ancestery, background, class, weapons, armor, and spells found in the DataParser.
  Smart pointers are used (unique and shared) in the ancestery, background, class, weapons, armor, and spells found in the DataParser.  No raw pointers are used.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Pathfinder`.