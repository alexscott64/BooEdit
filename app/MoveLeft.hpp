/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveLeft.hpp

This class is in charge of moving the cursor right by one when ctrl+u is pressed
*/
#ifndef MOVELEFT_HPP
#define MOVELEFT_HPP

#include "Command.hpp"
#include "Editor.hpp"

class MoveLeft : public Command
{
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
};

#endif
