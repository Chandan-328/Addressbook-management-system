
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "contacts.h"

// Checks whether the contact name follows the required naming rules.
int validate_name(char name[])
{
    int count_check = 0;
    int counter = 0;
    int i = 0;
    int check = 0;

    while(name[i] != '\0')
    {
        char ch = name[i];

        count_check++;

        if(!isalpha((unsigned char)ch) && ch != ' ')
        {
            check = 1;
            break;
        }

        if(ch == ' ')
        {
            counter++;
        }
        i++;
    }

    if(check)
    {
        printf("Invalid name ! Use only alphabets and spaces.\n");
    }

    if(count_check < 3 || counter == count_check)
    {
        check = 1;
        printf("Name must contain at least 3 characters !!!\n");
    }

    return (check == 0) ? 1 : 0;
}


// Validates the phone number's format and checks for duplicates.
int validate_phone(char number[], Addressbook *addressbook, int index)
{
    int check = 0;
    int count_check = 0;
    int i = 0;

    while(number[i] != '\0')
    {
        char ch = number[i];

        if(!isdigit((unsigned char)ch))
        {
            check = 1;
            break;
        }

        count_check++;
        i++;
    }

    if(check)
    {
        printf("Invalid number ! Only digits are allowed.\n");
    }

    if(number[0] < '6' || number[0] > '9')
    {
        check = 1;
        printf("Invalid number ! First digit must be between 6 and 9.\n");
    }

    if(count_check != 10)
    {
        check = 1;
        printf("Invalid number ! Phone number must contain exactly 10 digits.\n");
    }

    if(check == 0)
    {
        for(int j = 0; j < addressbook->count; j++)
        {
            // Skip the contact currently being edited
            if(j != index)
            {
                if(strcmp(number, addressbook->contacts[j].number) == 0)
                {
                    check = 1;
                    printf("Number already exists !\n");
                    break;
                }
            }
        }
    }

    return (check == 0) ? 1 : 0;
}


// Validates the email format and checks whether it already exists.
int validate_email(char email[], Addressbook *addressbook, int index)
{
    int check = 0;
    int i = 0;
    int dot = 0;
    int last_dot = -1;
    int At_count = 0;
    int At_index = 0;
    int dot_index = -1;

    int size_of_mail = strlen(email);

    while(email[i] != '\0')
    {
        char ch = email[i];

        if(!islower((unsigned char)ch) &&
           !isdigit((unsigned char)ch) &&
           ch != '@' && ch != '.')
        {
            check = 1;
        }

        if(ch == '@')
        {
            At_count++;
            At_index = i;
        }

        if(ch == '.' && i > 0 && email[i - 1] == '.')
        {
            dot = 1;
        }

        if(ch == '.' && i > At_index &&
           dot_index == -1 && At_count == 1)
        {
            dot_index = i;
        }

        if(ch == '.')
        {
            last_dot = i;
        }

        i++;
    }

    if(check)
    {
        printf("Invalid email! Use only lowercase letters, digits, '@' and '.'\n");
    }

    if(dot)
    {
        check = 1;
        printf("Invalid email! Consecutive dots are not allowed.\n");
    }

    if(At_count > 1 || At_count == 0)
    {
        check = 1;
        printf("Invalid email! It must contain exactly one '@' symbol.\n");
    }

    if(At_count == 1 &&
       (At_index == 0 || At_index == size_of_mail - 1))
    {
        check = 1;
        printf("Invalid email! '@' cannot be at the beginning or end.\n");
    }

    if(At_count == 1 && At_index > 0 && email[At_index - 1] == '.')
    {
        check = 1;
        printf("Invalid email! A dot cannot appear immediately before '@'.\n");
    }

    if(At_count == 1 && dot_index == -1)
    {
        check = 1;
        printf("Invalid email! A dot must appear after '@'.\n");
    }
    else if(At_count == 1 && dot_index - At_index < 2)
    {
        check = 1;
        printf("Invalid email! At least one character must appear between '@' and the dot.\n");
    }

    if(At_count == 1 &&
       (last_dot <= At_index ||
        (size_of_mail - last_dot - 1) < 2 ||
        last_dot == -1))
    {
        check = 1;
        printf("Invalid email! The domain must have a dot followed by at least two characters.\n");
    }

    if(last_dot != -1 && last_dot > At_index &&
       (size_of_mail - last_dot - 1) >= 2)
    {
        for(int j = last_dot + 1; j < size_of_mail; j++)
        {
            char ch = email[j];

            if(!islower((unsigned char)ch))
            {
                check = 1;
                printf("Invalid email! Domain extension must contain only lowercase letters.\n");
                break;
            }
        }
    }

    if(size_of_mail > 0 &&
       (email[0] == '.' || email[size_of_mail - 1] == '.'))
    {
        check = 1;
        printf("Invalid email! It cannot start or end with a dot.\n");
    }

    if(check == 0)
    {
        for(int j = 0; j < addressbook->count; j++)
        {
            // Skip the contact currently being edited
            if(j != index)
            {
                if(strcmp(email, addressbook->contacts[j].email) == 0)
                {
                    check = 1;
                    printf("Email already exists. Please enter a different email.\n");
                    break;
                }
            }
        }
    }

    return (check == 0) ? 1 : 0;
}
