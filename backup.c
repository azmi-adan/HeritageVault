#include <stdio.h>
#include <time.h>
#include "file_handling.h"

void autoBackup() {
    printf("Performing automatic backup...\n");
    
    // Create backup filename with timestamp
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char backupFilename[100];
    snprintf(backupFilename, sizeof(backupFilename), 
             "backup_%04d%02d%02d_%02d%02d%02d.txt",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    // Simple backup - copy the data file
    FILE* source = fopen("heritage_data.txt", "r");
    FILE* backup = fopen(backupFilename, "w");
    
    if (source && backup) {
        char ch;
        while ((ch = fgetc(source)) != EOF) {
            fputc(ch, backup);
        }
        printf("Backup created successfully: %s\n", backupFilename);
    } else {
        printf("Error: Backup failed!\n");
    }
    
    if (source) fclose(source);
    if (backup) fclose(backup);
}