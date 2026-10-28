#include <stdio.h>
#include "file.h"

/* Save all contacts into contacts.txt */
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    int i;
    /* Open the file in write mode */

    fp = fopen("contacts.txt", "w");
    /* Check whether the file was opened successfully */

    if(fp == NULL)
    {
        printf("Error: Unable to open contacts.txt\n");
        return;
    }

    /* Write each contact into the file */
    for(i = 0;i < addressBook->contactCount;i++)
    {
        /* Store name, phone and email separated by commas */
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    /* Close the file after saving all contacts */
    fclose(fp);
}


/* Load contacts from contacts.txt */
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;
    Contact contact;
    /* Start with zero contacts before loading from the file */
    addressBook->contactCount = 0;

    /* Open the file in read mode */
    fp = fopen("contacts.txt", "r");

    /* If the file does not exist, return without loading */
    if(fp == NULL)
    {
        return;
    }

    /* Read contacts until the file ends or maximum limit is reached */
    while(addressBook->contactCount < MAX_CONTACTS &&fscanf(fp, " %49[^,],%19[^,],%49[^\n]",contact.name,contact.phone,contact.email) == 3)
    {
        /* Store the loaded contact in the address book */
        addressBook->contacts[addressBook->contactCount] = contact;

        /* Increase the contact count after loading one contact */
        addressBook->contactCount++;
    }
    /* Close the file after loading all contacts */
    fclose(fp);
}