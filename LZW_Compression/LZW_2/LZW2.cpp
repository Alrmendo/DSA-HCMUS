#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

void compress(const string &inputFile, const string &outputFile) 
{
    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; ++i) 
	{
        dictionary[string(1, char(i))] = i;
    }
    
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    
    string current = "";
    char inputChar;
    while (inFile.get(inputChar)) {
        string next = current + inputChar;
        if (dictionary.find(next) != dictionary.end()) {
            current = next;
        } else {
            outFile.write((char*)&dictionary[current], sizeof(int));
            dictionary[next] = dictionary.size();
            current = string(1, inputChar);
        }
    }
    
    if (!current.empty()) {
        outFile.write((char*)&dictionary[current], sizeof(int));
    }
    
    inFile.close();
    outFile.close();
}

void decompress(const string &inputFile, const string &outputFile) {
    vector<string> dictionary(256);
    for (int i = 0; i < 256; ++i) {
        dictionary[i] = string(1, char(i));
    }
    
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    
    int code;
    inFile.read((char*)&code, sizeof(int));
    string current = dictionary[code];
    outFile << current;
    
    while (inFile.read((char*)&code, sizeof(int))) {
        string entry;
        if (code < dictionary.size()) {
            entry = dictionary[code];
        } else if (code == dictionary.size()) {
            entry = current + current[0];
        }
        
        outFile << entry;
        dictionary.push_back(current + entry[0]);
        current = entry;
    }
    
    inFile.close();
    outFile.close();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " compress/decompress input_file output_file" << endl;
        return 1;
    }

    string operation = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    if (operation == "compress") {
        compress(inputFile, outputFile);
        ifstream inFile(outputFile, ios::binary | ios::ate);
        if (inFile.is_open()) {
            streampos fileSize = inFile.tellg();
            cout << "Compressed " << fileSize << " bytes." << endl;
            inFile.close();
        } else {
            cerr << "Failed to open compressed file." << endl;
            return 1;
        }
    } else if (operation == "decompress") {
        decompress(inputFile, outputFile);
        cout << "Decompression completed." << endl;
    } else {
        cout << "Unknown operation. Use 'compress' or 'decompress'." << endl;
        return 1;
    }

    return 0;
}
