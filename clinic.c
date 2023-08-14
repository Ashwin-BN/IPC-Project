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

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->patientName, patient->patientID);
        displayFormattedPhone(patient->patientPhone.phoneNumber);
        printf(" (%s)\n", patient->patientPhone.phoneDescription);
    }
    else
    {
        printf("%05d %-15s ", patient->patientID,
            patient->patientName);
        displayFormattedPhone(patient->patientPhone.phoneNumber);
        printf(" (%s)\n", patient->patientPhone.phoneDescription);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientID, patient->patientName);

    displayFormattedPhone(patient->patientPhone.phoneNumber);

    printf(" (%s)\n", patient->patientPhone.phoneDescription);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientID, patient->patientName);

        displayFormattedPhone(patient->patientPhone.phoneNumber);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->patientName, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->patientPhone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    // iteration variable and flag variable for error checking
    int i, error = 1;

    // If the format is a table, display a header for the table
    if (fmt == FMT_TABLE)
        displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        // Check if the patient is valid or not
        if (patient[i].patientID != 0)
        {
            // Display information about the patient
            displayPatientData(&patient[i], fmt);
            // Set the error flag to 0 because we found at least one patient
            error = 0;
        }
    }
    // ERROR message if no valid patients found
    if (error)
        printf("*** No records found ***\n\n");
    else
        putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    // Variable for user choice 
    int choice;
    // Loop for Search Option menu untill user chooses previous menu
    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");

        // Input User choice within the availbe options 
        choice = inputIntRange(0, 2);
        putchar('\n');

        if (choice == 1)
        {
            // Search patients by patient number
            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            // calling suspend() to wait for user input
            suspend();
        }
        else if (choice == 2)
        {
            // Search patients by patient phone number
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();
        }
    } while (choice);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    // iteration variable and flag variable for error checking
    int i, error = 1;
    // Loop for finding an empty slot in the patient data structure
    for (i = 0; error && i < max; i++)
    {
        //Check if the current patient slot is empty
        if (patient[i].patientID == 0)
        {
            // Assign a new patient ID using nextPatientNumber function
            patient[i].patientID = nextPatientNumber(patient, max);
            /* Calling inputPatient function to input details
                for the new patient  */
            inputPatient(&patient[i]);
            printf("*** New patient record added ***\n\n");
            error = 0;
        }

    }
    // ERROR message if no empty slots found
    if (error)
        printf("ERROR: Patient listing is FULL!\n\n");
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int pID, index;

    /** Prompt the user to enter the patient number
        and validating it using inputIntPositive() */
    printf("Enter the patient number: ");
    pID = inputIntPositive();
    putchar('\n');

    /* Find the index of the patient in the array based on the
       entered patient number.
       if index found showing error message */
    if ((index = findPatientIndexByPatientNum(pID, patient, max)) == -1)
        printf("ERROR: Patient record not found!\n");

    else
        menuPatientEdit(&patient[index]);
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int pID, index;
    char choice;

    /** Prompt the user to enter the patient number to be removed
        and validating it using inputIntPositive() */
    printf("Enter the patient number: ");
    pID = inputIntPositive();
    putchar('\n');

    // Finding the index of the patient with the given patient number
    if ((index = findPatientIndexByPatientNum(pID, patient, max)) == -1)
        printf("ERROR: Patient record not found!\n");

    else
    {
        // Displaying the patient data of the found patient
        displayPatientData(&patient[index], FMT_FORM);

        // Confirming if the user wants to remove the patient record
        printf("\nAre you sure you want to remove "
            "this patient record? (y/n): ");
        choice = inputCharOption("yn");

        if (choice == 'y')
        {
            // Set the patient number to 0, indicating an empty record slot
            patient[index].patientID = 0;
            // Clear the name and phone information to remove the patient data
            strcpy(patient[index].patientName, "");
            strcpy(patient[index].patientPhone.phoneDescription, "");
            strcpy(patient[index].patientPhone.phoneNumber, "");
            printf("Patient record has been removed!\n");
        }
        else
            printf("Operation aborted.\n");
    }
    putchar('\n');
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, j;

    // Display the table header with the date column
    displayScheduleTableHeader(&data->appointments->date, 1);

    // Sort appointments by date and time
    sortAppointmentsByDate(data);

    // Main Loop to display sheduled appoitments
    for (i = 0; i < data->maxAppointments; i++) 
    {
        // Check if the appointment is not empty
        if (isNotEmpty(&data->appointments[i])) 
        {
            // Sub Loop forr displaying sheduled data
            for (j = 0; j < data->maxPatient; j++) 
            {
                // Display the schedule data for the patient and appointment
                if (data->patients[j].patientID == data->appointments[i].patientID)
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }
        }
    }

    putchar('\n');
}



// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i, j;
    struct Date dateInput = { 0 };
    dateInput = dateValidation();
    putchar('\n');

    // Display the table header with the input date
    displayScheduleTableHeader(&dateInput, 0);

    sortAppointmentsByDate(data);

    // Main Loop for displaying sheduled data
    for (i = 0; i < data->maxAppointments; i++) 
    {
        if (isNotEmpty(&data->appointments[i])) 
        {
            // checking if the appoitment date matches input date
            if ((dateInput.year == data->appointments[i].date.year) && 
                (dateInput.month == data->appointments[i].date.month)
                && (dateInput.day == data->appointments[i].date.day)) 
            {
                // Sub Loop for displaying sheduled data
                for (j = 0; j < data->maxPatient; j++) 
                {
                    // Display the schedule data for the patient and appointment
                    if (data->patients[j].patientID == data->appointments[i].patientID) 
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                }
            }
        }
    }
    putchar('\n');
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointment, int maxAppointments,
    struct Patient* patients, int maxPatients)
{
    int i, error = 0;
    struct Appointment newAppoints = { 0 };

    printf("Patient Number: ");
    newAppoints.patientID = inputIntPositive();

    // Loop until a valid appointment time is selected
    while (!error) {
        newAppoints.date = dateValidation();
        newAppoints.time = timeValidation();

        int counter = 0, match = 0;
        for (i = 0; i < maxAppointments; i++) 
        {
            if (isNotEmpty(&appointment[i])) 
            {
                counter++;

                // Checking if the selected appointment time is already taken
                if (newAppoints.date.year == appointment[i].date.year 
                    && newAppoints.date.month == appointment[i].date.month
                    && newAppoints.date.day == appointment[i].date.day 
                    && newAppoints.time.hour == appointment[i].time.hour
                    && newAppoints.time.min == appointment[i].time.min) 
                {
                    match = 1;
                }
            }
        }
        putchar('\n');

        // ERROR message for unavailable appoitment time
        if (match)
            printf("ERROR: Appointment timeslot is not available!\n\n");

        // Add the new appointment to the array
        else 
        {
            appointment[counter].patientID = newAppoints.patientID;
            appointment[counter].date = newAppoints.date;
            appointment[counter].time = newAppoints.time;

            printf("*** Appointment scheduled! ***\n\n");
            error = 1;
        }
    }
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appoitment,
    int maxAppointments, struct Patient* patients, int maxPatients)
{
    int pID, index = -1, dateIndex = -1;
    char ch = '\0';
    struct Date date = { 0 };

    printf("Patient Number: ");
    pID = inputIntPositive();
    index = findPatientIndexByPatientNum(pID, patients, maxPatients);

    // Checking if the patient record exists
    if (index == -1)
        printf("ERROR: Patient record not found!\n\n");

    else 
    {
        date = dateValidation();
        // Find the appointment index by patient number and date
        dateIndex = findIndexByDate(pID, date, appoitment, maxAppointments);
        putchar('\n');

        // Display patient data for confirmation
        displayPatientData(&patients[index], FMT_FORM);

        printf("Are you sure you want to remove this appointment (y,n): ");
        ch = inputCharOption("yn");
        putchar('\n');

        if (ch == 'y') 
        {
            // Remove the appointment by setting patientID to 0
            appoitment[dateIndex].patientID = 0;
            printf("Appointment record has been removed!\n\n");
        }

        else 
            printf("Operation aborted.\n\n");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int pID, found;

    /* Prompt user to input patient number for search
       and validating it using inputIntPositive() */
    printf("Search by patient number: ");
    pID = inputIntPositive();
    putchar('\n');

    // Checking if patient number exists
    if ((found = findPatientIndexByPatientNum(pID, patient, max)) == -1)
        printf("*** No records found ***\n");

    else
        // if patient number is found, display patient data using specified format
        displayPatientData(&patient[found], FMT_FORM);
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    // iteration variable and flag variable for error checking
    int i, error = 1;
    // character array to store the phone number
    char phoneNumber[PHONE_LEN + 1];

    /*  Prompt user to input patient phone number
       and validating it using inputCString() */
    printf("Search by phone number: ");
    inputCString(phoneNumber, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    // Display header for patient data table
    displayPatientTableHeader();

    /* Loop for comparing the user-input phone number with the
        phone number of the current patient  */
    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].patientPhone.phoneNumber, phoneNumber) == 0)
        {
            // If a match is found, display the patient's data in table format
            displayPatientData(&patient[i], FMT_TABLE);
            error = 0;
        }
    }
    // ERROR message if no record were found
    if (error)
        printf("\n*** No records found ***\n");
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    // Initialize the highest ID with the first patient's ID
    int highestID = patient[0].patientID;

    for (i = 1; i < max; i++)
    {
        if (patient[i].patientID > highestID)
            // Update the highest ID if a higher one is found
            highestID = patient[i].patientID;
    }

    // Return the next available patient ID by adding 1 to the highest ID
    return highestID + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i;

    for (i = 0; i < max; i++)
    {
        // Compare the patient ID with the given patient number
        if (patient[i].patientID == patientNumber)
            return i;   // Return the index if a matching patient is found
    }
    // If anything is not found, -1 is returned
    return -1;
}


