/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveEnd.hpp

This class moves the cursor down one line when ctrl+p is pressed
*/
#ifndef MOVEEND_HPP
#define MOVEEND_HPP
#include "Command.hpp"
#include "Editor.hpp"
class MoveEnd : public Command
{
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    int previousColumn;
};
#endif
