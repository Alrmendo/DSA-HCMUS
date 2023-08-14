#include <iostream>

using namespace std;


struct Node
{
    int key;
    Node* left;
    Node* right;
};

Node *createNode (int data)
{
    Node* newNode = new Node;
    newNode -> key = data;
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

int height(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        int left = height(root -> left);
        int right = height(root -> right);
        return max(left + 1, right + 1);
    }
}

void leftRotate(Node*& root)
{
    Node* r1 = root -> left;
    root -> left = r1 -> right;
    r1 -> right = root;

    root = r1;
}

void rightRotate(Node*& root)
{
    Node* r1 = root -> right;
    root -> right = r1 -> left;
    r1 -> left = root;

    root = r1;
}

void RebalanceAVL(Node*& root)
{
    int balance = height(root -> left) - height(root -> right);
    
    // nghieng ve trai
    if(balance >= 2)
    {
        // L-L rotation
        if(height(root -> left -> left) >= height(root -> left -> right))
        {
            leftRotate(root); // xoay sang phai
        }
        else
        {
            leftRotate(root -> right);
            rightRotate(root);
        }
    }

    // nghieng ve phai
    else if(balance <= -2)
    {
        // R-R rotation
        if(height(root -> right -> right) >= height(root -> right -> left))
        {
            rightRotate(root);
        }
        else
        {
            rightRotate(root -> left);
            leftRotate(root);
        }
    }
}

void Insert(Node*& root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
    }
    else if (data > root->key)
    {
        Insert(root->left, data);
    }
    else if (data < root->key)
    {
        Insert(root->right, data);
    }

    RebalanceAVL(root);
    return;
}

void NLR(Node*& root)
{
    if(root == NULL)
    {
        return;
    }
    cout << root -> key << " ";
    NLR(root -> left);
    NLR(root -> right);
}

void Remove(Node* &root, int x)
{
    if (root == NULL)
    {
        return;
    }

    if (x < root->key)
    {
        Remove(root->left, x);
    }
    else if (x > root->key)
    {
        Remove(root->right, x);
    }
    else // Tìm thấy nút có giá trị x
    {
        // Trường hợp 1: Nút không có con hoặc chỉ có một con
        if (root->left == NULL)
        {
            Node* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root;
            root = root->left;
            delete temp;
        }
        else // Trường hợp 2: Nút có cả hai con
        {
            // Tìm nút có giá trị nhỏ nhất trong cây con phải (duyệt LNR)
            Node* minRight = root->right;
            while (minRight->left != NULL)
            {
                minRight = minRight->left;
            }

            // Thay thế giá trị của nút hiện tại bằng giá trị nhỏ nhất từ cây con phải
            root->key = minRight->key;

            // Xóa nút có giá trị nhỏ nhất từ cây con phải
            Remove(root->right, minRight->key);
        }
    }

    RebalanceAVL(root);
}

bool isCorrectNode(Node* root, Node* &prev)
{
     if (root == NULL)
    {
        return true;
    }

    if (!isCorrectNode(root -> left, prev))
    {
        return false;
    }

    if (prev != NULL && root -> key <= prev -> key)
    {
        return false;
    }
    prev = root;

    return isCorrectNode(root -> right, prev);
}

bool isBST(Node* root)
{
    Node* prev = NULL;
    return isCorrectNode(root, prev);
}

bool isAVL(Node* root)
{
    if (!root)
    {
        return true;
    }

    if (isBST(root) == false)
    {
        return false;
    }

    int left_height, right_height;
    left_height = height(root->left);
    right_height = height(root->right);

    if (abs(left_height - right_height) <= 1 && isAVL(root->left) && isAVL(root->right))
    {
        return true;
    }

    return false;
}

int getBalance(Node* node) {
    if (node == NULL)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

bool isAVL_2(Node* root) {
    if (root == NULL)
    {
        return true;
    }

    int balance = getBalance(root);

    return (abs(balance) <= 1) && isAVL(root->left) && isAVL(root->right);
}

int main()
{
    Node* root = NULL;
    for (int i = 0; i < 10; ++i)
    {
        Insert(root, i);
    }
    NLR(root);
    cout << endl;

    if (isAVL(root)) //isAVL_2
    {
        cout << "is AVL tree" << endl;
    }
    else
    {
        cout << "is not AVL tree" << endl;
    }

    return 0;
}