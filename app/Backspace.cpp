/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : Backspace.cpp

ctrl + h - Backspace
*/
#include "Backspace.hpp"
#include "EditorException.hpp"
#include "BooEditLog.hpp"

void Backspace::execute(Editor& editor)
{
    deleteLine = false;
    if(editor.cursorLine() == 1 && editor.cursorColumn() == 1) {
        throw EditorException("Already at beginning");
    } else if(editor.lineSize() == 0)  { // empty string, just undo a new line
        deleteLine = true; // we delete an empty line
        editor.clearLine();
    } else if(editor.cursorColumn() != 1) {
        oldChar = editor.getChar(); // save for when we undo
        deleteLine = false; // we don't delete a line
        editor.undoInsertCharacter(); // deletes the character
    } else { // we delete an entire line
        deleteLine = true;
        editor.backspace();
    }
}

void Backspace::undo(Editor& editor)
{
    if(deleteLine == false) {
        // we just need to re-insert our character
        editor.insertCharacter(oldChar);
    } else if (editor.cursorColumn() == (editor.lineSize() + 1)) {
        editor.undoClearLine(); // undo empty line
    } else {
        editor.undoBackspace();
    }
}
