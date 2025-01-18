#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Constants
#define MAX_GENDER_LETTERS 8
#define MAX_FIRST_NAME_LETTERS 30
#define MAX_LAST_NAME_LETTERS 30
#define MAX_BIRTH_DATE_LETTERS 11
#define MAX_EMAIL_LETTERS 50
#define MAX_PASSWORD_LETTERS 12

/* 
FEATURES
Big and nice title
Time and date in upper right corner

ENTER MENU
1. Login (username and password) 
2. Create new account

MAIN MENU
1. Add new project
    -> 1. Project name, description,TODO list, start date, add persons, end date, set priority
2. All projects list
    -> Projects done, projects to be done ... 
3. Edit project
    -> add new task to project, change existing tasks, mark as completed etc, delete project
4. Exit
*/

// Structures
typedef struct User {
    char gender[MAX_GENDER_LETTERS];
    char firstName[MAX_FIRST_NAME_LETTERS];
    char lastName[MAX_LAST_NAME_LETTERS];
    char birthDate[MAX_BIRTH_DATE_LETTERS];
    char email[MAX_EMAIL_LETTERS];
    char password[MAX_PASSWORD_LETTERS];
} User;

// Function prototypes
void application();
void showTitle();
void getTimeAndDate(char *date);
int showLoginMenu();
bool checkIfOnlyLetters(char *text);
bool checkIfBirthDateValid(char *text);
struct User showRegistrationForm();
struct User createNewUser(const char *gender, const char *first_name, const char *last_name, const char *birth_date, const char *email, const char *password);

int main(void) {
    application(); // Start application
    return 0;
}

void application() {
    User newUser;
    showTitle();
    int loginMenuUserInput = showLoginMenu();
    if(loginMenuUserInput == 1) {
        // TODO: write function to enter application
    } else if (loginMenuUserInput == 2) {
        newUser = showRegistrationForm();
    } else if (loginMenuUserInput == 3) {
        system("cls"); // clear terminal screen
        exit(1);
    }
}
// Print nice and styled application title in terminal with date 
void showTitle() {
    char date[25];
    getTimeAndDate(date);
    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PROJECT MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 %s \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n", date);
    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\n");
}

// Format date strign and assign it to date array given in argument
void getTimeAndDate(char *date) {
    time_t result;
    // Array size must be big enough to contain number of chars + terminating operator (\0)
    char dayInWeekArr[4];
    char monthArr[4];
    char dayInMonthArr[4];
    char yearArr[6];

    result = time(NULL);
    int dayInWeek = localtime(&result)->tm_wday; // Day of week (0-6; Sunday 
    int month = localtime(&result)->tm_mon; // Month (0-11; January )
    int dayInMonth = localtime(&result)->tm_mday; // Day of month (1
    int year = localtime(&result)->tm_year + 1900; // Year (current year minus 1900)

    // Fill dayInWeekArr with string depending on integer value
    switch(dayInWeek) {
        case 0:
            sprintf(dayInWeekArr, "Sun");
            break;
        case 1:
            sprintf(dayInWeekArr, "Mon");
            break;
        case 2:
            sprintf(dayInWeekArr, "Tue");
            break;
        case 3:
            sprintf(dayInWeekArr, "Wed");
            break;
        case 4:
            sprintf(dayInWeekArr, "Thu");
            break;
        case 5:
            sprintf(dayInWeekArr, "Fri");
            break;
        case 6:
            sprintf(dayInWeekArr, "Sat");
            break;
        default:
            sprintf(dayInWeekArr, "###");
            break;
    }

    // Fill monthArr with string depending on integer value
    switch(month) {
        case 0:
            sprintf(monthArr, "Jan");
            break;
        case 1:
            sprintf(monthArr, "Feb");
            break;
        case 2:
            sprintf(monthArr, "Mar");
            break;
        case 3:
            sprintf(monthArr, "Apr");
            break;
        case 4:
            sprintf(monthArr, "May");
            break;
        case 5:
            sprintf(monthArr, "Jun");
            break;
        case 6:
            sprintf(monthArr, "Jul");
            break;
        case 7:
            sprintf(monthArr, "Aug");
            break;
        case 8:
            sprintf(monthArr, "Sep");
            break;
        case 9:
            sprintf(monthArr, "Oct");
            break;
        case 10:
            sprintf(monthArr, "Nov");
            break;
        case 11:
            sprintf(monthArr, "Dec");
            break;
        default:
            sprintf(monthArr, "###");
            break;
    }

    //char array represented as string
    sprintf(dayInMonthArr, "%d", dayInMonth);
    sprintf(yearArr, "%d", year);

    // Form string like Mon Dec 19 2022
    strcpy(date, dayInWeekArr);
    strcat(date, " ");
    strcat(date, monthArr);
    strcat(date, " ");
    strcat(date, dayInMonthArr);
    strcat(date, " ");
    strcat(date, yearArr);
}

// Function asks user to choose between two options and returns user choice
int showLoginMenu() {
    int choice;
    printf("\t\t\tChoose option to enter application:\n");
    printf("\t\t\t\t\xB3\xB2\xB2\xB2 1. Login\n");
    printf("\t\t\t\t\xB3\xB2\xB2\xB2 2. Register\n");
    printf("\t\t\t\t\xB3\xB2\xB2\xB2 3. Exit application\n");
    do {
        printf("\tEnter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice != 1 && choice != 2 && choice != 3) {
            printf("Wrong input! Input value must be 1, 2 or 3. Try again.\n");
        }
    } while (choice != 1 && choice != 2 && choice != 3);

    return choice;
}

