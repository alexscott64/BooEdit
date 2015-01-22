/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveUp.cpp

This class moves the cursor up one line when ctrl+i is pressed
*/

#include "MoveUp.hpp"
#include "EditorException.hpp"

void MoveUp::execute(Editor& editor)
{
    // test to see if we have a line above us
    if(editor.cursorLine() == 1)
    {
        throw EditorException("Already at top");
    } else {
        nextColumn = editor.cursorColumn(); // get cursor column at cur row
        editor.moveCursorUp();
    }
}

void MoveUp::undo(Editor& editor)
{
    editor.undoMoveCursorUp(nextColumn);
}
