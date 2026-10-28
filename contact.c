#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "populate.h"
#include "file.h"

/* Color codes used for displaying different messages */
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define WHITE "\033[1;37m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"

/* Function declarations */
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void printContacts(AddressBook *addressBook);
int chooseContact(AddressBook *addressBook);
int chooseContactByField(AddressBook *addressBook);

int validateName(AddressBook *addressBook, char name[], int index);
int validatePhone(AddressBook *addressBook, char phone[], int index);
int validateEmail(AddressBook *addressBook, char email[], int index);


/* Initialize the address book */
void initialize(AddressBook *addressBook)
{
    /* Load the previously saved contacts from the file */
    loadContactsFromFile(addressBook);

    /* If there are no contacts, add the sample contacts */
    if (addressBook->contactCount == 0)
    {
        populateAddressBook(addressBook);
    }
}

/* Validate the contact name */
int validateName(AddressBook *addressBook, char name[], int index)
{
    int i;
    int letterCount = 0;
    /* Check whether the entered name is empty */
    if(strlen(name) == 0)
    {
        printf(RED"Error: Name cannot be empty.\n"RESET);
        return 0;
    }

    /* Check each character in the name */
    for (i = 0;name[i] != '\0';i++)
    {
        if(isalpha((unsigned char)name[i]))
        {
            /* Count the number of letters in the name */
            letterCount++;
        }
        else if(name[i] != ' ')
        {
            /* Reject numbers and special characters */
            printf(RED"Error: Name must contain only alphabets and spaces.\n"RESET);
            return 0;
        }
    }
    /* Check whether the name has at least 3 letters */
    if(letterCount < 3)
    {
        printf(RED"Error: Name must contain at least 3 letters.\n"RESET);
        return 0;
    }
    /* Check whether the same name already exists */
    for (i = 0;i < addressBook->contactCount;i++)
    {
        /* Ignore the same contact while editing */
        if(i != index && strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf(RED"Error: This name already exists.\n"RESET);
            return 0;
        }
    }

    /* Return 1 if all name checks are successful */
    return 1;
}

/* Validate the contact phone number */
int validatePhone(AddressBook *addressBook, char phone[], int index)
{
    int i;
    /* Check whether the phone number has exactly 10 digits */
    if(strlen(phone) != 10)
    {
        printf(RED"Error: Phone number must contain exactly 10 digits.\n"RESET);
        return 0;
    }

    /* Check whether the phone number starts from 6 to 9 */
    if(phone[0] < '6' || phone[0] > '9')
    {
        printf(RED"Error: Phone number must start with 6 to 9.\n"RESET);
        return 0;
    }

    /* Check every character in the phone number */
    for(i = 0;phone[i] != '\0';i++)
    {
        if(!isdigit((unsigned char)phone[i]))
        {
            /* Reject letters and special characters */
            printf(RED"Error: Phone number must contain only digits.\n"RESET);
            return 0;
        }
    }

    /* Check whether the same phone number already exists */
    for(i = 0;i < addressBook->contactCount;i++)
    {
        /* Ignore the same contact while editing */
        if (i != index && strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf(RED"Error: This phone number already exists.\n"RESET);
            return 0;
        }
    }
    /* Return 1 if all phone checks are successful */
    return 1;
}

