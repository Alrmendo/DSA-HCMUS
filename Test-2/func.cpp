#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <queue>
#include <cctype>

using namespace std;

struct Flight
{
    string src;      // source
    string des;      // destination
    string airliner; // name of airliner
    int eco;         // economy seats
    int bus;         // business seats
    int hours;
    int mins;
};

struct Node
{
    Flight base;
    Node *left;
    Node *right;
};

void print_preorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->base.src << "," << root->base.des << "," << root->base.airliner << "," << root->base.eco << "," << root->base.bus << "," << root->base.hours << "," << root->base.mins << "\n";
    print_preorder(root->left);
    print_preorder(root->right);
}

void del_tree(Node *&root)
{
    if (root == NULL)
        return;
    del_tree(root->left);
    del_tree(root->right);
    delete root;
    root = NULL;
}

Flight getFlight(string line)
{
    stringstream s(line);
    string buf;
    Flight f;

    // Trích xuất nguồn và điểm đến
    getline(s, buf, '\"');   // Đọc đến dấu ngoặc kép đầu tiên
    getline(s, f.src, ',');  // Đọc đến dấu phẩy
    getline(s, f.des, '\"'); // Đọc đến dấu ngoặc kép đóng

    // Trích xuất tên hãng hàng không
    getline(s, buf, '\"');        // Đọc đến dấu ngoặc kép tiếp theo
    getline(s, f.airliner, '\"'); // Đọc đến dấu ngoặc kép đóng

    // Trích xuất số ghế hạng thương gia
    getline(s, buf, '\"'); // Đọc đến dấu ngoặc kép tiếp theo
    getline(s, buf, ' ');  // Đọc đến dấu cách tiếp theo
    f.bus = stoi(buf);

    // Trích xuất số ghế hạng phổ thông
    getline(s, buf, ' '); // Đọc đến dấu cách tiếp theo
    getline(s, buf, ' '); // Đọc đến dấu cách tiếp theo
    f.eco = stoi(buf);

    // Trích xuất thời gian bay (hours)
    getline(s, buf, '\"');
    getline(s, buf, '\"');
    getline(s, buf, ' ');
    f.hours = stoi(buf);

    // Trích xuất thời gian bay (minutes)
    getline(s, buf, ' ');
    getline(s, buf, ' ');

    if (buf == "hours\"]}" || buf == "hour\"]}")
    {
        f.mins = 0;
    }
    else if (buf == "minutes\"]}" || buf == "minute\"]}")
    {
        f.mins = f.hours;
        f.hours = 0;
    }
    else
    {
        f.mins = stoi(buf);
    }
    return f;
}

void readFile(string flightdata_filename, vector<Flight> &data)
{
    ifstream is(flightdata_filename.c_str());
    string buf;

    while (!is.eof())
    {
        getline(is, buf, '\n');
        data.push_back(getFlight(buf));
    }
    is.close();
}

void readFileData(string data_filename, string &level_list, char &ch)
{
    ifstream in(data_filename.c_str());
    if (!in.is_open())
    {
        cout << "Can't read data file" << endl;
        return;
    }
    getline(in, level_list);
    in >> ch;
}

