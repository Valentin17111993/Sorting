#include "Sort.h"
#include <algorithm>
#include <string>
#include <fstream>  // работа с файлами
#include <iostream>
#include <cstdlib> // для получения рандомных чисел
#include <ctime>

using namespace std;

int getMax(int* arr, int n)
{
	int Max = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > Max)
		{
			Max = arr[i];
		}
	}
	return Max;
}

void countSort(int* arr, int n)
{
	int* output = new int[n];
	int Max = getMax(arr, n);
	int* count = new int[Max + 1];

	for (int i = 0; i < Max + 1; i++)
	{
		count[i] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		count[arr[i]]++;
	}

	for (int i = 1; i < Max + 1; i++)
	{
		count[i] += count[i-1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}

	for (int i = 0; i < n; i++)
	{
		arr[i] = output[i];
	}

	delete[] output;
	delete[] count;

}

void countSort(int* arr, int n, int exp)
{
	int* output = new int[n];
	int count[10] = { 0 };

	for (int i = 0; i < n; i++)
	{
		count[(arr[i] / exp) % 10]++;
	}

	for (int i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (int i = 0; i < n; i++)
	{
		arr[i] = output[i];
	}

	delete[] output;
}

void radixSort(int* arr, int n)
{
	int m = getMax(arr, n);
	int exp = 1;

	while (m / exp != 0)
	{
		countSort(arr, n, exp);
		exp *= 10;
	}
}

int getExp(int value)
{
	int Exp = 1;
	while (value > 10)
	{
		value /= 10;
		Exp *= 10;
	}

	return Exp;
}

void bucketSort(int* arr, int n)
{
	Bucket bucket[10];
	int Exp = getExp(getMax(arr, n));

	for (int i = 0; i < 10; i++)
	{
		bucket[i].count = 0;
		bucket[i].data = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		int m = arr[i]/Exp;
		bucket[m].data[bucket[m].count++] = arr[i];
	}

	for (int i = 0; i < 10; i++)
	{
		if (bucket[i].count != 0)
		{
			countSort(bucket[i].data, bucket[i].count);
		}
	}

	int M = 0;

	for (int i = 0; i < 10; i++)
	{
		if (bucket[i].count != 0)
		{
			for (int j = 0; j < bucket[i].count; j++)
			{
				arr[j + M] = bucket[i].data[j];
			}
			M += bucket[i].count;
		}
	}
}

void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

void merge(int* arr, int l, int m, int r)
{
	int nl = m - l + 1;
	int nr = r - m;

	int* left = new int[nl];
	int *right = new int[nr];

	for(int i = 0; i < nl; i++)
	{
		left[i] = arr[i + l];
	}

	for (int j = 0; j < nr; j++)
	{
		right[j] = arr[j + m + 1];
	}

	int i = 0;
	int j = 0;
	int k = l;

	while (i < nl && j < nr)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < nl)
	{
		arr[k] = left[i];
		i++;
		k++;
	}
	while (j < nr)
	{
		arr[k] = right[j];
		j++;
		k++;
	}

	delete[] left;
	delete[] right;
}

void mergeSort(int* arr, int l, int r)
{
	if (l >= r)
	{
		return;
	}
	else
	{
		int m = (l + r - 1) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void insertionSort(int* arr, int l, int n)
{
	for (int i = l + 1; i < n; i++) 
	{
		int key = arr[i];
		int j = i - 1;

		// Сдвигаем элементы arr[0..i-1], которые больше чем key, на одну позицию вперед
		while (arr[j] >= key && j >= l)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}

void selectionSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int min = arr[i];
		int IndexMin = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				IndexMin = j;
			}
		}
		Swap(&arr[i], &arr[IndexMin]);
	}
}

void timSort(int* arr, int n)
{
	const int RUN = 16;
	for (int i = 0; i < n; i++)
	{
		int r;
		int k = n / RUN;
		int f = n - k * RUN;
		if (f < RUN)
		{
			r = n;
		}
		else
		{
			r = i + RUN;
		}
		insertionSort(arr, i, r);
	}
	for (int size = RUN; size < n; size *= 2)
	{
		for (int left = 0; left < n; left += 2 * size)
		{
			int mid = left + size - 1;
			int right;
			if ((left + 2 * size - 1) < (n - 1))
			{
				right = left + 2 * size - 1;
			}
			else
			{
				right = n - 1;
			}

			if (mid > right)
				mid = left;

			merge(arr, left, mid, right);
		}
	}
}

int partition(int* arr, int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
	for (int j = low; j < high; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			Swap(&arr[i], &arr[j]);
		}
	}
	Swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int* arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void write_arr(const string& filename, const int* arr, const int n)
{
	fstream fs;
	fs.open(filename, fstream::out);

	if (fs.is_open())
	{
		fs << n << '\n';
		for (int i = 0; i < n; i++)
		{
			fs << arr[i] << ' ';
		}
		fs << '\n';
		fs.close();
	}
}

void read_arr(const string& filename, int*& arr, int& n)
{
	fstream fs;
	fs.open(filename, fstream::in);

	if (fs.is_open())
	{
		fs >> n;
		arr = new int[n];
		for (int i = 0; i < n; i++)
		{
			fs >> arr[i];
		}
		fs.close();
	}
}