/* Validate the contact email */
int validateEmail(AddressBook *addressBook, char email[], int index)
{
    int i,atCount = 0,dotCount = 0,atPosition = -1,dotPosition = -1;
    /* Check whether the email is empty */
    if(strlen(email) == 0)
    {
        printf(RED "Error: Email cannot be empty.\n" RESET);
        return 0;
    }

    /* Check each character in the email */
    for(i = 0;email[i] != '\0';i++)
    {
        /* Allow only lowercase letters, digits, @ and dot */
        if(!islower((unsigned char)email[i]) &&!isdigit((unsigned char)email[i]) &&email[i] != '@' && email[i] != '.')
        {
            printf(RED"Error: Email can contain only lowercase letters, digits, @ and .\n"RESET);
            return 0;
        }

        /* Count @ symbols and store its position */
        if(email[i] == '@')
        {
            atCount++;
            atPosition = i;
        }

        /* Count dots and store the last dot position */
        if(email[i] == '.')
        {
            dotCount++;
            dotPosition = i;
        }
    }

    /* Check whether @ symbol is present */
    if(atCount == 0)
    {
        printf(RED"Error: Missing @ symbol in email.\n"RESET);
        return 0;
    }

    /* Check whether more than one @ is present */
    if(atCount > 1)
    {
        printf(RED"Error: Email must contain only one @ symbol.\n"RESET);
        return 0;
    }

    /* Check whether dot is present */
    if(dotCount == 0)
    {
        printf(RED"Error: Missing dot (.) in email.\n"RESET);
        return 0;
    }

    /* Check whether more than one dot is present */
    if(dotCount > 1)
    {
        printf(RED"Error: Email must contain only one dot (.).\n"RESET);
        return 0;
    }

    /* Check whether there is a character before @ */
    if(atPosition == 0)
    {
        printf(RED"Error: Email must contain characters before @.\n"RESET);
        return 0;
    }

    /* Check whether there is a character between @ and dot */
    if(dotPosition <= atPosition + 1)
    {
        printf(RED"Error: Email must contain at least one character between @ and dot.\n"RESET);
        return 0;
    }

    /* Check whether there is a character after dot */
    if(email[dotPosition + 1] == '\0')
    {
        printf(RED"Error: Email must contain characters after dot.\n"RESET);
        return 0;
    }

    /* Check whether the email ends with .com */
    if(strcmp(&email[dotPosition], ".com") != 0)
    {
        printf(RED"Error: Email domain must end with .com.\n"RESET);
        return 0;
    }

    /* Check whether the email already exists */
    for(i = 0;i < addressBook->contactCount;i++)
    {
        /* Ignore the same contact while editing */
        if (i != index && strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf(RED"Error: This email already exists.\n"RESET);
            return 0;
        }
    }

    /* Return 1 if all email checks are successful */
    return 1;
}


/* Create a new contact */
void createContact(AddressBook *addressBook)
{
    Contact contact;
    /* Check whether the address book is full */
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf(RED"\nError: Address book is full.\n"RESET);
        return;
    }
    printf(MAGENTA"\n╔══════════════════════════════════════╗\n"RESET);
    printf(MAGENTA"║          CREATE NEW CONTACT          ║\n"RESET);
    printf(MAGENTA"╚══════════════════════════════════════╝\n"RESET);

    /* Get and validate the name */
    while(1)
    {
        printf(YELLOW "Enter name: " RESET);

        /* Read the name from the user */
        scanf(" %[^\n]", contact.name);
        while(getchar() != '\n');

        /* Call name validation function */
        if(validateName(addressBook, contact.name, -1))
        {
            break;
        }
    }

    /* Get and validate the phone number */
    while(1)
    {
        printf(YELLOW "Enter phone number: " RESET);
        /* Read the phone number from the user */
        scanf(" %[^\n]", contact.phone);
        while(getchar() != '\n');

        /* Call phone validation function */
        if(validatePhone(addressBook, contact.phone, -1))
        {
            break;
        }
    }

    /* Get and validate the email */
    while(1)
    {
        printf(YELLOW "Enter email: " RESET);
        /* Read the email from the user */
        scanf(" %[^\n]", contact.email);
        while(getchar() != '\n');

        /* Call email validation function */
        if(validateEmail(addressBook, contact.email, -1))
        {
            break;
        }
    }

    /* Store the new contact in the next free position */
    addressBook->contacts[addressBook->contactCount] = contact;

    /* Increase the total number of contacts */
    addressBook->contactCount++;

    /* Save the updated contacts to the file */
    saveContactsToFile(addressBook);

    printf(GREEN"\nContact created successfully!\n"RESET);
}

