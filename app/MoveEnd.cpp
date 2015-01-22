/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveEnd.cpp

This class moves the cursor down one line when ctrl+p is pressed
*/
#include "MoveEnd.hpp"
#include "EditorException.hpp"

void MoveEnd::execute(Editor& editor)
{
    if(editor.cursorColumn() == (editor.lineSize() + 1)) {
        throw EditorException(" ");
    } else {
        previousColumn = editor.cursorColumn();
        editor.moveCursorEnd();
    }
}

void MoveEnd::undo(Editor& editor)
{
    editor.undoMoveCursorEnd(previousColumn);
}
