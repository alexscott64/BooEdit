/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : InsertNewLine.hpp

This class is in charge of creating a new line when the user presses ctrl+j/m
*/

#ifndef INSERTNEWLINE_HPP
#define INSERTNEWLINE_HPP

#include "Command.hpp"
#include "Editor.hpp"

class InsertNewLine : public Command
{
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
};

#endif
