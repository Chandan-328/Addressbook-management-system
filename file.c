#include<stdio.h>
#include "contacts.h"

/*
 * Function: SaveContactsToFile
 * Purpose : Saves the current contact list to contacts.csv.
 *           Rewrites the file with the complete list using write mode.
 */
void SaveContactsToFile(Addressbook *addressbook)
{
    FILE *fp= fopen("contacts.csv", "w");
    if(fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }
    fprintf(fp, "Name,Mobile Number,Email\n");
    for (int i = 0; i < addressbook->count; i++)
    {
        fprintf(fp, "%s,%s,%s\n",addressbook->contacts[i].name,
                addressbook->contacts[i].number,
                addressbook->contacts[i].email);
    }
    fclose(fp);
    printf("Contacts saved successfully.\n");
}

/*
 * Function: LoadContactsFromFile
 * Purpose : Loads previously saved contacts from contacts.csv into
 *           the address book when the program starts.
 */
void LoadContactsFromFile(Addressbook *addressbook)
{
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL)
    {
        printf("No existing contacts file found.\n");
        return;
    }
    char line[100];
    if (fgets(line, sizeof(line), fp) != NULL)
    {
        while (addressbook->count < MAX_CONTACTS &&
       fgets(line, sizeof(line), fp) != NULL)
        {
            Contact temp;
            if (sscanf(line, "%49[^,],%19[^,],%49[^\r\n]",temp.name,temp.number,temp.email) == 3)
            {
                addressbook->contacts[addressbook->count] = temp;
                addressbook->count++;
            }
        }
        
    }
    fclose(fp);
}