// Imports 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

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
    char section;
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

void insertDataFaculty(Faculty faculties[]);
void insertDataStudent(Student students[]);
Date inputDate();
Address inputAddress();
void removeData(Faculty faculties[] ,int index);
void removeData(Student students[] ,int index);
void editDataFaculty(Faculty faculties[] ,int index);
void editDataStudent(Student students[] ,int index);
// Haven't done it but thinking of it storing array of the results and then printing them. 
// Might or not return an array maybe make it void. 
int * searchData(Student students[]);
int * searchData(Faculty faculties[]);
// Even if the INDEX is global we need a local one inorder to use this for the search function too.
void printFaculty(Faculty faculties[], int index);
void printStudent(Student students[], int index);
void printDate(Date day);
void printAddress(Address address);
// Couldn't overload or template the function so needed two different ones.
// Used to compare name for the sort algorithm that was included with <algorithm>.
// It reteurn true or false depending on the names and passes it to the
// sort func which is found inside the <algorithm> import.
bool compareTwoNamesStu(Student stu1, Student stu2);
bool compareTwoNamesFac(Faculty fac1, Faculty fac2);

void deconstruct(Student students[], Faculty faculties[]);

int main(){

    Student students[MAX_REC];
    Faculty faculties[MAX_REC];
    int choice, subChoice, index;
    construct(students, faculties);

    do{
        cout<<"1. Input Data."<<endl;
        cout<<"2. Edit Data."<<endl;
        cout<<"3. Remove Data."<<endl;
        cout<<"4. Print Data."<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"1. Accept Faculty Data."<<endl;    
                cout<<"2. Accept Student Data."<<endl;    
                cin>>subChoice;
                if(subChoice == 1){
                    insertDataFaculty(faculties);
                }else if(subChoice == 2){
                    insertDataStudent(students);
                }else{
                    cout<<"Incorrect choice.";
                }
                break;

            case 2:
                cout<<"1. Edit Faculty Data."<<endl;    
                cout<<"2. Edit Student Data."<<endl;    
                cin>>subChoice;
                if(subChoice == 1){
                    cout<<"Enter number: ";
                    cin>>index;
                    editDataFaculty(faculties, index);
                }else if(subChoice == 2){
                    cout<<"Enter number: ";
                    cin>>index;
                    editDataStudent(students, index);
                }else{
                    cout<<"Incorrect choice.";
                }
                break;

            case 3:
                cout<<"1. Delete Faculty Data."<<endl;    
                cout<<"2. Delete Student Data."<<endl;    
                cin>>subChoice;
                if(subChoice == 1){
                    cout<<"Enter number: ";
                    cin>>index;
                    removeData(faculties, index);
                }else if(subChoice == 2){
                    cout<<"Enter number: ";
                    cin>>index;
                    removeData(students, index);
                }else{
                    cout<<"Incorrect choice.";
                }
                break;

            case 4:
                cout<<"1. Print Faculty Data."<<endl;    
                cout<<"2. Print Student Data."<<endl;    
                cin>>subChoice;
                if(subChoice == 1){
                    printFaculty(faculties, INDEX[0]);
                }else if(subChoice == 2){
                    printStudent(students, INDEX[1]);
                }else{
                    cout<<"Incorrect choice.";
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
    // I don't think this is nessecary since we already sort when data inputed.
    // Sorting the names before saving
    //sort(faculties, faculties + INDEX[0], compareTwoNamesFac);
    //sort(students, students + INDEX[1], compareTwoNamesStu);

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
        cout<<"Date of Employment: "<<endl;
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
    for(int i = index; i < INDEX[0]; ++i){
        faculties[i] = faculties[i + 1];
    }
    INDEX[0]--;
}

void removeData(Student students[] ,int index){
    for(int i = index; i < INDEX[1]; ++i){
        students[i] = students[i + 1];
    }
    INDEX[1]--;
}

void editDataFaculty(Faculty faculties[] ,int index){
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

void editDataStudent(Student students[] ,int index){
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

void printFaculty(Faculty faculties[], int index){ 
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
}

void printStudent(Student students[], int index){
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
}


void printDate(Date day){
    cout<<setw(2)<<day.day<<"/"<<setw(2)<<day.month<<"/"<<setw(4)<<day.year<<"|";
}

void printAddress(Address address){
    cout<<setw(9)<<address.houseNum<<"|"<<setw(6)<<address.woreda<<"|"<<setw(4)<<address.city<<"|";
}

bool compareTwoNamesStu(Student stu1, Student stu2){
    if(stu1.firstName != stu2.firstName){
        return (strcmp(stu1.firstName, stu2.firstName) < 0);
    }
    return (strcmp(stu1.lastName, stu2.lastName) < 0); 
}

bool compareTwoNamesFac(Faculty fac1, Faculty fac2){
    if(fac1.firstName != fac2.firstName){
        return (strcmp(fac1.firstName, fac2.firstName) < 0);
    }
    return (strcmp(fac1.lastName, fac2.lastName) < 0); 
}