/////////////////////////////////////
// HELPER FUNCTIONS
/////////////////////////////////////

// Find the appointment array index by patient number and the date
int findIndexByDate(int patientID, struct Date date,
    const struct Appointment appoints[], int maxAppoints)
{
    // iteration value and setting variable index to -1
    int i, index = -1;
    // Loop for finding index by date
    for (i = 0; index == -1 && i < maxAppoints; i++) 
    {   // Comparing patient ID and date
        if ((date.year == appoints[i].date.year) 
            && (date.month == appoints[i].date.month) 
            && (date.day == appoints[i].date.day)) 
        {
            if (appoints[i].patientID == patientID)
                index = i;
        }
    }
    // returning the index 
    return index;
}

// Check if there still has data to read; if data is not empty return 1, otherwise return 0
int isNotEmpty(const struct Appointment* appointment)
{
    int result = 0;
    // validating patientID
    if (appointment->patientID != 0)
        result = 1;

    return result;
}

// Check the opening and closing hour and time interval
struct Time timeValidation(void)
{
    /* variables for hours and minutes
       variable for result */
    int hour, min, result = 1;
    while (result) 
    {
        // Prompt hour and minute input from the user
        printf("Hour (0-23)  : ");
        hour = inputIntRange(0, 23);

        printf("Minute (0-59): ");
        min = inputIntRange(0, 59);

        // Validating time 
        if (hour >= TIME_START && hour < TIME_END && min % TIME_INTERVAL == 0)
            result = 0;

        else if (hour == TIME_END && min == 0)
            result = 0;

        else
            printf("ERROR: Time must be between %02d:00 and %02d:00 "
                "in %d minute intervals.\n\n", TIME_START, TIME_END, TIME_INTERVAL);
    }
    struct Time time = { hour, min };
    // Return the validated time
    return time;
}

// Check the range of year, month, day is correct
struct Date dateValidation(void) {
    int year, month, day;

    // Prompting year, month, and day input from the user
    printf("Year        : ");
    year = inputIntRange(2024, 2027);

    printf("Month (1-12): ");
    month = inputIntRange(1, 12);

    // Validating day based on the month and leap year
    if (month == 2) 
    {
        if (year % 4 == 0) 
        {
            printf("Day (1-29)  : ");
            day = inputIntRange(1, 29);
        }
        else 
        {
            printf("Day (1-28)  : ");
            day = inputIntRange(1, 28);
        }
    }
    else if (month % 2 == 1 || month == 8) 
    {
        printf("Day (1-31)  : ");
        day = inputIntRange(1, 31);
    }
    else if (month % 2 == 0) 
    {
        printf("Day (1-30)  : ");
        day = inputIntRange(1, 30);
    }

    struct Date dates = { year, month, day };
    // Return validated dat
    return dates;
}

