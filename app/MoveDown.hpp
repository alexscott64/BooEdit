/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveDown.hpp

This class moves the cursor down one line when ctrl+k is pressed
*/
#ifndef MOVEDOWN_HPP
#define MOVEDOWN_HPP

#include "Command.hpp"
#include "Editor.hpp"

class MoveDown : public Command
{
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    int previousColumn;
};

#endif
