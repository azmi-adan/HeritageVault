#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heritage.h"
#include "file_handling.h"
#include "backup.h"

void addItem() {
    HeritageItem newItem;
    static int nextId = 1;
    
    printf("\n=== ADD HERITAGE ITEM ===\n");
    
    // Get item details
    printf("Enter heritage site name: ");
    fgets(newItem.name, MAX_TITLE, stdin);
    newItem.name[strcspn(newItem.name, "\n")] = 0;
    
    printf("Enter description: ");
    fgets(newItem.description, MAX_DESC, stdin);
    newItem.description[strcspn(newItem.description, "\n")] = 0;
    
    printf("Enter location (County): ");
    fgets(newItem.location, MAX_LOCATION, stdin);
    newItem.location[strcspn(newItem.location, "\n")] = 0;
    
    printf("Enter condition (Good/Fair/Poor): ");
    fgets(newItem.condition, MAX_CONDITION, stdin);
    newItem.condition[strcspn(newItem.condition, "\n")] = 0;
    
    printf("Enter media file name: ");
    fgets(newItem.mediaFile, MAX_MEDIA, stdin);
    newItem.mediaFile[strcspn(newItem.mediaFile, "\n")] = 0;
    
    // Validate data
    if (!validateHeritageData(&newItem)) {
        printf("Error: Invalid data entered. Please check your inputs.\n");
        return;
    }
    
    // Assign ID and save
    newItem.id = nextId++;
    if (saveHeritageItem(&newItem)) {
        printf("Heritage item added successfully! ID: %d\n", newItem.id);
        autoBackup(); // Perform automatic backup
    } else {
        printf("Error: Failed to save heritage item.\n");
    }
}

void viewAllItems() {
    printf("\n=== ALL HERITAGE ITEMS ===\n");
    HeritageItem* items = NULL;
    int count = loadAllHeritageItems(&items);
    
    if (count == 0) {
        printf("No heritage items found.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        printf("\n--- Item %d ---\n", i + 1);
        printf("ID: %d\n", items[i].id);
        printf("Name: %s\n", items[i].name);
        printf("Location: %s\n", items[i].location);
        printf("Condition: %s\n", items[i].condition);
        printf("Description: %s\n", items[i].description);
        printf("Media: %s\n", items[i].mediaFile);
    }
    
    free(items);
}

void searchItem() {
    char searchTerm[MAX_TITLE];
    int found = 0;
    
    printf("\n=== SEARCH HERITAGE ITEMS ===\n");
    printf("Enter search term (name or location): ");
    fgets(searchTerm, MAX_TITLE, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;
    
    HeritageItem* items = NULL;
    int count = loadAllHeritageItems(&items);
    
    printf("\nSearch Results:\n");
    for (int i = 0; i < count; i++) {
        if (strstr(items[i].name, searchTerm) != NULL || 
            strstr(items[i].location, searchTerm) != NULL) {
            printf("\n--- Found Item ---\n");
            printf("ID: %d\n", items[i].id);
            printf("Name: %s\n", items[i].name);
            printf("Location: %s\n", items[i].location);
            printf("Condition: %s\n", items[i].condition);
            printf("Description: %s\n", items[i].description);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No items found matching '%s'\n", searchTerm);
    }
    
    free(items);
}

void editItem() {
    int id;
    printf("\n=== EDIT HERITAGE ITEM ===\n");
    printf("Enter ID of item to edit: ");
    scanf("%d", &id);
    getchar(); // Clear newline
    
    // Implementation for editing would go here
    printf("Edit functionality for item ID %d would be implemented here.\n", id);
}

void deleteItem() {
    int id;
    printf("\n=== DELETE HERITAGE ITEM ===\n");
    printf("Enter ID of item to delete: ");
    scanf("%d", &id);
    getchar(); // Clear newline
    
    // Implementation for deletion would go here
    printf("Delete functionality for item ID %d would be implemented here.\n", id);
}

void generatePublicReport() {
    printf("\n=== PUBLIC REPORT ===\n");
    HeritageItem* items = NULL;
    int count = loadAllHeritageItems(&items);
    
    printf("Public Report - Heritage Sites Summary\n");
    printf("Total Sites: %d\n\n", count);
    
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %s (%s)\n", 
               items[i].id, items[i].name, items[i].location, items[i].condition);
    }
    
    free(items);
}

void generateDetailedReport() {
    printf("\n=== DETAILED OFFICER REPORT ===\n");
    HeritageItem* items = NULL;
    int count = loadAllHeritageItems(&items);
    
    printf("Detailed Officer Report\n");
    printf("=======================\n");
    printf("Total Heritage Sites: %d\n\n", count);
    
    for (int i = 0; i < count; i++) {
        printf("Site %d:\n", items[i].id);
        printf("  Name: %s\n", items[i].name);
        printf("  Location: %s\n", items[i].location);
        printf("  Condition: %s\n", items[i].condition);
        printf("  Description: %s\n", items[i].description);
        printf("  Media File: %s\n", items[i].mediaFile);
        printf("  --------------------\n");
    }
    
    free(items);
}

int validateHeritageData(HeritageItem* item) {
    // Check if required fields are not empty
    if (strlen(item->name) == 0) {
        printf("Error: Name cannot be empty.\n");
        return 0;
    }
    if (strlen(item->location) == 0) {
        printf("Error: Location cannot be empty.\n");
        return 0;
    }
    if (strlen(item->condition) == 0) {
        printf("Error: Condition cannot be empty.\n");
        return 0;
    }
    
    // Validate condition value
    char conditionLower[MAX_CONDITION];
    strcpy(conditionLower, item->condition);
    for (int i = 0; conditionLower[i]; i++) {
        conditionLower[i] = tolower(conditionLower[i]);
    }
    
    if (strcmp(conditionLower, "good") != 0 && 
        strcmp(conditionLower, "fair") != 0 && 
        strcmp(conditionLower, "poor") != 0) {
        printf("Error: Condition must be Good, Fair, or Poor.\n");
        return 0;
    }
    
    return 1;
}