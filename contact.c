#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <stdio_ext.h>

void listContacts(AddressBook *addressBook)            // List all contacts  in terminal.
{
    //   Bubble sort by name.

    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp;

                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    //    Display sorted contacts.

    printf("\n!!! Sorted Contacts !!!\n");

    
    printf(CYAN "\n===============================================================\n" RESET);
    printf(CYAN "                     CONTACT LIST                              \n" RESET);
    printf(CYAN "===============================================================\n" RESET);

    printf(YELLOW "| %-3s | %-15s | %-13s | %-19s|\n","S.No", "Name", "Phone", "Email");

    printf(CYAN "---------------------------------------------------------------\n" RESET);


    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf(BLUE"|%-3d | %-15s|  %-13s| %-20s |\n"RESET, i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf(GREEN"--------------------------------------------------------------\n"RESET);


    // Save sorted contacts into file.

    saveContactsToFile(addressBook);

    printf(RED "\nTotal Contacts: %d\n" RESET,addressBook->contactCount);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// check name is valid or not and return value to res variable declare in create contact function.

int validate_name(char *str1)
{

    if (str1[0] == '\0')
    {
        return 0;
    }

    for (int i = 0; str1[i]; i++)
    {
        if (str1[i] >= 'a' && str1[i] <= 'z' || str1[i] >= 'A' && str1[i] <= 'Z' || str1[i] == '.' || str1[i] == ' ')
        {
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// check number is valid or not and return value to res variable declare in create contact function.

int validate_number(char *str2, AddressBook *addressBook)
{
    int count = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, str2) == 0)
        {
            printf(RED"\nPhone number already exist!!\n\nPlease Enter new number!!\n"RESET);

            count = 1;
        }
    }
    if (count)
    {
        return 0;
    }

    if (strlen(str2) != 10)
    {
        return 0;
    }

    for (int i = 0; str2[i]; i++)
    {
        if (str2[i] >= '0' && str2[i] <= '9')
        {
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// check email is valid or not and return value to res variable declare in create contact function.

int validate_email(char *str3, AddressBook *addressBook)
{
    // Check duplicate email.
    int count = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, str3) == 0)
        {
            count = 1;
            printf(RED"\nEmail already exist!!\nPlease Enter new Email!!\n"RESET);
        }
    }
    if (count)
    {
        return 0;
    }

    //   check first character.

    int len = strlen(str3);

    if (len < 4)
    {
        return 0;
    }

    if ((str3[0] >= '0' && str3[0] <= '9') || (str3[0] == '@' || str3[0] == '.') || (str3[0] >= 'A' && str3[0] <= 'Z'))
    {
        return 0;
    }

    // checking in email that .com is  present in last or not.

    if (str3[len - 1] == 'm' && str3[len - 2] == 'o' && str3[len - 3] == 'c' && str3[len - 4] == '.')
    {
    }

    else
    {
        return 0;
    }

    //  Find @ and make sure only one time @ exists.

    int count1 = 0;
    int pos = -1;

    for (int i = 0; str3[i]; i++)
    {
        if (str3[i] == '@')
        {
            count1++;
            pos = i;
        }
    }

    //   Only one @ should present in email.

    if (count1 != 1)
    {
        return 0;
    }

    //  @ should not be present before .com.

    if (pos + 1 >= len - 4)
    {
        return 0;
    }

    //  Check string after @.

    for (int i = pos + 1; i < len - 4; i++)
    {
        if (str3[i] < 'a' || str3[i] > 'z')
        {
            return 0;
        }
    }

    // Check characters in complete email

    for (int i = 0; str3[i]; i++)
    {
        if ((str3[i] >= '0' && str3[i] <= '9') || (str3[i] >= 'a' && str3[i] <= 'z') || (str3[i] == '@') || (str3[i] == '.'))
        {
        }

        else
        {
            printf(RED"\nEntered email is invalid\n"RESET);
            return 0;
        }
    }
    return 1;
}

// Create new contact in AddressBook list.

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */


    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is Full!\n");
        return;
    }

    char str1[50];
    char str2[20];
    char str3[50];
    int res;

    // Read name from user until user not entered correct name.

    do
    {
        printf("\nEnter the name : ");
        scanf(" %[^\n]", str1);

        res = validate_name(str1);

    } while (res == 0);

    // Read number from user until user not entered correct number.

    do
    {
        printf("\nEnter the Phone Number : ");
        scanf(" %[^\n]", str2);

        res = validate_number(str2, addressBook);

    } while (res == 0);

    // Read email from user until user not entered correct email.

    do
    {
        printf("\nEnter the Email id : ");
        scanf(" %[^\n]", str3);

        res = validate_email(str3, addressBook);

    } while (res == 0);

    strcpy(addressBook->contacts[addressBook->contactCount].name, str1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str2);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str3);

    addressBook->contactCount++;
    printf(YELLOW"\nContact created successfully.\n"RESET);
}

// Search the contacts using search by number function and return to search contact function.

int Search_by_number(AddressBook *addressBook)
{

    char str_number[20];

    printf("\nEnter the number:");
    scanf(" %[^\n]", str_number);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, str_number) == 0)
        {
            printf("%s", str_number);
            return i;
        }
    }
    printf(RED"\nNumber Not Exist\n"RESET);
    return -1;
}

// Search the contacts using search by name function and return to search contact function.

