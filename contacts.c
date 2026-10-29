#include "contacts.h"
#include<stdio.h>
#include<string.h>
#include<ctype.h>

// Initializes the address book by setting the contact count to zero.
void initialize(Addressbook *addressbook)
{
    addressbook->count=0;                         
}
/*
 * Function: createcontact
 * Purpose : Accepts and validates a new contact's name, phone number,
 *           and email before storing the contact in the address book.
 * Returns : 1 if the contact is added successfully, otherwise 0.
 */
int createcontact(Addressbook *addressbook)
{
    if(addressbook->count >= MAX_CONTACTS)
    {
        printf("Contacts full ! Please delete contacts to add new contacts.\n");
        return 0;
    }

    char name[50];
    char number[20];
    char email[50];

    int valid = 0;

    // Name input and validation
    for(int attempt = 1; attempt <= 3; attempt++)
    {
        printf("\nENTER THE NAME : ");

        if(scanf(" %49[^\n]", name) != 1)
        {
            printf("Invalid name input.\n");
            return 0;
        }

        if(validate_name(name))
        {
            valid = 1;
            break;
        }
    }

    if(!valid)
    {
        printf("Three attempts failed!\n");
        printf("Name validation failed. Contact not added.\n");
        return 0;
    }

    valid = 0;

    // Phone input and validation
    for(int attempt = 1; attempt <= 3; attempt++)
    {
        printf("ENTER PHONE NUMBER : ");

        if(scanf("%19s", number) != 1)
        {
            printf("Invalid phone number input.\n");
            return 0;
        }

        // -1 means this is a new contact, not an edit
        if(validate_phone(number, addressbook, -1))
        {
            valid = 1;
            break;
        }
    }

    if(!valid)
    {
        printf("Three attempts failed!\n");
        printf("Number validation failed. Contact not added.\n");
        return 0;
    }

    valid = 0;

    // Email input and validation
    for(int attempt = 1; attempt <= 3; attempt++)
    {
        printf("ENTER EMAIL ADDRESS : ");

        if(scanf("%49s", email) != 1)
        {
            printf("Invalid email input.\n");
            return 0;
        }

        // -1 means this is a new contact, not an edit
        if(validate_email(email, addressbook, -1))
        {
            valid = 1;
            break;
        }
    }

    if(!valid)
    {
        printf("Three attempts failed!\n");
        printf("Email validation failed. Contact not added.\n");
        return 0;
    }

    strcpy(addressbook->contacts[addressbook->count].name, name);
    strcpy(addressbook->contacts[addressbook->count].number, number);
    strcpy(addressbook->contacts[addressbook->count].email, email);

    addressbook->count++;

    printf("Contact added successfully.\n");

    return 1;
}

/*
 * Function: searchcontact
 * Purpose : Displays the search menu and allows the user to search
 *           for a contact by name, mobile number, or email address.
 */
int searchcontact(Addressbook *addressbook)
{
    int choice=0;
    do
    {
        printf("\n1.Search by name \n");
        printf("2.Search by mobile number\n");
        printf("3.Search by mail id\n");
        printf("4.Exit\n");
        printf("Enter choice : ");
        if(scanf("%d",&choice) != 1)
        {
            printf("Invalid choice !\n");
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }
        switch(choice)
        {
            case 1:
            searchname(addressbook);
            break;
            
            case 2:
            searchnumber(addressbook);
            break;
        
            case 3:
            searchemail(addressbook);
            break;

            case 4:
            printf("Exited successfully.\n");
            break;

            default:
            printf("No contacts available..!\n");
        }
    } while (choice !=4);
    return -1;

}
/*
 * Function: editcontact
 * Purpose : Finds an existing contact and allows the user to modify
 *           the name, mobile number, or email address.
 */
