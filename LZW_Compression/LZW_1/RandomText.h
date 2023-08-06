#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

string generateRandomText(int length) 
{
    string result;
    mt19937 rand_gen;
    rand_gen.seed(time(0));

    for (int i = 0; i < length; i++) 
    {
        result += char('a' + rand_gen() % 26);
    }

    return result;
}

int main() 
{
    // Generating random texts
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

    ofstream ofile;
    ofile.open("random_text_300000.txt");
    ofile << random_text_300000;
    ofile.close();

    ofstream ofile;
    ofile.open("random_text_500000.txt");
    ofile << random_text_500000;
    ofile.close();

    return 0;
}
