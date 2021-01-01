/*
 -----------------GROUP MEMEBRS--------------------
 NO. ------NAME-------------SECTION---------CODE---
 1. BITSU ALEMAYEHU MAMO | DRB 2001 A  |   JA 6711
 2. ROBEL EPHREM SHIFERAW| DRB 2001 B  |   DA 9202
 3. Abdellah ILIYAS AWOL | DRB 2001 A  |   EH 3182


 ------------------NAME: SCHOOL RECORD MANAGMENT SYSTEM---------------------
 ------------------------------DESCRIPTION----------------------------------
 This program takes an input of student and factulty records and persistently
 saves the data in a binary file. Using the data provided it can search, prin
 t, remove, edit and insert records. In addittion to reciving records it sort
 s them in alphabetical order. Most of the cosole output is done in a user fr
 iendly way.

*/ 

//USED !strcmpi IN IF STATMENTS SINCE IT RETURN 0 IF TWO STRINGS ARE EQUAL

// Imports 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <stdlib.h>

using namespace std;

// Constants and Global Variables
const int MAX_REC = 500;
const char * STU_FILE = "students.bin";
const char * FAC_FILE = "faculty.bin";
const char * INDEX_FILE = "index.bin";
int INDEX[2] = {0,0};

// Structures for records  
struct Date{
    int day,month,year;
};
struct Address{
    char woreda[3], city[3], houseNum[4];
};
struct Student{
    char firstName[20], lastName[20], grade[3];
    int age;
    char section[3];
    Address address;
    Date admission;
};
struct Faculty{
    char firstName[20], lastName[20], job[20] ;
    int age;
    Address address;
    Date employmentDate;
};

// The sort function from algorithm take 3 parameters(the list, end of the list
// , function[bool based on comparison])

// Function prototypes
// The start and end function where the files are loaded and saved
void construct(Student students[], Faculty faculties[]);
void deconstruct(Student students[], Faculty faculties[]);

// Insertion of data 
void insertFacultyRecord(Faculty faculties[]);
void insertStudentRecord(Student students[]);
Date inputDate();
Address inputAddress();

// Modification of data.
void removeRecord(Faculty faculties[] ,int index);
void removeRecord(Student students[] ,int index);
void editFacultyRecord(Faculty faculties[] ,int index);
void editStudentRecord(Student students[] ,int index);

// Searching of Records
void searchRecords(Student students[]);
void searchRecords(Faculty faculties[]);

// Printing of data
// Need local index value to use the function everywhere
void printFacultyRecords(Faculty faculties[], int index);
void printStudentRecords(Student students[], int index);
void printDate(Date day);
void printAddress(Address address);

// Printing of Menu (To make code cleaner)
void mainMenu();
void subMenu(int n);
void incorrectChoice();

// Comparator function for sorting 
// Can't overload or template 
bool compareTwoNamesStu(Student stu1, Student stu2);
bool compareTwoNamesFac(Faculty fac1, Faculty fac2);


int main(){
    
    // Initializaton or variables
    Student students[MAX_REC];
    Faculty faculties[MAX_REC];
    int choice, subChoice, index;
    construct(students, faculties);

    do{
        mainMenu();
        cin>>choice;

        switch(choice){
            case 1:
                system("cls");
                subMenu(choice);
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        insertFacultyRecord(faculties);
                        break;
                    case 2:
                        insertStudentRecord(students);
                        break;
                    default:
                        incorrectChoice();
                        break;
                }
                break;

            case 2:
                system("cls");
                subMenu(choice);
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        printFacultyRecords(faculties, INDEX[0]);
                        cout<<"| Enter number => ";
                        cin>>index;
                        editFacultyRecord(faculties, index);
                        break;
                    case 2:
                        printStudentRecords(students, INDEX[1]);
                        cout<<"| Enter number => ";
                        cin>>index;
                        editStudentRecord(students, index);
                        break;
                    default:
                        incorrectChoice();
                        break;
                }
                break;

            case 3:
                system("cls");
                subMenu(choice);
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        printFacultyRecords(faculties, INDEX[0]);
                        cout<<"| Enter number => ";
                        cin>>index;
                        removeRecord(faculties, index);
                        break;
                    case 2:
                        printStudentRecords(students, INDEX[1]);
                        cout<<"| Enter number => ";
                        cin>>index;
                        removeRecord(students, index);
                        break;
                    default:
                        incorrectChoice();
                        break;
                }
                break;

            case 4:
                system("cls");
                subMenu(choice);
                cin>>subChoice;
                system("cls");
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        printFacultyRecords(faculties, INDEX[0]);
                        break;
                    case 2:
                        printStudentRecords(students, INDEX[1]);
                        break;
                    default:
                        incorrectChoice();
                        break;
                }
                break;

            case 5:
                system("cls");
                subMenu(choice);
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        searchRecords(faculties);
                        break;
                    case 2:
                        searchRecords(students);
                    default:
                        incorrectChoice();
                        break;
                }
                break;

            default:
                if(!(choice >= 1 && choice <= 5))
                    incorrectChoice();
                break;
        }
    }while(choice != 0 && choice >= 1 && choice <= 5);
    deconstruct(students, faculties);

    return 0;
}

