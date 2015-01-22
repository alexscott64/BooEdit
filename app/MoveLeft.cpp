/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveLeft.cpp

This class is in charge of moving the cursor right by one when ctrl+u is pressed
*/
#include <vector>
#include <string>
#include <sstream>
#include "MoveLeft.hpp"
#include "Editor.hpp"
#include "EditorException.hpp"
#include "BooEditLog.hpp"

void MoveLeft::execute(Editor& editor)
{
    // if we try to move past the beginning, throw exception
    if(editor.cursorColumn() == 1 && editor.cursorLine() == 1) {
        throw EditorException("Already at beginning");
    } else { // otherwise, move the cursor left
        editor.moveCursorLeft();
    }
}

void MoveLeft::undo(Editor& editor)
{
    editor.moveCursorRight();
}
