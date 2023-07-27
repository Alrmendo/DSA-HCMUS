#pragma once
#include "DataGenerator.h"
#include "AlgoTiming.h"
#include "count_comparision_Algo.h"
#include <iomanip>
#include <string>
#include <string.h>

string sort_names[] = {
    "selection-sort", "insertion-sort","bubble-sort", "shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort", "couting-sort", "radix-sort", "flash-sort"
};

string Order[4] = {"-rand", "-sorted", "-rev", "-nsorted"};

// --- Run a sorting algorithm on the given input data + Write down the sorted array to the "output.txt" file
void command1(string Algorithm, string fileName, string Output) {
	cout << endl;
	cout << "ALGORITHM MODE" << endl;
	cout << "Algorithm: " << Algorithm << endl;
	ifstream fin(fileName);
	if (!fin) 
	{
		cout << "Cannot open the InputFile" << endl;
		return;
	}

	cout << "Input file: " << fileName << endl;
	int n = 0; 
	// gán size cho input file

	string buff; getline(fin, buff);
	// đọc một dòng đầu tiên từ tệp văn bản được mở và lưu trữ nó trong chuỗi buff
	// kiểm tra xem tệp có chứa ký tự đặc biệt "\xEF\xBB\xBF" ở đầu tệp không

	char IdentifierUTF8[] = "\xEF\xBB\xBF";
	// mảng ký tự để lưu trữ chuỗi ký tự "\xEF\xBB\xBF" nó là một đại diện cho ký tự đặc biệt BOM (Byte Order Mark) trong mã UTF-8.

	const char* firstline = buff.c_str(); 
	// Chuỗi buff được chuyển đổi thành một con trỏ const char* bằng cách sử dụng c_str() để sử dụng trong hàm strstr tiếp theo.

	if (strstr(firstline, IdentifierUTF8) != NULL) 
	{
		// Hàm strstr được sử dụng để tìm kiếm chuỗi IdentifierUTF8 (ký tự BOM) trong chuỗi firstline. 
		// Nếu chuỗi IdentifierUTF8 xuất hiện trong firstline, điều kiện này sẽ trả về con trỏ không phải NULL.

		char* number =(char*) (firstline + 3*sizeof(char));
		// Nếu tệp văn bản chứa ký tự BOM, con trỏ number sẽ trỏ tới vị trí sau 4 ký tự đầu tiên của chuỗi firstline. 
		// Mục đích là bỏ qua ký tự BOM và chỉ trỏ đến phần số nguyên trong dòng đầu tiên.

		n = atoi(number);
		// Hàm atoi được sử dụng để chuyển đổi chuỗi số nguyên đại diện bởi number thành giá trị số nguyên và gán cho biến n.
	}
	else {
		n = stoi(buff);
		// Nếu tệp văn bản không chứa ký tự BOM, dòng đầu tiên của tệp được chuyển đổi thành số nguyên bằng cách sử dụng hàm stoi và gán cho biến n.
	}

	// --- Input
	cout << "Input size: " << n << endl;
	int* arr = new int[n];
	cout << "---------------------------------\n";
	for (int i = 0; i < n; i++)
	{
		fin >> arr[i];
	}
	
	// --- Sort type selection
	int sort_type1 = 0;
	for (sort_type1 = 0; sort_type1 < 11; ++sort_type1)
	{
		if (sort_names[sort_type1] == Algorithm)
		{
			break;
		}
	}

	// --- Timing and Comparison Counting
	clock_t start, end;
	long long int com1 = 0;

	if (Output == "-time") 
	{
		// Nếu Output bằng "-time", chương trình đo thời gian chạy của thuật toán sắp xếp.
		start = clock();
		SortAl(arr, n, sort_type1);
		end = clock();
		double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
		// Bằng cách tính hiệu giữa thời gian start và end được lấy từ hàm clock().
		// Kết quả được in ra là thời gian chạy tính bằng mili giây.
		cout << "Running time (if required): " << fixed << time << endl;
		cout << "Comparisons (if required): NOT REQUIRED" << endl;

	}
	else if (Output == "-comp") {
		// Nếu Output bằng "-comp", chương trình đếm số lần so sánh được thực hiện trong quá trình sắp xếp.
		Count_SortAl(arr, n, sort_type1, com1);
		cout << "Running time (if required): NOT REQUIRED" << endl;
		cout << "Comparisons (if required): " << com1 << endl;
		// Kết quả được lưu trong biến com1 và in ra là số lần so sánh.
	}
	else if (Output == "-both") {
		// Nếu Output bằng "-both", chương trình thực hiện cả đo thời gian và đếm số lần so sánh. 
		int* b = new int[n];
		// Nó tạo một bản sao của mảng gốc arr có tên b và sử dụng nó để đếm số lần so sánh trong khi sắp xếp arr. 
		for (int i = 0; i < n; i++)
		{
			b[i] = arr[i];
		}

		clock_t start, end;
		start = clock();
		SortAl(arr, n, sort_type1);
		end = clock();
		double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

		long long int com1 = 0;
		Count_SortAl(b, n, sort_type1, com1);

		// Thời gian chạy và số lần so sánh được in ra.
		cout << "Running time (if required): " << fixed << time << endl;
		cout << "Comparisons(if required): " << com1 << endl;

		delete[] b;
	}
	else{
		cout << "Wrong output parameters!";
	}

	ofstream fout("output.txt");
	fout << n << endl;
	for (int i = 0; i < n - 1; i++)
	{
		fout << arr[i] << " ";
	}
	fout << arr[n - 1]; // Phần tử cuối cùng của mảng được ghi riêng để tránh dư dấu cách ở cuối tệp.
	delete[] arr;
}

