#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[10];
char currentUser[50];

/* ---- FUNCTION DECLARATIONS ---- */
int loginSystem();
void mainMenu();
void adminMenu();
void userMenu();
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

/* ------------------------------ MAIN ------------------------------ */
int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nAccess Denied. Exiting...\n");
    }
    return 0;
}

/* ----------------------- LOGIN SYSTEM ----------------------------- */
int loginSystem() {
    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("\nError: credentials.txt not found!\n");
        return 0;
    }

    char user[50], pass[50], fileUser[50], filePass[50], fileRole[10];

    printf("\n=====******* LOGIN SYSTEM *******=====\n");
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) != EOF) {
        if (strcmp(user, fileUser) == 0 && strcmp(pass, filePass) == 0) {
            strcpy(currentUser, fileUser);
            strcpy(currentRole, fileRole);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* ---------------------- MAIN MENU ------------------------- */
void mainMenu() {
    if (strcmp(currentRole, "admin") == 0) {
        adminMenu();
    } else if(strcmp(currentRole, "user") == 0){
        userMenu();
    }
}

/* ---------------------- ADMIN MENU ------------------------- */
void adminMenu() {
    int ch;
    do {
        printf("\n=====******* ADMIN MENU *******=====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 6);
}

/* ---------------------- USER MENU ------------------------- */
void userMenu() {
    int ch;
    do {
        printf("\n=====******* USER MENU *******=====\n");
        printf("1. View Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: viewStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    } while (ch != 3);
}

/* ---------------------- ADD STUDENT ------------------------- */
void addStudent() {
    FILE *fp = fopen(STUDENT_FILE, "a");
    struct Student s;

    printf("\nEnter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student added successfully!\n");
}

/* ---------------------- VIEW STUDENTS ------------------------- */
void viewStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct Student s;

    if (!fp) {
        printf("No student records found.\n");
        return;
    }

    printf("\n=====******* STUDENT LIST *******=====\n");
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

/* ---------------------- SEARCH STUDENT ------------------------- */
void searchStudent() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    int r, found = 0;
    struct Student s;

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == r) {
            printf("\nRecord Found!\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");

    fclose(fp);
}

/* ---------------------- UPDATE STUDENT ------------------------- */
void updateStudent() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *tmp = fopen("temp.txt", "w");

    int r, found = 0;
    struct Student s;

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == r) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(tmp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(tmp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record Updated!\n");
    else
        printf("Record not found.\n");
}

/* ---------------------- DELETE STUDENT ------------------------- */
void deleteStudent() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *tmp = fopen("temp.txt", "w");

    int r, found = 0;
    struct Student s;

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &r);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == r) {
            found = 1;
            continue;  
        }
        fprintf(tmp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(tmp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record Deleted!\n");
    else
        printf("Record not found.\n");
}