/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveHome.cpp

This class moves the cursor down one line when ctrl+y is pressed
*/
#include "MoveHome.hpp"
#include "EditorException.hpp"

void MoveHome::execute(Editor& editor)
{
    if(editor.cursorColumn() == 1)
    {
        throw EditorException(" "); // no error message, just don't execute
    } else {
        previousColumn = editor.cursorColumn();
        editor.moveCursorHome();
    }
}

void MoveHome::undo(Editor& editor)
{
    editor.undoMoveCursorHome(previousColumn);
}
