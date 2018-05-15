/*
Author: Do Viet Tung
Id: s1232004
Compile: g++ -std=c++11 -o test p4.cpp
Run: ./test
Input:
[number of elements]
[elements]
*/
#include <iostream>
#include <algorithm>

using namespace std;

class Heap {
private:
	int *elements;
	int size;
public:
	Heap(int A[], int size) {
		this->size = size;
		elements = (int *)malloc(sizeof(int) * size);
		for (int i = 0; i < size; ++i) {
			elements[i] = A[i];
		}
		heapBottomUp();
	}

	void printHeap() {
		for (int i = 0; i < size; ++i)
			cout << elements[i] << " ";
		cout << endl;
	}

	void maxHeapify(int i) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int largest = i;
		if (left < size && elements[left] > elements[largest])
			largest = left;
		if (right < size && elements[right] > elements[largest])
			largest = right;
		if (largest != i) {
			// cout << "Swap "  << elements[i] << " and " << elements[largest] << endl;
			// cout << elements[left] << " " << elements[right] << endl;
			swap(elements[i], elements[largest]);
			maxHeapify(largest);
		}
	}

	void heapBottomUp() {
		for (int i = size / 2; i >= 0; --i) {
			maxHeapify(i);
		}
	}
};

int main() {
	int n;
	cin >> n;
	int A[n];
	for (int i = 0; i < n; ++i)
		cin >> A[i];
	Heap h = Heap(A, n);
	h.printHeap();
}