/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveRight.hpp

This class is in charge of moving the cursor right by one when ctrl+o is pressed
*/

#ifndef MOVERIGHT_HPP
#define MOVERIGHT_HPP

#include <vector>
#include <string>
#include "Command.hpp"
#include "Editor.hpp"

class MoveRight : public Command
{
public:
void execute(Editor& editor);
void undo(Editor& editor);
};

#endif
