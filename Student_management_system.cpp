#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student
{
public:
    int rollNo;
    string name;
    int age;
    float marks;

    void input()
    {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Marks: ";
        cin >> marks;
    }
};

// Check if roll number already exists
bool rollExists(int roll)
{
    ifstream file("students.txt");

    string temp;
    Student s;

    while (getline(file, temp, '|'))
    {
        s.rollNo = stoi(temp);

        getline(file, s.name, '|');
        getline(file, temp, '|');
        s.age = stoi(temp);

        getline(file, temp);
        s.marks = stof(temp);

        if (s.rollNo == roll)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Add student
void addStudent()
{
    Student s;
    s.input();

    if (rollExists(s.rollNo))
    {
        cout << "\nRoll Number already exists!\n";
        return;
    }

    ofstream file("students.txt", ios::app);

    file << s.rollNo << "|"
         << s.name << "|"
         << s.age << "|"
         << s.marks << endl;

    file.close();

    cout << "\nStudent Added Successfully!\n";
}

// Display all students
void displayStudents()
{
    ifstream file("students.txt");

    if (!file)
    {
        cout << "\nNo records found.\n";
        return;
    }

    Student s;
    string temp;

    cout << "\n-------------------------------------------\n";
    cout << "RollNo\tName\t\tAge\tMarks\n";
    cout << "-------------------------------------------\n";

    while (getline(file, temp, '|'))
    {
        s.rollNo = stoi(temp);

        getline(file, s.name, '|');

        getline(file, temp, '|');
        s.age = stoi(temp);

        getline(file, temp);
        s.marks = stof(temp);

        cout << s.rollNo << "\t"
             << s.name << "\t"
             << s.age << "\t"
             << s.marks << endl;
    }

    file.close();
}

// Search student
void searchStudent()
{
    int roll;
    bool found = false;

    cout << "Enter Roll Number: ";
    cin >> roll;

    ifstream file("students.txt");

    Student s;
    string temp;

    while (getline(file, temp, '|'))
    {
        s.rollNo = stoi(temp);

        getline(file, s.name, '|');

        getline(file, temp, '|');
        s.age = stoi(temp);

        getline(file, temp);
        s.marks = stof(temp);

        if (s.rollNo == roll)
        {
            cout << "\nStudent Found\n";
            cout << "Roll No : " << s.rollNo << endl;
            cout << "Name    : " << s.name << endl;
            cout << "Age     : " << s.age << endl;
            cout << "Marks   : " << s.marks << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nStudent Not Found.\n";
    }

    file.close();
}

// Update student
void updateStudent()
{
    int roll;
    bool found = false;

    cout << "Enter Roll Number to Update: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream tempFile("temp.txt");

    Student s;
    string temp;

    while (getline(file, temp, '|'))
    {
        s.rollNo = stoi(temp);

        getline(file, s.name, '|');

        getline(file, temp, '|');
        s.age = stoi(temp);

        getline(file, temp);
        s.marks = stof(temp);

        if (s.rollNo == roll)
        {
            cout << "\nEnter New Details\n";
            s.input();
            found = true;
        }

        tempFile << s.rollNo << "|"
                 << s.name << "|"
                 << s.age << "|"
                 << s.marks << endl;
    }

    file.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nRecord Updated Successfully.\n";
    else
        cout << "\nStudent Not Found.\n";
}

// Delete student
void deleteStudent()
{
    int roll;
    bool found = false;

    cout << "Enter Roll Number to Delete: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream tempFile("temp.txt");

    Student s;
    string temp;

    while (getline(file, temp, '|'))
    {
        s.rollNo = stoi(temp);

        getline(file, s.name, '|');

        getline(file, temp, '|');
        s.age = stoi(temp);

        getline(file, temp);
        s.marks = stof(temp);

        if (s.rollNo == roll)
        {
            found = true;
            continue;
        }

        tempFile << s.rollNo << "|"
                 << s.name << "|"
                 << s.age << "|"
                 << s.marks << endl;
    }

    file.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nRecord Deleted Successfully.\n";
    else
        cout << "\nStudent Not Found.\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n=================================\n";
        cout << "   STUDENT MANAGEMENT SYSTEM\n";
        cout << "=================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 6);

    return 0;
}
