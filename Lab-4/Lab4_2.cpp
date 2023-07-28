#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct NODE{
    int key; // du lieu cua Node ==> du lieu ma Node se luu tru
    NODE* left;
    NODE* right;
};

// --- 1. Initialize a NODE from a given value
NODE* createNode(int data)
{
    NODE* newNode = new NODE;
    newNode -> key = data;
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

// --- 2. Add a NODE with given value into a given Binary Search Tree
void Insert(NODE* &pRoot, int x)
{
    if(pRoot == NULL) // neu khong co phan tu nao
    {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot -> key)
    {
        Insert(pRoot -> left, x); // pRoot->left se la phan tu tiep theo (Root luc nay la phan tu dau tien ben trai)
    }
    else if (x > pRoot -> key)
    {
        Insert(pRoot -> right, x); // pRoot->right se la phan tu tiep theo (Root luc nay la phan tu dau tien ben phai)
    }
}

// --- 12. Initialize a Binary Search Tree from a given array
NODE* createTree(int a[], int n)
{
    NODE* pRoot = new NODE;
    pRoot = NULL;
    for (int i = 0; i < n; ++i)
    {
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

// --- 3. Pre-order Traversal
void NLR(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    cout << pRoot -> key << " "; // root
    NLR(pRoot -> left);
    NLR(pRoot -> right);
}

// --- 4. In-order Traversal
void LNR(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    LNR(pRoot -> left);
    cout << pRoot -> key << " "; // root
    LNR(pRoot -> right);
}

// --- 5. Post-order Traversal
void LRN(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    LRN(pRoot -> left);
    LRN(pRoot -> right);
    cout << pRoot -> key << " "; // root
}

// --- 6. Level-order Traversal
void LevelOrder(NODE* pRoot) 
{
    if (pRoot == NULL) 
    {
        return;
    }

    queue <NODE*> q;
    q.push(pRoot);

    while (!q.empty()) 
    {
        NODE* curr = q.front();
        q.pop();
        cout << curr -> key << " ";

        if (curr -> left != NULL) 
        {
            q.push(curr -> left);
        }
        if (curr -> right != NULL) 
        {
            q.push(curr -> right);
        }
    }
}

// --- 7. Calculate the height of a given Binary Tree
int Height(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    return max(Height(pRoot -> left), Height(pRoot -> right)) + 1;
}

// --- 8. Count the number of NODE from a given Binary Tree
int countNode(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return 0;
    }
    return 1 + countNode(pRoot -> left) + countNode(pRoot -> right);
}

// --- 9. Calculate the total value of all NODEs from a given Binary Tree
int sumNode(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return 0;
    }
    return pRoot -> key + sumNode(pRoot -> left) + sumNode(pRoot -> right);
}

// --- 10. Find and return a NODE with given value from a given Binary Search Tree
NODE* Search(NODE* pRoot, int key)
{
    if (pRoot == NULL || pRoot -> key == key)
    {
        return pRoot;
    }

    if (key < pRoot -> key)
    {
        return Search(pRoot -> left, key);
    }
    else
    {
        return Search(pRoot -> right, key);
    }
}

// --- 11. Remove a NODE with given value from a given Binary Search Tree
void Remove(NODE* &pRoot, int x)
{
    if (pRoot == NULL)
    {
        return;
    }

    if (x < pRoot -> key)
    {
        Remove(pRoot -> left, x);
    }
    else if (x > pRoot -> key)
    {
        Remove(pRoot -> right, x);
    }
    else
    {
        // Case 1: Node khong co con hoac co 1 con
        if (pRoot -> left == NULL)
        {
            NODE* temp = pRoot;
            pRoot = pRoot -> right;
            delete temp;
        }
        else if (pRoot -> right == NULL)
        {
            NODE* temp = pRoot;
            pRoot = pRoot -> left;
            delete temp;
        }
        else // Case 2: Node co hai con
        {
            // Find the smallest value in the right subtree (LNR)
            NODE* minRight = pRoot -> right;
            while (minRight -> left != NULL)
            {
                minRight = minRight -> left;
            }

            // Replace the current node with the LNR value
            pRoot -> key = minRight -> key;

            // Remove the LNR from the right subtree
            Remove(pRoot -> right, minRight -> key);
        }
    }
}

// --- 13. Completely remove a given Binary Search Tree
void removeTree(NODE* &pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(pRoot -> left != NULL)
    {
        removeTree(pRoot -> left); // vì pRoot -> NULL
    }
    if(pRoot -> right != NULL)
    {
        removeTree(pRoot -> right);
    }

    NODE* temp = pRoot;
    pRoot = NULL;
    delete temp;
}

// --- 14. Calculate the height of a NODE with given value: (return -1 if value not exist)
int heightNode(NODE* pRoot, int value)
{
    if (pRoot == NULL)
    {
        return -1;
    }

    if (value < pRoot -> key)
    {
        return heightNode(pRoot -> left, value);
    }
    else if (value > pRoot -> key)
    {
        return heightNode(pRoot -> right, value);
    }
    else
    {
        // Value found, calculate height from this node
        return Height(pRoot);
    }
}

// --- 15. Calculate the level of a given NODE
int Level(NODE* pRoot, NODE* p)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    else
    {
        if (pRoot -> key > p -> key)
        {
            return 1 + Level(pRoot -> left, p);
        }
        else if (pRoot -> key < p -> key)
		{
			return 1 + Level(pRoot -> right, p);
		}
		else
		{
			return 1;
		}
    }
}

// --- 16. Count the number leaves from a given Binary Tree
int countLeaf(NODE* pRoot)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    else if (!pRoot -> left && !pRoot -> right)
    {
        return 1;
    }
    else
    {
        return countLeaf(pRoot -> left) + countLeaf(pRoot -> right);
    }
}

