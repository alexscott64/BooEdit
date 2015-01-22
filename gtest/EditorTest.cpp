/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 4 - People Just Love to Play with Words
Class           : ICS45C Fall 2014
File            : EditorTest.cpp

Test the Editor class
*/
#include <gtest/gtest.h>
#include <string>
#include "Editor.hpp"

TEST(TestEditor, canInsertCharacter)
{
    Editor ea;
    char input = 'c';
    std::string output{"c"};
    ea.insertCharacter(input);
    ASSERT_EQ(output, ea.line(1));
}