// --- Run a sorting algorithm on the data generated automatically with specified size and order
// --- Write down the generated input to the "input.txt" file
void command2(string Algorithm, string inputSize, string  inputOrder, string OutputCMD) {
	cout << endl;
	cout << "ALGORITHM MODE" << endl;
	cout << "Algorithm: " << Algorithm << endl;

	// --- Sort type selection
	int sort_type1 = 0;
	for (sort_type1 = 0; sort_type1 < 11; sort_type1++)
	{
		if (sort_names[sort_type1] == Algorithm)
		{
			break;
		}
	}

	// --- Xác định kích thước đầu vào
	int n = stoi(inputSize);
	// chuyển đổi chuỗi inputSize thành số nguyên
	cout << "Input size: " << n << endl;


	// --- Xác định thứ tự đầu vào
	int _order = 0;
	// Được sử dụng để đại diện cho thứ tự của dữ liệu đầu vào
	for (_order = 0; _order < 4; _order++)
	{
		if (Order[_order] == inputOrder)
		{
			break;
		}
	}
	cout << "Input order: " << inputOrder << endl;
	cout << "---------------------------------\n";
	int* arr = new int[n];
	GenerateData(arr, n, _order);

	// --- Write down the generated input to the "input.txt" file
	ofstream fout("input.txt");
	if (!fout) {
		cout << "cannot open input.txt in cmd2 ";
		return;
	}
	fout << n << endl;
	for (int i = 0; i < n - 1; i++)
	{
		fout << arr[i] << " ";
	}
	fout << arr[n - 1]; // tránh dư dấu cách ở cuối tệp.
	fout.close();


	// --- Timing and Comparison Counting
	clock_t start, end;
	long long int com1 = 0;

	if (OutputCMD == "-time") {
		start = clock();
		SortAl(arr, n, sort_type1);
		end = clock();
		double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
		cout << "Running time (if required): " << fixed << time << endl;
		cout << "Comparisons (if required): NOT REQUIRED" << endl;

	}
	else if (OutputCMD == "-comp") {
		Count_SortAl(arr, n, sort_type1, com1);
		cout << "Running time (if required): NOT REQUIRED" << endl;
		cout << "Comparisons (if required): " << com1 << endl;

	}
	else if (OutputCMD == "-both") {
		int* b = new int[n];
		for (int i = 0; i < n; i++)
		{
			b[i] = arr[i];
		}
		start = clock();
		SortAl(arr, n, sort_type1);
		end = clock();
		double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

		long long int com1 = 0;
		Count_SortAl(b, n, sort_type1, com1);

		cout << "Running time (if required): " << fixed << time << endl;
		cout << "Comparisons (if required): " << com1 << endl;

		delete[] b;
	}
	else{
		cout << "Wrong output parameters!";
	}

	ofstream fout_out("output.txt");
	fout_out << n << endl;
	for (int i = 0; i < n - 1; i++)
	{
		fout_out << arr[i] << " ";
	}
	fout_out << arr[n - 1]; // tránh dư dấu cách ở cuối tệp.
	fout_out.close();
}

