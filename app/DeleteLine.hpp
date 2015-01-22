/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : DeleteLine.hpp

ctrl + d - Delete Line
*/
#ifndef DELETELINE_HPP
#define DELETELINE_HPP
#include <string>
#include "Command.hpp"
#include "Editor.hpp"

class DeleteLine : public Command
{
public:
    void execute(Editor& editor);
    void undo(Editor& editor);
private:
    std::string oldString;
    int oldColumn;
    bool singleLine; // check to see if there is only one line
    bool lastLine; // check to see if we deleted the last line
};

#endif
