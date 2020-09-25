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
void construct(Student students[], Faculty faculties[]);
void insertDataFaculty(Faculty faculties[]);
void insertDataStudent(Student students[]);
void removeDataFaculty(Faculty faculties[] ,int index);
void removeDataStudent(Student students[] ,int index);
void editDataFaculty(Faculty faculties[] ,int index);
void editDataStudent(Student students[] ,int index);
Date inputDate();
void deconstruct(Student students[], Faculty faculties[]);

int main(){
    Student students[MAX_REC];
    Faculty faculties[MAX_REC];

    construct(students, faculties);

    cout<<INDEX[0]<<","<<INDEX[1];

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

    // Opens and reads student file if it exists
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
    // Save data to student file
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
        cout<<"Name: ";
        cin>>faculties[i].name;
        cout<<"Job Desc: ";
        cin>>faculties[i].job;
        cout<<"Age: ";
        cin>>faculties[i].age;
        cout<<"Date of Employment: "<<endl;
        faculties[i].employmentDate = inputDate();
    }
}

void insertDataStudent(Student students[]){
    int n;
    int index = INDEX[1]; 
    cout<<"How many peole would you like to record"<<endl;
    cin>>n;
    INDEX[1] = INDEX[1] + n;
    for(int i = index; i < INDEX[1]; ++i){
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