// Sort appointments data based on the date
void sortAppointmentsByDate(struct ClinicData* data)
{
    int i, j;
    struct Appointment temp;

    // Iterate through the list of appointments using Bubble Sort algorithm
    // Compare adjacent appointments and swap if they are out of order
    for (i = data->maxAppointments - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            // Extract date and time information for the current and next appointments
            struct Date date1 = data->appointments[j].date;
            struct Date date2 = data->appointments[j + 1].date;
            struct Time time1 = data->appointments[j].time;
            struct Time time2 = data->appointments[j + 1].time;

            // Compare dates and times to determine if a swap is needed
            if (date1.year > date2.year ||
                (date1.year == date2.year && date1.month > date2.month) ||
                (date1.year == date2.year && date1.month == date2.month && date1.day > date2.day) ||
                (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && time1.hour > time2.hour) ||
                (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && time1.hour == time2.hour && time1.min > time2.min)) {

                // Swap the appointments if they are out of order
                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }
        }
        // Move the last appointment of the inner loop to its correct position
        // This is a step of the Bubble Sort algorithm
        data->appointments[i] = data->appointments[j];
    }
}




//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    // Displaying form to take input
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientID);
    printf("Name  : ");

    // Prompt and input the patient's name
    inputCString(patient->patientName, 1, NAME_LEN);
    putchar('\n');

    // Call a function to input phone data for the patient
    inputPhoneData(&patient->patientPhone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int choice;
    // Display header for phone information
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n2. Home\n3. Work\n4. TBD\nSelection: ");

    // Prompt user for contact preference
    choice = inputIntRange(1, 4);

    // Updating phone description according to user choice
    switch (choice)
    {
    case 1:
        strcpy(phone->phoneDescription, "CELL");
        break;

    case 2:
        strcpy(phone->phoneDescription, "HOME");
        break;

    case 3:
        strcpy(phone->phoneDescription, "WORK");
        break;

    case 4:
        strcpy(phone->phoneDescription, "TBD");
        strcpy(phone->phoneNumber, "");
        break;
    }

    if (choice == 1 || choice == 2 || choice == 3)
    {
        putchar('\n');
        printf("Contact: %s\nNumber : ", phone->phoneDescription);
        // Prompt user for Phone number 
        inputCString(phone->phoneNumber, PHONE_LEN, PHONE_LEN);
    }

    putchar('\n');
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(char* fileName, struct Patient* ptr, int maxRecord)
{
    // Open the file for reading
    FILE* fp = fopen(fileName, "r");
    // character buffer to store each line read from the file
    char buffer[80];        
    // variable to keep track of number of records imported
    int counter;            
    // char variable to tokenize the data in each line
    char* nextToken;        

    // Check if the file was successfully opened
    if (fp == NULL)
    {
        printf("READING ERROR...\n");
        return -1;
    }
    counter = 0;
    
    // Read lines from the file until end of file (EOF) or maximum records reached
    while (fgets(buffer, 80, fp) != NULL && counter < maxRecord)
    {
        buffer[strlen(buffer) - 1] = '\0';
        nextToken = strtok(buffer, "|");
        ptr[counter].patientID = atoi(nextToken);
        nextToken = strtok(NULL, "|");
        strcpy(ptr[counter].patientName, nextToken);
        nextToken = strtok(NULL, "|");
        strcpy(ptr[counter].patientPhone.phoneDescription, nextToken);
        if (strcmp(ptr[counter].patientPhone.phoneDescription, "TBD") == 0)
            ptr[counter].patientPhone.phoneNumber[0] = '\0';
        else
        {
            nextToken = strtok(NULL, "|");
            strcpy(ptr[counter].patientPhone.phoneNumber, nextToken);
        }
        counter++;
    }
    fclose(fp);
    return counter;

}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(char* fileName, struct Appointment* ptr, int maxRecord)
{
    FILE* fp = fopen(fileName, "r");
    int counter;

    if (fp == NULL)
    {
        printf("READING ERROR...\n");
        return -1;
    }
    counter = 0;

    while (fscanf(fp, "%d,%d,%d,%d,%d,%d",
        &ptr[counter].patientID, &ptr[counter].date.year,
        &ptr[counter].date.month, &ptr[counter].date.day,
        &ptr[counter].time.hour, &ptr[counter].time.min) == 6 && counter < maxRecord)
        counter++;
    fclose(fp);
    return counter;
}



















Veterinary Clinic System
======================== =
1) PATIENT     Management
2) APPOINTMENT Management
------------------------ -
0) Exit System
------------------------ -
Selection: 1

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 3

ERROR : Patient listing is FULL!

<ENTER> to continue...

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 1

