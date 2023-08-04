#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

template<class T>
struct Node 
{
    T key;
    Node* next;
    Node(T data, Node* pNext) : key(data), next(pNext) {}
};

struct FRACTION 
{
    int numerator;
    int denominator;
    FRACTION(int num = 0, int denom = 1) : numerator(num), denominator(denom) {}

    bool operator>(const FRACTION& other) const {
        return (numerator * other.denominator) > (other.numerator * denominator);
    }

    bool operator<(const FRACTION& other) const {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }

    bool operator>=(const FRACTION& other) const {
        return (numerator * other.denominator) >= (other.numerator * denominator);
    }

    bool operator<=(const FRACTION& other) const {
        return (numerator * other.denominator) <= (other.numerator * denominator);
    }
};

istream& operator>> (istream& inDev, FRACTION& f) 
{
    inDev >> f.numerator >> f.denominator;
    return inDev;
}

ostream& operator << (ostream& outDev, FRACTION a) 
{
    outDev << a.numerator << '/' << a.denominator;
    return outDev;
}

template<class T>
bool increase(T a, T b) 
{
    return a < b;
}

template<class T>
bool decrease(T a, T b) 
{
    return a > b;
}

template<class T>
Node<T>* createNode(T data) 
{
    Node<T>* newNode = new Node<T>(data, NULL);
    return newNode;
}

template<class T>
void makeOrderedList(Node<T>*& h, T k, bool(*order)(T, T)) 
{
    Node<T>* p1 = h, * p2 = p1->next;
    while (p2 && order(p2->key, k)) 
    {
        p1 = p2;
        p2 = p1->next;
    }
    Node<T>* p = createNode(k);
    p1->next = p; p->next = p2;
}

template<class T>
void printList(Node<T>* head) 
{
    if (head == NULL) 
    {
        return;
    }
    Node<T>* curNode = head;
    while (curNode != NULL) 
    {
        cout << curNode->key << "->";
        curNode = curNode->next;
    }
    cout << '\n';
}

template<class T>
void deleteList(Node<T>*& head) 
{
    while (head != NULL) 
    {
        Node<T>* resNode = head;
        head = head->next;
        delete resNode;
    }
}

int main() 
{
    Node<int>* intDummyNode = new Node<int>(INT_MAX, NULL);
    Node<string>* stringDummyNode = new Node<string>("", NULL);
    Node<FRACTION>* fractionDummyNode = new Node<FRACTION>(FRACTION(0, 1), NULL);
    string str = "";
    int data;
    FRACTION frac(0, 1);
    int choice = 0;
    int iOrder;

    cout << "Choose order of the list:\n";
    cout << "1. Increase.\n";
    cout << "2. Decrease.\n";
    cout << "Enter your choice: ";
    cin >> iOrder;

    while (iOrder != 1 && iOrder != 2) 
    {
        cout << "Invalid! Please enter again: ";
        cin >> iOrder;
    }

    do {
        cout << "=== Menu ===\n";
        cout << "1. Integer\n";
        cout << "2. String\n";
        cout << "3. Fraction\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter an integer: ";
                cin >> data;
                if (iOrder == 1) 
                {
                    makeOrderedList(intDummyNode, data, increase<int>);
                } else {
                    makeOrderedList(intDummyNode, data, decrease<int>);
                }
                cout << "Current list: ";
                printList(intDummyNode->next);
                break;

            case 2:
                cout << "Enter a string: ";
                cin.ignore();
                getline(cin, str);
                if (iOrder == 1) {
                    makeOrderedList(stringDummyNode, str, increase<string>);
                } else {
                    makeOrderedList(stringDummyNode, str, decrease<string>);
                }
                cout << "Current list: ";
                printList(stringDummyNode->next);
                break;

            case 3:
                cout << "Enter a fraction (numerator denominator): ";
                cin >> frac.numerator >> frac.denominator;
                if (iOrder == 1) {
                    makeOrderedList(fractionDummyNode, frac, increase<FRACTION>);
                } else {
                    makeOrderedList(fractionDummyNode, frac, decrease<FRACTION>);
                }
                cout << "Current list: ";
                printList(fractionDummyNode->next);
                break;

            case 4:
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 4);

    deleteList(intDummyNode);
    deleteList(stringDummyNode);
    deleteList(fractionDummyNode);
    system("pause");
    return 0;
}