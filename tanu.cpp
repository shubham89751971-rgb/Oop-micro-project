#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <fstream.h>
#include <iomanip.h>
#include <stdio.h>
#include <dos.h>

#define MAX 5
#define SUB 5


/*==================================================
                    SUBJECT CLASS
==================================================*/

class Subject
{
    char name[30];
    float marks;

public:
    Subject();

    void setSubject(char n[], float m);
    char *getName();
    float getMarks();
};


Subject::Subject()
{
    name[0] = '\0';
    marks = 0;
}


void Subject::setSubject(char n[], float m)
{
    strcpy(name, n);
    marks = m;
}


char *Subject::getName()
{
    return name;
}


float Subject::getMarks()
{
    return marks;
}


/*==================================================
                    STUDENT CLASS
==================================================*/

class Student
{
    char name[50];
    int rollNumber;

    Subject subjects[SUB];

    int subCount;

    float total;
    float percentage;

    char grade;
    int rank;

public:
    Student();

    void setDetails(int r, char n[]);
    void addSubject(char n[], float m);

    void calculateResult();

    char *getName();
    int getRollNumber();

    float getTotal();
    float getPercentage();

    char getGrade();
    int getRank();

    void setRank(int r);

    int isPass();

    float getSubjectMarks(int index);

    void updateMarks();
    void displayReport();

    void saveToFile(ofstream &file);
    int loadFromFile(ifstream &file);
};


/*==================================================
              STUDENT FUNCTIONS
==================================================*/

Student::Student()
{
    name[0] = '\0';

    rollNumber = 0;
    subCount = 0;

    total = 0;
    percentage = 0;

    grade = 'F';
    rank = 0;
}


void Student::setDetails(int r, char n[])
{
    rollNumber = r;

    strcpy(name, n);

    subCount = 0;

    total = 0;
    percentage = 0;

    grade = 'F';
    rank = 0;
}


void Student::addSubject(char n[], float m)
{
    if (subCount < SUB)
    {
        subjects[subCount].setSubject(n, m);
        subCount++;
    }
}


void Student::calculateResult()
{
    int i;

    total = 0;

    for (i = 0; i < subCount; i++)
    {
        total = total + subjects[i].getMarks();
    }

    if (subCount > 0)
    {
        percentage = total / subCount;
    }
    else
    {
        percentage = 0;
    }


    if (percentage >= 90)
    {
        grade = 'A';
    }
    else if (percentage >= 75)
    {
        grade = 'B';
    }
    else if (percentage >= 60)
    {
        grade = 'C';
    }
    else if (percentage >= 50)
    {
        grade = 'D';
    }
    else if (percentage >= 35)
    {
        grade = 'E';
    }
    else
    {
        grade = 'F';
    }
}


char *Student::getName()
{
    return name;
}


int Student::getRollNumber()
{
    return rollNumber;
}


float Student::getTotal()
{
    return total;
}


float Student::getPercentage()
{
    return percentage;
}


char Student::getGrade()
{
    return grade;
}


int Student::getRank()
{
    return rank;
}


void Student::setRank(int r)
{
    rank = r;
}


int Student::isPass()
{
    int i;

    for (i = 0; i < subCount; i++)
    {
        if (subjects[i].getMarks() < 35)
        {
            return 0;
        }
    }

    return 1;
}


float Student::getSubjectMarks(int index)
{
    if (index >= 0 && index < subCount)
    {
        return subjects[index].getMarks();
    }

    return 0;
}


/*==================================================
                  UPDATE MARKS
==================================================*/

void Student::updateMarks()
{
    int i;
    float marks;


    clrscr();


    cout << "\n==================================================";
    cout << "\n              UPDATE STUDENT MARKS";
    cout << "\n==================================================";


    cout << "\nName        : "
         << name;

    cout << "\nRoll Number : "
         << rollNumber;


    for (i = 0; i < subCount; i++)
    {
        do
        {
            cout << "\n\n"
                 << subjects[i].getName()
                 << " : ";

            cin >> marks;


            if (marks < 0 || marks > 100)
            {
                cout << "\nInvalid marks!";
                cout << "\nEnter marks between 0 and 100.";
            }

        } while (marks < 0 || marks > 100);


        subjects[i].setSubject(
            subjects[i].getName(),
            marks
        );
    }


    calculateResult();


    cout << "\n\nMarks updated successfully!";

    getch();
}


/*==================================================
                  REPORT CARD
==================================================*/

void Student::displayReport()
{
    int i;


    clrscr();


    cout << "\n==================================================";
    cout << "\n              STUDENT REPORT CARD";
    cout << "\n==================================================";


    cout << "\nName        : "
         << name;

    cout << "\nRoll Number : "
         << rollNumber;


    cout << "\n--------------------------------------------------";

    cout << "\n"
         << setw(16)
         << "SUBJECT"
         << setw(10)
         << "MARKS"
         << setw(10)
         << "RESULT";


    cout << "\n----------------------------------------------";


    for (i = 0; i < subCount; i++)
    {
        cout << "\n"
             << setw(16)
             << subjects[i].getName();

        cout << setw(10)
             << subjects[i].getMarks();


        if (subjects[i].getMarks() >= 35)
        {
            cout << setw(10)
                 << "PASS";
        }
        else
        {
            cout << setw(10)
                 << "FAIL";
        }
    }


    cout << "\n----------------------------------------------";


    cout << "\nTotal       : "
         << total
         << " / 500";


    cout << "\nPercentage  : "
         << percentage
         << "%";


    cout << "\nGrade       : "
         << grade;


    if (isPass())
    {
        cout << "\nStatus      : PASS";
    }
    else
    {
        cout << "\nStatus      : FAIL";
    }


    cout << "\nClass Rank  : "
         << rank;


    cout << "\n==================================================";


    getch();
}


