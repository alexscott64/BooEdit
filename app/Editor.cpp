// Editor.cpp
//
// ICS 45C Fall 2014
// Project #4: People Just Love to Play with Words
//
// Implementation of the Editor class

#include <sstream>
#include <vector>
#include <string>
#include "Editor.hpp"
#include "EditorException.hpp"
#include "BooEditLog.hpp"

// functions that will help us clean up some code
namespace
{
    // generate offset for a substring (start index, end index)
    // for use in inserting a new line
    int getSubstringOffset(size_t sl, int start)
    {
        return sl - start;
    }
}

Editor::Editor()
    : numberOfLines{1}, column{1}, row{1}
{
    lines.insert(lines.begin(), "");
}


int Editor::cursorLine() const
{
    return row;
}


int Editor::cursorColumn() const
{
    return column;
}


int Editor::lineCount() const
{
    return numberOfLines;
}

// return text at a given line number
const std::string& Editor::line(int lineNumber) const
{
    return lines[lineNumber - 1];
}

size_t Editor::lineSize() const
{
    return lines[row - 1].size();
}

char Editor::getChar() const
{
    std::string cur = lines[row - 1];
    char curChar = cur.at(column - 2);
    return curChar;
}


// Movement functions
void Editor::moveCursorRight()
{
    size_t sLine = lines[row - 1].size();
    if(sLine == 0) {
        row++;
        column = 1;
    } else if(column == sLine + 1) { // current column is at end of line
        row++;
        column = 1;
    } else {
        column++;
    }
}

void Editor::moveCursorLeft()
{
    if(column == 1) {
        size_t sLine = lines[row - 2].size();
        row--;
        column = sLine + 1;
    } else {
        column--;
    }
}

// moves the cursor down
void Editor::moveCursorDown()
{
    size_t nextLine = lines[row].size();
    size_t curLine = lines[row - 1].size();
    int currentColumn = column; // save our current column
    row++;
    if(nextLine == 0) { // empty line below us
        column = 1;
    } else if(curLine > nextLine) { // line 1 length > line 2 length
        if(currentColumn > nextLine) { // we are beyond length of line 1
            column = nextLine + 1; // set column to max value of line 2
        } else { // otherwise
            column = currentColumn; // put column to where cursor was originally
        }
    } else if(curLine <= nextLine) { // line 1 length < line 2 length
        column = currentColumn; // put column to where cursor was originally
    }
}

// we take in the previous column we were on so that we can just go back to it
void Editor::undoMoveCursorDown(int col)
{
    row--;
    column = col;
}

// moves cursor up a row
void Editor::moveCursorUp()
{
    size_t prevLine = lines[row - 2].size(); // line above us
    size_t curLine = lines[row - 1].size(); // current line
    int currentColumn = column; // current column
    row--; // go one row up
    if(prevLine == 0) { // empty(/1char) line above us
        column = 1; // set column to start
    } else if(prevLine > curLine) { // line 1 length > line 2 length
        column = currentColumn; // set prevLine column to where ours is
    } else if(prevLine <= curLine) { // line 1 length < line 2 length
        if(currentColumn > prevLine) { // current col in line 2 is larger l1
            column = prevLine + 1; // set column above us to length l1 + 1
        } else {
            column = currentColumn;
        }
    }
}

// take in the column we were just at before we moved up
// increment the row to where we were and set column to what it was
void Editor::undoMoveCursorUp(int col)
{
    row++;
    column = col;
}

// move cursor to the beginning of the current line
void Editor::moveCursorHome()
{
    column = 1;
}

// move cursor to the beginning of the current line
void Editor::undoMoveCursorHome(int col)
{
    column = col;
}

// move cursor to the end of the line + 1
void Editor::moveCursorEnd()
{
    size_t sLine = lines[row - 1].size();
    if(sLine == 0) {
        column = 1;
    } else {
        column = sLine + 1;
    }
}

// move cursor to previous position before end was called
void Editor::undoMoveCursorEnd(int col)
{
    column = col;
}

// create a new line
void Editor::insertNewLine()
{
    std::string currLine = lines[row - 1];
    size_t tempSize = currLine.size();
    if(column != 1 || column != 0 || (column - 1) != tempSize) {
        int lengthOffset = getSubstringOffset(tempSize, (column - 1));
        std::string cutTemp = currLine.substr((column - 1), lengthOffset);
        // Insert a new line
        lines[row - 1].erase(column - 1);
        // after incrementing, row and amount of lines, initialize the new row
        numberOfLines++;
        lines.insert(lines.begin() + row, cutTemp);
        row++;
        column = 1;
    } else {
        numberOfLines++;
        lines.insert(lines.begin() + row, "");
        row++;
        column = 1;
    }
}

