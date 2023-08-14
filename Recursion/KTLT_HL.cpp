#include <iostream>

using namespace std;

bool isPrime(int num) 
{
    if (num <= 1)
    {
        return false;
    }

    for (int i = 2; i * i <= num; ++i) 
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool isPerfect(int num) 
{
    int sum = 1;
    for (int i = 2; i * i <= num; ++i) 
    {
        if (num % i == 0) 
        {
            sum += i;
            if (i != num / i)
            {
                sum += num / i;
            }
        }
    }
    return sum == num;
}

int countPrimes(const int arr[], int size, int index) 
{
    if (index < 0)
    {
        return 0;
    }

    int count = 0;

    if (isPrime(arr[index])) 
    {
        count = 1;
    }

    return count + countPrimes(arr, size, index - 1);
}

int countPerfectNumbers(const int arr[], int size, int index) 
{
    if (index < 0)
    {
        return 0;
    }

    int count = 0;

    if (isPerfect(arr[index])) 
    {
        count = 1;
    }

    return count + countPerfectNumbers(arr, size, index - 1);
}

int sumEvenNumbers(const int arr[], int size, int index) 
{
    if (index < 0)
    {
        return 0;
    }

    int sum = 0;

    if (arr[index] % 2 == 0) 
    {
        sum = arr[index];
    }

    return sum + sumEvenNumbers(arr, size, index - 1);
}

void listPrimeIndices(const int arr[], int size, int index) 
{
    if (index < 0)
    {
        return;
    }

    listPrimeIndices(arr, size, index - 1);

    if (isPrime(arr[index])) 
    {
        cout << index << " ";
    }
}

void listEvenIndices(const int arr[], int size, int index) 
{
    if (index < 0)
    {
        return;
    }

    listEvenIndices(arr, size, index - 1);

    if (arr[index] % 2 == 0) 
    {
        cout << index << " ";
    }
}

int main() 
{
    const int size = 8;
    int arr[size] = {2, 4, 7, 9, 16, 17, 25, 28};

    cout << "Number of prime numbers: " << countPrimes(arr, size, size - 1) << endl;
    cout << "Number of perfect numbers: " << countPerfectNumbers(arr, size, size - 1) << endl;
    cout << "Sum of even numbers: " << sumEvenNumbers(arr, size, size - 1) << endl;

    cout << "Indices of prime numbers: ";
    listPrimeIndices(arr, size, size - 1);
    cout << endl;

    cout << "Indices of even numbers: ";
    listEvenIndices(arr, size, size - 1);
    cout << endl;

    return 0;
}
