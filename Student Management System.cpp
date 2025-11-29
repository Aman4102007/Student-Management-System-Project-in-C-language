#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_SEMESTERS 8

struct Student {
    int Sapid;
    int roll_no;
    char name[50];
    char phone[15];
    char email[50];
    int year;
    int semester;
    float sgpa[MAX_SEMESTERS];
    float cgpa;
};

struct Student students[MAX_STUDENTS];
int numberofstudents = 0;


float calculatecgpa(struct Student stud)
{
    float sum = 0.0;

    for (int i = 0; i < stud.semester; i++)
    {
        sum += stud.sgpa[i];
    }

    if (stud.semester == 0) return 0;

    return sum / stud.semester;
}


void add_students()
{
    if (numberofstudents >= MAX_STUDENTS)
    {
        printf("Maximum number of students reached.\n");
        return;
    }

    struct Student stud;

    printf("Enter SAPID: ");
    scanf("%d", &stud.Sapid);

    printf("Enter Roll Number: ");
    scanf("%d", &stud.roll_no);

    printf("Enter Name: ");
    scanf("%s", stud.name);

    printf("Enter Phone Number: ");
    scanf("%s", stud.phone);

    printf("Enter Email: ");
    scanf("%s", stud.email);

    printf("Enter Year (1 to 4): ");
    scanf("%d", &stud.year);

    printf("Enter Current Semester (1 to 8):");
    scanf("%d", &stud.semester);

    printf("Enter SGPA for %d semesters:\n", stud.semester);
    for (int i = 0; i < stud.semester; i++)
    {
        printf("Semester %d SGPA: ", i + 1);
        scanf("%f", &stud.sgpa[i]);
    }

    stud.cgpa = calculatecgpa(stud);

    students[numberofstudents++] = stud;

    printf("Student added successfully.\n");
}


void search_student()
{
    int Sapid;
    printf("Enter SAPID to search: ");
    scanf("%d", &Sapid);

    for (int i = 0; i < numberofstudents; i++)
    {
        if (students[i].Sapid == Sapid)
        {
            printf("\nStudent Found ");
            printf("SAPID: %d\n", students[i].Sapid);
            printf("Roll No: %d\n", students[i].roll_no);
            printf("Name: %s\n", students[i].name);
            printf("Phone: %s\n", students[i].phone);
            printf("Email: %s\n", students[i].email);
            printf("Year: %d\n", students[i].year);
            printf("Semester: %d\n", students[i].semester);

            printf("SGPA: ");
            for (int j = 0; j < students[i].semester; j++)
                printf("%.2f ", students[i].sgpa[j]);

            printf("\nCGPA: %.2f\n", calculatecgpa(students[i]));
            return;
        }
    }
    printf("Student not found.\n");
}

void display_cgpa_all()
{
    if (numberofstudents == 0)
    {
        printf("No students available.\n");
        return;
    }

    for (int i = 0; i < numberofstudents; i++)
    {
        printf("SAPID: %d | Name: %s | CGPA: %.2f\n",
            students[i].Sapid,
            students[i].name,
            calculatecgpa(students[i]));
    }
}


void average_cgpa_per_year()
{
    float yearsum[5] = { 0 };
    int yearcount[5] = { 0 };

    for (int i = 0; i < numberofstudents; i++)
    {
        int y = students[i].year;
        yearsum[y] += calculatecgpa(students[i]);
        yearcount[y]++;
    }

    for (int y = 1; y <= 4; y++)
    {
        if (yearcount[y] > 0)
            printf("Year %d: Average CGPA = %.2f\n", y, yearsum[y] / yearcount[y]);
        else
            printf("Year %d: No Students.\n", y);
    }
}


void display_all_students()
{
    for (int i = 0; i < numberofstudents; i++)
    {
        printf("SAPID: %d | Roll: %d | Name: %s | Phone: %s | Email: %s | Year: %d | Sem: %d | CGPA: %.2f\n",
            students[i].Sapid, students[i].roll_no, students[i].name,
            students[i].phone, students[i].email, students[i].year,
            students[i].semester, calculatecgpa(students[i]));
    }
}


void delete_student()
{
    int Sapid;
    printf("Enter SAPID to delete: ");
    scanf("%d", &Sapid);

    for (int i = 0; i < numberofstudents; i++)
    {
        if (students[i].Sapid == Sapid)
        {
            for (int j = i; j < numberofstudents - 1; j++)
            {
                students[j] = students[j + 1];
            }

            numberofstudents--;
            printf("Student deleted successfully.\n");
            return;
        }
    }
    printf("Student not found.\n");
}


void display_sorted_by_Sapid()
{
    struct Student temp;

    for (int i = 0; i < numberofstudents - 1; i++)
    {
        for (int j = 0; j < numberofstudents - i - 1; j++)
        {
            if (students[j].Sapid > students[j + 1].Sapid)
            {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    display_all_students();
}


void display_sorted_by_name()
{
    struct Student temp;

    for (int i = 0; i < numberofstudents - 1; i++)
    {
        for (int j = 0; j < numberofstudents - i - 1; j++)
        {
            if (strcmp(students[j].name, students[j + 1].name) > 0)
            {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    display_all_students();
}


int main()
{
    int choice;

    while (1)
    {
        printf("\nSTUDENT MANAGEMENT SYSTEM \n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Display CGPA for All Students\n");
        printf("4. Average CGPA Per Year\n");
        printf("5. Display All Students\n");
        printf("6. Delete Student\n");
        printf("7. Sort by SAPID\n");
        printf("8. Sort by Name\n");
        printf("9. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1: add_students(); break;
        case 2: search_student(); break;
        case 3: display_cgpa_all(); break;
        case 4: average_cgpa_per_year(); break;
        case 5: display_all_students(); break;
        case 6: delete_student(); break;
        case 7: display_sorted_by_Sapid(); break;
        case 8: display_sorted_by_name(); break;
        case 9: exit(0);
        default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
