#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Contact {
    char name[50];
    char phone[20];
    char address[100];
};


void addContactToFile(struct Contact contact) {
    FILE *file = fopen("contacts.txt", "a"); 
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s\n", contact.name, contact.phone, contact.address);

    fclose(file); 
}

void displayContactsFromFile() {
    FILE *file = fopen("contacts.txt", "r"); 
    if (file == NULL) {
        printf("No contact.\n");
        return;
    }

    struct Contact contact;
    int contactCount = 0;

    printf("Contact List::\n");
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        contactCount++;
        printf("%d. Name: %s\n   Phone: %s\n   Address: %s\n", contactCount, contact.name, contact.phone, contact.address);
    }

    if (contactCount == 0) {
        printf("No contact.\n");
    }

    fclose(file); 
}


void searchContactByName(char *searchName) {
    FILE *file = fopen("contacts.txt", "r"); 
    if (file == NULL) {
        printf("No contact.\n");
        return;
    }

    struct Contact contact;
    int found = 0;

    printf("Enter name to search for: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        if (strstr(contact.name, searchName) != NULL) {
            found = 1;
            printf("Contact found:\n");
            printf(" Name: %s\n Phone: %s\n Address: %s\n", contact.name, contact.phone, contact.address);
        }
    }

    if (!found) {
        printf("Cannot find! \"%s\".\n", searchName);
    }

    fclose(file); 
}

int main() {
    int choice;
    char searchName[50];

    while (1) {
        printf("\nWelcome to the Contact Manager!\n");
        printf("1. Add a new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                struct Contact newContact;
                printf("Enter name: ");
                fgets(newContact.name, sizeof(newContact.name), stdin);
                newContact.name[strcspn(newContact.name, "\n")] = '\0';
                printf("Enter phone number: ");
                fgets(newContact.phone, sizeof(newContact.phone), stdin);
                newContact.phone[strcspn(newContact.phone, "\n")] = '\0';
                printf("Enter address: ");
                fgets(newContact.address, sizeof(newContact.address), stdin);
                newContact.address[strcspn(newContact.address, "\n")] = '\0';

                addContactToFile(newContact);
                printf("Contact added successfully!\n");
                break;
            }
            case 2:
                displayContactsFromFile();
                break;
            case 3:
                searchContactByName(searchName);
                break;
            case 4:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please select again!\n");
        }
    }

    return 0;
}
