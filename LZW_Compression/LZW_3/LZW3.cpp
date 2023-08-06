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

// Mapping from strings to integers
map<string, int> dict;

// Mapping from integers to strings
map<int, string> revdict;

// Structure to store information about encoded strings
struct encodeinfo {
    string P;
    int index;
};

// Function to perform LZW encoding
vector<encodeinfo> LZW_encode(string s, int encodenum) {
    string P = "";
    char C;
    vector<encodeinfo> EncodeResult;

    for (int i = 0; i < s.length(); i++) {
        C = s[i];
        string tempStr = P + C;

        map<string, int>::iterator iter = dict.find(tempStr);
        if (iter != dict.end()) {
            P = tempStr;
        } else {
            encodeinfo a = { P, dict[P] };
            EncodeResult.push_back(a);
            encodenum++;
            dict[tempStr] = encodenum;
            P = C;
        }
    }
    encodeinfo a = { P, dict[P] };
    EncodeResult.push_back(a);
    
    return EncodeResult;
}

// Function to perform LZW decoding
string LZW_decode(vector<encodeinfo> code, int beginnum) {
    string ret = "";
    string P = "";
    char C;
    int pW, cW;

    cW = code[0].index;
    ret += revdict[cW];

    for (int i = 1; i < code.size(); i++) {
        pW = cW;
        cW = code[i].index;
        map<int, string>::iterator iter = revdict.find(cW);

        if (iter != revdict.end()) {
            ret += iter->second;
            P = revdict[pW];
            C = revdict[cW][0];
            string tempStr = P + C;
            beginnum++;
            revdict[beginnum] = tempStr;
        } else {
            P = revdict[pW];
            C = revdict[pW][0];
            beginnum++;
            string tempStr = P + C;
            revdict[beginnum] = tempStr;
            ret += tempStr;
        }
    }
    return ret;
}

int main() {
    cout << "Enter the filename to be processed: " << endl;
    string filename;
    cin >> filename;
    
    cout << "Enter the address of the output file: " << endl;
    string outfname;
    cin >> outfname;

    FILE *pFile;
    char *file = (char*)filename.c_str();
    pFile = fopen(file, "rb");
    fseek(pFile, 0, SEEK_END);
    int nLen = ftell(pFile);
    cout << "File size: " << nLen << " bytes" << endl;
    fclose(pFile);

    dict.clear();
    revdict.clear();

    for (int i = 0; i < 128; i++) {
        string s = "t";
        s[0] = char(i);
        dict[s] = i;

        revdict[i] = char(i);
    }

    ifstream fin(filename.c_str());

    string allTxtStr;
    string s;
    while (getline(fin, s)) {
        allTxtStr += s;
        allTxtStr += '\t';
    }
    fin.close();

    cout << "Compressing..." << endl;
    vector<encodeinfo> res = LZW_encode(allTxtStr, 128);
    cout << "Encoded data length: " << res.size() << endl;

    // Generate the output binary filename based on the input filename
    string outname = filename.substr(0, filename.find_last_of('.')) + "_encoded.bin";

    // Open the output binary file for writing encoded data
    ofstream binaryOut(outname.c_str(), ios::binary);
    if (!binaryOut.is_open()) {
        cerr << "Error opening output binary file." << endl;
        return 1;
    }

    // Write the encoded data to the binary file
    for (size_t i = 0; i < res.size(); ++i) {
        const encodeinfo& info = res[i];
        binaryOut.write(reinterpret_cast<const char*>(&info), sizeof(info));
    }

    binaryOut.close();

    double ratio = (double)nLen / (4 * res.size());
    cout << "Compression ratio: " << fixed << setprecision(3) << ratio << endl;

    cout << "Decompressing..." << endl;
    string result = LZW_decode(res, 128);

    ofstream fout(outfname.c_str(), ios::out);

    stringstream ss(result);  // Use stringstream to read from the decompressed string
    string line;
    while (getline(ss, line, '\t')) {  // Assuming '\t' is the delimiter
        fout << line << endl;
    }

    fout.close();

    cout << "Decompression completed." << endl;
    system("pause");
    return 0;
}