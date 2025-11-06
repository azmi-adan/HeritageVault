#include <stdio.h>
#include <string.h>
#include "auth.h"

int login() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    printf("\n=== LOGIN ===\n");
    printf("Username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline
    
    printf("Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline
    
    if (validateCredentials(username, password)) {
        printf("Login successful! Welcome, %s!\n", username);
        return 1;
    } else {
        printf("Invalid credentials! Please try again.\n");
        return 0;
    }
}

int validateCredentials(char* username, char* password) {
    // Simple authentication - in real system, this would be more secure
    if (strcmp(username, "officer") == 0 && strcmp(password, "password") == 0) {
        return 1;
    }
    return 0;
}