Node *createNode(Flight f)
{
    Node *n = new Node;
    n->base = f;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void insert(Node *&root, Flight &f)
{
    if (root == NULL)
    {
        root = createNode(f);
        return;
    }

    if (f.src > root->base.src)
    {
        insert(root->right, f);
    }
    else if (f.src < root->base.src)
    {
        insert(root->left, f);
    }
    else
    {
        int totalnew = f.hours * 60 + f.mins;
        int totalroot = root->base.hours * 60 + root->base.mins;

        if (totalnew > totalroot)
            insert(root->right, f);
        else if (totalnew < totalroot)
            insert(root->left, f);
        else
        {
            if (f.des > root->base.des)
                insert(root->right, f);
            else if (f.des < root->base.des)
                insert(root->left, f);
        }
    }
}

void insertFlight(Node *&root, vector<Flight> flights)
{
    for (int i = 0; i < flights.size(); ++i)
    {
        if (flights[i].src[0] == flights[i].des[0])
        {
            insert(root, flights[i]);
        }
    }
}

// cau 2
bool checkLevel(vector<int> level, int currentLevel)
{
    for (int i = 0; i < level.size(); ++i)
    {
        if (currentLevel == level[i])
        {
            return true;
        }
    }
    return false;
}

void print_levellist(Node *root, string level_list)
{
    stringstream ss(level_list);
    vector<int> level;
    string buf;

    while (getline(ss, buf, '.'))
    {
        if (buf == " ")
        {
            break;
        }
        level.push_back(stoi(buf));
    }

    if (root == NULL)
    {
        return;
    }

    queue<Node *> queue;
    queue.push(root);
    int currentLevel = 0;

    while (!queue.empty())
    {
        Node *curr = queue.front();
        int numNodeLevel = queue.size();
        while (numNodeLevel > 0)
        {
            if (checkLevel(level, currentLevel))
            {
                cout << curr->base.src << "," << curr->base.des << "," << curr->base.airliner << "," << curr->base.eco << "," << curr->base.bus << "," << curr->base.hours << "," << curr->base.mins << "\n";
            }
            queue.pop();
            if (!queue.empty())
            {
                curr = queue.front();
            }
            if (curr->right != NULL)
            {
                queue.push(curr->right);
            }
            if (curr->left != NULL)
            {
                queue.push(curr->left);
            }
            --numNodeLevel;
        }
        ++currentLevel;
    }
}

// Cau 3

void Remove(Node *&root, string x)
{
    if (root == NULL)
    {
        return;
    }
    else if (x < root->base.src)
    {
        Remove(root->left, x);
    }
    else if (x > root->base.src)
    {
        Remove(root->right, x);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            Node *minRight = root->right;
            while (minRight->left == NULL)
            {
                minRight = minRight->left;
            }
            root->base.src = minRight->base.src;
            Remove(root->right, minRight->base.src);
        }
    }
}

bool check(string &src, char &ch)
{
    if (toupper(src[0]) < toupper(ch))
    {
        // chuyển đổi ký tự đầu tiên của chuỗi src và ký tự ch thành chữ cái hoa (uppercase)
        // để thực hiện so sánh không phân biệt chữ hoa hay chữ thường
        return true;
    }
    return false;
}

void removeChar(Node *&root, char &ch)
{
    if (root == NULL)
    {
        return;
    }
    removeChar(root->left, ch);
    removeChar(root->right, ch);

    if (check(root->base.src, ch))
    {
        Remove(root, root->base.src);
    }
}

void findMaxSeatsPathDFS(Node *currentNode, string &maxPath, int &maxSeats, string currentPath, int currentSeats)
{
    if (currentNode == NULL)
    {
        if (currentSeats > maxSeats)
        {
            maxSeats = currentSeats;
            maxPath = currentPath;
        }
        return;
    }

    currentPath += currentNode->base.src + "," + currentNode->base.des + " -> ";
    currentSeats += currentNode->base.bus + currentNode->base.eco;

    findMaxSeatsPathDFS(currentNode->left, maxPath, maxSeats, currentPath, currentSeats);
    findMaxSeatsPathDFS(currentNode->right, maxPath, maxSeats, currentPath, currentSeats);
}

void ex4(Node *root)
{
    string maxPath = "";
    int maxSeats = 0;
    findMaxSeatsPathDFS(root, maxPath, maxSeats, "", 0);

    cout << "Maximum total seats: " << maxSeats << endl;
    cout << "Path with maximum seats: " << maxPath << endl;
}

void todo(string flightdata_filename, string data_filename)
{
    Node *root = NULL;
    vector<Flight> dataFlight;
    string level_list;
    char ch;

    readFile(flightdata_filename, dataFlight);
    readFileData(data_filename, level_list, ch);
    insertFlight(root, dataFlight);
    cout << "========================" << endl;
    print_levellist(root, level_list);
    cout << "========================" << endl;
    insertFlight(root, dataFlight);
    removeChar(root, ch);
    print_levellist(root, level_list);
    cout << "========================" << endl;
    ex4(root);
}

int main()
{
    todo("g1.v2.jl", "data.txt");
}