void construct(Student students[], Faculty faculties[]){

    // Opens and reads index file if it exists
    ifstream indFile(INDEX_FILE, ios::binary);
    if(indFile.is_open()){
        for(int i = 0; i < 2; ++i){
            indFile.read((char *)&INDEX[i], sizeof(INDEX[i]));
        }
    }
    indFile.close();

    // Opens and reads students file if it exists
    ifstream stuFile(STU_FILE, ios::binary);
    if(stuFile.is_open()){
        for(int i = 0; i < INDEX[1]; ++i){
            stuFile.read((char *)&students[i], sizeof(students[i]));
        }
    }
    stuFile.close();

    // Opens and reads faculty file if it exists
    ifstream facFile(FAC_FILE, ios::binary);
    if(facFile.is_open()){
        for(int i = 0; i < INDEX[0]; ++i){
            facFile.read((char *)&faculties[i], sizeof(faculties[i]));
        }
    }
    facFile.close();

}

void deconstruct(Student students[], Faculty faculties[]){
    // Sorting not nessecarry since data will already be sorted
    // ios::trunc used to remove previous data and save the current one
    // Saves data to students file
    ofstream stuFile(STU_FILE, ios::binary | ios::trunc);
    for(int i = 0; i < INDEX[1]; ++i){
        stuFile.write((char *)&students[i], sizeof(Student));
    }
    stuFile.close();

    // Saves data to Faculty file 
    ofstream facFile(FAC_FILE, ios::binary | ios::trunc);
    for(int i = 0; i < INDEX[0]; ++i){
        facFile.write((char *)&faculties[i], sizeof(Faculty));
    }
    facFile.close();

    // Saves indices to index file;
    ofstream indFile(INDEX_FILE, ios::binary | ios::trunc);
    for(int i = 0; i < 2; ++i){
        indFile.write((char *)&INDEX[i], sizeof(int));
    }
    indFile.close();

}

void insertFacultyRecord(Faculty faculties[]){
    system("cls");
    int amountOfNewRecord;
    int index = INDEX[0]; 
    cout<<"+--------------------------------------+"<<endl;
    cout<<"| Number of Faculty to Record =>    ";
    cin>>amountOfNewRecord;
    system("cls");
    INDEX[0] = INDEX[0] + amountOfNewRecord;

        cout<<"+-----------------------INSERT--------------------------+"<<endl;
    for(int i = index; i < INDEX[0]; ++i){
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<setw(19)<<"| Employee Number: "<<setw(3)<<i+1<<setw(35)<<right<<" |"<<endl;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| First Name => ";cin>>faculties[i].firstName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Last Name  => ";cin>>faculties[i].lastName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Job Desc   => ";cin>>faculties[i].job;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Age        => ";cin>>faculties[i].age;
        cout<<"+-------------------------------------------------------+"<<endl;
        // Address input
        faculties[i].address = inputAddress();
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"|\t\tEmployment"<<endl;
        faculties[i].employmentDate = inputDate();
        cout<<"+-------------------------------------------------------+"<<endl;
    }
    system("pause");
    sort(faculties, faculties + INDEX[0], compareTwoNamesFac);
}