Pat.# Name            Phone#
---- - -------------- - --------------------
01024 Shaggy Yanson(304)800 - 5191 (CELL)
01032 Pugsley Yanson(304)800 - 5191 (CELL)
01040 Beans Maulin(364)915 - 5831 (HOME)
01048 Banjo Codi(___)___ - ____(TBD)
01056 Lettuce Peas(793)434 - 6809 (WORK)
01064 Bullet Lemme(___)___ - ____(TBD)
01072 Nugget Smee(388)689 - 3085 (WORK)
01080 Bessie Lidgely(___)___ - ____(TBD)
01088 Potato Yards(583)678 - 8577 (HOME)
01096 Alfie Burnhard(410)371 - 3391 (CELL)
01104 Pickles Green(443)554 - 6362 (WORK)
01112 Archie Ashness(692)256 - 5724 (HOME)
01120 Wyatt Ashness(692)256 - 5724 (HOME)
01128 Bug Tevlin(___)___ - ____(TBD)
01136 Noodles Ickov(646)669 - 1227 (HOME)
01142 Chicken Smee(388)689 - 3085 (WORK)
01150 Spikey Yanson(304)800 - 5191 (CELL)
01158 Carrots Maulin(258)722 - 9393 (CELL)
01166 Insect Tevlin(___)___ - ____(TBD)
01174 Archie Mollen(374)186 - 3267 (HOME)

< ENTER > to continue...

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 5

Enter the patient number : 1398

ERROR : Patient record not found!

<ENTER> to continue...

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 5

Enter the patient number : 1064

Name : Bullet Lemme
Number : 01064
Phone : (___)___ - ____(TBD)

Are you sure you want to remove this patient record ? (y / n) : yes
ERROR : Character must be one of[yn] : y
Patient record has been removed!

<ENTER> to continue...

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 3

Patient Data Input
------------------
Number : 01175
Name : Crusty Critter Cobbs
ERROR : String length must be no more than 15 chars : Crusty Critter

Phone Information
---------------- -
How will the patient like to be contacted ?
1. Cell
2. Home
3. Work
4. TBD
Selection : 1

Contact : CELL
Number : 22277766666
ERROR : String length must be exactly 10 chars : 222777666
ERROR : String length must be exactly 10 chars : 2227776666

* **New patient record added * **

<ENTER> to continue...

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 4

Enter the patient number : 1080

Edit Patient(01080)
======================== =
1) NAME : Bessie Lidgely
2) PHONE: (___)___ - ____
------------------------ -
0) Previous menu
------------------------ -
Selection: 1

Name : Sandy Beach

Patient record updated!

Edit Patient(01080)
======================== =
1) NAME : Sandy Beach
2) PHONE: (___)___ - ____
------------------------ -
0) Previous menu
------------------------ -
Selection: 2

Phone Information
---------------- -
How will the patient like to be contacted ?
1. Cell
2. Home
3. Work
4. TBD
Selection : 3

Contact : WORK
Number : 9993334444

Patient record updated!

Edit Patient(01080)
======================== =
1) NAME : Sandy Beach
2) PHONE: (999)333 - 4444
------------------------ -
0) Previous menu
------------------------ -
Selection: 0

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 1

Pat.# Name            Phone#
---- - -------------- - --------------------
01024 Shaggy Yanson(304)800 - 5191 (CELL)
01032 Pugsley Yanson(304)800 - 5191 (CELL)
01040 Beans Maulin(364)915 - 5831 (HOME)
01048 Banjo Codi(___)___ - ____(TBD)
01056 Lettuce Peas(793)434 - 6809 (WORK)
01175 Crusty Critter(222)777 - 6666 (CELL)
01072 Nugget Smee(388)689 - 3085 (WORK)
01080 Sandy Beach(999)333 - 4444 (WORK)
01088 Potato Yards(583)678 - 8577 (HOME)
01096 Alfie Burnhard(410)371 - 3391 (CELL)
01104 Pickles Green(443)554 - 6362 (WORK)
01112 Archie Ashness(692)256 - 5724 (HOME)
01120 Wyatt Ashness(692)256 - 5724 (HOME)
01128 Bug Tevlin(___)___ - ____(TBD)
01136 Noodles Ickov(646)669 - 1227 (HOME)
01142 Chicken Smee(388)689 - 3085 (WORK)
01150 Spikey Yanson(304)800 - 5191 (CELL)
01158 Carrots Maulin(258)722 - 9393 (CELL)
01166 Insect Tevlin(___)___ - ____(TBD)
01174 Archie Mollen(374)186 - 3267 (HOME)

