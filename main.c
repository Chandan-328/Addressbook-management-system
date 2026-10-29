#include<stdio.h>
#include<ctype.h>
#include"contacts.h"
int main()
{
    // Creates an Addressbook variable that holds the contact array and contact count.
    Addressbook addressbook;
    // Initialize the address book before using it.
    initialize(&addressbook);
    // Restore contacts saved during previous program executions.
    LoadContactsFromFile(&addressbook);
    int choice;
    do
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) !=1)
        {
            printf("Invalid choice !\n");
            int ch;
            while(ch=getchar() !='\n' && ch != EOF);
            continue;
        }
        switch(choice)
        {
            case 1:
            if(createcontact(&addressbook))
            {
                SaveContactsToFile(&addressbook);
            }
            break;
            case 2:
            searchcontact(&addressbook);
            break;
            case 3:
            editcontact(&addressbook);
            break;
            case 4:
            deletecontact(&addressbook);
            break;
            case 5:
            listcontact(&addressbook);
            break;
            case 6:
            char ch;
            printf("Do you want to exit (y/n)\n");
            scanf(" %c",&ch);
            if(ch=='y' || ch=='Y')
            {
                printf("Exiting address book...\n");
                break;
            }
            else
            {
                choice = 1;
            }
            break;
            default:
            printf("Invalid choice ! Please try again.\n");

        }
    } while (choice !=6);
    return 0;
}