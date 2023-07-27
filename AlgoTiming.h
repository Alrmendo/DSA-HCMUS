#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

// --- Selection Sort
void Selection_sort(int arr[], int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		int imin = i, min = arr[i];
		for (int j = i + 1; j < n; ++j)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				imin = j;
			}
		}
		swap(arr[i], arr[imin]);
	}
}

// --- Insertion Sort
void Insertion_sort(int arr[], int n)
{
	for (int i = 1; i < n; ++i)
	{
		int v = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > v)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = v;
	}
}

// --- Bubble Sort
void Bubble_sort(int arr[], int n)
{
	for (int i = 2; i < n; ++i)
	{
		for (int j = n; j >= i; --j)
		{
			if (arr[j] < arr[j - 1])
			{
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

// --- Shaker Sort
void Shaker_sort(int arr[], int n) {
    int left, right, k, i;
    left = 0;
    right = n - 1;
    k = 0;
    while(left < right) {
        for( int i = left; i < right; i++)
        {
			if(arr[i] > arr[i + 1]) 
			{
                swap(arr[i], arr[i + 1]);
                k = i;
            }
		}
        right = k;

        for( int i = right; i > left; i--)
        {
			if(arr[i] < arr[i - 1]) 
			{
                swap(arr[i], arr[i - 1]);
                k = i;
            }
		}
        left = k;
    }
}

// --- Shell Sort
void Shell_sort(int arr[], int n)
{
	for (int mid = n / 2; mid > 0; mid /= 2)
	{
		for (int i = mid; i < n; i += 1)
		{
			int temp = arr[i];
			int j;
			for (j = i; (j >= mid) && (arr[j - mid] > temp); j -= mid)
			{
				arr[j] = arr[j - mid];
			}
			arr[j] = temp;
		}
	}
}

// --- Heap Sort
void C_HeapBuild(int arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
	{
		largest = left;
	}

	if (right < n && arr[right] > arr[largest])
	{
		largest = right;
	}

	if (largest != i)
	{
		swap(arr[largest], arr[i]);
		C_HeapBuild(arr, n, largest);
	}
}

void C_CreatHeap(int arr[], int n)
{
	for (int j = n / 2; j >= 0; j--)
	{
		C_HeapBuild(arr, n, j);
	}
}

void C_Heap_sort(int arr[], int n) {
	C_CreatHeap(arr, n);
	for (int i = n - 1; i >= 0; --i)
	{
		swap(arr[0], arr[i]);
		C_HeapBuild(arr, i, 0);
	}
}

// --- Merge Sort
void merge(int arr[], int l, int m, int r)
{
	vector <int> a1(arr + l, arr + m + 1);
	vector <int> a2(arr + m + 1, arr + r + 1);
	int i = 0, j = 0;
	while (i < a1.size() && j < a2.size())
	{
		if (a1[i] <= a2[j])
		{
			arr[l++] = a1[i++];
		}
		else
		{
			arr[l++] = a2[j++];
		}
	}
	while (i < a1.size())
	{
		arr[l++] = a1[i++];
	}
	while (j < a2.size())
	{
		arr[l++] = a2[j++];
	}
}

void Merge_sort(int arr[], int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int m = (l + r) / 2;
	Merge_sort(arr, l, m);
	Merge_sort(arr, m + 1, r);
	merge(arr, l, m, r);
}

// --- Quick Sort
int partition(int arr[], int low, int high) {
	int pivot = arr[high]; 
	int right = high - 1;
	int left = low; 
	while (true) 
	{         
		while ((left <= right) && (arr[left] < pivot))
		{
			left++; 
		}
		while ((right >= left) && (arr[right] > pivot))
		{
			right--;
		}
		if (left >= right) 
			break;
		swap(arr[left], arr[right]); 
		left++;                     
		right--;
	}
	swap(arr[left], arr[high]);            
	return left;            
}

void Quick_sort(int arr[], int low, int high) {
	if (low < high) 
	{
		int pivot = partition(arr, low, high); 
		Quick_sort(arr, low, pivot - 1);        
		Quick_sort(arr, pivot + 1, high);     
	}
}
 
// --- Counting Sort
void getMinMax(int arr[], int n, int& min, int& max) {
	min = arr[0];
	max = arr[0];
	for (int i = 1; i < n; i++) {
		if (min > arr[i])
		{
			min = arr[i];
		}
		if (max < arr[i])
		{
			max = arr[i];
		}
	}
}

void Counting_sort(int arr[], int n) {
	int min, max;
	getMinMax(arr, n, min, max);
	int* count = new int[max - min + 1];

	for (int i = 0; i < max - min + 1; i++)
	{
		count[i] = 0; // khởi tạo các giá trị của mảng bằng 0
	}
	for (int i = 0; i < n; i++)
	{
		count[arr[i] - min]++; // lưu số lần xuất hiện vào mảng
	}
	int k = 0;
	for (int i = 0; i < max - min + 1; i++)
		while (count[i] > 0)
		{
			arr[k++] = i + min;
			count[i]--;
		}

	delete[] count;
}

// --- Radix Sort
void Radix_sort(int* a, int n)
{
	int* b = new int[n];
	int m = a[0], exp = 1;

	for (int i = 0; i < n; i++)
	{
		if (a[i] > m)
		{
			m = a[i];
		}
	}

	while (m / exp > 0)
	{
		int bucket[10] = { 0 };
		for (int i = 0; i < n; i++)
		{
			bucket[a[i] / exp % 10]++;
		}
		for (int i = 1; i < 10; i++)
		{
			bucket[i] += bucket[i - 1];
		}
		for (int i = n - 1; i >= 0; i--)
		{
			int pos_output = --bucket[a[i] / exp % 10];
			b[pos_output] = a[i];
		}

		for (int i = 0; i < n; i++)
		{
			a[i] = b[i];
		}
		exp *= 10;
	}
	delete[] b;
}

// --- Flash Sort
void Flash_sort(int arr[], int n) {
	int minVal = arr[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0; i < m; i++)
	{
		l[i] = 0;
	}
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < minVal)
		{
			minVal = arr[i];
		}
		if (arr[i] > arr[max])
		{
			max = i;
		}
	}
	if (arr[max] == minVal)
	{
		return;
	}
	double c1 = (double)(m - 1) / (arr[max] - minVal);
	for (int i = 0; i < n; i++)
	{
		int k = int(c1 * (arr[i] - minVal));
		++l[k];
	}
	for (int i = 1; i < m; i++)
	{
		l[i] += l[i - 1];
	}
	swap(arr[max], arr[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (nmove < n - 1)
	{
		while (j > l[k] - 1)
		{
			j++;
			k = int(c1 * (arr[j] - minVal));
		}
		flash = arr[j];
		if (k < 0)
		{
			break;
		}
		while (j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = arr[t = --l[k]];
			arr[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	Insertion_sort(arr, n);
}

void SortAl(int arr[], int n, int type) 
{
	switch (type) {
	case 0:
		Selection_sort(arr, n);
		break;
	case 1:
		Insertion_sort(arr, n);
		break;
	case 2:
		Bubble_sort(arr, n);
		break;
	case 3:
		Shaker_sort(arr, n);
		break;
	case 4:
		Shell_sort(arr, n);
		break;
	case 5:
		C_Heap_sort(arr, n);
		break;
	case 6:
		int l, r;
		l = 0;
		r = n - 1;
		Merge_sort(arr, l, r);
		break;
	case 7:
		int low, high;
		low = 0;
		high = n - 1;
		Quick_sort(arr, low, high);
		break;
	case 8:
		Counting_sort(arr, n);
		break;
	case 9:
		Radix_sort(arr, n);
		break;
	case 10:
		Flash_sort(arr, n);
		break;
	default:
		cout << "Error: unknown data type!\n";
	}
}