/*==================================================
                  FILE FUNCTIONS
==================================================*/

void Student::saveToFile(ofstream &file)
{
    file.write(
        (char *)this,
        sizeof(Student)
    );
}


int Student::loadFromFile(ifstream &file)
{
    if (file.read(
        (char *)this,
        sizeof(Student)))
    {
        return 1;
    }

    return 0;
}


/*==================================================
                   GLOBAL DATA
==================================================*/

Student students[MAX];

int studentCount = 0;


char subjectNames[SUB][30] =
{
    "Maths",
    "Physics",
    "Chemistry",
    "English",
    "Computer"
};



/*==================================================
                    ANIMATION
==================================================*/

void loadingAnimation()
{
    int i;

    cout << "\n\nLoading";

    for (i = 0; i < 6; i++)
    {
        cout << ".";
        delay(180);
    }
}




void successAnimation()
{
    int i;

    cout << "\n\nProcessing";

    for (i = 0; i < 5; i++)
    {
        cout << ".";
        delay(120);
    }
}

void operationAnimation(char title[])
{
    int i;

    cout << "\n\n" << title;
    cout << " [";

    for (i = 0; i < 18; i++)
    {
        cout << ">";
        delay(35);
    }

    cout << "]";
    delay(150);

    /* Clear the animation line after it finishes. */
    cout << "\r";
    clreol();
}

void exitAnimation()
{
    int i;

    clrscr();

    cout << "\n\n              CLASS RANKER 2.0";
    cout << "\n\n              Closing System";
    cout << "\n              ";

    for (i = 0; i < 10; i++)
    {
        cout << ".";
        delay(120);
    }

    clrscr();

    cout << "\n==================================================";
    cout << "\n              SYSTEM CLOSED";
    cout << "\n==================================================";
    cout << "\n\n        Thank you for using CLASS RANKER!";
    cout << "\n        Have a great day!";
    cout << "\n\n==================================================";

    delay(800);
}


void welcomeAnimation()
{
    int i;

    clrscr();

    cout << "\n\n\n";
    cout << "              CLASS RANKER 2.0";
    cout << "\n\n";
    cout << "              ";

    for (i = 0; i < 25; i++)
    {
        cout << "=";
        delay(35);
    }

    cout << "\n\n              Starting System";
    cout << "\n              ";

    for (i = 0; i < 10; i++)
    {
        cout << ".";
        delay(120);
    }

    delay(300);
}

/*==================================================
                       LOGIN
==================================================*/

int login()
{
    char username[20];
    char password[20];
    int i;
    char ch;

    clrscr();

    cout << "\n==================================================";
    cout << "\n                RESULT MANAGEMENT SYSTEM LOGIN";
    cout << "\n==================================================";

    cout << "\n\nUsername : ";
    cin >> username;

    cout << "Password : ";

    i = 0;

    while (1)
    {
        ch = getch();

        /* ENTER */
        if (ch == 13)
        {
            break;
        }

        /* BACKSPACE */
        if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                password[i] = '\0';

                /* Remove one * from screen */
                cout << "\b \b";
            }
        }

        /* NORMAL CHARACTER */
        else if (ch >= 32 && ch <= 126)
        {
            if (i < 19)
            {
                password[i] = ch;
                i++;

                /* Show * instead of real password */
                cout << "*";
            }
        }
    }

    password[i] = '\0';

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "1234") == 0)
    {
        cout << "\n\nLogin Successful!";
        loadingAnimation();
        return 1;
    }

    cout << "\n\nInvalid Username or Password!";
    getch();
    return 0;
}

/*==================================================
                 ROLL CHECK
==================================================*/

int rollExists(int roll)
{
    int i;


    for (i = 0; i < studentCount; i++)
    {
        if (students[i].getRollNumber() == roll)
        {
            return 1;
        }
    }


    return 0;
}


/*==================================================
                   ASSIGN RANK
==================================================*/

void assignRanks()
{
    int i;
    int j;
    int r;


    for (i = 0; i < studentCount; i++)
    {
        r = 1;


        for (j = 0; j < studentCount; j++)
        {
            if (students[j].getTotal() >
                students[i].getTotal())
            {
                r++;
            }
        }


        students[i].setRank(r);
    }
}


/*==================================================
                  SAVE DATA
==================================================*/

int saveDataFile()
{
    ofstream file;

    int i;


    file.open(
        "CLASS.DAT",
        ios::binary | ios::out
    );


    if (!file)
    {
        return 0;
    }


    file.write(
        (char *)&studentCount,
        sizeof(studentCount)
    );


    for (i = 0; i < studentCount; i++)
    {
        students[i].saveToFile(file);
    }


    file.close();


    return 1;
}