// --- 17. Count the number of NODE from a given Binary Search Tree which key value is less than a given value
int countLess(NODE* pRoot, int x)
{
    if (pRoot == NULL)
    {
        return 0;
    }

    if (pRoot -> key < x)
    {
        // The current node's key is less than the given value
        // So we count this node and continue to count in its right subtree
        return 1 + countLess(pRoot -> right, x);
    }
    else
    {
        // The current node's key is greater than or equal to the given value
        // So we only need to count in its left subtree
        return countLess(pRoot -> left, x);
    }
}

// --- 18. Count the number of NODE from a given Binary Search Tree which key value is greater than a given value
int countGreater(NODE* pRoot, int x)
{
    if (pRoot == NULL)
    {
        return 0;
    }

    if (pRoot->key > x)
    {
        // The current node's key is greater than the given value
        // So we count this node and continue to count in its left subtree
        return 1 + countGreater(pRoot -> left, x);
    }
    else
    {
        // The current node's key is less than or equal to the given value
        // So we only need to count in its right subtree
        return countGreater(pRoot -> right, x);
    }
}

bool isCorrectNode(NODE* pRoot, NODE* &prev)
{
     if (pRoot == NULL)
    {
        return true;
    }

    // Check the left subtree
    if (!isCorrectNode(pRoot -> left, prev))
    {
        return false;
    }

    // Check the current node
    if (prev != NULL && pRoot -> key <= prev -> key)
    {
        return false;
    }
    prev = pRoot;

    // Check the right subtree
    return isCorrectNode(pRoot -> right, prev);
}

// --- 19_1. Determine if a given Binary Tree is Binary Search Tree
bool isBST(NODE* pRoot)
{
    NODE* prev = NULL; // Initialize a pointer to track the previously visited node
    return isCorrectNode(pRoot, prev);
}

void GetVectorInOrder(NODE* pRoot, vector <int> ans)
{
    if(pRoot == NULL)
    {
        return;
    }
    GetVectorInOrder(pRoot -> left, ans);
    ans.push_back(pRoot -> key);
    GetVectorInOrder(pRoot -> right, ans);
}
// --- 19_2. Determine if a given Binary Tree is Binary Search Tree
bool isBST_2(NODE* pRoot)
{
    vector <int> ans;
    GetVectorInOrder(pRoot, ans);

    for (int i = 1; i < ans.size(); ++i)
    {
        if (ans[i - 1] >= ans[i])
        {
            return false;
        }
    }
    return true;
}

// --- 20. Determine if a given Binary Tree is a Full Binary Search Tree
bool isFullBST(NODE* pRoot)
{
    if(!pRoot)
    {
        return true; // An empty tree is considered a full BST
    }
    if(!pRoot -> left && !pRoot -> right)
    {
        return true; // A single node is considered a full BST
    }
    if(pRoot -> left && pRoot -> right)
    {
        return isBST(pRoot) && isFullBST(pRoot -> left) && isFullBST(pRoot -> right);
    }

    // If the node has only one child, it's not a full BST
    return false;
}

int main() {
    int a[] = {6, 4, 9, 2, 5, 11};
    NODE* pRoot = createTree(a, 6);

    // --- 3
    cout << "Pre-order Traversal (NLR): ";
    NLR(pRoot);
    cout << endl;

    // --- 4
    cout << "In-order Traversal (LNR): ";
    LNR(pRoot);
    cout << endl;

    // --- 5
    cout << "Post-order Traversal (LRN): ";
    LRN(pRoot);
    cout << endl;

    // --- 6
    cout << "Level-order Traversal: ";
    LevelOrder(pRoot);
    cout << endl;

    // --- 7
    cout << "The height of Binary Tree: " << Height(pRoot) << endl;

    // --- 8
    cout << "Count the NODEs: " << countNode(pRoot) << endl;

    // --- 9
    cout << "total value of all NODEs: " << sumNode(pRoot) << endl;

    // --- 10
    if(Search(pRoot, 5))
    {
        cout << "Found" << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }

    // --- 11
    cout << "After removing node with key: "; 
    Remove(pRoot, 4);
    LevelOrder(pRoot);
    cout << endl;

    // --- 14
    if (heightNode(pRoot, 6) != -1)
    {
        cout << "The height of NODE: " << heightNode(pRoot, 6) << endl;
    }
    else
    {
        cout << "NODE not found!" << endl;
    }

    // --- 15
    NODE* targetNode = Search(pRoot, 6);
    if (targetNode)
    {
        cout << "The level of NODE: " << Level(pRoot, targetNode) << endl;
    }
    else
    {
        cout << "NODE not found!" << endl;
    }

    // --- 16
    cout << "Number of leaf nodes in the Binary Tree: " << countLeaf(pRoot) << endl;

    int x = 8;
    // --- 17
    cout << "Number of nodes with key value less than " << x << ": " << countLess(pRoot, x) << endl;

    // --- 18
    cout << "Number of nodes with key value greater than " << x << ": " << countGreater(pRoot, x) << endl;

    // --- 19
    if (isBST(pRoot)) //can change "isBST" to "isBST_2"
    {
        cout << "The Binary Tree is a Binary Search Tree (BST)." << endl;
    }
    else
    {
        cout << "The Binary Tree is not a Binary Search Tree (BST)." << endl;
    }

    // --- 20
    if (isFullBST(pRoot))
    {
        cout << "The given binary tree is a full Binary Search Tree (BST)." << endl;
    }
    else
    {
        cout << "The given binary tree is not a full Binary Search Tree (BST)." << endl;
    }

    removeTree(pRoot);
    return 0;
}
