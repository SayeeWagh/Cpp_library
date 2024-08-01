#include <iostream>

using namespace std;

struct student{

    string name;
    int roll_no;
    float sgpa;
};

void bubbleSort(student arr[],int n)
{
    for(int i =0;i<4;i++)
    {
        for(int j=0;j<4-i;j++)
        {
            if (arr[j].roll_no > arr[j+1].roll_no)
            {
                student a = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = a;
            }
        }
    }
}

void insertionSort(student arr[],int n)
{
    for(int i = 1; i<n; i++)
    {
        student key = arr[i];
        int j=i-1;

        while(j>=0 && arr[j].name>key.name)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

int partition(student arr[],int low,int high)
{
    float pivot = arr[high].sgpa;
    int i = low-1;

    for(int j= low; j<high; ++j)
    {
        if (arr[j].sgpa>pivot)
        {
            ++i;

            student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    student temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return i+1;
}

void quickSort(student arr[],int low, int high)
{
    if(low<high)
    {
        int pi = partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

void searchSgpa(student s[], int n,float search)
{
    bool found = false;
    for(int i = 0; i<n;i++)
    {
        if(s[i].sgpa == search)
        {
            if(!found)
            {
                cout<<"Student with SGPA::"<<search<<endl;
                found = true;
            }
            cout<<"Name:"<<s[i].name<<endl;
        }
    }

    if(!found)
    {
        cout<<"No students found with SGPA::"<<search<<endl;
    }
}

int binarSearch(student arr[],int size,string key)
{
    int start = 0;
    int end = size-1;

    int mid = start + (end - start)/2;

    while(start<=end)
    {
        if(arr[mid].name == key)
        {
            return mid;
        }

        if(key>arr[mid].name)
        {
            start = mid+1;
        }
        else
        {
            end = mid-1;
        }
        mid = start + (end-start)/2;
    }
    return -1;
}



int main()
{
    student s[5];
    for(int i=0;i<5;i++){
        cout<<"Enter the details of student no."<<i+1<<endl;
        cout<<"Enter the Name:-";
        cin>>s[i].name;
        cout<<"Enter the Roll number:-";
        cin>>s[i].roll_no;
        cout<<"Enter the SGPA:-";
        cin>>s[i].sgpa;
        cout<<endl;

    }

    int choice;
    float search;
    string key;


    do
    {
        cout<<"Menu:"<<endl;
        cout<<endl;
        cout<<"1.Display details of students:"<<endl;
        cout<<"2.Sorted Roll numbers:"<<endl;
        cout<<"3.Sorted Names:"<<endl;
        cout<<"4.Top 3 students:"<<endl;
        cout<<"5.search by sgpa:"<<endl;
        cout<<"6.search by name:"<<endl;
        cout<<"7.Exit:"<<endl;
        cout<<endl;
        cout<<"Enter your choice::";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
        case 1:
            cout<<"Details of the students are::"<<endl;
            cout<<endl;
            for(int i=0;i<5;i++)
            {
                cout<<"Student no."<<i+1<<":-"<<endl;
                cout<<"Name:-"<<s[i].name<<endl;
                cout<<"Roll Number:-"<<s[i].roll_no<<endl;
                cout<<"SGPA:-"<<s[i].sgpa<<endl;
                cout<<endl;
            }
            break;
        case 2:
            //bubbleSort
            bubbleSort( s , 5);
            cout<<"Sorted Roll Numbers::"<<endl;
            cout<<endl;
            for(int j=0;j<5;j++)
            {
                cout<<s[j].roll_no<<endl;
            }
            cout<<endl;
            break;
        case 3:
            //insertionSort
            insertionSort(s,5);

            cout<<"Sorted Names of students are::"<<endl;
            cout<<endl;
            for(int i=0; i<5; i++)
            {
                cout<<s[i].name<<endl;
            }
            cout<<endl;
            break;
        case 4:
            //quickSort

            quickSort(s,0,4);

            cout<<"Top 3 students are::"<<endl;
            cout<<endl;

            for(int i=0;i<3;++i)
            {
                cout<<"Name::"<<s[i].name<<",Roll number::"<<s[i].roll_no<<",SGPA::"<<s[i].sgpa<<endl;
            }
            cout<<endl;
            break;

        case 5:
            //search by sgpa

            cout<<"Enter SGPA to search::";
            cin>>search;
            cout<<endl;

            searchSgpa(s,5,search);
            cout<<endl;
            break;
        case 6:
            //binary search


            cout<<"Enter the name to search::";
            cin>>key;
            cout<<endl;
            insertionSort(s,5);
            int index;
            index = binarSearch(s,5,key);
            if(index != -1)
            {
                cout<<"Student found:"<<endl;
                cout<<endl;
                cout<<"Name::"<<s[index].name<<endl;
                cout<<"Roll number::"<<s[index].roll_no<<endl;
                cout<<"SGPA::"<<s[index].sgpa<<endl;
            }
            else{
                cout<<"Student not found"<<endl;

            }
            cout<<endl;
            break;
        case 7:
            cout<<"Exiting"<<endl;
            break;
        default:
            cout<<"Enter valid choice:"<<endl;
            cout<<endl;
        }


    }while(choice !=7);




    return 0;
}