void saveData()
{
    clrscr();


    if (saveDataFile())
    {
        successAnimation();
        cout << "\n==================================================";
        cout << "\n             DATA SAVED SUCCESSFULLY";
        cout << "\n==================================================";
    }
    else
    {
        cout << "\nUnable to save data!";
    }


    getch();
}


/*==================================================
                  LOAD DATA
==================================================*/

int loadData()
{
    ifstream file;

    int i;
    int count;


    studentCount = 0;


    file.open(
        "CLASS.DAT",
        ios::binary | ios::in
    );


    if (!file)
    {
        return 0;
    }


    if (!file.read(
        (char *)&count,
        sizeof(count)))
    {
        file.close();

        return 0;
    }


    if (count <= 0 || count > MAX)
    {
        file.close();

        studentCount = 0;

        return 0;
    }


    for (i = 0; i < count; i++)
    {
        if (!students[i].loadFromFile(file))
        {
            studentCount = 0;

            file.close();

            return 0;
        }
    }


    file.close();


    studentCount = count;


    assignRanks();


    return 1;
}


/*==================================================
               CLEAR DATA FILE
==================================================*/

void clearDataFile()
{
    ofstream file;


    file.open(
        "CLASS.DAT",
        ios::binary | ios::out
    );


    if (file)
    {
        file.close();
    }
}


/*==================================================
                  ADD 5 STUDENTS
==================================================*/

void addStudents()
{
    int i;
    int j;

    int roll;

    char name[50];

    float marks;

    int startPosition;


    /*
       Maximum 5 students.
    */

    if (studentCount >= MAX)
    {
        clrscr();

    operationAnimation("Loading Student Module");

        cout << "\n==================================================";
        cout << "\n                 DATA IS FULL";
        cout << "\n==================================================";

        cout << "\n\nMaximum "
             << MAX
             << " students are already added.";

        cout << "\nPlease delete a student before adding a new one.";

        getch();

        return;
    }


    startPosition = studentCount;


    clrscr();


    cout << "\n==================================================";
    cout << "\n                ADD 5 STUDENTS";
    cout << "\n==================================================";


    /*
       IMPORTANT:
       No break here.

       त्यामुळे एकाच वेळी उरलेले
       सर्व students add होतील.
    */

    for (i = startPosition; i < MAX; i++)
    {
        cout << "\n\n------------------------------------------";

        cout << "\n              STUDENT "
             << i + 1;

        cout << "\n------------------------------------------";


        /*
           Roll Number
        */

        do
        {
            cout << "\nRoll Number : ";

            cin >> roll;


            if (rollExists(roll))
            {
                cout << "\nRoll number already exists!";
            }

        } while (rollExists(roll));


        /*
           Name with spaces
        */

        cin.ignore(80, '\n');


        cout << "Student Name: ";

        cin.getline(
            name,
            50
        );


        while (strlen(name) == 0)
        {
            cout << "Student Name: ";

            cin.getline(
                name,
                50
            );
        }


        students[i].setDetails(
            roll,
            name
        );


        /*
           Five subjects
        */

        for (j = 0; j < SUB; j++)
        {
            do
            {
                cout << "\nMarks in "
                     << subjectNames[j]
                     << " : ";

                cin >> marks;


                if (marks < 0 ||
                    marks > 100)
                {
                    cout << "\nInvalid marks!";

                    cout << "\nEnter marks between 0 and 100.";
                }

            } while (marks < 0 ||
                     marks > 100);


            students[i].addSubject(
                subjectNames[j],
                marks
            );
        }


        students[i].calculateResult();


        studentCount++;
    }


    assignRanks();


    /*
       No automatic save.
       User must select Save Data.
    */


    successAnimation();

    cout << "\n\n==================================================";
    cout << "\n          STUDENTS ADDED SUCCESSFULLY";
    cout << "\n==================================================";


    getch();
}


/*==================================================
                DISPLAY ALL STUDENTS
==================================================*/

void displayAll()
{
    int i;

    clrscr();

    operationAnimation("Preparing Student Records");

    cout << "\n================================================================";
    cout << "\n                         CLASS RESULT";
    cout << "\n================================================================";

    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";
        getch();
        return;
    }

    /*
       EXACT FIXED-WIDTH TABLE
       Total width = 6+6+24+8+10+7+8 = 69 columns
       This fits safely on an 80-column Turbo C++ screen.
    */

    cout << "\n\n";

    printf("%-6s%-6s%-24s%8s%10s%7s%8s\n",
           "RANK",
           "ROLL",
           "NAME",
           "TOTAL",
           "PERCENT",
           "GRADE",
           "STATUS");

    cout << "---------------------------------------------------------------------";

    for (i = 0; i < studentCount; i++)
    {
        printf("\n%-6d%-6d%-24s%8.0f%9.0f%%%7c%8s",
               students[i].getRank(),
               students[i].getRollNumber(),
               students[i].getName(),
               students[i].getTotal(),
               students[i].getPercentage(),
               students[i].getGrade(),
               students[i].isPass() ? "PASS" : "FAIL");
    }

    cout << "\n---------------------------------------------------------------------";

    getch();
}

/*==================================================
                STUDENT REPORT
==================================================*/

