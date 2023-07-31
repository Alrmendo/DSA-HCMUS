#include <iostream>
#include <cstring>

using namespace std;

// --- Bai a
void toBinary(int x) 
{
    if (x > 1) 
    {
        toBinary(x / 2);
    }
    cout << x % 2;
}

// --- Bai b
int sumOfDigits(int x) 
{
    if (x == 0) 
    {
        return 0;
    }
    return x % 10 + sumOfDigits(x / 10);
}

// --- Bai c
bool isPalindrome(int l, int r, char* s) 
{
    if (l >= r) 
    {
        return true;
    }
    return (s[l] == s[r]) && isPalindrome(l + 1, r - 1, s);
}

int main() 
{
    int choice, result;
    do{
        cout << "Choose the function to test:\n";
        cout << "1. Binary representation\n";
        cout << "2. Sum of digits\n";
        cout << "3. Palindrome check\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                int num_a;
                cout << "Enter a number to convert to binary: ";
                cin >> num_a;
                cout << "Binary representation of " << num_a << ": ";
                toBinary(num_a);
                cout << endl;
                break;

            case 2:
                int num_b;
                cout << "Enter a number to find the sum of its digits: ";
                cin >> num_b;
                cout << "Sum of digits of " << num_b << ": " << sumOfDigits(num_b) << endl;
                break;

            case 3:
                char str[100];
                cout << "Enter a string to check if it is a palindrome: ";
                cin >> str;
                result = isPalindrome(0, strlen(str) - 1, str);
                if (result == true)
                {
                    cout << "YES" << endl;
                }
                else {
                    cout << "NO" << endl;
                }
                break;

            default:
                cout << "Invalid choice. Please choose 1, 2, or 3.\n";
        }
        cout << endl;

    } while (choice != 0);

    return 0;
}