void editcontact(Addressbook *addressbook)
{
    int choice=0;
    do
    {
        printf("\n1.Edit by name \n");
        printf("2.Edit by mobile number\n");
        printf("3.Edit by Email address\n");
        printf("4.Exit\n");
        printf("Enter choice : ");
        if(scanf("%d",&choice) !=1)
        {
            printf("Invalid choice! \n");
            int ch;
            while((ch=getchar()) !='\n' && ch != EOF);
            continue;
        }
        if(choice==4)
        {
            printf("Exited successfully \n");
            break;
        }
        if(choice >= 1 && choice <= 3)
        {
            if(choice == 1)
            {
                int index=searchname(addressbook);
                if(index != -1)
                {
                    int valid_name;
                    char new_name[50];
                    do
                    {
                        printf("Enter new name for the contact : ");
                        scanf(" %49[^\n]",new_name);
                        valid_name = validate_name(new_name);
                        if(valid_name == 0)
                        {
                            printf("\nInvalid name format!Please retry \n");
                             int ch;
                             while((ch = getchar()) != '\n' && ch != EOF);

                        }
                    }while(valid_name == 0);
                    int check=strcmp(addressbook->contacts[index].name,new_name);
                    if(check==0)
                    {
                        printf("Same name entered again !\n");
                    }
                    else
                    {
                        strcpy(addressbook->contacts[index].name,new_name);
                        SaveContactsToFile(addressbook);
                        printf("Name successfully changed \n");
                    }
                }
                
            }
            if(choice == 2)
            {
                char new_number[50];
                int index=searchnumber(addressbook);
                if(index != -1)
                {
                    int valid_number;
                    do
                    {
                        printf("Enter new number for the contact : ");
                        scanf(" %49[^\n]",new_number);
                        valid_number = validate_phone(new_number,addressbook,index);
                        if(valid_number == 0)
                        {
                            printf("\nInvalid number format!Please retry \n");
                             int ch;
                             while((ch = getchar()) != '\n' && ch != EOF);

                        }
                    }while(valid_number == 0);
                    int check=strcmp(addressbook->contacts[index].number,new_number);
                    if(check==0)
                    {
                        printf("Same number entered again !\n");
                    }
                    else
                    {
                        strcpy(addressbook->contacts[index].number,new_number);
                        SaveContactsToFile(addressbook);
                        printf("Number successfully changed \n");
                    }
                    
                }
            }
            if(choice == 3)
            {
                char new_email[50];
                int index=searchemail(addressbook);
                if(index != -1)
                {
                    int valid_email;
                    do
                    {
                        printf("Enter new email for the contact : ");
                        scanf(" %49[^\n]",new_email);
                        valid_email = validate_email(new_email,addressbook,index);
                        if(valid_email == 0)
                        {
                            printf("\nInvalid email format!Please retry \n");
                             int ch;
                             while((ch = getchar()) != '\n' && ch != EOF);

                        }
                    }while(valid_email == 0);
                    int check=strcmp(addressbook->contacts[index].email,new_email);
                    if(check==0)
                    {
                        printf("Same email entered again !\n");
                    }
                    else
                    {
                        strcpy(addressbook->contacts[index].email,new_email);
                        SaveContactsToFile(addressbook);
                        printf("Email successfully changed \n");
                    }
                    
                }
            }
        }
        else
        {
            printf("Invalid choice \n");
            
        }
    }while(choice !=4);
}
/*
 * Function: listcontact
 * Purpose : Displays all contacts currently stored in the address book.
 */
void listcontact(Addressbook *addressbook)
{
    if(addressbook->count==0)
    {
        printf("No contacts available.\n");
    }
    else
    {
        printf("                                  ADDRESSBOOK                                         \n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("SN       Name                   Mobile number                   Email            \n");
        printf("--------------------------------------------------------------------------------------\n");
        for(int i=0;i<addressbook->count;i++)
        {
            printf("%-5d %-25s %-25s %-25s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].number,addressbook->contacts[i].email);
        }
    }
    
}
/*
 * Function: deletecontact
 * Purpose : Finds a contact, requests confirmation, and removes the
 *           selected contact from the address book.
 */
void deletecontact(Addressbook *addressbook)
{
    int choice=0;
    do
    {
        printf("\n1.Delete contact by name \n");
        printf("2.Delete by mobile number\n");
        printf("3.Delete by Email address\n");
        printf("4.Exit\n");
        printf("Enter choice : ");
        if(scanf("%d",&choice) !=1)
        {
            printf("Invalid choice! \n");
            int ch;
            while((ch=getchar()) !='\n' && ch != EOF);
            continue;
        }
        if(choice==4)
        {
            printf("Exited successfully \n");
            break;
        }
        if(choice >= 1 && choice <= 3)
        {
            if(choice == 1)
            {
                int index=searchname(addressbook);
                if(index != -1)
                {
                    char ch;
                    printf("Do you want to delete the contact (y/n)\n");
                    scanf(" %c",&ch);
                    if(ch=='y' || ch=='Y')
                    {
                        for(int i=index;i < addressbook->count-1;i++)
                        {
                            addressbook->contacts[i] = addressbook->contacts[i+1];
                        }
                        addressbook->count--;
                        SaveContactsToFile(addressbook);
                        printf("Contact deleted successfully.\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }
                    
                }
            }
            if(choice == 2)
            {
                char new_number[50];
                int index=searchnumber(addressbook);
                if(index != -1)
                {
                    char ch;
                    printf("Do you want to delete the contact (y/n)\n");
                    scanf(" %c",&ch);
                    if(ch=='y' || ch=='Y')
                    {
                        for(int i=index;i < addressbook->count-1;i++)
                        {
                            addressbook->contacts[i] = addressbook->contacts[i+1];
                        }
                        addressbook->count--;
                        SaveContactsToFile(addressbook);
                        printf("Contact deleted successfully.\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }
                    
                }
            }
            if(choice == 3)
            {
                char new_email[50];
                int index=searchemail(addressbook);
                if(index != -1)
                {
                    char ch;
                    printf("Do you want to delete the contact (y/n)\n");
                    scanf(" %c",&ch);
                    if(ch=='y' || ch=='Y')
                    {
                        for(int i=index;i < addressbook->count-1;i++)
                        {
                            addressbook->contacts[i] = addressbook->contacts[i+1];
                        }
                        addressbook->count--;
                        SaveContactsToFile(addressbook);
                        printf("Contact deleted successfully.\n");
                    }
                    else
                    {
                        printf("Deletion cancelled.\n");
                    }
                    
                }
            }
        }
        else
        {
            printf("Invalid choice \n");
            
        }
    }while(choice !=4);
    
}