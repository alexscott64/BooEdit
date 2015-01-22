/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : InsertNewLine.cpp

This class is in charge of creating a new line when the user presses ctrl+j/m

We create a new line just under the current line. Any text at or after the
cursor on the current line is moved to the beginning of the new line.
*/
#include <sstream>
#include "InsertNewLine.hpp"
#include "BooEditLog.hpp"

void InsertNewLine::execute(Editor& editor)
{
    editor.insertNewLine();
}

void InsertNewLine::undo(Editor& editor)
{
    editor.undoNewLine();
}
