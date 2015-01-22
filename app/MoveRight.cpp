/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : MoveRight.cpp

This class is in charge of moving the cursor right by one when ctrl+o is pressed
*/
#include <vector>
#include <string>
#include "MoveRight.hpp"
#include "Editor.hpp"
#include "EditorException.hpp"

void MoveRight::execute(Editor& editor)
{
    if(editor.cursorColumn() >= (editor.lineSize() + 1)
        && editor.lineCount() == editor.cursorLine()) {
        throw EditorException("Already at end");
    } else { // otherwise, move the cursor right
        editor.moveCursorRight();
    }
}
// undo should move the cursor left
void MoveRight::undo(Editor& editor)
{
    editor.moveCursorLeft();
}