< ENTER > to continue...

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 2

Search Options
==========================
1) By patient number
2) By phone number
..........................
0) Previous menu
..........................
Selection: 1

Search by patient number : 1182

* **No records found * **

<ENTER> to continue...

Search Options
==========================
1) By patient number
2) By phone number
..........................
0) Previous menu
..........................
Selection: 1

Search by patient number : 1088

Name : Potato Yards
Number : 01088
Phone : (583)678 - 8577 (HOME)

< ENTER > to continue...

Search Options
==========================
1) By patient number
2) By phone number
..........................
0) Previous menu
..........................
Selection: 2

Search by phone number : 3048005191

Pat.# Name            Phone#
---- - -------------- - --------------------
01024 Shaggy Yanson(304)800 - 5191 (CELL)
01032 Pugsley Yanson(304)800 - 5191 (CELL)
01150 Spikey Yanson(304)800 - 5191 (CELL)

< ENTER > to continue...

Search Options
==========================
1) By patient number
2) By phone number
..........................
0) Previous menu
..........................
Selection: 2

Search by phone number : 4435546362

Pat.# Name            Phone#
---- - -------------- - --------------------
01104 Pickles Green(443)554 - 6362 (WORK)

< ENTER > to continue...

Search Options
==========================
1) By patient number
2) By phone number
..........................
0) Previous menu
..........................
Selection: 0

Patient Management
======================== =
1) VIEW   Patient Data
2) SEARCH Patients
3) ADD    Patient
4) EDIT   Patient
5) REMOVE Patient
------------------------ -
0) Previous menu
------------------------ -
Selection: 0

Veterinary Clinic System
======================== =
1) PATIENT     Management
2) APPOINTMENT Management
------------------------ -
0) Exit System
------------------------ -
Selection: 2

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 1

Clinic Appointments for the Date : <ALL>

Date       Time  Pat.# Name            Phone#
---------- ---- - ---- - -------------- - --------------------
2024 - 02 - 29 10:00 01024 Shaggy Yanson(304)800 - 5191 (CELL)
2024 - 02 - 29 10 : 30 01080 Sandy Beach(999)333 - 4444 (WORK)
2024 - 02 - 29 11:00 01120 Wyatt Ashness(692)256 - 5724 (HOME)
2024 - 02 - 29 11 : 30 01088 Potato Yards(583)678 - 8577 (HOME)
2024 - 02 - 29 12:00 01112 Archie Ashness(692)256 - 5724 (HOME)
2024 - 02 - 29 12 : 30 01128 Bug Tevlin(___)___ - ____(TBD)
2024 - 02 - 29 13:00 01040 Beans Maulin(364)915 - 5831 (HOME)
2024 - 02 - 29 13 : 30 01032 Pugsley Yanson(304)800 - 5191 (CELL)
2024 - 02 - 29 14 : 00 01104 Pickles Green(443)554 - 6362 (WORK)
2025 - 02 - 28 11 : 30 01056 Lettuce Peas(793)434 - 6809 (WORK)
2026 - 06 - 09 14:00 01104 Pickles Green(443)554 - 6362 (WORK)
2026 - 06 - 20 10 : 30 01048 Banjo Codi(___)___ - ____(TBD)
2027 - 03 - 10 11:00 01112 Archie Ashness(692)256 - 5724 (HOME)
2027 - 03 - 12 10 : 30 01024 Shaggy Yanson(304)800 - 5191 (CELL)
2027 - 03 - 12 13 : 00 01112 Archie Ashness(692)256 - 5724 (HOME)

< ENTER > to continue...

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 2

Year : 2025
Month(1 - 12) : 2
Day(1 - 28) : 29
ERROR!Value must be between 1 and 28 inclusive : 28

Clinic Appointments for the Date : 2025 - 02 - 28

Time  Pat.# Name            Phone#
---- - ---- - -------------- - --------------------
11:30 01056 Lettuce Peas(793)434 - 6809 (WORK)

< ENTER > to continue...

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 2

Year : 2024
Month(1 - 12) : 2
Day(1 - 29) : 29

Clinic Appointments for the Date : 2024 - 02 - 29