void insertStudentRecord(Student students[]){
    system("cls");
    int amountOfNewRecord;
    int index = INDEX[1]; 
    cout<<"+--------------------------------------+"<<endl;
    cout<<"| Number of Students to Record =>    ";
    cin>>amountOfNewRecord;
    system("cls");
    INDEX[1] = INDEX[1] + amountOfNewRecord;

        cout<<"+-----------------------INSERT--------------------------+"<<endl;
    for(int i = index; i < INDEX[1]; ++i){
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<setw(19)<<"| Student Number: "<<setw(3)<<i+1<<setw(35)<<right<<" |"<<endl;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| First Name => ";cin>>students[i].firstName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Last Name  => ";cin>>students[i].lastName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Age        => ";cin>>students[i].age;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Grade      => ";cin>>students[i].grade;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Section    => ";cin>>students[i].section;
        cout<<"+-------------------------------------------------------+"<<endl;
        // Address input
        students[i].address = inputAddress();
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"|\t\tAdmission"<<endl;
        students[i].admission = inputDate();
        cout<<"+-------------------------------------------------------+"<<endl;
    }
    system("pause");
    sort(students, students + INDEX[1], compareTwoNamesStu);
}

// Didn't use complex logic for date since the project is on fucntions and files
// If needed logic for date can be added to this function
Date inputDate(){
    Date day;
    do{
        cout<<"| Date(dd mm yyyy) => ";
        cin>>day.day>>day.month>>day.year;
    }while((day.day < 1 || day.day > 30) || (day.month < 1 || day.month > 12));

    return day;
}

Address inputAddress(){
    Address address;
    cout<<"| Address(HouseNo[XXX] Woreda[XX] City[XX]) => ";
    cin>>address.houseNum>>address.woreda>>address.city;

    return address;
}

void removeRecord(Faculty faculties[] ,int index){
    system("cls");
    if(index > 0 && index < INDEX[0] + 1){
        index--;
        for(int i = index; i < INDEX[0]; ++i){
            faculties[i] = faculties[i + 1];
        }
        INDEX[0]--;
    }    
}

void removeRecord(Student students[] ,int index){
    system("cls");
    if(index > 0 && index < INDEX[1] + 1){
        index--;
        for(int i = index; i < INDEX[1]; ++i){
            students[i] = students[i + 1];
        }
        INDEX[1]--;
    }    
}

void editFacultyRecord(Faculty faculties[] ,int index){
    system("cls");
    if(index > 0 && index < INDEX[0] + 1){
        index--;
        cout<<"+-----------------------EDIT----------------------------+"<<endl;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<setw(19)<<"| Employee Number: "<<setw(3)<<index+1<<setw(35)<<right<<" |"<<endl;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| First Name => ";cin>>faculties[index].firstName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Last Name => ";cin>>faculties[index].lastName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Job Desc => ";cin>>faculties[index].job;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Age => ";cin>>faculties[index].age;
        cout<<"+-------------------------------------------------------+"<<endl;
        // Address input
        faculties[index].address = inputAddress();
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"|\t\tEmployment"<<endl;
        faculties[index].employmentDate = inputDate();
        cout<<"+-------------------------------------------------------+"<<endl;

        system("pause");
        sort(faculties, faculties + INDEX[0], compareTwoNamesFac);
    }
}

void editStudentRecord(Student students[] ,int index){
    system("cls");
    if(index > 0 && INDEX[1] + 1){
        index--;
        cout<<"+-----------------------EDIT----------------------------+"<<endl;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<setw(19)<<"| Student Number: "<<setw(3)<<index+1<<setw(35)<<right<<" |"<<endl;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| First Name => ";cin>>students[index].firstName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Last Name  => ";cin>>students[index].lastName;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Age        => ";cin>>students[index].age;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Grade      => ";cin>>students[index].grade;
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"| Section    => ";cin>>students[index].section;
        cout<<"+-------------------------------------------------------+"<<endl;
        // Address input
        students[index].address = inputAddress();
        cout<<"+-------------------------------------------------------+"<<endl;
        cout<<"|\t\tAdmission"<<endl;
        students[index].admission = inputDate();
        cout<<"+-------------------------------------------------------+"<<endl;

        system("pause");
        sort(students, students + INDEX[1], compareTwoNamesStu);
    }
}

