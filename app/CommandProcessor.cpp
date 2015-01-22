// CommandProcessor.cpp
//
// ICS 45C Fall 2014
// Project #4: People Just Love to Play with Words
//
// Implementation of the CommandProcessor class

#include <vector>
#include <sstream>
#include "CommandProcessor.hpp"
#include "BooEditLog.hpp"
#include "Editor.hpp"
#include "EditorException.hpp"
#include "Keypress.hpp"
#include "MoveRight.hpp"
#include "MoveLeft.hpp"
#include "InsertCharacter.hpp"
#include "InsertNewLine.hpp"
#include "MoveUp.hpp"
#include "MoveDown.hpp"
#include "MoveHome.hpp"
#include "MoveEnd.hpp"
#include "Backspace.hpp"
#include "DeleteLine.hpp"

CommandProcessor::CommandProcessor(Editor& editor, EditorView& view)
    : editor{editor}, view{view}
{
}


namespace
{
    // An "enum class" defines a type that has one of the constant values
    // specified.  So, in this case, a variable of type UserInteractionType
    // could have the value UserInteractionType::command,
    // UserInteractionType::undo, etc.
    enum class UserInteractionType
    {
        command,
        undo,
        redo,
        quit
    };

    // A UserInteraction describes one interaction that the user undertakes
    // with BooEdit.  There are four different kinds of interactions:
    //
    // * Commands, which attempt to affect some kind of change on the editor
    // * Undo, which asks for the previous change to be undone
    // * Redo, which asks for the most-recently undone change to be redone
    // * Quit, which asks for the editor to be stopped altogether
    //
    // A Command* is included for the case where UserInteractionType::command
    // is the specified type; otherwise, it will be nullptr.
    struct UserInteraction
    {
        UserInteractionType type;
        Command* command;
    };

    UserInteraction makeCommandInteraction(Command* command)
    {
        return UserInteraction{UserInteractionType::command, command};
    }

    UserInteraction makeUndoInteraction()
    {
        return UserInteraction{UserInteractionType::undo, nullptr};
    }


    UserInteraction makeRedoInteraction()
    {
        return UserInteraction{UserInteractionType::redo, nullptr};
    }


    UserInteraction makeQuitInteraction()
    {
        return UserInteraction{UserInteractionType::quit, nullptr};
    }

    UserInteraction nextUserInteraction()
    {
        Command* command = nullptr;
        while (true)
        {
            Keypress keypress = nextKeypress();

            if (keypress.ctrl)
            {
                // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly
                switch (keypress.c)
                {
                case 'X':
                    booEditLog("Quit");
                    return makeQuitInteraction();
                case 'O':
                    command = new MoveRight;
                    return makeCommandInteraction(command);
                case 'U':
                    command = new MoveLeft;
                    return makeCommandInteraction(command);
                case 'I':
                    command = new MoveUp;
                    return makeCommandInteraction(command);
                case 'K':
                    command = new MoveDown;
                    return makeCommandInteraction(command);
                case 'Y':
                    command = new MoveHome;
                    return makeCommandInteraction(command);
                case 'P':
                    command = new MoveEnd;
                    return makeCommandInteraction(command);
                case 'H':
                    command = new Backspace;
                    return makeCommandInteraction(command);
                case 'D':
                    command = new DeleteLine;
                    return makeCommandInteraction(command);
                case 'J':
                case 'M':
                    command = new InsertNewLine;
                    return makeCommandInteraction(command);
                case 'Z':
                    return makeUndoInteraction();
                case 'A':
                    return makeRedoInteraction();
                }
            }
            else
            {
                // The user pressed a normal key (e.g., 'h') without holding
                // down Ctrl; react accordingly
                command = new InsertCharacter(keypress.c);
                return makeCommandInteraction(command);
            }
        } // end while
    } // end nextUserInteraction

    // method to clear the objects in the undo/redo vectors
    void freeVector(std::vector<Command*> &element) {
        for(int i = 0; i < element.size(); i++)
        {
            delete element[i]; // delete command object
        }
        element.clear(); // clear vector
    } // end free vector
} // end namespace

// This function implements command execution
void CommandProcessor::run()
{
    bool commandInteraction = false;
    std::vector<Command*> undoVector; // used for undo
    std::vector<Command*> redoVector; // used for redo
    view.refresh();
    while (true)
    {
        UserInteraction interaction = nextUserInteraction();
        if (interaction.type == UserInteractionType::quit)
        {
            break;
        }
        else if (interaction.type == UserInteractionType::undo) // UNDO
        {
            try
            {
                if(undoVector.empty())
                {
                    throw EditorException(" ");
                } else {
                    interaction.command = undoVector.back();
                    redoVector.push_back(interaction.command);
                    interaction.command->undo(editor);
                    commandInteraction = false;
                    undoVector.pop_back();
                }
            }
            catch (EditorException& e)
            {
                view.showErrorMessage(e.getReason());
            }
            view.refresh();
        }
        else if (interaction.type == UserInteractionType::redo) // REDO
        {
            try
            {
                // if the redo stack is empty -> we can't redo
                // if the last known state was at command -> we can't redo
                if(redoVector.empty() || commandInteraction == true)
                {
                    freeVector(redoVector);
                    throw EditorException(" ");
                } else {
                    interaction.command = redoVector.back();
                    undoVector.push_back(interaction.command);
                    interaction.command->execute(editor);
                    redoVector.pop_back();
                    view.clearErrorMessage();
                }
            }
            catch(EditorException& e)
            {
                view.showErrorMessage(e.getReason());
            }
            view.refresh();
        }
        else if (interaction.type == UserInteractionType::command) // COMMAND
        {
            try
            {
                interaction.command->execute(editor);
                freeVector(redoVector);
                commandInteraction = true;
                undoVector.push_back(interaction.command);
                view.clearErrorMessage();
            }
            catch (EditorException& e)
            {
                delete interaction.command;
                view.showErrorMessage(e.getReason());
            }
            view.refresh();
        }
    } // end while
    freeVector(undoVector);
    freeVector(redoVector);
} // end run