int Search_by_name(AddressBook *addressBook)
{

    int index, count = 0;
    char str_name[50];

    printf("\nEnter the name: ");
    scanf(" %[^\n]", str_name);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasecmp(addressBook->contacts[i].name, str_name) == 0)
        {
            printf("%s\n", addressBook->contacts[i].name);
            count++;
            index = i;
        }
    }
    if (count > 1)
    {
        printf(MAGENTA"\nMultiple name present"RESET);

        return Search_by_number(addressBook);
    }
    else if (count == 1)
    {
        return index;
    }
    else
    {
        printf(RED"\nName not exist"RESET);
        return -1;
    }
}

// Search the contacts using search by email function and return to search contact function.

int Search_by_Email(AddressBook *addressBook)
{

    char str_email[50];

    printf("\nEnter the email: ");
    scanf(" %[^\n]", str_email);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, str_email) == 0)
        {
            printf("%s", str_email);
            return i;
        }
    }
    printf(RED"\nEmail Not Exist"RESET);
    return -1;
}

// Search contact is present or not in Addressbook list.

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */

    int choice, index;
    do
    {
        printf("\nSearch by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");

        __fpurge(stdin);

        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            index = Search_by_name(addressBook);
            if (index >= 0)
            {
                printf("\nFound at index: %d", index);
            }
            break;
        case 2:
            index = Search_by_number(addressBook);
            if (index >= 0)
            {
                printf("\nFound at index: %d", index);
            }
            break;
        case 3:
            index = Search_by_Email(addressBook);
            if (index >= 0)
            {
                printf("\nFound at index: %d", index);
            }
            break;
        case 4:
            printf(RED"\nExit From Search Contact\n"RESET);
            printf("\n...Go Back To Address Book Menu...\n");
            break;
        default:
            printf(RED"Invalid input"RESET);
            break;
        }
    } while (choice != 4);
}

// Edit contacts that present in list and after editing the contacts return back to editcontact function.

int edit_present_contacts(int index, AddressBook *addressBook)
{
    int choose;
    do
    {

        printf("\nEnter Field to edit : ");
        printf("\n1.Name:");
        printf("\n2.phone:");
        printf("\n3.Email");
        printf("\n4.Exit:");

        printf("\nEnter the choice:");

        __fpurge(stdin);

        scanf("%d", &choose);

        switch (choose)
        {
        case 1:
            char Name[50];

            printf("\nEnter the name:");
            scanf(" %[^\n]", Name);
            if (validate_name(Name))
            {
                strcpy(addressBook->contacts[index].name, Name);
                printf("\n...Sucessfully Changed...\n");
            }
            else
            {
                printf("\nInvalid name\n");
            }
            break;

        case 2:
            char Number[20];

            printf("\nEnter the number:");
            scanf(" %[^\n]", Number);
            if (validate_number(Number, addressBook))
            {
                strcpy(addressBook->contacts[index].phone, Number);
                printf("\n...Sucessfully Changed...\n");
            }
            else
            {
                printf("\nInvalid number\n");
            }
            break;

        case 3:
            char Email[50];

            printf("\nEnter the email:");
            scanf(" %[^\n]", Email);
            if (validate_email(Email, addressBook))
            {
                strcpy(addressBook->contacts[index].email, Email);
                printf("\n...Sucessfully Changed...\n");
            }
            else
            {
                printf("\nInvalid email\n");
            }
            break;

        case 4:
            printf(RED"\n!!!!Exit!!!!\n"RESET);
            printf("\n!!!Return to Edit contact!!!\n");
            break;

        default:
            printf(RED"\nInvalid input"RESET);
            break;
        }

    } while (choose != 4);
}

// Edit contact from Addressbook list.it call the edit_present_contacts to edit.

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    int choose,index = -1;

    do
    {
         

        printf("\nEdit contacts by:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");

         __fpurge(stdin);

        scanf("%d", &choose);

        switch (choose)
        {
        case 1:
            index = Search_by_name(addressBook);
            break;

        case 2:
            index = Search_by_number(addressBook);
            break;

        case 3:
            index = Search_by_Email(addressBook);
            break;

        case 4:
            printf(RED"\nExit From Edit Contact..\n..Go Back To Address Book Menu..\n"RESET);
            return;

        default:
            printf(RED"Invalid input"RESET);
            break;
        }

        if (index == -1)
        {
            printf("\nGo back to Edit menu\n");
        }
        else
        {
            edit_present_contacts(index, addressBook);
        }
    } while (choose != 4);
}


// For deleting contacts ask the user to give input and then call the delete_contacts to delete.

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */

    int choice, index = -1;

    do
    {
        printf("\nSearch for delete:\n");
        printf("1.Name :\n");
        printf("2.number :\n");
        printf("3.Email :\n");
        printf("4.Exit :\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        __fpurge(stdin);

        switch (choice)
        {

        case 1:
            index = Search_by_name(addressBook);
            break;

        case 2:
            index = Search_by_number(addressBook);
            break;

        case 3:
            index = Search_by_Email(addressBook);
            break;

        case 4:
            printf(RED"\nExit....From Delete Menu....\n//..Go Back To Address book Menu....\n"RESET);
            return;

        default:
            printf(RED"Invalid input"RESET);
            break;
        }

//       first check index then Delete contacts from lists using if else and loop;

        if (index >= 0)
        {

            for (int i = index; i < addressBook->contactCount - 1; i++)
            {

                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            addressBook->contactCount--;

            printf(RED"\nDeleted Successfully...\n"RESET);
        }
        else
        {
            printf(RED"\nContact not found...\n"RESET);
        }
    } while (choice != 4);
}