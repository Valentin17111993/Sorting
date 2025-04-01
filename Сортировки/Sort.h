#include <string>
#include <fstream> 

#pragma once
using namespace std;
struct Bucket
{
	int count;
	int* data;
};

int getMax(int* arr, int n);
void countSort(int* arr, int n);
void countSort(int* arr, int n, int exp);
void radixSort(int* arr, int n);
int getExp(int value);
void bucketSort(int* arr, int n);
void Swap(int* a, int* b);
void bubbleSort(int* arr, int n);
void merge(int* arr, int l, int m, int r);
void mergeSort(int* arr, int l, int r);
void insertionSort(int* arr, int l, int n);
void selectionSort(int* arr, int n);
void timSort(int* arr, int n);
int partition(int* arr, int low, int high);
void quickSort(int* arr, int low, int high);
void write_arr(const string& filename, const int* arr, const int n);
void read_arr(const string& filename, int*& arr, int& n);