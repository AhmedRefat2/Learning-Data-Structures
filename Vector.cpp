#include <assert.h>
#include <iostream>
using namespace std;

class Vector // Dynamic Array
{
private:
    int *arr {};
    int size {0}; // user size
    int capacity {}; // actual size
public:
    Vector(int size) : capacity(size * 2) // initializer list
    {
        if (size < 0)
            size = 1;
        arr = new int[capacity] { };
    }

    int get_size()
    {
        return size;
    }

    int get_capacity()
    {
        return capacity;
    }

    // get
    int get(int idx)
    {
        assert(0 <= idx && idx < size);
        return arr[idx];
    }

    // Set
    void set(int idx, int val)
    {
        assert(0 <= idx && idx < size);
        arr[idx] = val;
    }

    void print()
    {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << endl;
    }

    int find(int val)
    {
        for (int i = 0; i < size; ++i)
            if (arr[i] == val)
                return i; // index
        return -1; // not found
    }

    int get_front()
    {
        return arr[0];
    }

    int get_back()
    {
        return arr[size - 1];
    }


    /// Using Pointers Helps Us :
    /// 1. Create new One
    /// 2. Delete Old One


    void push_back(int val) // O(n) Time => Linear Number Of Steps
    {
        // 1. new array
        int *new_arr = new int[size + 1]; // size + 1 steps
        // 2. Copy Old Data
        for (int i = 0; i < size; ++i) // 3 size + 1 steps
            new_arr[i] = arr[i];
        // 3. Add new Element and Increase Size
        new_arr[size++] = val; // 2 steps
        // 4. Swap Pointers
        swap(arr, new_arr);  // 3 steps
        // 5. Delete Old array (Unless Data)
        delete[] new_arr; // size steps

        // total steps : 5 size + 7 steps => O(Size)
    }

    /// push_back enhancement
    /// capacity trick
    /// double size while size = capacity,
    /// Amortized Analysis,
    /// memory increase

    void expand_capacity()
    {
        capacity *= 2;
        cout<<"Expand capacity to : " << capacity<< "\n";
        int *new_arr = new int[capacity];
        for (int i = 0; i < size; ++i)
            new_arr[i] = arr[i];

        swap(new_arr, arr);
        delete[] new_arr;
    }

    void push_back_updated(int val)
    {
        if (size == capacity)
            expand_capacity();
        arr[size++] = val;
    }


    // Insert Function

    void insert (int pos, int val) // O(n)
    {
        assert(pos < size && pos >= 0);
        if (size == capacity)
            expand_capacity();
        for (int i = size; i > pos; --i) // 3(size-pos) + 1 steps => worst case O(size)
            arr[i] = arr[i - 1];
        arr[pos] = val;
        ++size;
    }

    /*
     Problem #1: Right rotation
        ● Consider our Vector class. Add the member function: void right_rotate()
        ● The function shifts every element 1 step towards the right.
            ○ What about the rightmost element? It goes to the first idx
        ● Example
        ● Assume the array content is: 0 1 2 3 4
        ● After a right rotation it will be: 4 0 1 2 3
            ○ Notice how, in this case, the '4' has been rotated to the head of the array!
        ● Ensure you avoid expanding the array's capacity
    */

    void right_rotate() // O(n)
    {
        int last_value =arr[size - 1];
        for (int i = size - 1; i > 0; --i)
            arr[i] = arr[i - 1];
        arr[0] = last_value;
    }


    /*
      Problem #2: Left rotation
        ● Consider our Vector class. Add the member function: void left_rotate()
        ● The function rotates the whole array 1 step to the left
            ○ However, in this case, the leftmost element will be 'rotated' around to the back of the array!
        ● Example
        ● Assume the array content is: 0 1 2 3 4
        ● After a left rotation, it will be: 1 2 3 4 0
            ○ Notice how the 0 has 'rotated' to the tail of the array after applying left_rotate()
        ● Ensure you avoid expanding the array's capacity
    */

    void left_rotate() // O(n)
    {
        int first_value = arr[0];
        for (int i = 0; i < size - 1; ++i)
            arr[i] = arr[i + 1];
        arr[size - 1] = first_value;
    }


    /*
      Problem #3: Right rotation with steps
        ● Implement void right_rotate(int times)
        ● This one applies the right rotation times time
        ● Assume array content is: 0 1 2 3 4
        ● right_rotate(2) ⇒ it will be: 3 4 0 1 2
        ● The challenge: times can be up to: 2000000000
        ● Your code should be efficient to some extent
    */

    void right_rotate(int times) // O(n^2)
    {
        times %= size;
        for (int i = 0; i < times; ++i)
            right_rotate();
    }

