#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <unordered_map>

using namespace std;

string generateRandomText(int length) {
    string result;
    mt19937 rand_gen;
    rand_gen.seed(time(0));

    for (int i = 0; i < length; i++) {
        result += char('a' + rand_gen() % 26);
    }

    return result;
}

vector<int> encoding(string s1)
{
	unordered_map<string, int> table;
	for (int i = 0; i <= 255; i++) 
    {
		string ch = "";
		ch += char(i);
		table[ch] = i;
	}

	string p = "", c = "";
	p += s1[0];
	int code = 256;
	vector<int> output_code;
	for (int i = 0; i < s1.length(); i++) 
    {
		if (i != s1.length() - 1)
		{
            c += s1[i + 1];
        }
		if (table.find(p + c) != table.end()) 
        {
			p = p + c;
		}
		else {
			output_code.push_back(table[p]);
			table[p + c] = code;
			code++;
			p = c;
		}
		c = "";
	}
	output_code.push_back(table[p]);
	return output_code;
}

void decoding(vector<int> op)
{
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) 
    {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
	int old = op[0], n;
	string s = table[old];
	string c = "";
	c += s[0];
	int count = 256;
	for (int i = 0; i < op.size() - 1; i++) 
    {
		n = op[i + 1];
		if (table.find(n) == table.end()) 
        {
			s = table[old];
			s = s + c;
		}
		else {
			s = table[n];
		}
		c = "";
		c += s[0];
		table[count] = table[old] + c;
		count++;
		old = n;
	}
}

int main() 
{
    // Generate random texts
    string random_text_10000 = generateRandomText(10000);
    string random_text_30000 = generateRandomText(30000);
    string random_text_50000 = generateRandomText(50000);
    string random_text_100000 = generateRandomText(100000);
    string random_text_300000 = generateRandomText(300000);
    string random_text_500000 = generateRandomText(500000);

    // Writing random texts to files
    ofstream ofile;
    ofile.open("random_text_10000.txt");
    ofile << random_text_10000;
    ofile.close();

    ofile.open("random_text_30000.txt");
    ofile << random_text_30000;
    ofile.close();

    ofile.open("random_text_50000.txt");
    ofile << random_text_50000;
    ofile.close();

    ofile.open("random_text_100000.txt");
    ofile << random_text_100000;
    ofile.close();

    ofile.open("random_text_300000.txt");
    ofile << random_text_300000;
    ofile.close();

    ofile.open("random_text_500000.txt");
    ofile << random_text_500000;
    ofile.close();

    // Call the encoding function and save the encoded output to files
    vector<int> encoded_10000 = encoding(random_text_10000);
    vector<int> encoded_30000 = encoding(random_text_30000);
    vector<int> encoded_50000 = encoding(random_text_50000);
    vector<int> encoded_100000 = encoding(random_text_100000);
    vector<int> encoded_300000 = encoding(random_text_300000);
    vector<int> encoded_500000 = encoding(random_text_500000);

    // Writing encoded outputs to files
    ofstream encoded_ofile;

    encoded_ofile.open("encoded_text_10000.txt");
    for (size_t i = 0; i < encoded_10000.size(); i++) 
	{
        encoded_ofile << encoded_10000[i] << " ";
    }
    encoded_ofile.close();

    encoded_ofile.open("encoded_text_30000.txt");
    for (size_t i = 0; i < encoded_30000.size(); i++) 
	{
        encoded_ofile << encoded_30000[i] << " ";
    }
    encoded_ofile.close();

    encoded_ofile.open("encoded_text_50000.txt");
    for (size_t i = 0; i < encoded_50000.size(); i++) 
	{
        encoded_ofile << encoded_50000[i] << " ";
    }
    encoded_ofile.close();

    encoded_ofile.open("encoded_text_100000.txt");
    for (size_t i = 0; i < encoded_100000.size(); i++) 
	{
        encoded_ofile << encoded_100000[i] << " ";
    }
    encoded_ofile.close();

    encoded_ofile.open("encoded_text_300000.txt");
    for (size_t i = 0; i < encoded_300000.size(); i++) 
	{
        encoded_ofile << encoded_300000[i] << " ";
    }
    encoded_ofile.close();

    encoded_ofile.open("encoded_text_500000.txt");
    for (size_t i = 0; i < encoded_500000.size(); i++) 
	{
        encoded_ofile << encoded_500000[i] << " ";
    }
    encoded_ofile.close();

    // Call the decoding function to decode the encoded texts
    decoding(encoded_10000);
    decoding(encoded_30000);
    decoding(encoded_50000);
    decoding(encoded_100000);
    decoding(encoded_300000);
    decoding(encoded_500000);

    return 0;
}