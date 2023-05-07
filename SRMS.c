
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void add_student();
void search_student();
void update_student();
void delete_student();

// Student structure
struct student {
    char name[50];
    int roll_number;
    int marks;
    int attendance;
};

int main() {
    int choice;

    while (1) {
        // Display menu
        printf("\nStudent Record Management System\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                search_student();
                break;
            case 3:
                update_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void add_student() {
    struct student s;
    FILE *fp;

    // Open file for writing
    fp = fopen("students.dat", "ab");

    // Get student details from user
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter roll number: ");
    scanf("%d", &s.roll_number);
    printf("Enter marks: ");
    scanf("%d", &s.marks);
    printf("Enter attendance: ");
    scanf("%d", &s.attendance);

    // Write student details to file
    fwrite(&s, sizeof(struct student), 1, fp);

    // Close file
    fclose(fp);

    printf("Student added successfully!\n");
}

void search_student() {
    struct student s;
    FILE *fp;
    int roll_number;
    char name[50];
    int found = 0;

    // Open file for reading
    fp = fopen("students.dat", "rb");

    // Get search criteria from user
    printf("Enter roll number or name of student to search: ");
    scanf("%s", name);

    // Search for student in file
    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (strcmp(s.name, name) == 0 || s.roll_number == atoi(name)) {
            printf("Name: %s\n", s.name);
            printf("Roll Number: %d\n", s.roll_number);
            printf("Marks: %d\n", s.marks);
            printf("Attendance: %d\n", s.attendance);
            found = 1;
            break;
        }
    }

    // Close file
    fclose(fp);

    if (!found) {
        printf("Student not found!\n");
    }
}

void update_student() {
    struct student s;
    FILE *fp;
    int roll_number;
    int found = 0;

    // Open file for reading and writing
    fp = fopen("students.dat", "rb+");

    // Get roll number of student to update
    printf("Enter roll number of student to update: ");
    scanf("%d", &roll_number);

    // Search for student in file
    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_number == roll_number) {
            // Get updated student details from user
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new marks: ");
            scanf("%d", &s.marks);
            printf("Enter new attendance: ");
            scanf("%d", &s.attendance);

            // Move file pointer to beginning of current record
            fseek(fp, -sizeof(struct student), SEEK_CUR);

            // Write updated student details to file
            fwrite(&s, sizeof(struct student), 1, fp);

            found = 1;
            break;
        }
    }

    // Close file
    fclose(fp);

    if (!found) {
        printf("Student not found!\n");
    } else {
        printf("Student details updated successfully!\n");
    }
}

void delete_student() {
    struct student s;
    FILE *fp, *temp;
    int roll_number;
    int found = 0;

    // Open file for reading and writing
    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    // Get roll number of student to delete
    printf("Enter roll number of student to delete: ");
    scanf("%d", &roll_number);

    // Copy all records except the one to be deleted to temporary file
    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_number != roll_number) {
            fwrite(&s, sizeof(struct student), 1, temp);
        } else {
            found = 1;
        }
    }

    // Close files
    fclose(fp);
    fclose(temp);

    // Rename temporary file to original file
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (!found) {
        printf("Student not found!\n");
    } else {
        printf("Student deleted successfully!\n");
    }
}