/* Display all contacts */
void printContacts(AddressBook *addressBook)
{
    int i;
    printf(CYAN"\n----------------------------------------------------------------\n"RESET);
    printf(CYAN"|        No.   Name                 Phone        Email          |\n"RESET);
    printf(CYAN"----------------------------------------------------------------\n"RESET);

    /* Go through each contact and display it */
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("║ %-5d ║ %-20s ║ %-12s ║ %-28s ║\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    printf(CYAN"╚═══════╩══════════════════════╩══════════════╩══════════════════════════════╝\n"RESET);
}

/* Sort and display contacts */
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    int i;
    int j;
    Contact temp;

    /* Check whether there are any contacts */
    if(addressBook->contactCount == 0)
    {
        printf(RED"\nError: No contacts available.\n"RESET);
        return;
    }

    /* Compare contacts using bubble sort */
    for(i = 0;i < addressBook->contactCount - 1;i++)
    {
        for(j = 0;j < addressBook->contactCount - i - 1;j++)
        {
            int swap = 0;
            /* Sort contacts by name */
            if(sortCriteria == 1)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name) > 0)
                {
                    swap = 1;
                }
            }
            /* Sort contacts by phone */
            else if(sortCriteria == 2)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j + 1].phone) > 0)
                {
                    swap = 1;
                }
            }

            /* Sort contacts by email */
            else if(sortCriteria == 3)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j + 1].email) > 0)
                {
                    swap = 1;
                }
            }

            /* Swap contacts if they are in the wrong order */
            if(swap == 1)
            {
                /* Store the first contact temporarily */
                temp = addressBook->contacts[j];

                /* Move the second contact to the first position */
                addressBook->contacts[j] = addressBook->contacts[j + 1];

                /* Put the first contact in the second position */
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf(BLUE"\n╔══════════════════════════════════════╗\n"RESET);
    printf(BLUE"║            CONTACT LIST             ║\n"RESET);
    printf(BLUE"╚══════════════════════════════════════╝\n"RESET);

    /* Display the sorted contacts */
    printContacts(addressBook);
}


/* Select a contact */
int chooseContact(AddressBook *addressBook)
{
    int number;

    /* Check whether contacts are available */
    if (addressBook->contactCount == 0)
    {
        printf(RED"Error: No contacts available.\n"RESET);
        return -1;
    }

    /* Display contacts before selecting */
    printContacts(addressBook);

    printf(YELLOW"Enter contact number: "RESET);

    /* Read contact number */
    if(scanf("%d", &number) != 1)
    {
        while (getchar() != '\n');

        printf(RED"Error: Please enter a valid number.\n"RESET);
        return -1;
    }

    while(getchar() != '\n');

    /* Check whether the selected number is valid */
    if(number < 1 || number > addressBook->contactCount)
    {
        printf(RED"Error: Contact number does not exist.\n"RESET);
        return -1;
    }

    /* Convert contact number into array index */
    return number - 1;
}


/* Search and select a contact by name, phone or email */
int chooseContactByField(AddressBook *addressBook)
{
    char search[50];
    int choice,i,found = 0;
    int matches[MAX_CONTACTS];
    int matchCount = 0;
    int number;

    if(addressBook->contactCount == 0)
    {
        printf(RED"Error: No contacts available.\n"RESET);
        return -1;
    }

    printf(CYAN"\n1. Search by name\n"RESET);
    printf(CYAN"2. Search by phone\n"RESET);
    printf(CYAN"3. Search by email\n"RESET);
    printf(CYAN"4. Exit\n"RESET);
    printf(YELLOW"Enter your choice: "RESET);

    if(scanf("%d", &choice) != 1)
    {
        while(getchar() != '\n');
        printf(RED"Error: Please enter a valid number.\n"RESET);
        return -1;
    }
    while(getchar() != '\n');

    if(choice == 4)
    {
        return -1;
    }

    if(choice < 1 || choice > 3)
    {
        printf(RED"Error: Invalid search choice.\n"RESET);
        return -1;
    }

    printf(YELLOW"Enter search value: "RESET);
    scanf(" %[^\n]", search);
    while(getchar() != '\n');

    for(i = 0;i < addressBook->contactCount;i++)
    {
        int j;
        int match = 1;

        for(j = 0; search[j] != '\0'; j++)
        {
            char fieldChar;

            if(choice == 1)
                fieldChar = addressBook->contacts[i].name[j];
            else if(choice == 2)
                fieldChar = addressBook->contacts[i].phone[j];
            else
                fieldChar = addressBook->contacts[i].email[j];

            if(fieldChar == '\0')
            {
                match = 0;
                break;
            }

            if(tolower((unsigned char)fieldChar) !=
               tolower((unsigned char)search[j]))
            {
                match = 0;
                break;
            }
        }

        if(match == 1)
        {
            matches[matchCount] = i;
            matchCount++;
            found = 1;
        }
    }

    if(found == 0)
    {
        printf(RED"Error: Contact not found.\n"RESET);
        return -1;
    }

    printf(GREEN"\n╔══════════════════════════════════════╗\n"RESET);
    printf(GREEN"║          CONTACT FOUND               ║\n"RESET);
    printf(GREEN"╚══════════════════════════════════════╝\n"RESET);

    for(i = 0;i < matchCount;i++)
    {
        printf(YELLOW"\nContact %d\n"RESET,i + 1);
        printf("Name  : %s\n", addressBook->contacts[matches[i]].name);
        printf("Phone : %s\n", addressBook->contacts[matches[i]].phone);
        printf("Email : %s\n", addressBook->contacts[matches[i]].email);
    }

    printf(YELLOW"\nEnter contact number to select: "RESET);
    if(scanf("%d", &number) != 1)
    {
        while(getchar() != '\n');
        printf(RED"Error: Please enter a valid number.\n"RESET);
        return -1;
    }
    while(getchar() != '\n');

    if(number < 1 || number > matchCount)
    {
        printf(RED"Error: Contact number does not exist.\n"RESET);
        return -1;
    }

    return matches[number - 1];
}


