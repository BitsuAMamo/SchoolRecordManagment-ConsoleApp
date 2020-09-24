#include <iostream>
#include <fstream>

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
    int houseNum;
    char woreda[2];
    string city;
};
struct Student{
    string name;
    int age,grade;
    char section;
    Date admition;
};
struct Faculty{
    string name, job;
    int age;
    Date employmentDate;
};
// Function prototypes
void construct(Student students, Faculty faculties, int index[]);
void insertDataFaculty(Faculty faculties[]);
void insertDataStudent(Student students[]);
void removeDataFaculty(Faculty faculties[] ,int index);
void removeDataStudent(Student students[] ,int index);
void editDataFaculty(Faculty faculties[] ,int index);
void editDataStudent(Student students[] ,int index);
Date inputDate();
void deconstruct();

int main(){
    Student students[MAX_REC];
    Faculty faculties[MAX_REC];

    insertDataFaculty(faculties);
    cout<<INDEX[0];


    return 0;
}

void construct(Student students, Faculty faculties){
    // Opens and reads student file if it exists
    ifstream stuFile(STU_FILE, ios::binary);
    if(stuFile.is_open()){

    }
    stuFile.close();

    // Opens and reads faculty file if it exists
    ifstream facFile(FAC_FILE, ios::binary);
    if(facFile.is_open()){

    }
    facFile.close();

    // Opens and reads index file if it exists
    ifstream indFile(INDEX_FILE, ios::binary);
    if(indFile.is_open()){

    }
    indFile.close();

}

void deconstruct(){
    // Opens and reads student file if it exists
    ofstream stuFile(STU_FILE, ios::binary | ios::trunc);

    stuFile.close();

    // Opens and reads faculty file if it exists
    ofstream facFile(FAC_FILE, ios::binary | ios::trunc);

    facFile.close();

    // Opens and reads index file if it exists
    ofstream indFile(INDEX_FILE, ios::binary | ios::trunc);

    indFile.close();

}


void insertDataFaculty(Faculty faculties[]){
    int n;
    int index = INDEX[0]; 
    cout<<"How many peole would you like to record"<<endl;
    cin>>n;
    for(int i = index; i < n + index; ++i){
        cout<<"Employee Number: "<<i+1<<endl;
        cout<<"Name: ";
        cin>>faculties[i].name;
        cout<<"Job Desc: ";
        cin>>faculties[i].job;
        cout<<"Age: ";
        cin>>faculties[i].age;
        cout<<"Date of Employment: "<<endl;
        faculties[i].employmentDate = inputDate();
    }
    INDEX[0] = INDEX[0] + n;
}

void insertDataStudent(Student students[]){
    int n;
    int index = INDEX[1]; 
    cout<<"How many peole would you like to record"<<endl;
    cin>>n;
    for(int i = index; i < n + index; ++i){
        cout<<"Name: ";
        cin>>students[i].name;
        cout<<"Age: ";
        cin>>students[i].age;
        cout<<"Grade: ";
        cin>>students[i].grade;
        cout<<"Section: ";
        cin>>students[i].section;
        cout<<"Date of Employment: "<<endl;
        students[i].admition = inputDate();
    }
    INDEX[1] = INDEX[1] + n;

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
