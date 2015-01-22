/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : Backspace.hpp

ctrl + h - Backspace
*/
#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP
#include <string>
#include "Command.hpp"
#include "Editor.hpp"

class Backspace : public Command
{
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    char oldChar;
    bool deleteLine; // used as a flag, if false, we don't delete a character
};

#endif
