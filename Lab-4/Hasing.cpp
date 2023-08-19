#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

struct Company
{
    string name;
    string profit_tax;
    string address;
};

Company getCompany(string line)
{
    stringstream s(line);
    string buf;
    Company c;

    getline(s, c.name, '|');
    getline(s, c.profit_tax, '|');
    getline(s, c.address);

    return c;
}

vector<Company> ReadCompanyList(string file_name)
{
    vector<Company> companies;
    ifstream file(file_name);
    string line;

    while(getline(file, line)) 
    // được sử dụng để lặp qua các dòng trong một tập tin văn bản.
    // file: đại diện cho luồng đầu vào để đọc từ tập tin.
    // line: Đây là một biến kiểu string sẽ chứa nội dung của mỗi dòng được đọc từ tập tin.
    {
        companies.push_back(getCompany(line));
        // trả về false nếu đã đến cuối tập tin hoặc xảy ra lỗi.
    }

    file.close();
    return companies;
}

void PrintCompanies(const vector<Company> &companies)
{
    ofstream outputFile("output.txt");

    if(!outputFile.is_open())
    {
        cout << "Error opening output.txt" << endl;
        return;
    }

    for (int i = 0; i < companies.size(); ++i)
    {
        const Company &c = companies[i];
        outputFile << "Name: " << c.name << endl;
        outputFile << "Proxit tax: " << c.profit_tax << endl;
        outputFile << "Address: " << c.address << endl;
        outputFile << "--------------------------------" << endl;
    }

    outputFile.close();
}

//Lab 4
long long power(int x, int y) // hàm tính luỹ thừa
{
    long long n = 1; // Khởi tạo giá trị ban đầu của lũy thừa
    long long m = pow(10,9) + 9;
    for (int i = 0; i < y; ++i)
    {
        n = n * x; // Tính lũy thừa bằng cách nhân với x
        n = n % m;  // Thực hiện phép toán modulo sau mỗi bước lũy thừa để giới hạn giá trị
    }
    return n; // Trả về giá trị lũy thừa
}

// Hàm tính giá trị băm cho chuỗi ký tự
long long HashString(string company_name)
{
    long long result = 0; // Kết quả cuối cùng của giá trị băm
    int p = 31;
    long long m = pow(10,9) + 9;
    if(company_name.length() <= 20)
    {
        for (int i = 0; i < company_name.length(); ++i)
        {
            // Tính giá trị băm cho mỗi ký tự theo công thức, sau đó cộng vào kết quả
            long long temp = ((int)company_name[i] * power(p, i)) % m; // Chuyển đổi ký tự thành số nguyên bằng (int)
            result = result + temp;
        }
    }

    else
    {
        for(int i = 0; i < 20; ++i)
        {
            // Tính giá trị băm cho các ký tự cuối cùng trong chuỗi dài hơn 20, sau đó cộng vào kết quả
            long long temp = ((int)company_name[company_name.length() - i - 1] * power(p, company_name.length() - i - 1)) % m; // Chuyển đổi ký tự thành số nguyên bằng (int)
            result = result + temp;
        }
    }
    result = result % m; // Thực hiện phép toán modulo cuối cùng cho giá trị băm
    return result;
}

// Hàm tính giá trị băm cho một chuỗi tên công ty
int HashFunction(string name)
{
    int hashValue = HashString(name); // Tính giá trị băm cho chuỗi tên
    return (int) hashValue % 2000; // đảm bảo nằm trong khoảng 0 - 1999
}

// Hàm chèn một công ty vào bảng băm sử dụng linear probing
void insert(Company* hash_table, Company company)
{
    int index = HashFunction(company.name); // Tính vị trí ban đầu trong bảng băm

    // Duyệt qua các slot trong bảng băm để tìm vị trí trống hoặc vị trí chứa công ty có tên tương tự
    while(hash_table[index].name != "")
    {
        if(hash_table[index].name == company.name)
        {
            return; // Công ty đã tồn tại, không chèn lại
        }
        ++index; // Di chuyển tới vị trí tiếp theo
        if(index == 2000)
        {
            index = 0; // Quay lại đầu bảng nếu đã duyệt hết
        }
    }

    // Khi tìm được vị trí trống, chèn công ty vào đó
    hash_table[index] = company;
}


// Hàm tạo bảng băm từ danh sách công ty sử dụng linear probing
Company* CreateHashTable(vector<Company> list_company)
{
    Company *hashTable = new Company[2000]; // Khởi tạo một mảng động để đại diện cho bảng băm

    // Lặp qua danh sách các công ty để chèn từng công ty vào bảng băm
    for(int i = 0; i < list_company.size(); ++i)
    {
        insert(hashTable, list_company[i]); // Chèn từng công ty vào bảng băm
    }

    return hashTable; // Trả về con trỏ đến bảng băm đã tạo
}

Company* Search(Company* hash_table, string company_name)
{
    int index = HashFunction(company_name);
    int initial_index = index;
    while(hash_table[index].name != "")
    {
        if(hash_table[index].name == company_name)
        {
            return &hash_table[index];
            ++index;
        }
        if(index == 2000)
        {
            index = 0;
        }
        if (index == initial_index)
        {
            break;
        }
    }
    return NULL;
}


int main ()
{
    vector <Company> companies = ReadCompanyList("MST.txt");
    for (int i = 0; i < companies.size(); ++i)
    {
        const Company &c = companies[i];
        cout << "Company: " << c.name << ", Hash: " << HashString(c.name) << endl;
    }
    PrintCompanies(companies);

    Company* hashTable = CreateHashTable(companies);
    string companyToSearch = "CONG TY CO PHAN THUONG MAI CHAU DUC PHAT";
    Company* foundCompany = Search(hashTable, companyToSearch);
    if (foundCompany)
    {
        cout << "Company Found - Name: " << foundCompany->name << ", Profit Tax: " << foundCompany->profit_tax << ", Address: " << foundCompany->address << endl;
    }
    else
    {
        cout << "Company not found." << endl;
    }

    PrintCompanies(companies);


    delete[] hashTable;

    return 0;
}