struct User showRegistrationForm() {
#define maxPasswordLength = 12, minPasswordLength = 8;
    User newUser;
    char gender[MAX_GENDER_LETTERS], firstName[MAX_FIRST_NAME_LETTERS], lastName[MAX_LAST_NAME_LETTERS], birthDate[MAX_BIRTH_DATE_LETTERS], email[MAX_EMAIL_LETTERS], password[MAX_PASSWORD_LETTERS], repeatedPassword[MAX_PASSWORD_LETTERS];
    bool firstNameOK = false, lastNameOK = false, birthDateOK = false, emailOK = false, passwordOK = false, repeatedPasswordOK = false;
    int genderChoice;

    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Fill in form to create new account \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\t\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3\n");
    printf("\n");

    // Ask for gender
    do {
        printf("\tChoose your gender:\n");
        printf("\t1. Male\n");
        printf("\t2. Female\n");
        printf("\tEnter value here (1 or 2): ");
        scanf("%d", &genderChoice);
        printf("\n");

        if(genderChoice != 1 && genderChoice !=2) {
            printf("\tWrong input! Input value must be 1 or 2. Try again.\n");
        }
    } while (genderChoice != 1 && genderChoice != 2);

    // Store gender to array
    if(genderChoice == 1) {
        sprintf(gender, "male");
    } else if(genderChoice == 2) {
        sprintf(gender, "female");
    }

    // Ask for first name
    printf("\tFirst name: ");
    scanf("%s", firstName);
    firstNameOK = checkIfOnlyLetters(firstName);
    printf("\n");

    // Ask for last name
    printf("\tLast name: ");
    scanf("%s", lastName);
    lastNameOK = checkIfOnlyLetters(lastName);
    printf("\n");

    // Ask for birth date
    printf("\tBirth date (in form dd.mm.yyyy): ");
    scanf("%s", birthDate);
    printf("\n");

    // Ask for email
    printf("\tE-mail: ");
    scanf("%s", email);
    printf("\n");

     // Ask for password
    printf("\tPassword: ");
    scanf("%s", password);
    printf("\n");

     // Ask for password
    printf("\tRepeat password: ");
    scanf("%s", repeatedPassword);
    printf("\n");


    // TODO: add function which checks if password is written correctly and matches repeated password

    newUser = createNewUser(gender, firstName, lastName, birthDate, email, password); // TODO: save newUser to file 

    return newUser; // TODO: return 1 if registration is succesfully done or 0 if user wants to go back to login menu
}

// Create and return User structure
struct User createNewUser(const char* gender ,const char* first_name, const char* last_name, const char* birth_date, const char* email, const char* password) {
    User u;
    strcpy(u.gender, gender);
    strcpy(u.firstName, first_name);
    strcpy(u.lastName, last_name);
    strcpy(u.birthDate, birth_date);
    strcpy(u.email, email);
    strcpy(u.password, password);
    return u;
}

// TODO: write function to check if first name is typed correctly (only letters) and does not exceed array size
// Loop through text characters and check if it contains only letters.
// Return true if text contains only letters. 
bool checkIfOnlyLetters(char *text) {
    for(int i = 0; i < strlen(text); i++) {
        if(isalpha(text[i])) {
            continue;
        } else {
            return false;
        }
        return true;
    }
}

// TODO: write function to check if birth date is typed correctly (numbers only and dots) and does not exceed array size
// Proper forme -> dd.mm.yyyy.
bool checkIfBirthDateValid(char *text) {
    int dd, mm, yyyy = 0;
    // dd -> from 1-31
    // mm -> from 1-12
    // yyyy -> from 1900 - (current year 2025)
    for(int i = 0; i < strlen(text); i++) {
        if(isdigit(text[i]) && i == 0 || i == 1) {
            // Form int value of entered day
            if(i==0) {
                dd += (int)text[i] * 10;
            } else if(i==1) {
                dd += (int)text[i];
                // Day can only be between 1-31 
                if(dd >= 1 && dd <= 31) {
                    continue;
                } else {
                    return false;
                }
            }
        } else if (text[i] == '.' && i == 2 || i == 5 || i == 10) {
            continue;
        } else if (isdigit(text[i]) && i == 6 || i == 7 || i == 8 || i == 9) {
            // Form int value of entered year
            if(i == 6) {
                yyyy += (int)text[i] * 1000;
            } else if(i == 7) {
                yyyy += (int)text[i] * 100; 
            } else if(i == 8) {
                yyyy += (int)text[i] * 10;
            } else if(i == 9) {
                yyyy += (int)text[i];
                // Year can only be between 1900-2025
                if(yyyy >= 1900 && yyyy <= 2025) {
                    continue;
                } else {
                    return false;
                }
            }
        } else if (isdigit(text[i]) && i == 3 || i == 4) {
            // TODO: Stopped here....
        }
    }
}

// TODO: write function to check if email does not exceed array size and that matches proper form

// TODO: write function to check if password does not exceed array size and that matches proper form (8-12 characters, 1 big letter, 1 special character)

// TODO: write function which checks if all test are passed for registration

// TODO: write function to save user in file
