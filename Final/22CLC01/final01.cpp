#include <iostream>

using namespace std;

struct TreeNode { 
  int val; 
  TreeNode *left; 
  TreeNode *right; 
};

TreeNode* createNode(int data)
{
    TreeNode* newNode = new TreeNode;
    newNode -> val = data;
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

void Insert(TreeNode*& r, int data)
{
    if(r == NULL)
    {
        r = createNode(data);
        return;
    }

    if(data < r -> val)
    {
        Insert(r -> left, data);
    }
    else if(data > r -> val)
    {
        Insert(r -> right, data);
    }
}

TreeNode* createTree(int a[], int n)
{
    TreeNode* r = NULL;
    for (int i = 0; i < n; ++i)
    {
        Insert(r, a[i]);
    }
    return r;
}

void deleteTree(TreeNode* r) 
{
    if (r == NULL) 
    {
        return;
    }

    deleteTree(r -> left);
    deleteTree(r -> right);
    delete r;
}

// tính tổng các giá trị trong cây con
int subtreeSum(TreeNode* r)
{
    if(r == NULL)
    {
        return 0;
    }
    return r -> val + subtreeSum(r -> left) + subtreeSum(r -> right);
}

// in ra các nút có tổng cây con trái bằng tổng cây con phải
void printNodesWithEqualSums(TreeNode* r)
{
    if(r == NULL)
    {
        return;
    }

    // Tính tổng các cây con trái và phải cho nút hiện tại
    int leftSum = subtreeSum(r -> left);
    int rightSum = subtreeSum(r -> right);

    // Kiểm tra xem tổng có bằng nhau hay không và in giá trị của nút nếu đúng
    if(leftSum == rightSum)
    {
        cout << r -> val << " ";
    }

    // Đệ quy kiểm tra cây con trái và phải
    printNodesWithEqualSums(r -> left);
    printNodesWithEqualSums(r -> right);
}

void findLongestPath(TreeNode* r, int path[], int& length, int& maxLength, int longestPath[]) 
/*
- r: Con trỏ tới nút gốc của cây nhị phân.
- path[]: Mảng lưu trữ đường dẫn hiện tại từ gốc đến nút hiện tại.
- length: Biến đếm độ dài của đường dẫn hiện tại.
- maxLength: Biến lưu trữ độ dài của đường dẫn dài nhất đã tìm thấy.
- longestPath[]: Mảng lưu trữ đường dẫn dài nhất đã tìm thấy.
*/
{
    if (r == NULL) 
    {
        return;
    }

    // Lưu giá trị của nút vào đường dẫn
    path[length] = r -> val;
    length++; // tăng biến length để chỉ số mảng trỏ đến vị trí tiếp theo.

    if (r -> left == NULL && r -> right == NULL) // Đây là điều kiện kiểm tra xem nút hiện tại có phải là nút lá (không có con trái và con phải) hay không.
    {
        if (length > maxLength)
        {
            maxLength = length;
            for (int i = 0; i < length; ++i) 
            {
                longestPath[i] = path[i]; // sao chép đường dẫn hiện tại từ mảng path vào mảng longestPath
            }
        }
    }

    // Duyệt cây con trái và cây con phải
    findLongestPath(r -> left, path, length, maxLength, longestPath);
    findLongestPath(r -> right, path, length, maxLength, longestPath);
    // Lưu ý: biến length được truyền vào các lệnh đệ quy này để duy trì độ dài của đường dẫn hiện tại khi di chuyển xuống cây.

    length--;
    // Khi thoát khỏi một nhánh của cây (sau khi đã duyệt qua cả cây con trái và cây con phải), giảm giá trị của biến length để quay lại nút cha và loại bỏ nút hiện tại khỏi đường dẫn.

}

// Hàm để in đường dài nhất từ gốc đến lá
void printLongestPath(TreeNode* r) 
{
    int path[100]; // Assuming max path length is 100
    int longestPath[100];
    int length = 0;
    int maxLength = 0;

    findLongestPath(r, path, length, maxLength, longestPath);

    cout << "Longest path: ";
    for (int i = 0; i < maxLength; ++i) {
        cout << longestPath[i] << " ";
    }
    cout << endl;
}

//Hashing
const int m = 7; // Number of slots
int keys[m];      // Array to store key
int values[m];    // Array to store val

void initializeTable()
{
    for(int i = 0; i < m; ++i)
    {
        keys[i] = -1; //sentinal value, khởi tạo keys với giá trị -1 (empty slot)
        values[i] = -1; //sentinal value, khởi tạo values với giá trị -1 (empty slot)
    }
}

int h1(int key)
{
    return key % m; 
}

void insert(int key, int val)
/*
key: Khóa bạn muốn lưu trữ trong bảng băm.
val: Giá trị tương ứng với khóa mà bạn muốn lưu trữ.
*/
{
    int index = h1(key);
    while(keys[index] != -1)
    {
        index = (index + 1) % m; // Linear probing: di chuyển đến ô tiếp theo trong trường hợp đã có khóa trong ô hiện tại
    }
    //Khi tìm được một vị trí trống, bạn lưu trữ khóa key vào mảng keys tại vị trí index và lưu trữ giá trị val tương ứng vào mảng values tại vị trí index
    keys[index] = key; // Lưu trữ khóa vào vị trí thích hợp
    values[index] = val; // Lưu trữ giá trị tương ứng vào vị trí thích hợp
}

bool search(int key, int &val) 
/*
key: Khóa bạn đang tìm kiếm.
val: Biến tham chiếu để lưu giá trị tương ứng với khóa nếu tìm thấy.
*/
{
    int index = h1(key);
    int originalIndex = index; // Lưu lại vị trí ban đầu để kiểm tra vòng lặp đã đi qua toàn bộ bảng
    while (keys[index] != -1) 
    {
        if (keys[index] == key) // Nếu tìm thấy khóa trong ô hiện tại
        {
            val = values[index];  // Lấy giá trị tương ứng
            return true; // Trả về true vì đã tìm thấy khóa
        }
        index = (index + 1) % m; // Linear probing: di chuyển đến ô tiếp theo trong trường hợp đã có khóa trong ô hiện tại
        if (index == originalIndex)
        {
            break; // Khóa không được tìm thấy sau khi đi qua toàn bộ bảng
        }
    }
    return false; // Trả về false nếu không tìm thấy khóa trong bảng
}


bool remove(int key) 
{
    int index = h1(key);
    int originalIndex = index; // Lưu lại vị trí ban đầu để kiểm tra vòng lặp đã đi qua toàn bộ bảng
    while (keys[index] != -1) 
    {
        if (keys[index] == key) // Nếu tìm thấy khóa trong ô hiện tại
        {
            keys[index] = -1; // Đánh dấu ô trống bằng giá trị -1
            values[index] = -1; // Đánh dấu giá trị trống bằng giá trị -1
            return true; // Trả về true vì đã tìm thấy và xóa khóa
        }
        index = (index + 1) % m; // Linear probing: di chuyển đến ô tiếp theo trong trường hợp đã có khóa trong ô hiện tại
        if (index == originalIndex) 
        {
            break; // Khóa không được tìm thấy sau khi đi qua toàn bộ bảng
        }
        
    }
    return false; // Trả về false nếu không tìm thấy khóa trong bảng
}

int main() {
    // Xây dựng cây nhị phân
    int arr[] = {10, 5, 15, 3, 7, 12, 18, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    TreeNode* r = createTree(arr, n);

    // Gọi hàm để in ra các nút có tổng cây con trái bằng tổng cây con phải
    printNodesWithEqualSums(r);
    cout << endl;

    // Gọi hàm để in đường dài nhất từ gốc đến lá
    printLongestPath(r);

    // Giải phóng bộ nhớ đã cấp phát
    deleteTree(r);

    //Hashing
    initializeTable();

    int values[] = {76, 93, 40, 47, 10, 55};
    for (int i = 0; i < 6; ++i) 
    {
        insert(values[i], values[i]);
    }

    int searchKey;
    cout << "Enter the search key: ";
    cin >> searchKey;
    int searchValue;
    if (search(searchKey, searchValue)) 
    {
        cout << "Value for key " << searchKey << ": " << searchValue << endl;
    } 
    else 
    {
        cout << "Key not found." << endl;
    }

    int deleteKey;
    cout << "Enter the key to be delete: ";
    cin >> deleteKey;

    if (remove(deleteKey)) 
    {
        cout << "Key " << deleteKey << " removed." << endl;
    } 
    else 
    {
        cout << "Key not found." << endl;
    }
    
    return 0;
}