// undo the new line
void Editor::undoNewLine()
{
    size_t updateCol = lines[row - 2].size(); // holds size of our old string
    lines[row - 2] += lines[row - 1];
    lines.erase(lines.begin() + (row - 1));
    row--;
    numberOfLines--;
    column = updateCol + 1; // update to point back to where we were
}

// insert a single character
void Editor::insertCharacter(char& c)
{
    lines[row - 1].insert(column - 1, 1, c);
    column++;
}

// usually used when deleting a character, or when using undo after doing
// calling insertCharacter()
void Editor::undoInsertCharacter()
{
    column--;
    lines[row - 1].erase(lines[row - 1].begin() + (column - 1));
}

// backspace
void Editor::backspace()
{
    // special case when we move the current line up
    // we append to the string above and add our column at the end
    size_t updateCol = lines[row - 2].size();
    lines[row - 2] += lines[row - 1];
    lines.erase(lines.begin() + (row - 1));
    row--;
    numberOfLines--;
    column = updateCol + 1;
}

void Editor::undoBackspace()
{
    std::string currLine = lines[row - 1];
    size_t tempSize = currLine.size();
    int lengthOffset = getSubstringOffset(tempSize, (column - 1));
    std::string cutTemp = currLine.substr((column - 1), lengthOffset);
    // Insert a new line
    lines[row - 1].erase(column - 1);
    // after incrementing, row and amount of lines, initialize the new row
    numberOfLines++;
    lines.insert(lines.begin() + row, ""); // initialize and shift other rows
    row++;
    column = 1;
    lines[row - 1] += cutTemp; // insert substring into new line
}

void Editor::clearLine() // only used when we backspace an empty line
{
    size_t prevLine = lines[row - 2].size();
    lines.erase(lines.begin() + (row - 1));
    row--;
    numberOfLines--;
    column = prevLine + 1;
}

void Editor::undoClearLine() // when we undo backspacing an empty line
{
    numberOfLines++;
    lines.insert(lines.begin() + row, "");
    row++;
    column = 1;
}

// delete an entire line of text
void Editor::deleteLine()
{
    if(row == 1 && numberOfLines == 1) { // we only have one line of text
        numberOfLines++;
        lines.insert(lines.begin() + row, "");
        row++;
        column = 1;
        lines.erase(lines.begin() + (row - 2));
        row--;
        numberOfLines--;
        column = 1;
    } else { // more than one line of text
        // deleting a line means we shift every line under it up by one
        size_t currentSize = lines[row - 1].size(); // size of current line
        size_t nextSize = lines[row].size(); // size of next line
        int currentColumn = column; // save current lines column
        lines.erase(lines.begin() + (row - 1));
        numberOfLines--;
        if(nextSize > currentSize) {
            column = currentColumn;
        }
        else if(nextSize <= currentSize) {
            if(nextSize < currentColumn) {
                column = nextSize + 1;
            } else if(nextSize >= currentColumn) {
                column = currentColumn;
            }
        }
    }
}

// delete an entire line if it is the last line
void Editor::deleteLastLine()
{
    size_t currentSize = lines[row - 1].size(); // size of line we are deleting
    size_t prevSize = lines[row - 2].size(); // size of line cursor will go to
    int currentColumn = column;
    lines.erase(lines.begin() + (row - 1));
    row--;
    numberOfLines--;
    if(currentSize > prevSize) {
        if(currentColumn > prevSize) {
            column = prevSize + 1;
        } else if(currentColumn <= prevSize) {
            column = currentColumn;
        }
    }
    else if(currentSize <= prevSize) {
        column = currentColumn;
    }
}

// undo when we delete an entire line
void Editor::undoDeleteLine(std::string oldString, int col)
{
    numberOfLines++;
    lines.insert(lines.begin() + (row - 1), oldString);
    column = col;
}

// undo when we delete the last line
void Editor::undoDeleteLastLine(std::string oldString, int col)
{
    numberOfLines++;
    lines.insert(lines.begin() + row, oldString);
    row++;
    column = col;
}

// undo a deletion of only a single line
void Editor::undoDeleteFirstLine(std::string oldString, int col)
{
    lines[row - 1] = oldString;
    column = col;
}
