#include <iostream>

using namespace std;

void print_array(int arr[], int size, int i)
{
    if(i >= size)
    {
        return;
    }

    cout << arr[i] << " ";
    print_array(arr, size, i + 1);
}

void print_array_reverse(int arr[], int size, int i)
{
    if (i < 0)
    {
        return;
    }

    cout << arr[i] << " ";
    print_array_reverse(arr, size, i - 1);
}

int sum_of_positive(int arr[], int size, int i)
{
    if(i >= size)
    {
        return 0;
    }
    if(arr[i] > 0)
    {
        return arr[i] + sum_of_positive(arr, size, i + 1);
    }
    else
    {
        return sum_of_positive(arr, size, i + 1);
    }
}

bool is_duplicate(int arr[], int size, int i, int value)
{
    // Base case: If the current index is equal to or greater than the array size, return false.
    if (i >= size)
    {
        return false;
    }

    // Recursive case: If the current element is equal to the value, return true (duplicate found).
    // Otherwise, call is_duplicate with the next index.
    if (arr[i] == value)
    {
        return true;
    }
    else
    {
        return is_duplicate(arr, size, i + 1, value);
    }
}

int count_distinct(int arr[], int size, int i)
{
    // Base case: If the current index is equal to or greater than the array size, return 0.
    if (i >= size)
    {
        return 0;
    }

    // Recursive case: If the current element is not a duplicate, increment the count,
    // then call count_distinct with the next index.
    int current_element = arr[i];
    if (!is_duplicate(arr, size, i + 1, current_element))
    {
        return 1 + count_distinct(arr, size, i + 1);
    }
    else
    {
        return count_distinct(arr, size, i + 1);
    }
}

bool all_odd(int arr[], int size, int i)
{
    if (i >= size)
    {
        return true;
    }
    if (arr[i] % 2 == 0)
    {
        return false;
    }
    else
    {
        return all_odd(arr, size, i + 1);
    }
}

int find_max(int arr[], int size, int i, int MAX)
{
    if (i >= size)
    {
        return MAX;
    }
    if (arr[i] > MAX)
    {
        return find_max(arr, size, i + 1, arr[i]);
    }
    else
    {
        return find_max(arr, size, i + 1, MAX);
    }
}

int main()
{
    int size;

    cout << "Enter the size of the array: ";
    cin >> size;

    int arr[size];

    cout << "Enter elements:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "a[" << i + 1 << "] = ";
        cin >> arr[i];
    }

    int choice;
    while (true)
    {
        cout << "\n===== Menu =====" << endl;
        cout << "1. Print the array" << endl;
        cout << "2. Print the array in reverse" << endl;
        cout << "3. Sum of positive numbers in the array" << endl;
        cout << "4. Number of distinct values in the array" << endl;
        cout << "5. Check if the array contains only odd numbers" << endl;
        cout << "6. Find the maximum value in the array" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Array: ";
            print_array(arr, size, 0);
            cout << endl;
            break;
        case 2:
            cout << "Array in reverse: ";
            print_array_reverse(arr, size, size - 1);
            cout << endl;
            break;
        case 3:
            cout << "Sum of positive numbers in the array: " << sum_of_positive(arr, size, 0) << endl;
            break;
        case 4:
            cout << "Number of distinct values in the array: " << count_distinct(arr, size, 0) << endl;
            break;
        case 5:
            if (all_odd(arr, size, 0))
                cout << "The array contains only odd numbers" << endl;
            else
                cout << "The array does not contain only odd numbers" << endl;
            break;
        case 6:
            cout << "The maximum value in the array is: " << find_max(arr, size, 0, arr[0]) << endl;
            break;
        case 7:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}