/* Search for a contact */
void searchContact(AddressBook *addressBook)
{
    int index;

    /* Check whether contacts are available */
    if(addressBook->contactCount == 0)
    {
        printf(RED"\nError: No contacts available.\n"RESET);
        return;
    }

    printf(BLUE"\n╔══════════════════════════════════════╗\n"RESET);
    printf(BLUE"║           SEARCH CONTACT             ║\n"RESET);
    printf(BLUE"╚══════════════════════════════════════╝\n"RESET);

    /* Search and select the matching contact */
    index = chooseContactByField(addressBook);

    if(index == -1)
    {
        return;
    }

    /* Display the selected contact */
    printf(GREEN"\nContact found!\n"RESET);
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);
}

/* Edit an existing contact */
void editContact(AddressBook *addressBook)
{
    int index;
    char newName[50];
    char newPhone[20];
    char newEmail[50];

    /* Select the contact to edit */
    index = chooseContact(addressBook);

    if (index == -1)
    {
        return;
    }

    printf(YELLOW"\n╔══════════════════════════════════════╗\n"RESET);
    printf(YELLOW"║            EDIT CONTACT              ║\n"RESET);
    printf(YELLOW"╚══════════════════════════════════════╝\n"RESET);

    /* Get and validate new name */
    while(1)
    {
        printf(YELLOW"Enter new name: "RESET);

        /* Read new name */
        scanf(" %[^\n]", newName);
        while (getchar() != '\n');

        /* Validate new name */
        if (validateName(addressBook, newName, index))
        {
            break;
        }
    }
    /* Get and validate new phone */
    while(1)
    {
        printf(YELLOW"Enter new phone number: "RESET);
        /* Read new phone number */
        scanf(" %[^\n]", newPhone);
        while(getchar() != '\n');

        /* Validate new phone */
        if(validatePhone(addressBook, newPhone, index))
        {
            break;
        }
    }
    /* Get and validate new email */
    while(1)
    {
        printf(YELLOW"Enter new email: "RESET);

        /* Read new email */
        scanf(" %[^\n]", newEmail);
        while(getchar() != '\n');

        /* Validate new email */
        if(validateEmail(addressBook, newEmail, index))
        {
            break;
        }
    }

    /* Update the name of the selected contact */
    strcpy(addressBook->contacts[index].name, newName);

    /* Update the phone number */
    strcpy(addressBook->contacts[index].phone, newPhone);

    /* Update the email */
    strcpy(addressBook->contacts[index].email, newEmail);

    /* Save the updated contact details */
    saveContactsToFile(addressBook);
    printf(GREEN"\nContact updated successfully!\n"RESET);
}

/* Delete a contact */
void deleteContact(AddressBook *addressBook)
{
    int index,i;
    char choice;

    /* Select the contact to delete */
    index = chooseContact(addressBook);

    if(index == -1)
    {
        return;
    }

    printf(YELLOW"Are you sure you want to delete this contact? (y/n): "RESET);

    /* Read delete confirmation */
    scanf(" %c", &choice);
    while (getchar() != '\n');

    /* Delete the contact if user confirms */
    if(choice == 'y' || choice == 'Y')
    {
        /* Shift all contacts after the deleted contact */
        for(i = index;i < addressBook->contactCount - 1;i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        /* Decrease the contact count */
        addressBook->contactCount--;

        /* Save the updated contacts */
        saveContactsToFile(addressBook);
        printf(GREEN"Contact deleted successfully!\n"RESET);
    }

    /* Cancel the delete operation */
    else if(choice == 'n' || choice == 'N')
    {
        printf("Delete cancelled.\n");
    }

    /* Handle invalid confirmation */
    else
    {
        printf(RED"Error: Please enter only y or n.\n"RESET);
    }
}