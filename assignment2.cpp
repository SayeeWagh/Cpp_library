#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

struct Node {
    char data;
    Node* next;
};

struct Stack {
    Node* top;

    Stack()
    {
        top = nullptr;
    }

    void push(char value)
    {
        Node* newNode= new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    char pop()
    {
        if(isEmpty())
        {
            cout<<"Stack is UnderFlow"<<endl;
            return'\0';
        }
        Node* temp = top;
        char value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }

    char peek()
    {
        if(isEmpty())
        {
            cout<<"Stack is empty"<<endl;
            return '\0';
        }
        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

};



bool isOperator(char c)
{
    return c == '+' || c == '*' || c == '/' || c == '^';
}

int precedence(char op)
{
    if(op == '+' || op == '-')
    {
        return 1;
    }
    if(op == '*' || op == '/')
    {
        return 2;
    }
    if(op == '^')
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

string infixTopostfix(string infix)
{
    Stack s;
    string postfix = "";

    for(int i = 0; i<infix.length(); i++)
    {
        char c= infix[i];

        if(isalnum(c))
        {
            postfix += c;
        }
        else if(c == '(')
        {
            s.push(c);
        }
        else if(c ==')')
        {
            while(!s.isEmpty() && s.peek() != '(')
            {
                postfix += s.pop();
            }
            s.pop();
        }
        else if(isOperator(c))
        {
            while(!s.isEmpty() && precedence(s.peek()) >= precedence(c))
            {
                postfix += s.pop();
            }
            s.push(c);
        }
    }

    while(!s.isEmpty())
    {
        postfix += s.pop();
    }

    return postfix;
}

string infixToprefix(string infix)
{
    Stack s;
    string reversedInfix = infix;
    string prefix ;

    reverse (reversedInfix.begin(),reversedInfix.end());

     for(char &c :reversedInfix )
     {
         if (c == '(')
         {
             c =')';
         }
         else if (c == ')')
         {
             c = '(';
         }
     }

     string postfix = infixTopostfix(reversedInfix);

     reverse(postfix.begin(),postfix.end());

     return postfix;

}

int evaluatePostfix(string postfix)
{
    Stack s;

    for(int i = 0; i<postfix.length(); i++)
    {
        char c = postfix[i];

        if(isdigit(c))
        {
            s.push(c - '0');
        }
        else if(isOperator(c))
        {
            int operand2 = s.pop();
            int operand1 = s.pop();
            int result;

            switch (c)
            {
                case '+':result = operand1 + operand2;break;
                case '-':result = operand1 - operand2;break;
                case '*':result = operand1 * operand2;break;
                case '/':result = operand1 / operand2;break;
            }

            s.push(result);
        }
    }

    return s.pop();
}

int evalutePrefix(string prefix)
{
    Stack s;

    reverse(prefix.begin(),prefix.end());

    for(int i = 0; i<prefix.length(); i++)
    {
        char c = prefix[i];

        if(isdigit(c))
        {
            s.push(c - '0');
        }
        else if(isOperator(c))
        {
            int operand2 = s.pop();
            int operand1 = s.pop();
            int result;

            switch (c)
            {
                case '+':result = operand1 + operand2;break;
                case '-':result = operand1 - operand2;break;
                case '*':result = operand1 * operand2;break;
                case '/':result = operand1 / operand2;break;
            }

            s.push(result);
        }
    }

    return s.pop();
}

int main()
{
    string infix;

    cout<<"Enter an infix expression:";
    cin>>infix;

    string postfix = infixTopostfix(infix);
    cout<<"Postfix Expression::"<<postfix<<endl;

    string prefix= infixToprefix(infix);
    cout<<"Prefix Expression::"<<prefix<<endl;

    cout<<"Postfix Evaluation::"<<evaluatePostfix(postfix)<<endl;
    cout<<"Prefix Evaluation::"<<evalutePrefix(prefix)<<endl;

    return 0;

}