// --- Run a sorting algorithm on ALL data arrangements of a specified size.
/*
Write down all four generated input:
– "input_1.txt": random order data
– "input_2.txt": nearly sorted data
– "input_3.txt": sorted data
– "input_4.txt": reversed data
*/
void command3(string Algorithm, string inputSize, string OutputCMD) {
	cout << endl;
	cout << "ALGORITHM MODE" << endl;
	cout << "Algorithm: " << Algorithm << endl;

	// --- Sort type selection
	int sort_type1 = 0;
	for (sort_type1 = 0; sort_type1 < 11; sort_type1++)
	{
		if (sort_names[sort_type1] == Algorithm)
		{
			break;
		}
	}

	// --- Xác định kích thước đầu vào
	int n = stoi(inputSize);
	cout << "Input size: " << n << endl << endl;

	string Order[4] = { "Randomize","Reversed","Sorted","Nearly Sorted" };
	// Mảng Order chứa các chuỗi mô tả thứ tự dữ liệu đầu vào.
	
	int GenerNum[4] = { 0,2,1,3 };
	// Mảng GenerNum chứa các chỉ số tương ứng với từng trường hợp trong một trường hợp switch-case trong hàm GenerateData.

	string InputFile[4] = { "input_1.txt", "input_4.txt", "input_3.txt", "input_2.txt" };
	// Mảng InputFile chứa tên tệp tương ứng với mỗi loại dữ liệu trong mảng Order.


	for (int i = 0; i < 4; i++) 
	{
		int* arr = new int[n];
		// truyền vào số thứ tự ứng với kiểu dữ liệu
		GenerateData(arr, n, GenerNum[i]); 

		// --- Write to input 
		string filename = InputFile[i];
		ofstream fout(filename); 
		// L:ấy tên file ứng với các kiểu dữ liệu "Random", "Reverse" ...
		if (!fout) 
		{
			cout << "cannot open input_x.txt in cmd3 ";
			return;
		}
		if (filename == "input_4.txt")
		{
			fout << "\xEF\xBB\xBF";
			// Một dấu thứ tự byte UTF-8 (\xEF\xBB\xBF) được ghi vào tệp để xác định tệp là định dạng UTF-8.
		}
		fout << n << endl;
		// Kích thước đầu vào n được ghi vào tệp

		for (int i = 0; i < n - 1; i++) // ghi từng phần tử trong mảng
		{
			fout << arr[i] << " ";
		}

		fout << arr[n - 1]; // tránh dư dấu cách ở cuối tệp.
		fout.close();

		cout << "Input order: " << Order[i] << endl;
		cout << "------------------------------\n";

		// --- Timing and Comparison Counting
		clock_t start, end;
		long long int com1 = 0;

		if (OutputCMD == "-time") {
			start = clock();
			SortAl(arr, n, sort_type1);
			end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
			cout << "Running time (if required): " << fixed << time << endl;
			cout << "Comparisons (if required): NOT REQUIRED" << endl;

		}
		else if (OutputCMD == "-comp") {
			Count_SortAl(arr, n, sort_type1, com1);
			cout << "Running time (if required): NOT REQUIRED" << endl;
			cout << "Comparisons (if required): " << com1 << endl;

		}
		else if (OutputCMD == "-both") {
			int* b = new int[n];
			for (int i = 0; i < n; i++)
			{
				b[i] = arr[i];
			}
			start = clock();
			SortAl(arr, n, sort_type1);
			end = clock();
			double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

			long long int com1 = 0;
			Count_SortAl(b, n, sort_type1, com1);

			cout << "Running time (if required): " << fixed << time << endl;
			cout << "Comparisons (if required): " << com1 << endl;

			delete[] b;
		}
		cout << endl << endl;
		delete[] arr;
	}
}

