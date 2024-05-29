#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct UserReg {
    char FirstName[60];
    char LastName[70];
    char Password[12];
    int isRegistered;
    long long AccountNumber;
};

// Function to register a user
void registerUser(struct UserReg *user) {
    printf("Enter Your Firstname: ");
    scanf("%s", user->FirstName);

    printf("Enter Your Lastname: ");
    scanf("%s", user->LastName);

    printf("Create Your Password: ");
    scanf("%s", user->Password);

    user->isRegistered = 1;

    FILE *filePointer = fopen("Database.txt", "w");
    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return;
    }

    srand(time(NULL));
    long long lower_bound = 1500000000LL;
    long long upper_bound = 9999999999LL;
    user->AccountNumber = lower_bound + (rand() % (upper_bound - lower_bound + 1));

    fprintf(filePointer, "%s\n", user->FirstName);
    fprintf(filePointer, "%s\n", user->LastName);
    fprintf(filePointer, "%s\n", user->Password);
    fprintf(filePointer, "%d\n", user->isRegistered);
    fprintf(filePointer, "%lld\n", user->AccountNumber);
    fclose(filePointer);

    printf("\nRegistration Details:\n");
    printf("First Name: %s\n", user->FirstName);
    printf("Last Name: %s\n", user->LastName);
    printf("Password: %s\n", user->Password);
    printf("Your 10-digit Account number: %lld\n", user->AccountNumber);
}

// Function to read user details from the file
void readUserDetails(struct UserReg *user) {
    FILE *filePointer = fopen("Database.txt", "r");
    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    if (fgets(user->FirstName, sizeof(user->FirstName), filePointer) == NULL ||
        fgets(user->LastName, sizeof(user->LastName), filePointer) == NULL ||
        fgets(user->Password, sizeof(user->Password), filePointer) == NULL ||
        fscanf(filePointer, "%d", &user->isRegistered) != 1 ||
        fscanf(filePointer, "%lld\n", &user->AccountNumber) != 1)  {
        printf("Error reading user data!\n");
        fclose(filePointer);
        return;
    }

    // Remove newline characters from strings
    user->FirstName[strcspn(user->FirstName, "\n")] = 0;
    user->LastName[strcspn(user->LastName, "\n")] = 0;
    user->Password[strcspn(user->Password, "\n")] = 0;

    fclose(filePointer);
}

// Function to login a user
void userLogin(struct UserReg *user) {
    struct UserReg storedUser = { .isRegistered = 0 };
    readUserDetails(&storedUser);

    if (storedUser.isRegistered) {
        printf("Enter Your Firstname: ");
        scanf("%s", user->FirstName);

        printf("Enter Your Lastname: ");
        scanf("%s", user->LastName);

        printf("Enter Your Password: ");
        scanf("%s", user->Password);

        if (strcmp(user->FirstName, storedUser.FirstName) == 0 &&
            strcmp(user->LastName, storedUser.LastName) == 0 &&
            strcmp(user->Password, storedUser.Password) == 0) {
            printf("Login successful!\n");
            printf("Your 10-digit Account number: %lld\n", user->AccountNumber);
        } else {
            printf("Login failed! Incorrect details.\n");
        }
    } else {
        printf("No user registered! Please register first\n");
    }
}

int main() {
    struct UserReg user = { .isRegistered = 0 };
    int Numb;
    int ContinueLoop = 1;

    while (ContinueLoop) {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("You are welcome to the JOGI Bank, pick between 1 and 2 to Register or Login: ");
        scanf("%d", &Numb);

        switch (Numb) {
            case 1:
                registerUser(&user);
                break;
            case 2:
                userLogin(&user);
                break;
            case 3:
                ContinueLoop = 0;
                break;
            default:
                printf("Invalid Input!\n");
                break;
        }
    }
    return 0;
}
