/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : InsertCharacter.cpp

Inserts a character where the cursor is currently positioned.
*/

#include <vector>
#include <algorithm>
#include "InsertCharacter.hpp"
#include "Keypress.hpp"

InsertCharacter::InsertCharacter(char inputChar)
    : Command{}, input{inputChar}
{
}

void InsertCharacter::execute(Editor& editor)
{
    editor.insertCharacter(input);
}

void InsertCharacter::undo(Editor& editor)
{
    editor.undoInsertCharacter();
}

