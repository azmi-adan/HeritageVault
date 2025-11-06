#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

#define DATA_FILE "heritage_data.txt"

int saveHeritageItem(HeritageItem* item) {
    FILE* file = fopen(DATA_FILE, "a");
    if (file == NULL) {
        return 0;
    }
    
    fprintf(file, "ID: %d\n", item->id);
    fprintf(file, "Name: %s\n", item->name);
    fprintf(file, "Description: %s\n", item->description);
    fprintf(file, "Location: %s\n", item->location);
    fprintf(file, "Condition: %s\n", item->condition);
    fprintf(file, "Media: %s\n", item->mediaFile);
    fprintf(file, "---\n");
    
    fclose(file);
    return 1;
}

int loadAllHeritageItems(HeritageItem** items) {
    FILE* file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        return 0;
    }
    
    HeritageItem* tempItems = NULL;
    int count = 0;
    int capacity = 10;
    
    tempItems = (HeritageItem*)malloc(capacity * sizeof(HeritageItem));
    if (tempItems == NULL) {
        fclose(file);
        return 0;
    }
    
    char line[500];
    HeritageItem currentItem;
    int readingItem = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        
        if (strncmp(line, "ID: ", 4) == 0) {
            sscanf(line + 4, "%d", &currentItem.id);
            readingItem = 1;
        } else if (strncmp(line, "Name: ", 6) == 0) {
            strcpy(currentItem.name, line + 6);
        } else if (strncmp(line, "Description: ", 13) == 0) {
            strcpy(currentItem.description, line + 13);
        } else if (strncmp(line, "Location: ", 10) == 0) {
            strcpy(currentItem.location, line + 10);
        } else if (strncmp(line, "Condition: ", 11) == 0) {
            strcpy(currentItem.condition, line + 11);
        } else if (strncmp(line, "Media: ", 7) == 0) {
            strcpy(currentItem.mediaFile, line + 7);
        } else if (strcmp(line, "---") == 0 && readingItem) {
            // End of item, add to array
            if (count >= capacity) {
                capacity *= 2;
                HeritageItem* newTemp = (HeritageItem*)realloc(tempItems, capacity * sizeof(HeritageItem));
                if (newTemp == NULL) {
                    free(tempItems);
                    fclose(file);
                    return 0;
                }
                tempItems = newTemp;
            }
            tempItems[count++] = currentItem;
            readingItem = 0;
            memset(&currentItem, 0, sizeof(HeritageItem));
        }
    }
    
    fclose(file);
    
    *items = tempItems;
    return count;
}