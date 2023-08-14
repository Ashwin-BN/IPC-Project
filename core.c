/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Ashwin B N
Student ID#: 112763222
Email      : abharathan-nettoor@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include "core.h"

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!


// Function to clear the standard input buffer
void clearInputBuffer()
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

int inputInt()
{
    // String to sore user input
    char buffer[80];
    // Variables to handle errors, loop control, and the final result
    int error, i, result;

    // LOOP for validating user input string
    do {
        // Initialize error flag to 0 (no error)
        error = 0;
        // Read user input as a string, limited to 79 characters
        fgets(buffer, 80, stdin);

        buffer[strlen(buffer) - 1] = '\0';

        // Validating each character in the input string 
        for (i = 0; i < (int)strlen(buffer); i++)
        {
            if (!isdigit(buffer[i]) && buffer[i] != '-')
                error = 1;
        }
        // ERROR message 
        if (error)
            printf("Error! Input a whole number: ");

    } while (error);

    // Convert the validated string to an integer 
    result = atoi(buffer);

    return result;
}

int inputIntPositive()
{
    int input;

    // LOOP for validating user input string
    do {
        // Calling inputInt() for integer user input
        input = inputInt();

        // ERROR message if input is -ve
        if (input <= 0)
            printf("ERROR! Value must be > 0: ");
    } while (input <= 0);
    return input;
}

int inputIntRange(int lower, int upper)
{
    int input;
    // LOOP for validating user input string
    do {
        input = inputInt();

        // ERROR message if input is not between given range
        if (!(input <= upper && input >= lower))
            printf("ERROR! Value must be between %d and %d inclusive: ",
                lower, upper);
    } while (!(input <= upper && input >= lower));

    return input;
}

char inputCharOption(const char* validCharacters)
{
    // String to store user input characters
    char buffer[80];
    // Pointer to check if user input character is valid
    char* found;

    do {
        fgets(buffer, 80, stdin);

        // Replace the newline character with null character
        buffer[strlen(buffer) - 1] = '\0';

        // Checking if user input is present in the valid string
        found = strstr(validCharacters, buffer);

        // ERROR message if user input is not present in the valid string
        if (found == NULL)
            printf("ERROR: Character must be one of [%s]: ", validCharacters);

    } while (found == NULL);

    //Returning the valid character
    return buffer[0];
}

void inputCString(char* inputStr, int minChar, int maxChar) {
    // To store the user input temporarily
    char buffer[80];
    int error, strLength;

    // LOOP for validating user input
    do {
        fgets(buffer, sizeof(buffer), stdin);

        // Replace the newline character with null character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Calculate the length of string
        strLength = strlen(buffer);

        // ERROR messages if, user input is not valid...
        if (minChar == maxChar && strLength != minChar)
        {
            printf("Invalid %d-digit number! Number: ", minChar);
            error = 1;
        }
        else if (strLength < minChar)
        {
            printf("ERROR: String length must be between %d and %d chars: ",
                minChar, maxChar);
            error = 1;
        }
        else if (strLength > maxChar)
        {
            printf("ERROR: String length must be no more than %d chars: ",
                maxChar);
            error = 1;
        }
        else
            error = 0;
    } while (error);

    // Copy the validated input to the output string
    strncpy(inputStr, buffer, maxChar);
    // Ensure null-termination
    inputStr[maxChar] = '\0';
}

void displayFormattedPhone(const char* phoneNo)
{
    int error = 1; //Initializing variable
    int i;  // Variable for iterration
    int strLenght = 0;  // Variable to count the total digits in the input string

    // Checks that the entered character is not an empty line
    if (phoneNo != NULL)
    {
        // LOOP for validating the characters in string
        for (i = 0; phoneNo[i] && error; i++)
        {
            // Validating if characters are digit and couting it
            if (isdigit(phoneNo[i]))
                strLenght++;
            else
                error = 0;
        }
    }
    // Printing accorinding to the  validation and if the lenght is 10
    if (error && strLenght == 10)
    {
        // Loop for printing in the format of phone number
        for (i = 0; i < strLenght; i++)
        {
            if (i == 0)
                printf("(%c", phoneNo[i]);

            else if (i == 3)
                printf(")%c", phoneNo[i]);

            else if (i == 6)
                printf("-%c", phoneNo[i]);

            else
                printf("%c", phoneNo[i]);

        }
    }
    // Printing statement if phone number is wrong
    else
        printf("(___)___-____");
}