#include <stdio.h>
#include "contact.h"
#include <stdio_ext.h>

int main() 
{
    int choice;
    AddressBook addressBook;  
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf(CYAN "\n========================================\n" RESET);
        printf(CYAN "          ADDRESS BOOK SYSTEM           \n" RESET);
        printf(CYAN "========================================\n" RESET);

        printf(YELLOW "1. Create Contact\n" RESET);
        printf(YELLOW "2. Search Contact\n" RESET);
        printf(YELLOW "3. Edit Contact\n" RESET);
        printf(YELLOW "4. Delete Contact\n" RESET);
        printf(YELLOW "5. List Contacts\n" RESET);
        printf(RED    "6. Save & Exit\n" RESET);

        printf(CYAN "========================================\n" RESET);
        printf("Enter your choice: ");

         __fpurge(stdin);          // solving the scanf issue.
        
        scanf("%d", &choice);
        
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);              // calling create contact function to create contacts.
                break;
            case 2:
                searchContact(&addressBook);              // calling search contact function to search by name,phone,email.
                 break;
            case 3:
                editContact(&addressBook);                //calling edit contact function to edit contacts by name,phone,email.
                break;
            case 4:
                deleteContact(&addressBook);              //calling delete contact function to delete contacts.
                break;
            case 5:          
                listContacts(&addressBook);               // it is used for see the list of contacts.
                break;
            case 6:
                printf(RED"Saving and Exiting...\n"RESET);
                saveContactsToFile(&addressBook);           // Here we are saving contacts to file and then exit from whole program.
                break;
            default:
                printf(RED"Invalid choice.\nPlease try again.\n"RESET);
                break;
        }
    } while (choice != 6);                   // it will run till user not choose the option 6.
    
    return 0;
}