void printFacultyRecords(Faculty faculties[], int index){ 
    if(index > 0){
        string name;
        cout<<"+-----------------------------------------------------------------------------------------------+"<<endl;
        cout<<"|"<<setw(4)<<"no. "<<"|"<<setw(42)<<left<<"name"<<"|"<<setw(3)<<"age"<<"|"<<setw(10)<<"job desc"<<"|"
            <<setw(9)<<"house no."<<"|"<<setw(6)<<"woreda"<<"|"<<setw(4)<<"city"<<"|"<<setw(10)<<"addmisson"<<"|"<<endl;
        cout<<"|----+------------------------------------------+---+----------+---------+------+----+----------|"<<endl;
        for(int i = 0; i < index; ++i){
            // Made a stirng with full name to make printing easier
            name = (string)faculties[i].firstName + " " + (string)faculties[i].lastName;
            cout<<"|"<<setw(4)<<i + 1<<"|";
            cout<<setw(42)<<name<<"|";
            cout<<setw(3)<<faculties[i].age<<"|";
            cout<<setw(10)<<faculties[i].job<<"|";
            printAddress(faculties[i].address);
            printDate(faculties[i].employmentDate);
            cout<<endl;
            cout<<"+----+------------------------------------------+---+----------+---------+------+----+----------+"<<endl;
        }
    }else{
        cout<<"+------------------+"<<endl;
        cout<<"|No Data Available!|"<<endl;
        cout<<"+------------------+"<<endl;
    }
    system("pause");
}

void printStudentRecords(Student students[], int index){
    if(index > 0){
        string name;
        cout<<"+----------------------------------------------------------------------------------------------+"<<endl;
        cout<<"|"<<setw(4)<<"No. "<<"|"<<setw(42)<<left<<"Name"<<"|"<<setw(3)<<"Age"<<"|"<<setw(5)<<"Grade"<<"|"<<setw(3)<<"Sec"<<"|"
            <<setw(9)<<"House No."<<"|"<<setw(6)<<"Woreda"<<"|"<<setw(4)<<"City"<<"|"<<setw(10)<<"Addmisson"<<"|"<<endl;
        cout<<"|----+------------------------------------------+---+-----+---+---------+------+----+----------|"<<endl;
        for(int i = 0; i < index; ++i){
            // Made a stirng with full name to make printing easier
            name = (string)students[i].firstName + " " + (string)students[i].lastName;
            cout<<"|"<<setw(4)<<i + 1<<"|";
            cout<<setw(42)<<name<<"|";
            cout<<setw(3)<<students[i].age<<"|";
            cout<<setw(5)<<students[i].grade<<"|";
            cout<<setw(3)<<students[i].section<<"|";
            printAddress(students[i].address);
            printDate(students[i].admission);
            cout<<endl;
            cout<<"+----+------------------------------------------+---+-----+---+---------+------+----+----------+"<<endl;
        }
    }else{
        cout<<"+------------------+"<<endl;
        cout<<"|No Data Available!|"<<endl;
        cout<<"+------------------+"<<endl;
    }
    system("pause");
}

void printDate(Date day){
    cout<<setw(2)<<day.day<<"/"<<setw(2)<<day.month<<"/"<<setw(4)<<day.year<<"|";
}

void printAddress(Address address){
    cout<<setw(9)<<address.houseNum<<"|"<<setw(6)<<address.woreda<<"|"<<setw(4)<<address.city<<"|";
}

void searchRecords(Student students[]){
    // Counter needed for the print function 
    Student results[MAX_REC];
    int counter  = 0, choice;
    char target_char[20];
    cout<<"+----+-------------------+"<<endl;
    cout<<"| 1. | Search by name.   |"<<endl;
    cout<<"| 2. | Search by grade.  |"<<endl;
    cout<<"| 3. | Search by section.|"<<endl;
    cout<<"+----+-------------------+"<<endl;
    cout<<"| Input => ";
    cin>>choice;

    switch(choice){
        case 1:
            cout<<"| Enter Name => ";
            cin>>target_char;
            for(int i = 0; i < INDEX[1];++i){
                if(!strcmpi(target_char, students[i].firstName) || !strcmpi(target_char, students[i].lastName)){
                    results[counter] = students[i];
                    counter++;
                }
            }
            break;
        case 2:
            cout<<"| Enter Grade => ";
            cin>>target_char;
            for(int i = 0; i < INDEX[1];++i){
                if(!strcmpi(target_char, students[i].grade) || !strcmpi(target_char, students[i].grade)){
                    results[counter] = students[i];
                    counter++;
                }
            }
            break;
        case 3:
            cout<<"| Enter Section => ";
            cin>>target_char;
            for(int i = 0; i < INDEX[1];++i){
                if(!strcmpi(target_char, students[i].section) || !strcmpi(target_char, students[i].section)){
                    results[counter] = students[i];
                    counter++;
                }
            }
            break;
    }
    printStudentRecords(results, counter);
}

