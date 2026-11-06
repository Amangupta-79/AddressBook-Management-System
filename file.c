#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {            // function defination of saving contacts to file.
  
    FILE *SV = fopen("contacts.txt","w");                 // Here we are opening the file in write mode.

    if (SV == NULL)                                       // Here we are checking the file is present or not.
    {
        printf("Error opening contacts.txt\n");
        return;
    }


    fprintf(SV,"#%d\n",addressBook->contactCount);
    
    for(int i=0; i<addressBook->contactCount; i++){
      
        fprintf(SV,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
    fclose(SV);
  
}

void loadContactsFromFile(AddressBook *addressBook) {          // function defination of load contacts from file.
    
    FILE *LC = fopen("contacts.txt","r");

    if (LC == NULL)
    {
        printf("Error opening contacts.txt\n");
        return;
    }

    addressBook->contactCount=0;

     
    fscanf(LC,"#%d\n",&addressBook->contactCount);
    
    for(int i=0; i<addressBook->contactCount; i++){
      
        fscanf(LC,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(LC);
  

}