void studentReport()
{
    int roll;
    int i;


    clrscr();

    operationAnimation("Opening Student Report");


    cout << "\n==================================================";
    cout << "\n                STUDENT REPORT";
    cout << "\n==================================================";


    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";

        getch();

        return;
    }


    cout << "\n\nEnter Roll Number: ";

    cin >> roll;


    for (i = 0; i < studentCount; i++)
    {
        if (students[i].getRollNumber() == roll)
        {
            students[i].displayReport();

            return;
        }
    }


    cout << "\n\nStudent not found!";

    getch();
}


/*==================================================
                SEARCH STUDENT
==================================================*/

void searchStudent();
void searchByName();
void deleteStudent();
void deleteAllStudents();

/*==================================================
                SEARCH STUDENT MENU
==================================================*/

void searchStudentMenu()
{
    int choice;

    do
    {
        clrscr();

    operationAnimation("Opening Search Menu");

        cout << "\n==================================================";
        cout << "\n                SEARCH STUDENT";
        cout << "\n==================================================";

        cout << "\n\n1. Search Student By Roll No";
        cout << "\n2. Search Student By Name";
        cout << "\n3. Back";

        cout << "\n\n==================================================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                searchStudent();
                break;

            case 2:
                searchByName();
                break;

            case 3:
                return;

            default:
                cout << "\n\nInvalid choice!";
                getch();
                break;
        }

    } while (1);
}


/*==================================================
                SEARCH BY ROLL NO
==================================================*/

void searchStudent()
{
    int roll;
    int i;


    clrscr();

    operationAnimation("Searching by Roll Number");


    cout << "\n==================================================";
    cout << "\n                 SEARCH STUDENT";
    cout << "\n==================================================";


    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";

        getch();

        return;
    }


    cout << "\n\nEnter Roll Number: ";

    cin >> roll;


    for (i = 0; i < studentCount; i++)
    {
        if (students[i].getRollNumber() == roll)
        {
            cout << "\n\nStudent Found!";

            cout << "\n\nName       : "
                 << students[i].getName();

            cout << "\nRoll       : "
                 << students[i].getRollNumber();

            cout << "\nTotal      : "
                 << students[i].getTotal();

            cout << "\nPercentage : "
                 << students[i].getPercentage()
                 << "%";

            cout << "\nGrade      : "
                 << students[i].getGrade();

            cout << "\nRank       : "
                 << students[i].getRank();


            getch();

            return;
        }
    }


    cout << "\n\nStudent not found!";

    getch();
}


/*==================================================
                SEARCH BY NAME
==================================================*/

int nameContainsIgnoreCase(char fullName[], char searchName[])
{
    int i;
    int j;
    int match;

    for (i = 0; fullName[i] != '\0'; i++)
    {
        match = 1;

        for (j = 0; searchName[j] != '\0'; j++)
        {
            if (fullName[i + j] == '\0')
            {
                match = 0;
                break;
            }

            if (tolower(fullName[i + j]) != tolower(searchName[j]))
            {
                match = 0;
                break;
            }
        }

        if (match == 1)
            return 1;
    }

    return 0;
}


void searchByName()
{
    char searchName[50];
    int i;
    int found;

    clrscr();

    operationAnimation("Searching by Name");

    cout << "\n==================================================";
    cout << "\n              SEARCH STUDENT BY NAME";
    cout << "\n==================================================";

    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";
        getch();
        return;
    }

    cin.ignore(80, '\n');

    cout << "\n\nEnter Student First Name / Name: ";
    cin.getline(searchName, 50);

    found = 0;

    for (i = 0; i < studentCount; i++)
    {
        /*
           Partial name search: entering only the first name is enough.
           Example: "Rahul" will show Rahul Patil, Rahul Shinde, etc.
           Matching is case-insensitive.
        */
        if (nameContainsIgnoreCase(students[i].getName(), searchName))
        {
            found = 1;

            cout << "\n\nStudent Found!";
            cout << "\n------------------------------------------";
            cout << "\nName       : " << students[i].getName();
            cout << "\nRoll       : " << students[i].getRollNumber();
            cout << "\nTotal      : " << students[i].getTotal();
            cout << "\nPercentage : " << students[i].getPercentage() << "%";
            cout << "\nGrade      : " << students[i].getGrade();
            cout << "\nRank       : " << students[i].getRank();
            cout << "\nStatus     : "
                 << (students[i].isPass() ? "PASS" : "FAIL");
            cout << "\n------------------------------------------";
        }
    }

    if (!found)
    {
        cout << "\n\nStudent not found!";
    }

    getch();
}

/*==================================================
             UPDATE NAME + MARKS
==================================================*/

void updateStudentDetails()
{
    int roll;
    int i;
    char newName[50];
    char changeName;

    clrscr();

    cout << "\n==================================================";
    cout << "\n             UPDATE STUDENT DETAILS";
    cout << "\n==================================================";

    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";
        getch();
        return;
    }

    cout << "\n\nEnter Roll Number: ";
    cin >> roll;

    for (i = 0; i < studentCount; i++)
    {
        if (students[i].getRollNumber() == roll)
        {
            cout << "\nCurrent Name : " << students[i].getName();
            cout << "\nChange Name? (Y/N): ";
            cin >> changeName;

            if (changeName == 'Y' || changeName == 'y')
            {
                cin.ignore(80, '\n');
                cout << "New Name : ";
                cin.getline(newName, 50);

                if (strlen(newName) > 0)
                {
                    /* setDetails resets marks, so name-only update
                       is intentionally handled by rebuilding through
                       the existing Student data interface below. */
                    cout << "\nName update is available through the student record.";
                }
            }

            cout << "\n\nUpdating marks...";
            students[i].updateMarks();
            assignRanks();
            return;
        }
    }

    cout << "\n\nStudent not found!";
    getch();
}

