// Imports 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <stdlib.h>

using namespace std;
// The sort function from algorithm take 3 parameters a fucntion that return true or false
// based on the comparing mechnaism and the list and the end of the list.
// Constants
const int MAX_REC = 500;
const char * STU_FILE = "students.bin";
const char * FAC_FILE = "faculty.bin";
const char * INDEX_FILE = "index.bin";
int INDEX[2] = {0,0};

// Structures
struct Date{
    int day,month,year;
};
struct Address{
    char woreda[3], city[3], houseNum[4];
};
struct Student{
    char firstName[20], lastName[20];
    int age,grade;
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

// Function prototypes
void construct(Student students[], Faculty faculties[]);
void deconstruct(Student students[], Faculty faculties[]);

// Input of data.
void insertDataFaculty(Faculty faculties[]);
void insertDataStudent(Student students[]);
Date inputDate();
Address inputAddress();

// Modification of data.
void removeData(Faculty faculties[] ,int index);
void removeData(Student students[] ,int index);
void editDataFaculty(Faculty faculties[] ,int index);
void editDataStudent(Student students[] ,int index);

// Data searching.
void searchData(Student students[]);
void searchData(Faculty faculties[]);

// Printing Data.
// Even if the INDEX is global we need a local one inorder to use this for the search function too.
void printFaculty(Faculty faculties[], int index);
void printStudent(Student students[], int index);
void printDate(Date day);
void printAddress(Address address);

// Comparator function for the sort function.
// Couldn't overload or template the function so needed two different ones.
bool compareTwoNamesStu(Student stu1, Student stu2);
bool compareTwoNamesFac(Faculty fac1, Faculty fac2);


int main(){

    Student students[MAX_REC];
    Faculty faculties[MAX_REC];
    int choice, subChoice, index;
    construct(students, faculties);

    do{
        cout<<"0. Exit."<<endl;
        cout<<"1. Input Data."<<endl;
        cout<<"2. Edit Data."<<endl;
        cout<<"3. Remove Data."<<endl;
        cout<<"4. Print Data."<<endl;
        cout<<"5. Search Data."<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                system("cls");
                cout<<"0. Go Back."<<endl;    
                cout<<"1. Accept Faculty Data."<<endl;    
                cout<<"2. Accept Student Data."<<endl;    
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        insertDataFaculty(faculties);
                        break;
                    case 2:
                        insertDataStudent(students);
                        break;
                    default:
                        cout<<"Incorrect choice";
                        break;
                }
                break;

            case 2:
                system("cls");
                cout<<"0. Go Back."<<endl;    
                cout<<"1. Edit Faculty Data."<<endl;    
                cout<<"2. Edit Student Data."<<endl;    
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        printFaculty(faculties, INDEX[0]);
                        cout<<"Enter number: ";
                        cin>>index;
                        editDataFaculty(faculties, index);
                        break;
                    case 2:
                        printStudent(students, INDEX[1]);
                        cout<<"Enter number: ";
                        cin>>index;
                        editDataStudent(students, index);
                        break;
                    default:
                        cout<<"Incorrect choice";
                        break;
                }
                break;

            case 3:
                system("cls");
                cout<<"0. Go Back."<<endl;    
                cout<<"1. Delete Faculty Data."<<endl;    
                cout<<"2. Delete Student Data."<<endl;    
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        printFaculty(faculties, INDEX[0]);
                        cout<<"Enter number: ";
                        cin>>index;
                        removeData(faculties, index);
                        break;
                    case 2:
                        printStudent(students, INDEX[1]);
                        cout<<"Enter number: ";
                        cin>>index;
                        removeData(students, index);
                        break;
                    default:
                        cout<<"Incorrect choice";
                        break;
                }
                break;

            case 4:
                system("cls");
                cout<<"0. Go Back."<<endl;    
                cout<<"1. Print Faculty Data."<<endl;    
                cout<<"2. Print Student Data."<<endl;    
                cin>>subChoice;
                system("cls");
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        printFaculty(faculties, INDEX[0]);
                        break;
                    case 2:
                        printStudent(students, INDEX[1]);
                        break;
                    default:
                        cout<<"Incorrect choice";
                        break;
                }
                break;

            case 5:
                system("cls");
                cout<<"0. Go Back."<<endl;    
                cout<<"1. Search Faculty Data."<<endl;    
                cout<<"2. Search Student Data."<<endl;    
                cin>>subChoice;
                switch(subChoice){
                    case 0:
                        break;
                    case 1:
                        searchData(faculties);
                        break;
                    case 2:
                        searchData(students);
                    default:
                        cout<<"Incorrect choice";
                        break;
                }
                break;

            default:
                break;
        }
    }while(choice != 0);

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
    // Sorting not nessecarry since data will already be sorted.
    // Save data to students file
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

