#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "contacts.h"

// Searches for a contact by name and returns its array index,
// or -1 if no matching contact is found.
int searchname(Addressbook *addressbook)
{
    char str_1[50];
    int found_1=0;
    printf("\nSearch the name : ");
    scanf(" %49[^\n]",str_1);
    for(int i=0;i < addressbook->count;i++)
    {
        int result=strcmp(addressbook->contacts[i].name,str_1);
        if(result==0)
        {
            printf("Contact found!\n");
            printf("Name         : %s\n", addressbook->contacts[i].name);
            printf("Mobile Number: %s\n", addressbook->contacts[i].number);
            printf("Email        : %s\n", addressbook->contacts[i].email);
            found_1=1;
            return i;
            }
        
    }
    if(found_1==0)
    {
        printf("Contact not found..\n");
        return -1;
    }
}

// Searches for a contact by mobile number and returns its array index,
// or -1 if no matching contact is found.
int searchnumber(Addressbook *addressbook)
{
    char str_2[50];
    int found_2=0;
    printf("\nSearch the number : ");
    scanf(" %49[^\n]",str_2);
    for(int i=0;i < addressbook->count;i++)
    {
        int result=strcmp(addressbook->contacts[i].number,str_2);
        if(result==0)
        {
            printf("Contact found!\n");
            printf("Name         : %s\n", addressbook->contacts[i].name);
            printf("Mobile Number: %s\n", addressbook->contacts[i].number);
            printf("Email        : %s\n", addressbook->contacts[i].email);
            found_2=1;
            return i;
        }
            
    }
    if(found_2==0)
    {
        printf("Contact not found..\n");
        return -1;
    }
}

// Searches for a contact by email address and returns its array index,
// or -1 if no matching contact is found.
int searchemail(Addressbook *addressbook)
{
    char str_3[50];
    int found_3=0;
    printf("\nSearch the Email address : ");
    scanf(" %49[^\n]",str_3);
    for(int i=0;i < addressbook->count;i++)
    {
        int result=strcmp(addressbook->contacts[i].email,str_3);
        if(result==0)
        {
            printf("Contact found!\n");
            printf("Name         : %s\n", addressbook->contacts[i].name);
            printf("Mobile Number: %s\n", addressbook->contacts[i].number);
            printf("Email        : %s\n", addressbook->contacts[i].email);
            found_3=1;
            return i;
        }
        
    }
    if(found_3==0)
    {
        printf("Contact not found\n");
        return -1;
    
    }
}