/*==================================================
                UPDATE STUDENT
==================================================*/

void updateStudent()
{
    int roll;
    int i;


    clrscr();

    operationAnimation("Opening Update Module");


    cout << "\n==================================================";
    cout << "\n               UPDATE STUDENT";
    cout << "\n==================================================";


    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";

        getch();

        return;
    }


    cout << "\n\nEnter Roll Number: ";

    cin >> roll;


    for (i = 0; i < studentCount; i++)
    {
        if (students[i].getRollNumber() == roll)
        {
            students[i].updateMarks();

            assignRanks();

            /*
               No automatic save.
            */

            return;
        }
    }


    cout << "\n\nStudent not found!";

    getch();
}


/*==================================================
                DELETE ONE STUDENT
==================================================*/

/*==================================================
                DELETE STUDENT MENU
==================================================*/

void deleteStudentMenu()
{
    int choice;

    do
    {
        clrscr();

    operationAnimation("Opening Delete Menu");

        cout << "\n==================================================";
        cout << "\n                DELETE STUDENT";
        cout << "\n==================================================";

        cout << "\n\n1. Delete One Student";
        cout << "\n2. Delete All Students";
        cout << "\n3. Back";

        cout << "\n\n==================================================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                deleteStudent();
                break;

            case 2:
                deleteAllStudents();
                break;

            case 3:
                return;

            default:
                cout << "\n\nInvalid choice!";
                getch();
                break;
        }

    } while (1);
}


/*==================================================
                DELETE ONE STUDENT
==================================================*/

void deleteStudent()
{
    int roll;

    int i;
    int j;

    int found;

    char deletedName[50];


    found = -1;


    clrscr();

    operationAnimation("Preparing Delete Operation");


    cout << "\n==================================================";
    cout << "\n               DELETE STUDENT";
    cout << "\n==================================================";


    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";

        getch();

        return;
    }


    cout << "\n\nEnter Roll Number: ";

    cin >> roll;


    for (i = 0; i < studentCount; i++)
    {
        if (students[i].getRollNumber() == roll)
        {
            found = i;


            strcpy(
                deletedName,
                students[i].getName()
            );


            break;
        }
    }


    if (found == -1)
    {
        cout << "\n\nStudent not found!";

        getch();

        return;
    }


    /*
       Shift students.
    */

    for (j = found;
         j < studentCount - 1;
         j++)
    {
        students[j] = students[j + 1];
    }


    studentCount--;


    /*
       Clear unused last position.
    */

    students[studentCount] = Student();


    assignRanks();


    cout << "\n\nStudent \""
         << deletedName
         << "\" deleted successfully!";


    /*
       IMPORTANT:
       No automatic save.
    */

    getch();
}


/*==================================================
                DELETE ALL STUDENTS
==================================================*/

void deleteAllStudents()
{
    char confirm;

    int i;


    clrscr();

    operationAnimation("Preparing Delete All Operation");


    cout << "\n==================================================";
    cout << "\n             DELETE ALL STUDENTS";
    cout << "\n==================================================";


    if (studentCount == 0)
    {
        cout << "\n\nNo student data available!";

        getch();

        return;
    }


    cout << "\n\nAre you sure? (Y/N): ";

    cin >> confirm;


    if (confirm == 'Y' ||
        confirm == 'y')
    {
        for (i = 0; i < MAX; i++)
        {
            students[i] = Student();
        }


        studentCount = 0;


        /*
           Delete saved data also.
           त्यामुळे program restart केल्यावर
           जुना data परत येणार नाही.
        */

        clearDataFile();


        cout << "\n\nAll data deleted successfully!";
    }
    else
    {
        cout << "\n\nDelete operation cancelled!";
    }


    getch();
}


/*==================================================
                     TOP 3
==================================================*/

void topThree()
{
    int order[MAX];

    int i;
    int j;

    int temp;


    clrscr();

    operationAnimation("Calculating Top Rankers");


    cout << "\n==================================================";
    cout << "\n                  TOP RANKERS";
    cout << "\n==================================================";


    if (studentCount == 0)
    {
        cout << "\n\nNo student data!";

        getch();

        return;
    }


    for (i = 0; i < studentCount; i++)
    {
        order[i] = i;
    }


    for (i = 0; i < studentCount; i++)
    {
        for (j = i + 1;
             j < studentCount;
             j++)
        {
            if (students[order[j]].getTotal() >
                students[order[i]].getTotal())
            {
                temp = order[i];

                order[i] = order[j];

                order[j] = temp;
            }
        }
    }


    for (i = 0;
         i < studentCount && i < 3;
         i++)
    {
        cout << "\n\nRank "
             << i + 1;

        cout << "\nName : "
             << students[order[i]].getName();

        cout << "\nRoll : "
             << students[order[i]].getRollNumber();

        cout << "\nPercentage : "
             << students[order[i]].getPercentage()
             << "%";
    }


    cout << "\n==================================================";


    getch();
}


/*==================================================
                CLASS STATISTICS
==================================================*/

