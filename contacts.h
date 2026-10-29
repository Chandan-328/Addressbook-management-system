#ifndef CONTACTS_H
#define CONTACTS_H
#define MAX_CONTACTS 100
typedef struct Contact
{   
    char name[50];
    char number[20];
    char email[50];

}Contact;
typedef struct Addressbook
{
    Contact contacts[MAX_CONTACTS];
    int count;

}Addressbook;
void initialize(Addressbook *addressbook);
int createcontact(Addressbook *addressbook);
int searchcontact(Addressbook *addressbook);
void editcontact(Addressbook *addressbook);
void deletecontact(Addressbook *addressbook);
void listcontact(Addressbook *addressbook);
int validate_name(char name[]);
int validate_phone(char number[], Addressbook *addressbook, int index);
int validate_email(char email[], Addressbook *addressbook, int index);
int searchname(Addressbook *addressbook);
int searchnumber(Addressbook *addressbook);
int searchemail(Addressbook *addressbook);
void SaveContactsToFile(Addressbook *addressbook);
void LoadContactsFromFile(Addressbook *addressbook);
#endif