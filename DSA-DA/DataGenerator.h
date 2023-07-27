#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>


using namespace std;

template <class T>
void HoanVi(T& a, T& b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int arr[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(arr[r1], arr[r2]);
	}
}

void GenerateData(int arr[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(arr, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(arr, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(arr, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(arr, n);
		break;
	default:
		cout << "Error: unknown data type!\n";
	}
}