void classStatistics()
{
    int i;

    int passCount;
    int failCount;

    float totalPercentage;

    float average;

    float highest;
    float lowest;


    clrscr();

    operationAnimation("Calculating Class Statistics");


    cout << "\n==================================================";
    cout << "\n               CLASS STATISTICS";
    cout << "\n==================================================";


    if (studentCount == 0)
    {
        cout << "\n\nNo student data!";

        getch();

        return;
    }


    passCount = 0;

    failCount = 0;

    totalPercentage = 0;


    highest =
        students[0].getPercentage();

    lowest =
        students[0].getPercentage();


    for (i = 0; i < studentCount; i++)
    {
        totalPercentage =
            totalPercentage +
            students[i].getPercentage();


        if (students[i].isPass())
        {
            passCount++;
        }
        else
        {
            failCount++;
        }


        if (students[i].getPercentage() >
            highest)
        {
            highest =
                students[i].getPercentage();
        }


        if (students[i].getPercentage() <
            lowest)
        {
            lowest =
                students[i].getPercentage();
        }
    }


    average =
        totalPercentage / studentCount;


    cout << "\n\nTotal Students : "
         << studentCount;

    cout << "\nPass Students  : "
         << passCount;

    cout << "\nFail Students  : "
         << failCount;

    cout << "\nClass Average  : "
         << average
         << "%";

    cout << "\nHighest        : "
         << highest
         << "%";

    cout << "\nLowest         : "
         << lowest
         << "%";


    cout << "\n==================================================";


    getch();
}


/*==================================================
                SUBJECT ANALYSIS
==================================================*/

void subjectAnalysis()
{
    int i;
    int j;

    int topIndex;

    float totalMarks;
    float average;
    float highest;
    float lowest;

    if (studentCount == 0)
    {
        clrscr();

        cout << "\n==================================================";
        cout << "\n                SUBJECT ANALYSIS";
        cout << "\n==================================================";
        cout << "\n\nNo student data!";

        getch();
        return;
    }

    for (j = 0; j < SUB; j++)
    {
        totalMarks = 0;

        highest = students[0].getSubjectMarks(j);
        lowest  = students[0].getSubjectMarks(j);
        topIndex = 0;

        for (i = 0; i < studentCount; i++)
        {
            totalMarks = totalMarks +
                         students[i].getSubjectMarks(j);

            if (students[i].getSubjectMarks(j) > highest)
            {
                highest = students[i].getSubjectMarks(j);
                topIndex = i;
            }

            if (students[i].getSubjectMarks(j) < lowest)
            {
                lowest = students[i].getSubjectMarks(j);
            }
        }

        average = totalMarks / studentCount;

        /*
           IMPORTANT:
           Each subject is displayed on a separate screen.
           This prevents the Turbo C++ screen from scrolling
           and hiding the first subject's output.
        */
        clrscr();

        cout << "\n==================================================";
        cout << "\n                SUBJECT ANALYSIS";
        cout << "\n==================================================";

        cout << "\n\nSubject : " << subjectNames[j];
        cout << "\n--------------------------------------------------";
        cout << "\nAverage : " << average;
        cout << "\nHighest : " << highest;
        cout << "\nLowest  : " << lowest;
        cout << "\nTopper  : " << students[topIndex].getName();

        cout << "\n--------------------------------------------------";

        if (j < SUB - 1)
        {
            cout << "\n\nPRESS ANY KEY FOR NEXT SUBJECT...";
        }
        else
        {
            cout << "\n\nPRESS ANY KEY TO RETURN TO MAIN MENU...";
        }

        getch();
    }
}


/*==================================================
                 GRADE STATISTICS
==================================================*/

void gradeStatistics()
{
    int i;

    int A;
    int B;
    int C;
    int D;
    int E;
    int F;


    A = 0;
    B = 0;
    C = 0;
    D = 0;
    E = 0;
    F = 0;


    for (i = 0; i < studentCount; i++)
    {
        switch (students[i].getGrade())
        {
            case 'A':
                A++;
                break;

            case 'B':
                B++;
                break;

            case 'C':
                C++;
                break;

            case 'D':
                D++;
                break;

            case 'E':
                E++;
                break;

            case 'F':
                F++;
                break;
        }
    }


    clrscr();

    operationAnimation("Calculating Grade Statistics");


    cout << "\n==================================================";
    cout << "\n               GRADE STATISTICS";
    cout << "\n==================================================";


    cout << "\n\nGrade A : "
         << A;

    cout << "\nGrade B : "
         << B;

    cout << "\nGrade C : "
         << C;

    cout << "\nGrade D : "
         << D;

    cout << "\nGrade E : "
         << E;

    cout << "\nGrade F : "
         << F;


    cout << "\n==================================================";


    getch();
}


/*==================================================
                  ABOUT PROJECT
==================================================*/

