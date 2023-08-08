#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Date 
{
    int year;
    int month;
    int day;
};

struct Node 
{
    Date date;
    Node* next;
};

bool compareDates(const Date& date1, const Date& date2) 
{
    if (date1.year != date2.year) 
    {
        return date1.year < date2.year;
    }
    if (date1.month != date2.month) 
    {
        return date1.month < date2.month;
    }
    return date1.day < date2.day;
}

Node* createNode(const Date& date) 
{
    Node* newNode = new Node;
    newNode->date = date;
    newNode->next = nullptr;
    return newNode;
}

void insertSorted(Node*& head, const Date& date) 
{
    if (head == nullptr || compareDates(date, head->date)) 
    {
        Node* newNode = createNode(date);
        newNode->next = head;
        head = newNode;
    } 
    else 
    {
        Node* current = head;
        while (current->next != nullptr && compareDates(current->next->date, date)) 
        {
            current = current->next;
        }
        Node* newNode = createNode(date);
        newNode->next = current->next;
        current->next = newNode;
    }
}

void readDatesFromFile(const string& filename, Node*& head) 
{
    ifstream inputFile(filename);
    if (!inputFile.is_open()) 
    {
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        stringstream ss(line);
        Date date;
        ss >> date.year >> date.month >> date.day;
        insertSorted(head, date);
    }
}

int main() 
{
    Node* head = nullptr;

    readDatesFromFile("input.txt", head);

    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) 
    {
        cout << "Could not open output.txt" << endl;
        return 1;
    }

    Node* current = head;
    while (current != nullptr) 
    {
        outputFile << current->date.year << " " << current->date.month << " " << current->date.day << endl;
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    cout << "Dates have been sorted and saved to output.txt" << endl;

    return 0;
}