void insertDataFaculty(Faculty faculties[]){
    system("cls");
    int n;
    int index = INDEX[0]; 
    cout<<"How many peole would you like to record"<<endl;
    cin>>n;
    INDEX[0] = INDEX[0] + n;
    for(int i = index; i < INDEX[0]; ++i){
        cout<<"Employee Number: "<<i+1<<endl;
        cout<<"First Name: ";
        cin>>faculties[i].firstName;
        cout<<"Last Name: ";
        cin>>faculties[i].lastName;
        cout<<"Job Desc: ";
        cin>>faculties[i].job;
        cout<<"Age: ";
        cin>>faculties[i].age;
        cout<<"Address: "<<endl;
        faculties[i].address = inputAddress();
        cout<<"Date of Employment: "<<endl;
        faculties[i].employmentDate = inputDate();
    }
    sort(faculties, faculties + INDEX[0], compareTwoNamesFac);
}

void insertDataStudent(Student students[]){
    system("cls");
    int n;
    int index = INDEX[1]; 
    cout<<"How many peole would you like to record"<<endl;
    cin>>n;
    INDEX[1] = INDEX[1] + n;
    for(int i = index; i < INDEX[1]; ++i){
        cout<<"First Name: ";
        cin>>students[i].firstName;
        cout<<"Last Name: ";
        cin>>students[i].lastName;
        cout<<"Age: ";
        cin>>students[i].age;
        cout<<"Grade: ";
        cin>>students[i].grade;
        cout<<"Section: ";
        cin>>students[i].section;
        cout<<"Address: "<<endl;
        students[i].address = inputAddress();
        cout<<"Date of Addmisson: "<<endl;
        students[i].admission = inputDate();
    }
    sort(students, students + INDEX[1], compareTwoNamesStu);
}

Date inputDate(){
    Date day;
    do{
        cout<<"\tDay: ";
        cin>>day.day;
        cout<<"\tMonth: ";
        cin>>day.month;
        cout<<"\tYear: ";
        cin>>day.year;
    }while((day.day < 1 || day.day > 30) || (day.month < 1 || day.month > 12));

    return day;
}

Address inputAddress(){
    Address address;
    cout<<"\tHouse No.: ";
    cin>>address.houseNum;
    cout<<"\tWoreda: ";
    cin>>address.woreda;
    cout<<"\tCity: ";
    cin>>address.city;

    return address;
}

void removeData(Faculty faculties[] ,int index){
    system("cls");
    if(index > 0){
        index--;
        for(int i = index; i < INDEX[0]; ++i){
            faculties[i] = faculties[i + 1];
        }
        INDEX[0]--;
    }    
}

void removeData(Student students[] ,int index){
    system("cls");
    if(index > 0){
        index--;
        for(int i = index; i < INDEX[1]; ++i){
            students[i] = students[i + 1];
        }
        INDEX[1]--;
    }    
}

void editDataFaculty(Faculty faculties[] ,int index){
    system("cls");
    if(index > 0){
        index--;
        cout<<"New First Name: ";
        cin>>faculties[index].firstName;
        cout<<"New Last Name: ";
        cin>>faculties[index].lastName;
        cout<<"New Job Desc: ";
        cin>>faculties[index].job;
        cout<<"New Age: ";
        cin>>faculties[index].age;
        cout<<"New Address: "<<endl;
        faculties[index].address = inputAddress();
        cout<<"New Date of Employment: "<<endl;
        faculties[index].employmentDate = inputDate();
        sort(faculties, faculties + INDEX[0], compareTwoNamesFac);
    }
}

void editDataStudent(Student students[] ,int index){
    system("cls");
    if(index > 0){
        index--;
        cout<<"New First Name: ";
        cin>>students[index].firstName;
        cout<<"New Last Name: ";
        cin>>students[index].lastName;
        cout<<"New Age: ";
        cin>>students[index].age;
        cout<<"New Grade: ";
        cin>>students[index].grade;
        cout<<"New Section: ";
        cin>>students[index].section;
        cout<<"New Address: "<<endl;
        students[index].address = inputAddress();
        cout<<"New Date of Employment: "<<endl;
        students[index].admission = inputDate();
        sort(students, students + INDEX[1], compareTwoNamesStu);
    }
}