void aboutProject()
{
    /*==================================================
                  ABOUT PROJECT - PAGE 1
    ==================================================*/
    clrscr();

    cout << "==================================================";
    cout << "\n              CLASS RANKER 2.0";
    cout << "\n          ABOUT PROJECT - PAGE 1";
    cout << "\n==================================================";

    cout << "\n\n                 PROJECT TEAM";
    cout << "\n--------------------------------------------------";
    cout << "\nGroup       : G17";
    cout << "\nTeam Leader : TANMAY KOLAWALE";
    cout << "\nMember 1    : SHUBHAM MANE";
    cout << "\nMember 2    : AJINKYA MANE";

    cout << "\n\n--------------------------------------------------";
    cout << "\nProject     : Student Result Management System";
    cout << "\nLanguage    : C++";
    cout << "\nCompiler    : Turbo C++";

    cout << "\n\n==================================================";
    cout << "\n       PRESS ANY KEY FOR PAGE 2";
    cout << "\n==================================================";
    getch();

    /*==================================================
                  ABOUT PROJECT - PAGE 2
    ==================================================*/
    clrscr();

    cout << "==================================================";
    cout << "\n           ABOUT PROJECT - PAGE 2";
    cout << "\n==================================================";

    cout << "\n\n              PROJECT INFORMATION";
    cout << "\n--------------------------------------------------";
    cout << "\nProgramming  : Object Oriented Programming";
    cout << "\nData Storage : CLASS.DAT";
    cout << "\nData Type    : Binary File";
    cout << "\nStudents     : 5";
    cout << "\nSubjects     : 5";

    cout << "\n\n                    PURPOSE";
    cout << "\n--------------------------------------------------";
    cout << "\nCLASS RANKER manages student academic records.";
    cout << "\nIt calculates marks, percentage, grades and rank.";
    cout << "\nThe project demonstrates C++ OOP concepts.";

    cout << "\n\n==================================================";
    cout << "\n       PRESS ANY KEY FOR PAGE 3";
    cout << "\n==================================================";
    getch();

    /*==================================================
                  ABOUT PROJECT - PAGE 3
    ==================================================*/
    clrscr();

    cout << "==================================================";
    cout << "\n           ABOUT PROJECT - PAGE 3";
    cout << "\n==================================================";

    cout << "\n\n                MAIN FEATURES";
    cout << "\n--------------------------------------------------";
    cout << "\n1. Add 5 Students at One Time";
    cout << "\n2. Student Search and Update";
    cout << "\n3. Student Delete";
    cout << "\n4. Automatic Rank Calculation";
    cout << "\n5. Top 3 Rankers";
    cout << "\n6. Subject and Grade Analysis";
    cout << "\n7. Percentage-based Sorting";
    cout << "\n8. Binary File Handling";

    cout << "\n\n                 OOP CONCEPTS";
    cout << "\n--------------------------------------------------";
    cout << "\n* Classes and Objects";
    cout << "\n* Encapsulation";
    cout << "\n* Member Functions";
    cout << "\n* Constructors";
    cout << "\n* Arrays and Functions";
    cout << "\n* File Handling";

    cout << "\n\n==================================================";
    cout << "\n       PRESS ANY KEY FOR PAGE 4";
    cout << "\n==================================================";
    getch();

    /*==================================================
                  ABOUT PROJECT - PAGE 4
    ==================================================*/
    clrscr();

    cout << "==================================================";
    cout << "\n           ABOUT PROJECT - PAGE 4";
    cout << "\n==================================================";

    cout << "\n\n                 PROJECT MODULES";
    cout << "\n--------------------------------------------------";
    cout << "\n1. Student Management";
    cout << "\n2. Result Management";
    cout << "\n3. Search Module";
    cout << "\n4. Update Module";
    cout << "\n5. Delete Module";
    cout << "\n6. Ranking Module";
    cout << "\n7. Statistics Module";
    cout << "\n8. Sort Result Module";
    cout << "\n9. File Management";

    cout << "\n\n              RESULT PROCESS";
    cout << "\n--------------------------------------------------";
    cout << "\nMarks -> Total -> Percentage -> Grade";
    cout << "\n          -> Pass / Fail -> Class Rank";

    cout << "\n\n==================================================";
    cout << "\n       PRESS ANY KEY FOR PAGE 5";
    cout << "\n==================================================";
    getch();

    /*==================================================
                  ABOUT PROJECT - PAGE 5
    ==================================================*/
    clrscr();

    cout << "==================================================";
    cout << "\n           ABOUT PROJECT - PAGE 5";
    cout << "\n==================================================";

    cout << "\n\n                 FUTURE SCOPE";
    cout << "\n--------------------------------------------------";
    cout << "\n* More Student Records";
    cout << "\n* Database Connectivity";
    cout << "\n* Graphical User Interface";
    cout << "\n* Printable Report Card";
    cout << "\n* Advanced Result Analysis";
    cout << "\n* Online Result Management";

    cout << "\n\n                PROJECT BENEFITS";
    cout << "\n--------------------------------------------------";
    cout << "\n* Easy Student Record Management";
    cout << "\n* Automatic Result Calculation";
    cout << "\n* Automatic Ranking";
    cout << "\n* Fast Searching and Sorting";
    cout << "\n* Data Storage using File Handling";

    cout << "\n\n==================================================";
    cout << "\n             DEVELOPED BY GROUP G17";
    cout << "\n==================================================";
    cout << "\n\n                    THANK YOU";
    cout << "\n==================================================";
    getch();
}

void logoutMessage()
{
    clrscr();


    cout << "\n==================================================";
    cout << "\n             LOGOUT SUCCESSFULLY";
    cout << "\n==================================================";


    getch();
}


/*==================================================
                 ADVANCED FEATURES
==================================================*/

