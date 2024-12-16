#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_FILE "users.txt"
#define MAX_LEN 100

typedef struct {
    int id;
    char name[MAX_LEN];
    int age;
} User;


int isExistingUser(int id) {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return 0; 
    }

    User user;
    while (fscanf(file, "%d,%[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            fclose(file);
            return 1; 
        }               
    }

    fclose(file);
    return 0; 
}

void init_file() {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
       
        file = fopen(USER_FILE, "w");
        if (!file) {
            perror("Error creating file");
            exit(1);
        }
        printf("File '%s' created successfully.\n", USER_FILE);
    } else {
        printf("File '%s' already exists.\n", USER_FILE);
    }
    fclose(file);
}

void add_user() {
    FILE *file = fopen(USER_FILE, "a+");
    if (!file) {
        perror("Error opening file");
        return;
    }

    User user;
    int id;

    printf("Enter User ID: ");
    scanf("%d", &id);
    
    if (isExistingUser(id)) {
        printf("Error: User ID %d already exists. Please enter a different ID.\n", id);
        fclose(file);
        return;
    }

    user.id = id;
    printf("Enter User Name: ");
    scanf(" %[^\n]", user.name);
    printf("Enter User Age: ");
    scanf("%d", &user.age);

    fprintf(file, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User added successfully.\n");
}


void read_user() {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    User user;
    printf("\nID\tName\t\tAge\n");
    printf("---------------------------\n");

    while (fscanf(file, "%d,%[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        printf("%d\t%-15s\t%d\n", user.id, user.name, user.age);
    }

    fclose(file);
}


void update_user() {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    User users[100]; 
    int count = 0;
    int id, found = 0;
    User user;

    printf("Enter User ID to update: ");
    scanf("%d", &id);


    while (fscanf(file, "%d,%[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %[^\n]", user.name);
            printf("Enter New Age: ");
            scanf("%d", &user.age);
        }
        users[count++] = user;
    }

    fclose(file);

    if (!found) {
        printf("User with ID %d not found.\n");
        return;
    }

    file = fopen(USER_FILE, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d\n", users[i].id, users[i].name, users[i].age);
    }
    fclose(file);
    printf("User updated successfully.\n");
}

void delete_user() {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    User users[100];
    int count = 0;
    int id, found = 0;
    User user;

    printf("Enter User ID to delete: ");
    scanf("%d", &id);

    while (fscanf(file, "%d,%[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id != id) {
            users[count++] = user;
        } else {
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("User with ID %d not found.\n");
        return;
    }

    file = fopen(USER_FILE, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d\n", users[i].id, users[i].name, users[i].age);
    }
    fclose(file);
    printf("User deleted successfully.\n");
}

int main() {
    int choice;

    init_file();

    while (1) {
        printf("\nUser Database:\n");
        printf("1. Add User\n");
        printf("2. Display Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_user();
                break;
            case 2:
                read_user();
                break;
            case 3:
                update_user();
                break;
            case 4:
                delete_user();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