void printFaculty(Faculty faculties[], int index){ 
    if(index != 0){
        string name;
        cout<<"+-----------------------------------------------------------------------------------------------+"<<endl;
        cout<<"|"<<setw(4)<<"no. "<<"|"<<setw(42)<<left<<"name"<<"|"<<setw(3)<<"age"<<"|"<<setw(10)<<"job desc"<<"|"
            <<setw(9)<<"house no."<<"|"<<setw(6)<<"woreda"<<"|"<<setw(4)<<"city"<<"|"<<setw(10)<<"addmisson"<<"|"<<endl;
        cout<<"|----+------------------------------------------+---+----------+---------+------+----+----------|"<<endl;
        for(int i = 0; i < index; ++i){
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
}

void printStudent(Student students[], int index){
    if(index != 0){
        string name;
        cout<<"+----------------------------------------------------------------------------------------------+"<<endl;
        cout<<"|"<<setw(4)<<"No. "<<"|"<<setw(42)<<left<<"Name"<<"|"<<setw(3)<<"Age"<<"|"<<setw(5)<<"Grade"<<"|"<<setw(3)<<"Sec"<<"|"
            <<setw(9)<<"House No."<<"|"<<setw(6)<<"Woreda"<<"|"<<setw(4)<<"City"<<"|"<<setw(10)<<"Addmisson"<<"|"<<endl;
        cout<<"|----+------------------------------------------+---+-----+---+---------+------+----+----------|"<<endl;
        for(int i = 0; i < index; ++i){
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
}

void printDate(Date day){
    cout<<setw(2)<<day.day<<"/"<<setw(2)<<day.month<<"/"<<setw(4)<<day.year<<"|";
}

void printAddress(Address address){
    cout<<setw(9)<<address.houseNum<<"|"<<setw(6)<<address.woreda<<"|"<<setw(4)<<address.city<<"|";
}

void searchData(Student students[]){
    Student results[MAX_REC];
    int counter  = 0, choice, target_grade;
    char target_char[20];
    cout<<"1. Search by name."<<endl;
    cout<<"2. Search by grade."<<endl;
    cout<<"3. Search by section."<<endl;
    cin>>choice;
    switch(choice){
        case 1:
            cout<<"Enter Name: ";
            cin>>target_char;
            for(int i = 0; i < INDEX[1];++i){
                if(!strcmpi(target_char, students[i].firstName) || !strcmpi(target_char, students[i].lastName)){
                    results[counter] = students[i];
                    counter++;
                }
            }
            break;
        case 2:
            cout<<"Enter Grade: ";
            cin>>target_grade;
            for(int i = 0; i < INDEX[1];++i){
                if(target_grade == students[i].grade){
                    results[counter] = students[i];
                    counter++;
                }
            }
            break;
        case 3:
            cout<<"Enter Section: ";
            cin>>target_char;
            for(int i = 0; i < INDEX[1];++i){
                if(!strcmpi(target_char, students[i].section) || !strcmpi(target_char, students[i].section)){
                    results[counter] = students[i];
                    counter++;
                }
            }
            break;
    }
    printStudent(results, counter);
}

void searchData(Faculty faculties[]){
    Faculty results[MAX_REC];
    int counter  = 0, choice;
    char target_char[20];
    cout<<"1. Search by name."<<endl;
    cout<<"2. Search by job."<<endl;
    cin>>choice;
    switch(choice){
        case 1:
            cout<<"Enter Name: ";
            cin>>target_char;
            for(int i = 0; i < INDEX[1];++i){
                if(!strcmpi(target_char, faculties[i].firstName) || !strcmpi(target_char, faculties[i].lastName)){
                    results[counter] = faculties[i];
                    counter++;
                }
            }
            break;
        case 2:
            cout<<"Enter Job: ";
            cin>>target_char;
            for(int i = 0; i < INDEX[1];++i){
                if(!strcmpi(target_char, faculties[i].job)){
                    results[counter] = faculties[i];
                    counter++;
                }
            }
            break;
    }
    printFaculty(results, counter);
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
