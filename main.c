/*

Description:These functions are created to manage contacts named as AdressBook

 createContact() - Used for creating a new contact in the Address Book.
                   Validates the name, phone number and email before storing.
 
 listContacts()- Used for displaying all contacts stored in the Address Book.
                 Shows the contact details in a simple formatted manner.

 searchContact()- Used for searching a contact using name, phone number or email.
                  Displays the matching contact details to the user.
 

editContact()- Used for modifying the details of an existing contact.
               Validates the new values before updating the contact.
 
deleteContact()- Used for deleting an existing contact from the Address Book.
                 Removes the selected contact and rearranges the remaining contacts.
 

printContacts()- Used for displaying all contacts in a formatted table.
                 Helps the user to view the stored contact details easily.


chooseContact() -Used for selecting a contact from the list of available contacts.
                 Returns the selected contact number for further operations.

chooseContactByField()- Used for selecting a contact based on a particular field.
                        Helps the user choose the required contact when multiple matches are found.

validateName()- Used for validating the name entered by the user.
                Checks whether the name contains valid characters and is not duplicated.

validatePhone()- Used for validating the phone number entered by the user.
                 Checks the phone number format and prevents duplicate numbers.

validateEmail()- Used for validating the email ID entered by the user.
                 Checks the email format and prevents duplicate email IDs.
 
 Sample input:

╔═════════════════════════════════════════════╗
║              📒 ADDRESS BOOK                ║
╠═════════════════════════════════════════════╣
║  1.  ➜  Add Contact                         ║
║  2.  ➜  Search Contact                      ║
║  3.  ➜  Edit Contact                        ║
║  4.  ➜  Delete Contact                      ║
║  5.  ➜  List / Sort Contacts                ║
║  6.  ➜  Exit                                ║
╠═════════════════════════════════════════════╣
║        Manage your contacts easily!         ║
╚═════════════════════════════════════════════╝

  Total Contacts : 14

  Enter your choice: 1

  ═══════ ADD CONTACT ═══════

╔══════════════════════════════════════╗
║          CREATE NEW CONTACT          ║
╚══════════════════════════════════════╝
Enter name: vikas
Enter phone number: 8987898767
Enter email: vikas@123.com

Output:

Contact created successfully!

╔═════════════════════════════════════════════╗
║              📒 ADDRESS BOOK                ║
╠═════════════════════════════════════════════╣
║  1.  ➜  Add Contact                         ║
║  2.  ➜  Search Contact                      ║
║  3.  ➜  Edit Contact                        ║
║  4.  ➜  Delete Contact                      ║
║  5.  ➜  List / Sort Contacts                ║
║  6.  ➜  Exit                                ║
╠═════════════════════════════════════════════╣
║        Manage your contacts easily!         ║
╚═════════════════════════════════════════════╝

 Total Contacts : 15

 Enter your choice: 6 

  ╔══════════════════════════════════════╗
  ║       Thank You for Using            ║
  ║          ADDRESS BOOK!               ║
  ╚══════════════════════════════════════╝
  Goodbye! Have a great day. 👋

*/



#include <stdio.h>
#include "contact.h"

#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

/* Display the main menu */
void print_menu(void)
{
    printf("\n");
    printf(CYAN "╔═════════════════════════════════════════════╗\n" RESET);
    printf(CYAN "║" WHITE "              📒 ADDRESS BOOK                " CYAN "║\n" RESET);
    printf(CYAN "╠═════════════════════════════════════════════╣\n" RESET);

    printf(CYAN "║  " GREEN "1.  ➜  Add Contact                         " CYAN "║\n" RESET);
    printf(CYAN "║  " BLUE "2.  ➜  Search Contact                      " CYAN "║\n" RESET);
    printf(CYAN "║  " YELLOW "3.  ➜  Edit Contact                        " CYAN "║\n" RESET);
    printf(CYAN "║  " RED "4.  ➜  Delete Contact                      " CYAN "║\n" RESET);
    printf(CYAN "║  " MAGENTA "5.  ➜  List / Sort Contacts                " CYAN "║\n" RESET);
    printf(CYAN "║  " WHITE "6.  ➜  Exit                                " CYAN "║\n" RESET);

    printf(CYAN "╠═════════════════════════════════════════════╣\n" RESET);
    printf(CYAN "║" WHITE "        Manage your contacts easily!         " CYAN "║\n" RESET);
    printf(CYAN "╚═════════════════════════════════════════════╝\n" RESET);
}

