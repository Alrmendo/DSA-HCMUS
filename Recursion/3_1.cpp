#include <iostream>
#include <math.h>

using namespace std;

// --- Bai a
int sum_of_intergers(int n)
{
    if(n == 1)
    {
        return 1;
    }
    else
    {
        return n + sum_of_intergers(n - 1);
    }
}

// --- Bai b
double sum_of_fraction(int n)
{
    if(n == 1)
    {
        return 1.0;
    }
    else
    {
        return 1.0 / n + sum_of_fraction(n - 1);
    }
}

// --- Bai c
int factorial(int n)
{
    if(n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

// --- Bai d
double powerRecursive(double x, int n) 
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return x * powerRecursive(x, n - 1);
    }
}

// --- Bai e
double sumOfPowersRecursive(double x, int n) 
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return pow(x, 2 * n) + sumOfPowersRecursive(x, n - 1);
    }
}

// --- Bai f
int fibonacci(int n) 
{
    if (n == 0 || n == 1) 
    {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}


int main() 
{
    int choice, n;
    double x, result;

    do {
        cout << "===== ASSIGNMENT 1 MENU =====" << endl;
        cout << "1. Sum of integers (Bai a)" << endl;
        cout << "2. Sum of fractions (Bai b)" << endl;
        cout << "3. Factorial (Bai c)" << endl;
        cout << "4. Power of x (Bai d)" << endl;
        cout << "5. Sum of powers of x (Bai e)" << endl;
        cout << "6. Fibonacci (Bai f)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a positive integer value for n: ";
                cin >> n;
                cout << "S(" << n << ") = " << sum_of_intergers(n) << endl;
                break;
            case 2:
                cout << "Enter a positive integer value for n: ";
                cin >> n;
                cout << "S(" << n << ") = " << sum_of_fraction(n) << endl;
                break;
            case 3:
                cout << "Enter a non-negative integer value for n: ";
                cin >> n;
                cout << "T(" << n << ") = " << factorial(n) << endl;
                break;
            case 4:
                cout << "Enter a value for x: ";
                cin >> x;
                cout << "Enter an integer value for n: ";
                cin >> n;
                cout << "T(" << x << ", " << n << ") = " << powerRecursive(x, n) << endl;
                break;
            case 5:
                cout << "Enter a real value for x: ";
                cin >> x;
                cout << "Enter a non-negative integer value for n: ";
                cin >> n;
                cout << "S(" << x << ", " << n << ") = " << sumOfPowersRecursive(x, n) << endl;
                break;
            case 6:
                cout << "Enter a non-negative integer value for n: ";
                cin >> n;
                cout << "f(" << n << ") = " << fibonacci(n) << endl;
                break;
            case 0:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
        cout << endl;

    } while (choice != 0);

    return 0;
}