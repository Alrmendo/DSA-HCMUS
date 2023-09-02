#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

void wordcloud(string* a, int n) {
    // Tạo một mảng boolean có kích thước n để theo dõi việc đếm các từ đã xuất hiện.
    bool* count = new bool[n];

    // Khởi tạo tất cả phần tử của mảng count thành giá trị false (0).
    for (int i = 0; i < n; ++i) {
        count[i] = false;
    }

    // Vòng lặp chính để xử lý từng từ trong mảng đầu vào.
    for (int i = 0; i < n; ++i) {
        // Nếu từ đã được đếm rồi, tiếp tục đến từ tiếp theo.
        if (count[i] == true) {
            continue;
        }

        // Nếu từ là khoảng trắng, bỏ qua nó và tiếp tục với từ tiếp theo.
        if (a[i] == " ") {
            continue;
        }

        // Khởi tạo biến đếm cho từ hiện tại và đặt giá trị ban đầu là 1.
        int counter = 1;
        // Vòng lặp lồng để so sánh từ hiện tại với các từ còn lại trong mảng.
        for (int j = i + 1; j < n; ++j) {
            // Nếu từ hiện tại giống với từ khác, tăng biến đếm và đánh dấu từ khác đã được đếm.
            if (a[i] == a[j]) {
                count[j] = true;
                ++counter;
            }
        }
        // In ra từ hiện tại và số lần xuất hiện của nó.
        cout << a[i] << " " << counter << endl;
    }

    delete[] count;
}

void merge(int arr[], int l, int m, int r) {
    vector<int> a1(arr + l, arr + m + 1);
    vector<int> a2(arr + m + 1, arr + r + 1);
    int i = 0, j = 0;
    while (i < a1.size() && j < a2.size()) {
        if (a1[i] <= a2[j]) {
            arr[l++] = a1[i++];
        } else {
            arr[l++] = a2[j++];
        }
    }
    while (i < a1.size()) {
        arr[l++] = a1[i++];
    }
    while (j < a2.size()) {
        arr[l++] = a2[j++];
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void readDataFromFile(const string& filename, string*& a, int& n) {
    ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file '" << filename << "'" << endl;
        exit(1);
    }

    string temp;
    getline(inputFile, temp);
    n = temp.length();
    a = new string[n];

    stringstream ss(temp);

    for (int i = 0; i < n; ++i) {
        ss >> a[i];
    }

    inputFile.close();
}

int main() {
    string* a;
    int n;
    readDataFromFile("data.txt", a, n);
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    wordcloud(a, n);
    delete[] a;

    return 0;
}
