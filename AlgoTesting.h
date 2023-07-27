#pragma once
#include "DataGenerator.h"
#include "AlgoTiming.h"
#include "count_comparision_Algo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

void TestingAll() 
{
	int size[6] = { 10000, 30000, 50000, 100000, 300000, 500000 };
	vector<string> Name;
    Name.push_back("Selection_Sort");
    Name.push_back("Insertion_Sort");
    Name.push_back("Bubble_Sort");
    Name.push_back("Shaker_Sort");
    Name.push_back("Shell_Sort");
    Name.push_back("Heap_Sort");
    Name.push_back("Merge_Sort");
    Name.push_back("Quick_Sort");
    Name.push_back("Counting_Sort");
    Name.push_back("Radix_Sort");
    Name.push_back("Flash_Sort");

    vector<string> Order;
    Order.push_back("RandomData");
    Order.push_back("SortedData");
    Order.push_back("ReverseData");
    Order.push_back("NearlySortedData");
	clock_t start, end;   

	ofstream fout("Testing_output.txt");
    if (!fout) {
        cout << "Failed to open Testing_output.txt" << endl;
        return;
    }

    for (int OrderNo = 0; OrderNo < 4; OrderNo++) 
	{
        fout << "Data order: " << Order[OrderNo] << endl;
        cout << "Kind of order: " << Order[OrderNo] << endl;

        for (int id = 0; id < 6; id++) 
		{
            int n = size[id];
            int* arr = new int[n];
            GenerateData(arr, n, OrderNo);

            fout << "--------------------------" << endl;
            fout << "Data size: " << n << endl;
            fout << "--------------------------" << endl;

            cout << "--------------------------" << endl;
            cout << "# Size of data: " << n << endl;
            cout << "--------------------------" << endl;

            for (int sort = 0; sort < 11; sort++) 
			{
                int* b = new int[n];
                int* c = new int[n];

                for (int i = 0; i < n; i++)
                {
					c[i] = b[i] = arr[i];
				}

                fout << "    === " << Name[sort] << " ===" << endl;
                cout << "    === " << Name[sort] << " ===" << endl;

                clock_t start = clock();
                SortAl(b, n, sort);
                clock_t end = clock();
                double time_use = (double)(end - start) / CLOCKS_PER_SEC * 1000;
                fout << "- Running Time: " << fixed << time_use << endl;
                cout << "- Running Time: " << fixed << time_use << endl;

                delete[] b;

                long long int count = 0;
                Count_SortAl(c, n, sort, count);
                fout << "- Comparision : " << count << endl;
                cout << "- Comparision : " << count << endl;
                fout << endl;
                cout << endl;

                delete[] c;
            }

            delete[] arr;
        }
    }
    fout.close();
}
