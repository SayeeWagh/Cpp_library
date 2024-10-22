#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

struct Student {
    int roll_no;
    string name;
    string div;
    string address;
};

void addStudent() {
    Student student;
    ofstream file("student.txt", ios::app);

    if(!file) {
        cout<<"Error opening file!!"<<endl;
        return;
    }

    cout<<"Enter the Roll Number: ";
    cin>>student.roll_no;
    cin.ignore();

    cout<<"Enter Name: ";
    getline(cin, student.name);

    cout<<"Enter Division: ";
    getline(cin, student.div);
    cout<<"Enter Address: ";
    getline(cin, student.address);

    file<<student.roll_no <<endl;
    file<<student.name <<endl;
    file<<student.div<<endl;
    file<<student.address<<endl;

    file.close();

    cout<<"Student record added successfully!!"<<endl;
    cout<<endl;
}

void displayStudent(int roll_No) {
    Student student;

    ifstream file("student.txt");

    if(!file) {
        cout<<"Error opening file!!"<<endl;
        cout<<endl;
        return;
    }

    bool found = false;

    while(file>>student.roll_no) {
        file.ignore();
        getline(file, student.name);
        getline(file, student.div);
        getline(file, student.address);

        if(student.roll_no == roll_No) {
            cout<<"Student Details: "<<endl;
            cout<<"Roll Number: "<<student.roll_no<<endl;
            cout<<"Name: "<<student.name<<endl;
            cout<<"Division: "<<student.div<<endl;
            cout<<"Address: "<<student.address<<endl;
            found = true;
            break;
        }
    }
    if(!found) {
        cout<<"Record of student with Roll Number "<<roll_No<<" does not exist!!"<<endl;
        cout<<endl;
    }
    file.close();
}

void deleteStudent(int rollno) {
    Student student;

    ifstream file("student.txt");
    ofstream tempFile("temp.txt");

    if(!file || !tempFile) {
        cout<<"Error opening file!!"<<endl;
        cout<<endl;
        return;
    }
    bool found = false;
    while (file>>student.roll_no) {
        file.ignore();
        getline(file, student.name);
        getline(file, student.div);
        getline(file, student.address);

        if(student.roll_no == rollno) {
            found=true;
            cout<<"Deleting record of Roll Number: "<<student.roll_no<<endl;
            continue;
        }

        tempFile<<student.roll_no<<endl;
        tempFile<<student.name<<endl;
        tempFile<<student.div<<endl;
        tempFile<<student.address<<endl;
    }
    if(!found) {
        cout<<"Record of student with Roll Number "<<rollno<<" does not exist!!"<<endl;
        cout<<endl;
    }
    else {
        cout<<"Student record deleted successfully!!"<<endl;
        cout<<endl;
    }
    file.close();
    tempFile.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");
}

int main()
{
    int choice, rollNo;

    do{
        cout<<"1.Add Student Record"<<endl;
        cout<<"2.Display Student Record"<<endl;
        cout<<"3.Delete Student Record"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cout<<endl;

        switch(choice) {
        case 1:
            addStudent();
            break;

        case 2:
            cout<<"Enter Roll Number to Display: ";
            cin>>rollNo;
            displayStudent(rollNo);
            cout<<endl;
            break;

        case 3:
            cout<<"Enter Roll Number to delete: ";
            cin>>rollNo;
            deleteStudent(rollNo);
            break;

        case 4:
            cout<<"Exiting....."<<endl;
            cout<<endl;
            break;

        default:
            cout<<"Invalid Choice!!"<<endl;
            cout<<endl;

        }
    }
    while(choice !=4);
    return 0;
}
