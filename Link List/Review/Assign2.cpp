#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student
{
    int ID;
    char Name[50];
    double GPA;
};

struct Node
{
    Student base;
    Node* next;
};

Node* createNode(const Student& student)
{
    Node* newNode = new Node;
    newNode->base = student;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node*& head, const Student& student)
{
    Node* newNode = createNode(student);
    newNode->next = head;
    head = newNode;
}

bool isValidName(const char* name)
{
    /*
    1. The name is not empty.
    2. The first character of the name is an uppercase letter.
    3. The name contains at least one space.
    */

    while (strlen(name) > 0) // ensures that the string is not empty
    {
        // strchr function searches for the specified character in the string.
        // It return NULL if its not found
        if(name[0] >= 'A' && name[0] <= 'Z' && strchr(name, ' ') != NULL) // This part ensures that the name contains at least one space.
        {
            // This condition checks if the first character of the string name is a uppercase letter.
            // It validates that the name starts with an uppercase letter.
            return true;
        }
        return false;
    }
    return false;
}

void outputList(Node* head, const char* filename)
{
    ofstream file(filename);
    if(!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    Node* cur = head;
    while(cur != NULL)
    {
        file << cur -> base.ID << "\n" << cur -> base.Name << "\n" << cur -> base.GPA << "\n";
        cur = cur->next;
    }

    file.close();
}

void readFile(const char* filename, Node*& head)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    while (!inputFile.eof())
    {
        Student student;

        inputFile >> student.ID;
        inputFile.ignore(); // Ignore the newline character

        inputFile.getline(student.Name, 50);

        inputFile >> student.GPA;
        inputFile.ignore(); // Ignore the newline character

        cout << "Read GPA: " << student.GPA << endl;

        insertNode(head, student);
    }
    inputFile.close();
}

Node* findMaxGPA(Node* head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node* cur = head->next;  // Start from the second node
    Node* maxGPA = head;

    while (cur != nullptr)
    {
        if (cur->base.GPA > maxGPA->base.GPA)
        {
            maxGPA = cur;
        }
        cur = cur->next;
    }

    return maxGPA;
}

void deleteLL(Node*& head)
{
    while (head != NULL) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.txt";

    Node* head = NULL;

    readFile(inputFileName, head);

    Node* validStudent = NULL;
    Node* cur = head;
    while (cur != NULL)
    {
        if (isValidName(cur->base.Name))
        {
            insertNode(validStudent, cur->base);
        }
        cur = cur->next;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        cout << "Error opening output file" << endl;
        return 1;
    }
    else
    {
        outputFile << "List with all students:\n";
        outputList(head, outputFileName);

        outputFile << "\nList with valid students:\n";
        outputList(validStudent, outputFileName);
    }

    Node* maxGPA = findMaxGPA(validStudent);
    if (maxGPA != NULL)
    {
        outputFile << "\nStudent with max GPA:\n"
                   << "ID: " << maxGPA->base.ID << "\n"
                   << "Name: " << maxGPA->base.Name << "\n"
                   << "GPA: " << maxGPA->base.GPA << "\n";
    }
    else
    {
        outputFile << "\nNo valid student found." << endl;
    }

    outputFile.close();

    deleteLL(head);
    deleteLL(validStudent);

    return 0;
}