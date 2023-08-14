/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Ashwin B  N
Student ID#: 112763222
Email      : abharathan-nettoor@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#define _CTR_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// Function to display a formatted phone number
void displayFormattedPhone(const char* phoneNo);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

/* Function to read an integer input from the user
   and validate it till correct input*/
int inputInt();

/* Function to read a posite integer input from the user
   and validate it till correct input*/
int inputIntPositive();

/* Function to read an integer input from the user within the mentioned range
   and validate it till correct input*/
int inputIntRange(int lower, int upper);

/* Function to read a character input from the user,
   which should be one of the valid characters provided*/
char inputCharOption(const char* validCharacters);

/* Function to read a string input from the user,
   which should be within the length range given*/
void inputCString(char* inputStr, int minNumChar, int maxNumChar);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