// --- Run two sorting algorithms on the given input (Comparison mode)
void command4(string Algorithm1, string Algorithm2, string InputFile)
{
	ifstream fin(InputFile);
	if (!fin)
	{
		cout << "Can not read file" << endl;
		return;
	}
	int n;

	string buff; getline(fin, buff);
	// đọc một dòng đầu tiên từ tệp văn bản được mở và lưu trữ nó trong chuỗi buff
	// kiểm tra xem tệp có chứa ký tự đặc biệt "\xEF\xBB\xBF" ở đầu tệp không

	char IdentifierUTF8[] = "\xEF\xBB\xBF";
	// mảng ký tự để lưu trữ chuỗi ký tự "\xEF\xBB\xBF" nó là một đại diện cho ký tự đặc biệt BOM (Byte Order Mark) trong mã UTF-8.

	const char* firstline = buff.c_str(); 
	// Chuỗi buff được chuyển đổi thành một con trỏ const char* bằng cách sử dụng c_str() để sử dụng trong hàm strstr tiếp theo.

	if (strstr(firstline, IdentifierUTF8) != NULL) 
	{
		// Hàm strstr được sử dụng để tìm kiếm chuỗi IdentifierUTF8 (ký tự BOM) trong chuỗi firstline. 
		// Nếu chuỗi IdentifierUTF8 xuất hiện trong firstline, điều kiện này sẽ trả về con trỏ không phải NULL.

		char* number =(char*) (firstline + 3*sizeof(char));
		// Nếu tệp văn bản chứa ký tự BOM, con trỏ number sẽ trỏ tới vị trí sau 4 ký tự đầu tiên của chuỗi firstline. 
		// Mục đích là bỏ qua ký tự BOM và chỉ trỏ đến phần số nguyên trong dòng đầu tiên.

		n = atoi(number);
		// Hàm atoi được sử dụng để chuyển đổi chuỗi số nguyên đại diện bởi number thành giá trị số nguyên và gán cho biến n.
	}
	else {
		n = stoi(buff);
		// Nếu tệp văn bản không chứa ký tự BOM, dòng đầu tiên của tệp được chuyển đổi thành số nguyên bằng cách sử dụng hàm stoi và gán cho biến n.
	}


	int* arr = new int[n], * b = new int[n], * c = new int[n], * d = new int[n];

	// --- Tạo các mảng và sao chép dữ liệu
	for (int i = 0; i < n; i++)
	{
		//Mục đích: thực hiện các thuật toán sắp xếp trên các mảng này và so sánh kết quả sau đó
		fin >> arr[i]; 
		b[i] = arr[i]; 
		c[i] = arr[i]; 
		d[i] = arr[i];
	}

	// --- Xuất thông tin chế độ so sánh
	cout << endl;
	cout << "COMPARE MODE" << endl;
	cout << "Algorithm: " << Algorithm1 << " | " << Algorithm2 << endl;
	cout << "Inputfile: " << InputFile << endl;
	cout << "InputSize: " << n << endl;

	// --- Xác định loại sắp xếp
	int sort_type1 = 0, sort_type2 = 0;

	// Thuật toán Sort thứ 1
	for (sort_type1 = 0; sort_type1 < 11; ++sort_type1)
	{
		if (sort_names[sort_type1] == Algorithm1)
		{
			break;
		}
	}

	// Thuật toán Sort thứ 2
	for (sort_type2 = 0; sort_type2 < 11; ++sort_type2)
	{
		if (sort_names[sort_type2] == Algorithm2)
		{
			break;
		}
	}

	// --- Timing and Comparison Counting
	clock_t start1, end1, start2, end2;
	double time1 = 0, time2 = 0;

	start1 = clock();
	SortAl(arr, n, sort_type1);
	end1 = clock();

	start2 = clock();
	SortAl(b, n, sort_type2);
	end2 = clock();

	time1 = (double)(end1 - start1) / CLOCKS_PER_SEC * 1000;
	time2 = (double)(end2 - start2) / CLOCKS_PER_SEC * 1000;
	cout << "Runtime: " << fixed << time1 << " | " << fixed << time2 << endl;

	// --- So sánh
	long long int com1 = 0;
	Count_SortAl(c, n, sort_type1, com1);
	long long int com2 = 0;
	Count_SortAl(d, n, sort_type2, com2);
	cout << "Comparisons: " << com1 << " | " << com2 << endl;
}

