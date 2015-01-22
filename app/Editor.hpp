// Editor.hpp
//
// ICS 45C Fall 2014
// Project #4: People Just Love to Play with Words
//
// The Editor class implements the "model" of BooEdit.  In other words, its
// job is to maintain the underlying data -- the current lines of text, where
// the cursor is supposed to be, etc. -- providing operations that allow the
// EditorView to access that data and also providing basic operations that
// allow the various Command objects to make necessary changes.
//
// The member functions already declared in the Editor class are absolutely
// necessary for EditorView to work, so they cannot be removed or have their
// declarations changed (though you may need to implement them; see
// Editor.cpp).
//
// You will absolutely need to implement additional member functions, because I
// haven't declared any functions that change the editor's data (e.g.,
// inserting characters, moving the cursor), which you'll need in order to
// implement the various Command objects.  You may also need additional member
// functions that access the editor's data in ways not provided here.
//
// When adding member functions, focus on adding "primitive" tools that you
// might be able to use in multiple command implementations, as opposed to
// just writing a member function for each commmand.
//
// The Editor class is unaware of the concept of "undo"; it is the job of the
// Command objects to know what they need to do in order to undo a Command.
//
// Note that the notion of "line number" and "column number" here is one-based,
// not zero-based, which means that the top left corner of the file is line 1
// column 1.  You can handle this however you'd like inside of your class, but
// the rest of BooEdit expects Editor objects to take and return one-based
// line and column numbers.

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <vector>

class Editor
{
public:
    // Initializes the editor.  Initially, the cursor is on line 1 column 1
    // and there is one empty line of text in the editor.
    Editor();

    // Returns the line number where the cursor currently should reside.
    int cursorLine() const;

    // Returns the column number where the cursor currently should reside.
    int cursorColumn() const;

    // Returns the number of lines of text currently in the editor.
    int lineCount() const;

    // Returns the text on the given line number.
    const std::string& line(int lineNumber) const;

    // command functions
    void moveCursorRight();
    void moveCursorLeft();
    void moveCursorDown();
    void moveCursorUp();
    void moveCursorHome();
    void moveCursorEnd();
    void insertNewLine();
    void deleteLine();
    void deleteLastLine();

    // undo command functions
    void undoMoveCursorDown(int col);
    void undoMoveCursorUp(int col);
    void undoMoveCursorHome(int col);
    void undoMoveCursorEnd(int col);
    void undoNewLine();
    void undoClearLine();
    void undoDeleteLine(std::string oldString, int col);
    void undoDeleteLastLine(std::string oldString, int col);
    void undoDeleteFirstLine(std::string oldString, int col);

    // insert/delete character function
    void insertCharacter(char& c);
    void undoInsertCharacter();
    void backspace();
    void clearLine(); // removes a new line, increments row up
    void undoBackspace();
    void deleteCharacter();

    // gives us the size of a line for error-checking in our command classes
    size_t lineSize() const;
    size_t oldLineSize() const;
    char getChar() const; // gets character at current column

private:
    // Write declarations for any private member variables here.
    // Additionally, you can add any private member functions you'd like.
    int numberOfLines;
    int column;
    int row;
    std::vector<std::string> lines;
};



#endif // EDITOR_HPP

