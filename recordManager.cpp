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
    Address address;
    Date admition;
};
struct Faculty{
    string name, job;
    int age;
    Address address;
    Date employmentDate;
};

// Function prototypes
void construct(Student students[], Faculty faculties[]);
void insertDataFaculty(Faculty faculties[]);
void insertDataStudent(Student students[]);
void removeData(Faculty faculties[] ,int index);
void removeData(Student students[] ,int index);
void editDataFaculty(Faculty faculties[] ,int index);
void editDataStudent(Student students[] ,int index);
void printFaculty(Faculty faculties[]);
void printStudent(Student students[]);
int * searchData(Student students[]);
int * searchData(Faculty faculties[]);
Date inputDate();
Address inputAddress();
//void sort(Student students[], Faculty faculties[]);
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
        cout<<"4. Search Data."<<endl;
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
                    printFaculty(faculties);
                }else if(subChoice == 2){
                    printStudent(students);
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
        cout<<"Name: ";
        cin>>faculties[i].name;
        cout<<"Job Desc: ";
        cin>>faculties[i].job;
        cout<<"Age: ";
        cin>>faculties[i].age;
        cout<<"Address: "<<endl;
        faculties[i].address = inputAddress();
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
        cout<<"Address: "<<endl;
        students[i].address = inputAddress();
        cout<<"Date of Employment: "<<endl;
        students[i].admition = inputDate();
    }
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
    cout<<"New Name: ";
    cin>>faculties[index].name;
    cout<<"New Job Desc: ";
    cin>>faculties[index].job;
    cout<<"New Age: ";
    cin>>faculties[index].age;
    cout<<"New Address: "<<endl;
    faculties[index].address = inputAddress();
    cout<<"New Date of Employment: "<<endl;
    faculties[index].employmentDate = inputDate();
}
void editDataStudent(Student students[] ,int index){
    cout<<"New Name: ";
    cin>>students[index].name;
    cout<<"New Age: ";
    cin>>students[index].age;
    cout<<"New Grade: ";
    cin>>students[index].grade;
    cout<<"New Section: ";
    cin>>students[index].section;
    cout<<"New Address: "<<endl;
    students[index].address = inputAddress();
    cout<<"New Date of Employment: "<<endl;
    students[index].admition = inputDate();
}
void printFaculty(Faculty faculties[]){
    for(int i = 0; i < INDEX[0]; ++i){
        cout<<"Faculty No. "<<i + 1<<endl;
        cout<<"\tName: "<<faculties[i].name<<endl;
        cout<<"\tJob Desc: "<<faculties[i].job<<endl;
        cout<<"\tAge: "<<faculties[i].age<<endl;
    }
}
void printStudent(Student students[]){
    for(int i = 0; i < INDEX[1]; ++i){
        cout<<"Student No. "<<i + 1<<endl;
        cout<<"\tName: "<<students[i].name<<endl;
        cout<<"\tAge: "<<students[i].age<<endl;
        cout<<"\tGrade: "<<students[i].grade<<endl;
        cout<<"\tSection: "<<students[i].section<<endl;
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