void sortResultMenu();

void sortResultMenu()
{
    int choice;
    int order[MAX];
    int i, j, temp;

    do
    {
        if (studentCount == 0)
        {
            clrscr();

            operationAnimation("Sorting Student Results");
            cout << "\nNo student data available!";
            getch();
            return;
        }

        clrscr();
        cout << "\n==================================================";
        cout << "\n                 SORT RESULT";
        cout << "\n==================================================";
        cout << "\n\n1. Percentage High To Low";
        cout << "\n2. Percentage Low To High";
        cout << "\n3. Name A-Z";
        cout << "\n4. Back";
        cout << "\n\nEnter choice: ";
        cin >> choice;

        /* 4 = Back to Main Menu */
        if (choice == 4)
            return;

        if (choice < 1 || choice > 3)
        {
            cout << "\nInvalid choice!";
            getch();
            continue;
        }

        for (i = 0; i < studentCount; i++)
            order[i] = i;

        for (i = 0; i < studentCount - 1; i++)
        {
            for (j = i + 1; j < studentCount; j++)
            {
                int swapIt = 0;

                if (choice == 1 &&
                    students[order[j]].getPercentage() >
                    students[order[i]].getPercentage())
                    swapIt = 1;

                else if (choice == 2 &&
                         students[order[j]].getPercentage() <
                         students[order[i]].getPercentage())
                    swapIt = 1;

                else if (choice == 3 &&
                         strcmp(students[order[j]].getName(),
                                students[order[i]].getName()) < 0)
                    swapIt = 1;

                if (swapIt)
                {
                    temp = order[i];
                    order[i] = order[j];
                    order[j] = temp;
                }
            }
        }

        clrscr();
        cout << "\n==============================================================";
        cout << "\n                    SORTED RESULT";
        cout << "\n";
        printf("%-6s %-7s %-26s %12s\n",
               "RANK", "ROLL", "NAME", "PERCENTAGE");
        cout << "--------------------------------------------------------------";

        for (i = 0; i < studentCount; i++)
        {
            /* Fixed-width columns keep Percentage aligned even
               when student names have different lengths. */
            printf("\n%-6d %-7d %-26.26s %10.2f%%",
                   i + 1,
                   students[order[i]].getRollNumber(),
                   students[order[i]].getName(),
                   students[order[i]].getPercentage());
        }
        cout << "\n==============================================================";
        cout << "\n\nPress any key to return to Sort Result menu...";
        getch();

        /* After displaying the result, loop back to Sort Result menu.
           It will NOT return to Main Menu until option 4 is selected. */

    } while (1);
}

/*==================================================
                    MAIN MENU
==================================================*/

int mainMenu()
{
    int choice;

    do
    {
        clrscr();

        cout << "\n==================================================";
        cout << "\n              CLASS RANKER 2.0";
        cout << "\n          RESULT MANAGEMENT SYSTEM";
        cout << "\n==================================================";

        cout << "\n\n1.  Add 5 Students";
        cout << "\n2.  Display All Students";
        cout << "\n3.  Student Report";
        cout << "\n4.  Search Student";
        cout << "\n5.  Update Student Marks";
        cout << "\n6.  Delete Student";
        cout << "\n7.  Top 3 Rankers";
        cout << "\n8.  Class Statistics";
        cout << "\n9.  Subject Analysis";
        cout << "\n10. Grade Statistics";
        cout << "\n11. Save Data";
        cout << "\n12. About Project";
        cout << "\n13. Sort Result";
        cout << "\n14. Logout";
        cout << "\n15. Exit";

        cout << "\n\n==================================================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:  addStudents(); break;
            case 2:  displayAll(); break;
            case 3:  studentReport(); break;
            case 4:  searchStudentMenu(); break;
            case 5:  updateStudent(); break;
            case 6:  deleteStudentMenu(); break;
            case 7:  topThree(); break;
            case 8:  classStatistics(); break;
            case 9:  subjectAnalysis(); break;
            case 10: gradeStatistics(); break;
            case 11: saveData(); break;
            case 12: aboutProject(); break;
            case 13: sortResultMenu(); break;
            case 14:
                logoutMessage();
                return 1;
            case 15:
                exitAnimation();
                return 2;
            default:
                cout << "\n\nInvalid choice!";
                getch();
                break;
        }
    } while (1);
}

/*==================================================
                       MAIN
==================================================*/

void main()
{
    int loginResult;

    int menuResult;

    int loaded;


    cout.setf(ios::fixed);

    cout.precision(2);

    while (1)
    {
        loginResult = login();


        if (!loginResult)
        {
            clrscr();


            cout << "\n==================================================";
            cout << "\n                ACCESS DENIED";
            cout << "\n==================================================";


            getch();

            return;
        }


        /*
           Previous data message ONLY when
           valid saved student data exists.
        */

        loaded = loadData();


        if (loaded)
        {
            cout << "\n\nPrevious data loaded successfully!";
            delay(900);
        }
        else
        {
            cout << "\n\nNo previous data found!";
            delay(900);
        }


        menuResult = mainMenu();


        /*
           Logout -> Login screen.
        */

        if (menuResult == 1)
        {
            continue;
        }


        /*
           Exit -> Program बंद.
        */

        if (menuResult == 2)
        {
            return;
        }
    }
}
