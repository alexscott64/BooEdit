/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveDown.cpp

This class moves the cursor down one line when ctrl+k is pressed
*/
#include "MoveDown.hpp"
#include "EditorException.hpp"

void MoveDown::execute(Editor& editor)
{
    if(editor.cursorLine() == editor.lineCount())
    {
        throw EditorException("Already at bottom");
    } else {
        previousColumn = editor.cursorColumn(); // get cursor column at cur row
        editor.moveCursorDown();
    }
}

void MoveDown::undo(Editor& editor)
{
    editor.undoMoveCursorDown(previousColumn);
}