// --- Run two sorting algorithms on the data generated automatically.
// --- Write down the generated input to the "input.txt" file.
void command5(string Algorithm1, string Algorithm2, string InputSize, string InputOrder) 
{
	cout << endl;
	cout << "COMPARE MODE" << endl;
	cout << "Algorithm: " << Algorithm1 << " | " << Algorithm2 << endl;
	cout << "Input size: " << InputSize << endl;
	cout << "Input Order: " << InputOrder << endl;

	// --- Xác định kiểu dữ liệu đầu vào
	int _order = 0;// input order;
	for (_order = 0; _order < 4; _order++)
	{
		if (Order[_order] == InputOrder)
		{
			break;
		}
	}

	// --- Xác định loại thuật toán
	int sort_type1 = 0, sort_type2 = 0;

	for (sort_type1 = 0; sort_type1 < 11; sort_type1++)
	{
		if (sort_names[sort_type1] == Algorithm1)
		{
			break;
		}
	}

	for (sort_type2 = 0; sort_type2 < 11; sort_type2++)
	{
		if (sort_names[sort_type2] == Algorithm2)
		{
			break;
		}
	}

	// --- Mở tệp đầu vào
	string InputFileName = "input.txt";
	ofstream fout(InputFileName);
	if (!fout)
	{
		cout << "Can not open input.txt" << endl;
		return;
	}

	int n = stoi(InputSize);
	fout << n << endl;
	int* arr = new int[n], * b = new int[n], * c = new int[n], * d = new int[n];
	GenerateData(arr, n, _order);
	for (int i = 0; i < n; i++)
	{
		fout << arr[i] << " ";
		b[i] = arr[i]; c[i] = arr[i], d[i] = arr[i];
	}

	// --- Timing and Comparison Counting
	clock_t start1, end1, start2, end2;
	double time1 = 0, time2 = 0;

	// Timing
	start1 = clock();
	SortAl(arr, n, sort_type1);
	end1 = clock();

	start2 = clock();
	SortAl(b, n, sort_type2);
	end2 = clock();

	// In kết quả ra màn hình
	time1 = (double)(end1 - start1) / CLOCKS_PER_SEC * 1000;
	time2 = (double)(end2 - start2) / CLOCKS_PER_SEC * 1000;
	cout << "Runtime: " << fixed << time1 << " | " << fixed << time2 << endl;

	// Comparison
	long long int com1 = 0;
	Count_SortAl(c, n, sort_type1, com1);

	long long int com2 = 0;
	Count_SortAl(d, n, sort_type2, com2);

	// In kết quả ra màn hình
	cout << "Comparisons: " << com1 << " | " << com2 << endl;
}

// Việc tránh dấu cách cuối cùng thường được thực hiện để đảm bảo tính nhất quán và thuận tiện trong việc xử lý dữ liệu sau này, đặc biệt là khi đọc tệp văn bản dưới dạng mảng hoặc chuỗi.
