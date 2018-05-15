/*
Author: Do Viet Tung
ID: s1232004

Compile and Runing Instructions:
- Compile: g++ -std=c++11 -o test p3.cpp
- Run: ./test
- Input:
+ First line: number of elements in the array
+ The rest is the elements in the array
*/


#include <iostream>

using namespace std;

void merge(int A[], int left, int mid, int right) {
	int firstLength = mid - left + 1; // from left to mid
	int secondLength = right - mid; // from mid + 1 to right
	int firstHalf[firstLength];
	int secondHalf[secondLength];

	// copy the array
	for (int i = 0; i < firstLength; ++i)
		firstHalf[i] = A[i + left];
	for (int i = 0; i < secondLength; ++i)
		secondHalf[i] = A[i + mid + 1];

	int i = 0, j = 0;
	int k = left;
	while (i < firstLength && j < secondLength) {
		if (firstHalf[i] <= secondHalf[j]) {
			A[k] = firstHalf[i];
			++i;
		} else {
			A[k] = secondHalf[j];
			++j;
		}
		++k;
	}

	while (i < firstLength) {
		A[k] = firstHalf[i];
		++i;
		++k;
	}
	while (j < secondLength) {
		A[k] = secondHalf[j];
		++j;
		++k;
	}
}

void mergeSort(int A[], int left, int right) {
	if (left < right) {
		int mid = (right - left) / 2 + left;
		mergeSort(A, left, mid);
		mergeSort(A, mid + 1, right);
		merge(A, left, mid, right);
	}
}

int main() {
	int n;
	cin >> n;
	int A[n];
	for (int i = 0; i < n; ++i)
		cin >> A[i];
	mergeSort(A, 0, n - 1);
	for (int i = 0; i < n; ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}