void searchRecords(Faculty faculties[]){
    // Counter needed for the print function 
    Faculty results[MAX_REC];
    int counter  = 0, choice;
    char target_char[20];
    cout<<"+----+-------------------+"<<endl;
    cout<<"| 1. | Search by Name.   |"<<endl;
    cout<<"| 2. | Search by Job.    |"<<endl;
    cout<<"+----+-------------------+"<<endl;
    cout<<"| Input => ";
    cin>>choice;
    switch(choice){
        case 1:
            cout<<"| Enter Name => ";
            cin>>target_char;
            for(int i = 0; i < INDEX[0];++i){
                if(!strcmpi(target_char, faculties[i].firstName) || !strcmpi(target_char, faculties[i].lastName)){
                    results[counter] = faculties[i];
                    counter++;
                }
            }
            break;
        case 2:
            cout<<"| Enter Job => ";
            cin>>target_char;
            for(int i = 0; i < INDEX[0];++i){
                if(!strcmpi(target_char, faculties[i].job)){
                    results[counter] = faculties[i];
                    counter++;
                }
            }
            break;
    }
    printFacultyRecords(results, counter);
}

void subMenu(int n){
    string values[5] = {"Accept", "Edit", "Delete", "Print", "Search"};

    system("cls");

    // Needed to use left casue there was a bug
    cout<<setw(10)<<left<<"+----+--"<<setw(6)<<values[n-1]<<setw(4)<<" Menu"<<setw(9)<<"--------+"<<endl;
    cout<<setw(6)<<"| 0. |"<<setw(20)<<"Go Back "<<setw(4)<<right<<"|"<<endl;
    cout<<setw(6)<<"| 1. |"<<setw(6)<<values[n-1]<<setw(18)<<" Faculty Records |"<<endl;
    cout<<setw(6)<<"| 2. |"<<setw(6)<<values[n-1]<<setw(18)<<" Student Records |"<<endl;
    cout<<setw(27)<<"+----+-----------------------+"<<endl;
    cout<<setw(12)<<"| Input =>  ";

}

void mainMenu(){
    system("cls");

    cout<<setw(22)<<"+----+--Main Menu-----+"<<endl;
    cout<<setw(22)<<left<<"| 0. | Exit "<<"|"<<endl;
    cout<<setw(22)<<"| 1. | Add to Record "<<"|"<<endl;
    cout<<setw(22)<<"| 2. | Edit Record "<<"|"<<endl;
    cout<<setw(22)<<"| 3. | Delete Record "<<"|"<<endl;
    cout<<setw(22)<<"| 4. | Print Record "<<"|"<<endl;
    cout<<setw(22)<<"| 5. | Search Record "<<"|"<<endl;
    cout<<setw(22)<<"+----+----------------+"<<endl;
    cout<<setw(12)<<"| Input =>  ";

}
void incorrectChoice(){
    cout<<"+------------------+"<<endl;
    cout<<"| Incorrect choice |"<<endl;
    cout<<"+------------------+";

}

bool compareTwoNamesStu(Student stu1, Student stu2){
    if(stu1.firstName != stu2.firstName){
        return (strcmpi(stu1.firstName, stu2.firstName) < 0);
    }
    return (strcmpi(stu1.lastName, stu2.lastName) < 0); 
}

bool compareTwoNamesFac(Faculty fac1, Faculty fac2){
    if(fac1.firstName != fac2.firstName){
        return (strcmpi(fac1.firstName, fac2.firstName) < 0);
    }
    return (strcmpi(fac1.lastName, fac2.lastName) < 0); 
}