/* Main function of the address book */
int main(void)
{
    int choice;
    int sortChoice;
    AddressBook addressBook;

    /* Initialize the address book */
    initialize(&addressBook);
    do
    {
        /* Display the main menu */
        print_menu();

        /* Display current number of contacts */
        printf(GREEN "\n  Total Contacts : %d\n" RESET,addressBook.contactCount);

        /* Ask the user for a choice */
        printf(YELLOW "\n  Enter your choice: " RESET);

        /* Check whether the entered choice is a number */
        if(scanf("%d", &choice) != 1)
        {
            /* Clear invalid input */
            while(getchar() != '\n');
            printf(RED "\n  ✗ Invalid input!\n" RESET);
            printf(RED "  Please enter a number from 1 to 6.\n" RESET);
            continue;
        }

        /* Clear remaining input */
        while(getchar() != '\n');
        /* Perform the selected operation */
        switch(choice)
        {
            /* Add a new contact */
            case 1:
                printf(GREEN "\n  ═══════ ADD CONTACT ═══════\n" RESET);
                createContact(&addressBook);
                break;
            /* Search for a contact */
            case 2:
                printf(BLUE "\n  ═══════ SEARCH CONTACT ═══════\n" RESET);
                searchContact(&addressBook);
                break;
            /* Edit an existing contact */
            case 3:
                printf(YELLOW "\n  ═══════ EDIT CONTACT ═══════\n" RESET);
                editContact(&addressBook);
                break;

            /* Delete an existing contact */
            case 4:
                printf(RED "\n  ═══════ DELETE CONTACT ═══════\n" RESET);
                deleteContact(&addressBook);
                break;

            /* Display sorting options */
            case 5:
                printf(MAGENTA "\n");
                printf("  ╔══════════════════════════════════╗\n");
                printf("  ║          CONTACT LIST            ║\n");
                printf("  ╠══════════════════════════════════╣\n");
                printf("  ║ " WHITE "1. " GREEN "Sort by Name                 " MAGENTA "║\n");
                printf("  ║ " WHITE "2. " YELLOW "Sort by Phone                " MAGENTA "║\n");
                printf("  ║ " WHITE "3. " BLUE "Sort by Email                " MAGENTA "║\n");
                printf("  ║ " WHITE "4. " RED "Back to Main Menu            " MAGENTA "║\n");
                printf("  ╚══════════════════════════════════╝\n");
                printf(RESET);

                /* Ask for sorting option */
                printf(YELLOW "  Enter sort choice: " RESET);

                /* Check whether sort choice is a number */
                if(scanf("%d", &sortChoice) != 1)
                {
                    /* Clear invalid input */
                    while(getchar() != '\n');

                    printf(RED "\n  ✗ Invalid input!\n" RESET);
                    printf(RED "  Please enter a number from 1 to 4.\n" RESET);

                    break;
                }

                /* Clear remaining input */
                while(getchar() != '\n');

                /* Sort by name */
                if(sortChoice == 1)
                {
                    printf(GREEN "\n  Sorting contacts by name...\n" RESET);
                    listContacts(&addressBook, 1);
                }

                /* Sort by phone */
                else if(sortChoice == 2)
                {
                    printf(YELLOW "\n  Sorting contacts by phone...\n" RESET);
                    listContacts(&addressBook, 2);
                }

                /* Sort by email */
                else if(sortChoice == 3)
                {
                    printf(BLUE "\n  Sorting contacts by email...\n" RESET);
                    listContacts(&addressBook, 3);
                }

                /* Return to main menu */
                else if(sortChoice == 4)
                {
                    printf(CYAN "\n  Returning to main menu...\n" RESET);
                }

                /* Invalid sorting option */
                else
                {
                    printf(RED "\n  ✗ Invalid sort choice!\n" RESET);
                    printf(RED "  Please choose between 1 and 4.\n" RESET);
                }

                break;

            /* Exit the program */
            case 6:
                printf("\n");
                printf(GREEN "  ╔══════════════════════════════════════╗\n" RESET);
                printf(GREEN "  ║       Thank You for Using            ║\n" RESET);
                printf(GREEN "  ║          ADDRESS BOOK!               ║\n" RESET);
                printf(GREEN "  ╚══════════════════════════════════════╝\n" RESET);
                printf(CYAN "  Goodbye! Have a great day. 👋\n\n" RESET);
                break;

            /* Handle invalid menu choices */
            default:
                printf(RED "\n  ✗ Invalid menu choice!\n" RESET);
                printf(RED "  Please enter a number from 1 to 6.\n" RESET);
        }

    } while (choice != 6);
    /* End the program */
    return 0;
}
