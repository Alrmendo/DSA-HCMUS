#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

// Khai báo từ điển đối chiếu từ chuỗi sang số nguyên
map<string, int> dict;

// Khai báo từ điển đối chiếu từ số nguyên sang chuỗi
map<int, string> revDict;

// Khai báo cấu trúc để lưu thông tin về các chuỗi đã được mã hóa
struct encodeinfo {
    string P;
    int index;
};

// Hàm thực hiện mã hóa LZW
vector<encodeinfo> LZW_encode(string s, int encodenum) 
{
    string P = "";  // Khởi tạo chuỗi P rỗng để lưu các ký tự trước đó
    char C;         // Khởi tạo ký tự C để duyệt qua chuỗi đầu vào
    vector<encodeinfo> EncodeResult;  // Vector để lưu thông tin đã mã hóa

    // Lặp qua từng ký tự trong chuỗi đầu vào
    for (int i = 0; i < s.length(); i++) 
    {
        C = s[i];  // Lấy ký tự hiện tại
        string tempStr = P + C;  // Tạo một chuỗi mới bằng cách ghép ký tự hiện tại vào P

        // Kiểm tra xem chuỗi mới (tempStr) có tồn tại trong từ điển không
        map<string, int>::iterator iter = dict.find(tempStr);
        if (iter != dict.end()) {
            // Nếu tồn tại, cập nhật P bằng tempStr để tiếp tục xây dựng cụm từ hiện tại
            P = tempStr;
        } else {
            // Nếu không tồn tại, thêm thông tin đã mã hóa cho P vào vector kết quả
            encodeinfo a = { P, dict[P] };
            EncodeResult.push_back(a);

            // Tăng số mã hóa và thêm chuỗi mới vào từ điển
            encodenum++;
            dict[tempStr] = encodenum;

            // Đặt lại P bằng ký tự hiện tại (C) để bắt đầu xây dựng cụm từ mới
            P = C;
        }
    }

    // Sau khi xử lý tất cả các ký tự, thêm thông tin đã mã hóa cho cụm từ cuối cùng
    encodeinfo a = { P, dict[P] };
    EncodeResult.push_back(a);
    
    return EncodeResult;  // Trả về vector chứa thông tin đã mã hóa
}


// Hàm thực hiện giải nén LZW
string LZW_decode(vector<encodeinfo> code, int beginNum) 
{
    string ret = "";  // Chuỗi kết quả giải nén
    string P = "";
    char C; 
    int pW, cW;

    cW = code[0].index;  // Lấy chỉ số đầu tiên từ mã hóa
    ret += revDict[cW];  // Thêm ký tự tương ứng vào chuỗi kết quả

    for (int i = 1; i < code.size(); i++) 
    {
        pW = cW;                  // Lưu trữ chỉ số trước đó
        cW = code[i].index;       // Lấy chỉ số hiện tại từ mã hóa
        map<int, string>::iterator iter = revDict.find(cW); // Tìm kiếm trong từ điển revDict sử dụng chỉ số cW

        if (iter != revDict.end()) 
        // Nếu chỉ số hiện tại tồn tại trong từ điển
        {
            ret += iter->second;     // Thêm chuỗi tương ứng vào chuỗi kết quả
            P = revDict[pW];         // Lấy chuỗi trước đó từ từ điển
            C = revDict[cW][0];      // Lấy ký tự đầu tiên của chuỗi hiện tại
            string tempStr = P + C;  // Tạo chuỗi tạm bằng cách ghép P và C
            beginNum++;              // Tăng chỉ số bắt đầu
            revDict[beginNum] = tempStr;  // Thêm chuỗi tạm vào từ điển
        } 
        else 
        // Nếu chỉ số hiện tại không tồn tại trong từ điển
        {
            P = revDict[pW];         // Lấy chuỗi trước đó từ từ điển
            C = revDict[pW][0];      // Lấy ký tự đầu tiên của chuỗi trước đó
            beginNum++;              // Tăng chỉ số bắt đầu
            string tempStr = P + C;  // Tạo chuỗi tạm bằng cách ghép P và C
            revDict[beginNum] = tempStr;  // Thêm chuỗi tạm vào từ điển
            ret += tempStr;          // Thêm chuỗi tạm vào chuỗi kết quả
        }
    }
    return ret;  // Trả về chuỗi kết quả giải nén
}


