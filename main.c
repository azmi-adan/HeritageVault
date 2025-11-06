#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "heritage.h"
#include "file_handling.h"
#include "backup.h"

void displayMainMenu();
void displayOfficerMenu();
void publicSearch();

int main() {
    int choice;
    int loggedIn = 0;
    
    printf("=== HeritageVault - Digital Preservation System ===\n");
    
    while(1) {
        if (!loggedIn) {
            displayMainMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar(); // Clear newline
            
            switch(choice) {
                case 1:
                    loggedIn = login();
                    break;
                case 2:
                    publicSearch();
                    break;
                case 3:
                    generatePublicReport();
                    break;
                case 4:
                    printf("Thank you for using HeritageVault!\n");
                    exit(0);
                default:
                    printf("Invalid choice! Please try again.\n");
            }
        } else {
            displayOfficerMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar(); // Clear newline
            
            switch(choice) {
                case 1:
                    addItem();
                    break;
                case 2:
                    editItem();
                    break;
                case 3:
                    deleteItem();
                    break;
                case 4:
                    viewAllItems();
                    break;
                case 5:
                    searchItem();
                    break;
                case 6:
                    generateDetailedReport();
                    break;
                case 7:
                    loggedIn = 0;
                    printf("Logged out successfully!\n");
                    break;
                default:
                    printf("Invalid choice! Please try again.\n");
            }
        }
    }
    
    return 0;
}

void displayMainMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Login (County Officer)\n");
    printf("2. Public Search\n");
    printf("3. Generate Public Reports\n");
    printf("4. Exit\n");
}

void displayOfficerMenu() {
    printf("\n=== OFFICER MENU ===\n");
    printf("1. Add Heritage Item\n");
    printf("2. Edit Heritage Item\n");
    printf("3. Delete Heritage Item\n");
    printf("4. View All Items\n");
    printf("5. Search Items\n");
    printf("6. Generate Detailed Report\n");
    printf("7. Logout\n");
}

void publicSearch() {
    printf("\n=== PUBLIC SEARCH ===\n");
    searchItem(); // Uses the same search function but might show limited info
}