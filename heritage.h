#ifndef HERITAGE_H
#define HERITAGE_H

#define MAX_TITLE 100
#define MAX_DESC 300
#define MAX_LOCATION 100
#define MAX_MEDIA 100
#define MAX_CONDITION 50

typedef struct {
    int id;
    char name[MAX_TITLE];
    char description[MAX_DESC];
    char location[MAX_LOCATION];
    char condition[MAX_CONDITION];
    char mediaFile[MAX_MEDIA];
} HeritageItem;

// Function declarations
void addItem();
void viewAllItems();
void searchItem();
void editItem();
void deleteItem();
void generatePublicReport();
void generateDetailedReport();
int validateHeritageData(HeritageItem* item);

#endif