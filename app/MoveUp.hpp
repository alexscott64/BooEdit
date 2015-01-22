/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveUp.hpp

This class moves the cursor up one line when ctrl+i is pressed
*/

#ifndef MOVEUP_HPP
#define MOVEUP_HPP

#include "Command.hpp"
#include "Editor.hpp"

class MoveUp : public Command
{
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    int nextColumn;
};

#endif
