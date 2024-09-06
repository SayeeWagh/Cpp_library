#include <iostream>

using namespace std;

const int SIZE =3;
int queue[SIZE];
int front=-1;
int rear=-1;


int insertion(int value)
{
    if((rear+1)%SIZE==front){

        cout<<"Queue Is Full!!"<<endl;
        cout<<endl;
    }
    else{

        if(front==-1)
        {
            front=0;
        }
        rear=(rear+1)%SIZE;
        queue[rear]=value;
        cout<<value<<" Inserted In The Queue..."<<endl;
        cout<<endl;
    }
}

int deletion()
{

    if(front==-1)
    {
        cout<<"Queue Is Empty!!"<<endl;
        cout<<endl;
    }
    else{
        cout<<queue[front]<<" Is Deleted From The Queue..."<<endl;
        cout<<endl;
        if(front==rear)
        {
            front = rear = -1;
        }
        else{
            front=(front+1)%SIZE;
        }
    }
}

void display()
{
    if(front==-1)
    {
        cout<<"Queue Is Empty!!!"<<endl;
        cout<<endl;
    }
    else{
        cout<<"Queue Elements Are::"<<endl;
        int i;
        for(i=front;i<=rear;i++)
        {
            cout<<queue[i]<<" ";
            i=(i+1)%SIZE;
        }
        cout<<queue[rear]<<endl;
    }
}

int main()
{
    int value,ch;
    char op;



    do{
        cout<<"Circular Queue Operations:"<<endl;
        cout<<endl;
        cout<<"1.Insertion \n2.Deletion \n3.Display"<<endl;
        cout<<endl;

        cout<<"Enter Your Choice:";
        cin>>ch;
        cout<<endl;
        switch(ch)
        {
        case 1:
            {
                cout<<"Enter The Value You Want To Insert To The Queue:";
                cin>>value;


                insertion(value);
                break;
            }
        case 2:
            {
                deletion();
                break;
            }
        case 3:
            {
                display();
                break;
            }
        default:
            {
                cout<<"Enter The Valid Choice"<<endl;
                cout<<endl;
                break;
            }

        }
        cout<<"Do You Want To Continue?(y/n):";
        cin>>op;
        cout<<endl;
    }
    while(op=='y' || op=='Y' );
    return 0;
}