Time  Pat.# Name            Phone#
---- - ---- - -------------- - --------------------
10:00 01024 Shaggy Yanson(304)800 - 5191 (CELL)
10 : 30 01080 Sandy Beach(999)333 - 4444 (WORK)
11:00 01120 Wyatt Ashness(692)256 - 5724 (HOME)
11 : 30 01088 Potato Yards(583)678 - 8577 (HOME)
12:00 01112 Archie Ashness(692)256 - 5724 (HOME)
12 : 30 01128 Bug Tevlin(___)___ - ____(TBD)
13:00 01040 Beans Maulin(364)915 - 5831 (HOME)
13 : 30 01032 Pugsley Yanson(304)800 - 5191 (CELL)
14 : 00 01104 Pickles Green(443)554 - 6362 (WORK)

< ENTER > to continue...

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 3

Patient Number : 1158
Year : 2027
Month(1 - 12) : 3
Day(1 - 31) : 10
Hour(0 - 23) : 11
Minute(0 - 59) : 0

ERROR : Appointment timeslot is not available!

Year : 2027
Month(1 - 12) : 3
Day(1 - 31) : 10
Hour(0 - 23) : 18
Minute(0 - 59) : 0
ERROR : Time must be between 10 : 00 and 14 : 00 in 30 minute intervals.

Hour(0 - 23) : 9
Minute(0 - 59) : 0
ERROR : Time must be between 10 : 00 and 14 : 00 in 30 minute intervals.

Hour(0 - 23) : 14
Minute(0 - 59) : 30
ERROR : Time must be between 10 : 00 and 14 : 00 in 30 minute intervals.

Hour(0 - 23) : 10
Minute(0 - 59) : 29
ERROR : Time must be between 10 : 00 and 14 : 00 in 30 minute intervals.

Hour(0 - 23) : 14
Minute(0 - 59) : 0

* **Appointment scheduled!***

<ENTER> to continue...

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 4

Patient Number : 5484
ERROR : Patient record not found!

<ENTER> to continue...

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 4

Patient Number : 1112
Year : 2024
Month(1 - 12) : 2
Day(1 - 29) : 29

Name : Archie Ashness
Number : 01112
Phone : (692)256 - 5724 (HOME)
Are you sure you want to remove this appointment(y, n) : y

Appointment record has been removed!

<ENTER> to continue...

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 1

Clinic Appointments for the Date : <ALL>

Date       Time  Pat.# Name            Phone#
---------- ---- - ---- - -------------- - --------------------
2024 - 02 - 29 10:00 01024 Shaggy Yanson(304)800 - 5191 (CELL)
2024 - 02 - 29 10 : 30 01080 Sandy Beach(999)333 - 4444 (WORK)
2024 - 02 - 29 11:00 01120 Wyatt Ashness(692)256 - 5724 (HOME)
2024 - 02 - 29 11 : 30 01088 Potato Yards(583)678 - 8577 (HOME)
2024 - 02 - 29 12:30 01128 Bug Tevlin(___)___ - ____(TBD)
2024 - 02 - 29 13:00 01040 Beans Maulin(364)915 - 5831 (HOME)
2024 - 02 - 29 13 : 30 01032 Pugsley Yanson(304)800 - 5191 (CELL)
2024 - 02 - 29 14 : 00 01104 Pickles Green(443)554 - 6362 (WORK)
2025 - 02 - 28 11 : 30 01056 Lettuce Peas(793)434 - 6809 (WORK)
2026 - 06 - 09 14:00 01104 Pickles Green(443)554 - 6362 (WORK)
2026 - 06 - 20 10 : 30 01048 Banjo Codi(___)___ - ____(TBD)
2027 - 03 - 10 11:00 01112 Archie Ashness(692)256 - 5724 (HOME)
2027 - 03 - 10 14 : 00 01158 Carrots Maulin(258)722 - 9393 (CELL)
2027 - 03 - 12 10:30 01024 Shaggy Yanson(304)800 - 5191 (CELL)
2027 - 03 - 12 13 : 00 01112 Archie Ashness(692)256 - 5724 (HOME)

< ENTER > to continue...

Appointment Management
==============================
1) VIEW   ALL Appointments
2) VIEW   Appointments by DATE
3) ADD    Appointment
4) REMOVE Appointment
------------------------------
0) Previous menu
------------------------------
Selection: 0

Veterinary Clinic System
======================== =
1) PATIENT     Management
2) APPOINTMENT Management
------------------------ -
0) Exit System
------------------------ -
Selection: 0

Are you sure you want to exit ? (y | n) : y

Exiting system... Goodbye.