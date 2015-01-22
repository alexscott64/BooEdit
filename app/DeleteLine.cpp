/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : DeleteLine.cpp

ctrl + d - Delete Line
*/
#include "DeleteLine.hpp"
#include "EditorException.hpp"

void DeleteLine::execute(Editor& editor)
{
    singleLine = false;
    lastLine = false;
    oldString = editor.line(editor.cursorLine()); // save old string
    oldColumn = editor.cursorColumn();
    if(editor.cursorLine() == 1 && editor.lineCount() == 1) { // only one line
        singleLine = true;
        editor.deleteLine();
    } else if(editor.cursorLine() == editor.lineCount()) { // last line
        lastLine = true;
        editor.deleteLastLine();
    } else { // any other line
        editor.deleteLine();
    }
}

void DeleteLine::undo(Editor& editor)
{
    if(singleLine == true) { // undo a single line deletion
        editor.undoDeleteFirstLine(oldString, oldColumn);
    } else if(lastLine == true) { // undo last line deletion
        editor.undoDeleteLastLine(oldString, oldColumn);
    } else { // undo other deletions
        editor.undoDeleteLine(oldString, oldColumn);
    }
}