int main() {
    // Nhập tên tệp cần nén
    cout << "Enter the filename to be compressed: " << endl;
    string filename;
    cin >> filename;
    
    // Nhập tên tệp đầu ra
    cout << "Enter the output file name: " << endl;
    string outfname;
    cin >> outfname;

    FILE *pFile;
    char *file = (char*)filename.c_str();
    
    // Mở tệp và tính kích thước
    pFile = fopen(file, "rb");
    fseek(pFile, 0, SEEK_END);
    int nLen = ftell(pFile);
    cout << "File size: " << nLen << " bytes" << endl;
    fclose(pFile);

    // Xóa từ điển và danh sách đảo của từ điển
    dict.clear();
    revDict.clear();

    // Khởi tạo từ điển với các ký tự ASCII
    for (int i = 0; i < 128; i++) 
    {
        string s = "t";
        s[0] = char(i);
        dict[s] = i;

        revDict[i] = char(i);
    }

    // Đọc nội dung của tệp vào chuỗi str
    ifstream fin(filename.c_str());
    string str;
    string s;
    while (getline(fin, s)) 
    {
        str += s;
        str += '\t';
    }
    fin.close();

    // Nén dữ liệu bằng LZW
    cout << "Compressing..." << endl;
    vector<encodeinfo> res = LZW_encode(str, 128);
    cout << "Encoded data length: " << res.size() << endl;

    // Tạo tên tệp nhị phân đầu ra dựa trên tên tệp đầu vào
    string outname = filename.substr(0, filename.find_last_of('.')) + "_encoded.bin";

    // Mở tệp nhị phân đầu ra để ghi dữ liệu đã nén
    ofstream binaryOut(outname.c_str(), ios::binary);
    if (!binaryOut.is_open()) 
    {
        cerr << "Error opening output binary file." << endl;
        return 1;
    }

    // Ghi dữ liệu đã nén vào tệp nhị phân
    for (size_t i = 0; i < res.size(); ++i) 
    {
        const encodeinfo& info = res[i];
        binaryOut.write(reinterpret_cast<const char*>(&info), sizeof(info));
    }

    binaryOut.close();

    // Tính tỷ lệ nén
    double ratio = (double)nLen / (4 * res.size());
    cout << "Compression ratio: " << fixed << setprecision(3) << ratio << endl;

    // Bắt đầu quá trình giải nén
    cout << "Decompressing..." << endl;
    string result = LZW_decode(res, 128);

    // Mở tệp đầu ra để ghi dữ liệu đã giải nén
    ofstream fout(outfname.c_str(), ios::out);

    // Sử dụng stringstream để đọc từ chuỗi đã giải nén
    stringstream ss(result);
    string line;
    while (getline(ss, line, '\t')) 
    { 
        fout << line << endl;
    }

    fout.close();

    // Hiển thị thông báo khi quá trình giải nén hoàn thành
    cout << "Decompression completed." << endl;
    
    // Dừng chương trình để xem kết quả
    system("pause");
    return 0;
}


/*
========== HOW TO USE THE PROGRAM ==========

1. Compile and run the program

2. Follow the instruction:
- The program will prompt you for input. Here's what each prompt means and how to respond:
    > Enter the filename to be processed: 
        - Provide the name of the text file you want to compress and decompress. 
        - Make sure the file is in the same directory as the compiled program.
        eg: "input.txt" (Make sure you already have a input file in your source code)

    > Enter the address of the output file: 
        - Provide the name for the output text file where the decompressed content will be saved.
        eg: "output.txt"

3. Check the Output Files:
- It will ouput 2 files:
    1. The compressed data will be named: '[input_filename]_encoded.bin'
    2. And the output when the data have been decompressed: '[output_filename].txt'
*/