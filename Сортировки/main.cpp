#include <iostream>
#include "Sort.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	int a[] = { 3, 5, 1, 2, 1, 0, 5, 4 };
	int n = sizeof(a) / sizeof(a[0]);

	string filename = "D://Valentine/SkillFactory/FILE.txt";
	write_arr(filename, a, n);

	int* arr_from_file = nullptr;
	int size = 0;
	read_arr(filename, arr_from_file, size);
	int l = 0;
	int r = size - 1;
	int m = (l + r - 1) / 2;
	auto start = chrono::high_resolution_clock::now();
	quickSort(arr_from_file, l, size - 1);
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Продолжительность работы алгоритма: " << elapsed.count() << " сек" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << arr_from_file[i] << " ";
	}
	cout << endl;
	cout << "Максимальный элемент : " << getMax(a, n) << endl;

	delete[] arr_from_file;
	return 0;
}