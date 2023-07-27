#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// --- Selection Sort
void Count_selection_sort(int arr[], int n, long long int& c)
{
	for (int i = 0; c++, i < n - 1; ++i)
	{
		int imin = i, min = arr[i];
		for (int j = i + 1; c++, j < n; ++j)
		{
			if (c++, arr[j] < min)
			{
				min = arr[j];
				imin = j;
			}
		}
		swap(arr[i], arr[imin]);
	}
}

// --- Insertion Sort
void Count_Insertion_sort(int arr[], int n, long long int& c)
{
	for (int i = 1; c++, i < n; ++i)
	{
		int v = arr[i];
		int j = i - 1;
		while ((c++, j >= 0) && (c++, arr[j] > v))
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = v;
	}
}

// --- Bubble Sort
void Count_Bubble_sort(int arr[], int n, long long int& c)
{
	for (int i = 2; c++, i < n; ++i)
	{
		for (int j = n; c++, j >= i; --j)
		{
			if (c++, arr[j] < arr[j - 1])
			{
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

// --- Shaker Sort
void Count_Shaker_sort(int arr[], int n, long long int& c) 
{
    int left, right, k, i;
    left = 0;
    right = n - 1;
    k = 0;
    while(c++, left < right) {
        for( int i = left; c++, i < right; i++)
            if(c++, arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                k = i;
            }
        right = k;

        for( int i = right; c++, i > left; i--)
            if(c++, arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                k = i;
            }
        left = k;
    }
}

// --- Shell Sort
void Count_Shell_sort(int arr[], int n, long long int& c)
{
	for (int mid = n / 2; c++, mid > 0; mid /= 2)
	{
		for (int i = mid; c++, i < n; i += 1)
		{
			int temp = arr[i];
			int j;
			for (j = i; (c++, j >= mid) && (c++, arr[j - mid] > temp); j -= mid)
			{
				arr[j] = arr[j - mid];
			}
			arr[j] = temp;
		}
	}
}

// --- Heap Sort
void HeapBuild(int arr[], int n, int i, long long int& c) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if ((c++, left < n) && (c++, arr[left] > arr[largest]))
	{
		largest = left;
	}

	if ((c++, right < n) && (c++, arr[right] > arr[largest]))
	{
		largest = right;
	}

	if (c++, largest != i)
	{
		swap(arr[largest], arr[i]);
		HeapBuild(arr, n, largest, c);
	}
}

void CreatHeap(int arr[], int n, long long int& c)
{
	for (int j = n / 2; c++, j >= 0; j--)
	{
		HeapBuild(arr, n, j, c);
	}
}

void Count_Heap_sort(int arr[], int n, long long int& c) {
	CreatHeap(arr, n, c);
	for (int i = n - 1; c++, i >= 0; --i)
	{
		swap(arr[0], arr[i]);
		HeapBuild(arr, i, 0, c);
	}
}

// --- Merge Sort
void merge(int arr[], int l, int m, int r, long long int& c)
{
	vector <int> a1(arr + l, arr + m + 1);
	vector <int> a2(arr + m + 1, arr + r + 1);
	int i = 0, j = 0;
	while ((c++, i < a1.size()) && (c++, j < a2.size()))
	{
		if (c++, a1[i] <= a2[j])
		{
			arr[l++] = a1[i++];
		}
		else
		{
			arr[l++] = a2[j++];
		}
	}
	while (c++, i < a1.size())
	{
		arr[l++] = a1[i++];
	}
	while (c++, j < a2.size())
	{
		arr[l++] = a2[j++];
	}
}

void Count_Merge_sort(int arr[], int l, int r, long long int& c)
{
	if (l >= r)
	{
		return;
	}
	int m = (l + r) / 2;
	Count_Merge_sort(arr, l, m, c);
	Count_Merge_sort(arr, m + 1, r, c);
	merge(arr, l, m, r, c);
}

// --- Quick Sort
int partition(int arr[], int low, int high, long long int& c) {
	int pivot = arr[high]; 
	int right = high - 1;
	int left = low; 
	while (true) 
	{         
		while ((c++, left <= right) && (c++, arr[left] < pivot))
		{
			left++; 
		}
		while ((c++, right >= left) && (c++, arr[right] > pivot))
		{
			right--;
		}
		if (c++, left >= right) 
			break;
		swap(arr[left], arr[right]); 
		left++;                     
		right--;
	}
	swap(arr[left], arr[high]);            
	return left;            
}

void Count_Quick_sort(int arr[], int low, int high, long long int& c) {
	if (c++, low < high) 
	{
		int pivot = partition(arr, low, high, c); 
		Count_Quick_sort(arr, low, pivot - 1, c);        
		Count_Quick_sort(arr, pivot + 1, high, c);     
	}
}

// --- Counting Sort
void getMinMax(int arr[], int n, int& min, int& max, long long int& c) {
	min = arr[0];
	max = arr[0];
	for (int i = 1; c++, i < n; i++) {
		if (c++, min > arr[i])
		{
			min = arr[i];
		}
		if (c++, max < arr[i])
		{
			max = arr[i];
		}
	}
}

void Count_Counting_sort(int arr[], int n, long long int& c) {
	int min, max;
	getMinMax(arr, n, min, max, c);
	int* count = new int[max - min + 1];

	for (int i = 0; c++, i < max - min + 1; i++)
	{
		count[i] = 0; // khởi tạo các giá trị của mảng bằng 0
	}
	for (int i = 0; c++, i < n; i++)
	{
		count[arr[i] - min]++; // lưu số lần xuất hiện vào mảng
	}
	int k = 0;
	for (int i = 0; c++, i < max - min + 1; i++)
		while (c++, count[i] > 0)
		{
			arr[k++] = i + min;
			count[i]--;
		}

	delete[] count;
}

// --- Radix Sort
void Count_Radix_sort(int* a, int n, long long int& c)
{
	int* b = new int[n];
	int m = a[0], exp = 1;

	for (int i = 0; c++, i < n; i++)
	{
		if (c++, a[i] > m)
		{
			m = a[i];
		}
	}

	while (c++, m / exp > 0)
	{
		int bucket[10] = { 0 };
		for (int i = 0; c++, i < n; i++)
		{
			bucket[a[i] / exp % 10]++;
		}
		for (int i = 1; c++, i < 10; i++)
		{
			bucket[i] += bucket[i - 1];
		}
		for (int i = n - 1; c++, i >= 0; i--)
		{
			int pos_output = --bucket[a[i] / exp % 10];
			b[pos_output] = a[i];
		}

		for (int i = 0; c++, i < n; i++)
		{
			a[i] = b[i];
		}
		exp *= 10;
	}
	delete[] b;
}

// --- Flash Sort
void Count_Flash_sort(int arr[], int n, long long int& c) 
{
	int minVal = arr[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0; c++, i < m; i++)
	{
		l[i] = 0;
	}
	for (int i = 1; c++, i < n; i++)
	{
		if (c++, arr[i] < minVal)
		{
			minVal = arr[i];
		}
		if (c++, arr[i] > arr[max])
		{
			max = i;
		}
	}
	if (c++, arr[max] == minVal)
	{
		return;
	}
	double c1 = (double)(m - 1) / (arr[max] - minVal);
	for (int i = 0; c++, i < n; i++)
	{
		int k = int(c1 * (arr[i] - minVal));
		++l[k];
	}
	for (int i = 1; c++, i < m; i++)
	{
		l[i] += l[i - 1];
	}

	swap(arr[max], arr[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (c++, nmove < n - 1)
	{
		while (c++, j > l[k] - 1)
		{
			j++;
			k = int(c1 * (arr[j] - minVal));
		}
		flash = arr[j];
		if (c++, k < 0)
		{
			break;
		}
		while (c++, j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = arr[t = --l[k]];
			arr[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	Count_Insertion_sort(arr, n, c);
}


void Count_SortAl(int arr[], int n, int type, long long int& c) {
	switch (type) {
	case 0:
		Count_selection_sort(arr, n, c);
		break;
	case 1:
		Count_Insertion_sort(arr, n, c);
		break;
	case 2:
		Count_Bubble_sort(arr, n, c);
		break;
	case 3:
		Count_Shaker_sort(arr, n, c);
		break;
	case 4:
		Count_Shell_sort(arr, n, c);
		break;
	case 5:
		Count_Heap_sort(arr, n, c);
		break;
	case 6:
		int l, r;
		l = 0;
		r = n - 1;
		Count_Merge_sort(arr, l, r, c);
		break;
	case 7:
		int low, high;
		low = 0;
		high = n - 1;
		Count_Quick_sort(arr, low, high, c);
		break;
	case 8:
		Count_Counting_sort(arr, n, c);
		break;
	case 9:
		Count_Radix_sort(arr, n, c);
		break;
	case 10:
		Count_Flash_sort(arr, n, c);
		break;
	default:
		cout << "Error: unknown data type!\n";
	}
}
