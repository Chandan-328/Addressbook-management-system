# Address Book Management System

A menu-driven C program for managing contacts. Each contact contains a name, mobile number, and email address. The in-memory address book can hold up to 100 contacts.

## Project flow

1. The program initializes an empty address book.
2. At startup, it attempts to load saved contacts from `contacts.csv` into memory. If the file does not exist, the program starts with an empty list.
3. The main menu lets you create, search, edit, delete, or list contacts.
4. Contact details are validated before they are added or updated. New contacts and changes to existing contacts are saved to `contacts.csv`.
5. Choosing Exit ends the program. Contacts are loaded again from `contacts.csv` the next time it starts.

Search, edit, and delete operations can find a contact by name, mobile number, or email. Deletion asks for confirmation before removing a contact.

## Source files

- `main.c` — initializes the address book, loads saved contacts, and runs the main menu.
- `contacts.c` — implements contact creation, search/edit/delete menus, and contact listing.
- `searchfunction.c` — searches contacts by name, mobile number, or email.
- `validate.c` — validates names, phone numbers, and email addresses, including duplicate checks.
- `file.c` — loads and saves contacts in CSV format.
- `contacts.h` — defines the contact and address book structures and declares shared functions.

## Build and run

With GCC:

```sh
gcc main.c contacts.c searchfunction.c validate.c file.c -o addressbook
./addressbook
```

On Windows, run the generated executable:

```powershell
.\addressbook.exe
```

The program reads and writes `contacts.csv` in its current working directory. If no saved contacts file is present, one is created when a contact is saved.
