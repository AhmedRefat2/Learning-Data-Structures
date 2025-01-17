#include <iostream>
#include <cassert>
using namespace std;


/*
    * Stack is a logical Data Structure
    * LIFO : Last_In First_Out
    * Stack ADT
    *   - Push(x) -> Add Element at the top
    *   - Pop()   -> Remove The element at the Top
    *   - Peek()  -> return the top
    * 2 Physical Models Of Memory
    *   - Consecutive -> Array
    *   - Scatterd -> Linked List
 */


////////////////// Using Array ////////////////////////

class Stack
{
private:
    int top{};
    int size{};
    int *arr{};
public:
    Stack(int size):size(size), top(-1)
    {
        arr = new int[size];
    };

    ~Stack()
    {
        delete[] arr;
    }


    // 1. push_back()
    void push_back(int element)
    {
        if (!is_full())
            arr[++top] = element;
        else
            cout<<"Stack Overflow"<<endl;
    }

    void pop()
    {
        assert(!is_empty());
        cout<<"The element "<<arr[top--]<<" is removed from the stack"<<endl;
    }

    int peek()
    {
        assert(!is_empty());
        return arr[top];
    }

    void Print()
    {
        for (int i = top; i >=0; --i)
            cout<<arr[i]<<" ";
        cout<<endl;
    }

    // is_empty
    bool is_empty()
    {
        return top == -1;
    }
    // is_full
    bool is_full()
    {
        return top == size - 1;
    }


};



int main()
{

    Stack S(5); // arr = 5 elements empty

    S.push_back(1);
    S.push_back(2);
    S.push_back(3);
    S.push_back(4);
    S.push_back(5);


    cout<<S.is_full()<<endl; // true
    S.Print(); // 5 4 3 2 1

    cout<<S.peek()<<endl; // 5
    S.pop(); // pop 5

    cout<<S.peek()<<endl; // 4
    S.Print(); // 4 3 2 1


    return 0;
}