    // Onthor Solution

    void right_rotate_version2(int times) // O(n) time && O(n) memory
    {
        times %= size;
        int start_index_of_rotate = size - times;
        int *tempArr = new int[capacity]; // capacity steps
        for (int i = 0, j = start_index_of_rotate; i < times && j < size; ++i, ++j)
            tempArr[i] = arr[j];
        for (int i = times, j = 0; i < size && j < start_index_of_rotate; ++i, ++j)
            tempArr[i] = arr[j];

        // 2 For Loops = size steps

        swap(tempArr, arr); // 3 steps
        delete[] tempArr; // size steps

        // total time : size steps
    }

    /*
      Problem #4: Deleting a position
        ● Implement method int pop(int idx) in the vector class
        ● It returns the deleted value
        ● Remove this element from the array
        ● Assume array is: 4 0 1 2 3
        ● pop(2)
            ○ Return value 1
            ○ New array: 4 0 2 3
    */

    int pop(int idx)
    {
        assert(0 <= idx && idx < size);
        int val = arr[idx];
        for (int i = idx; i < size - 1; ++i)
            arr[i] = arr[i + 1]; // shift left
        --size;
        return val;
    }


    /*
        Problem #5: Improved search
        ● Assume our vector is huge and we do many find() calls for almost a few small
        repetitive values
        ● One way to improve the code speed is: each time you find the value, you
        shift it one step to the left
        ● Eventually, the values that are queried a lot, will move to the head of array
        ● Implement method: int find_transposition(int value)
            ○ It returns the found position, but consider moving it one step to the left
        ● Example: 10 20 30 40 50. find_transposition(30)
            ○ New array 10 30 20 40 50
            ○ Return 1
    */

    int find_transposition(int value)
    {
        if (arr[0] == value) // found in the first index
            return 0;
        for (int i = 1; i < size; ++i)
            if (arr[i] == value)
            {
                swap(arr[i], arr[i - 1]);
                return i - 1;
            }
        return -1; // not found
    }


    ~Vector() // To handle memory leak
    {
        delete[] arr;
        arr = nullptr;
    }
};

int main()
{

    // Vector v(10);
    // for (int i = 0; i < 10; ++i)
    //     v.set(i, i + 1);
    //
    // v.print();
    // cout<<"index of Number 5: " << v.find(5)<<endl; // index = 4

    //////////////////////////////////////////////////////////////

    // Vector v(4);
    // v.set(0, 1);
    // v.set(1, 2);
    // v.set(2, 3);
    // v.set(3, 4);
    //
    // v.print();  // 1 2 3 4
    //
    // v.push_back(5);
    // v.push_back(6);
    // v.push_back(7);
    //
    // v.print(); // 1 2 3 4 5 6 7
    //

    /// Imagine this code
    /// for (int i = 0; i < 1000000; ++i)
    ///     v.push_back(i);
    /// 1 + 2 + 3 + 4 ...... = n * (n + 1) / 2 => O(N^2)

    ///////////////////////////////////////////////////////////////

    // Vector v(3); // size = 3 , capacity = 6
    //
    // v.push_back_updated(1); // size = 1
    // v.push_back_updated(2); // size = 2
    // v.push_back_updated(3);
    // v.push_back_updated(4);
    // v.push_back_updated(5); // size = 5
    // v.push_back_updated(6); // size = 6, capacity = 6
    // v.push_back_updated(7); // expand capacity to 12
    //
    // v.print();
    ////////////////////////////////////////////////////////

    /// Testing push_back_updated right_rotate - left-rotate - times
    /// Testing pop()
    /// Testing Improved Search

    // Vector v(3);
    //
    // for (int i = 1; i <= 6; ++i)
    //     v.push_back_updated(i);
    //
    // v.print(); // 1 2 3 4 5 6
    // v.right_rotate();
    // v.print(); // 6 1 2 3 4 5
    //
    // v.left_rotate();
    // v.print(); // 1 2 3 4 5 6
    //
    // v.right_rotate(4);
    // v.print(); // 3 4 5 6 1 2
    //
    // v.right_rotate_version2(2); // return to original array
    // v.print(); // 1 2 3 4 5 6
    //
    //
    // v.pop(2);
    // v.print(); // 1 2 4 5 6
    // cout<<"size now = "<<v.get_size()<<" Capacity = " << v.get_capacity()<<endl; // 5 6
    //
    // int idx = v.find_transposition(2); // return new index after transportaion
    //
    // cout<<"idx of value 2 = "<<idx<<endl; // 0
    // v.print(); // 2 1 4 5 6

    ////////////////////////////////////////////////////////////////

    return 0;
}
