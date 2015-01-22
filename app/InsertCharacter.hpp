/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : InsertCharacter.hpp

Inserts a character where the cursor is currently positioned.
*/

#ifndef INSERTCHARACTER_HPP
#define INSERTCHARACTER_HPP
#include <string>
#include "Command.hpp"
#include "Editor.hpp"

class InsertCharacter : public Command
{
public:
    InsertCharacter(char inputChar);
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    char input;

};

#endif
