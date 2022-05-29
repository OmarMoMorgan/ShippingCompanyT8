#pragma once
//#include "stdafx.h"
#include <iostream>
#include "Cargo.h"
#include"Truck.h"
using namespace std;


//instead of doing what happened where we have a node with prioirty and some data we will overload operator instead


template <typename T>
class PriorityQueueArr {
private:
	struct Node {
		int priority = 1;
		T data;
	};
	Node* arr;
	int size;
	int arrsize;

public:
	PriorityQueueArr() {
		arrsize = 1600;
		arr = new Node[arrsize];

		size = -1;
	}

	PriorityQueueArr(int maxSize) {
		arr = new Node[maxSize];
		size = -1;
		arrsize = maxSize;
	}


private:
	int leftChild(int i)
	{

		return ((2 * i) + 1);
	}

	// Function to return the index of the
	// right child of the given node
	int rightChild(int i)
	{

		return ((2 * i) + 2);
	}


	int parent(int i)
	{
		return (i - 1) / 2;
	}

	void shiftUp(int index) {
		while (index > 0 && arr[parent(index)].priority < arr[index].priority) {

			// Swap parent and current node
			swap(arr[parent(index)], arr[index]);

			// Update i to parent of i
			index = parent(index);
		}
	}



	//this method is mainly for debuggging right now it shall be optimized later to suit the ui
	void printar() {
		for (int i = 0; i < 5; i++) {
			cout << arr[i].data << endl;
		}
	}


	void shiftDown(int i)
	{
		int maxIndex = i;

		// Left Child
		int l = leftChild(i);

		if (l <= size && arr[l].priority > arr[maxIndex].priority) {
			maxIndex = l;
		}

		// Right Child
		int r = rightChild(i);

		if (r <= size && arr[r].priority > arr[maxIndex].priority) {
			maxIndex = r;
		}

		// If i not same as maxIndex
		if (i != maxIndex) {
			swap(arr[i], arr[maxIndex]);
			shiftDown(maxIndex);
		}
	}

	//function to resize the array thus it will take any size
	//it doubles the array size by 2
	void resize() {
		size_t newSize = arrsize * 2;
		Node* newArr = new Node[newSize];

		memcpy(newArr, arr, arrsize * sizeof(Node));

		arrsize = newSize;
		//delete[] arr;
		arr = newArr;
	}


public:
	T Pop()
	{
		T result = arr[0].data;

		// Replace the value at the root
		// with the last leaf
		arr[0] = arr[size];
		size = size - 1;

		// Shift down the replaced element
		// to maintain the heap property
		shiftDown(0);
		return result;
	}


	void insert(T n_item) {
		//Node n_node;
		//n_node.data = n_item;
		if (size < arrsize) {
			size++;
			arr[size].data = n_item;
			arr[size].priority = 1;

			// Shift Up to maintain heap property
			shiftUp(size);
		}
		//check this also if needed 
		//else {
		//	resize();
		//	size++;
		//	arr[size].data = n_item;
		//	arr[size].priority = 1;

		//	// Shift Up to maintain heap property
		//	shiftUp(size);
		//}
	}

	void insert(T n_data, int p)
	{
		if (size < arrsize) {
			size = size + 1;
			arr[size].data = n_data;
			arr[size].priority = p;

			// Shift Up to maintain heap property
			shiftUp(size);
		}
		//ceck this if needed
		//else {
		//	resize();
		//	size = size + 1;
		//	arr[size].data = n_data;
		//	arr[size].priority = p;

		//	// Shift Up to maintain heap property
		//	shiftUp(size);
		//}
	}


	int getCount() {
		return size + 1;
	}

	void peek(T& Output) {
		Output = arr[0].data;
	}

	bool Pop(T& Output) {
		if (getCount() == 0) {
			return false;
		}
		Output = arr[0].data;

		// Replace the value at the root
		// with the last leaf
		arr[0] = arr[size];
		size = size - 1;

		// Shift down the replaced element
		// to maintain the heap property
		shiftDown(0);
		return true;
	}

	void printarr() {}

	 void printarrCargo(){
	for (int i = 0; i < getCount(); i++) {
		cout << arr[i].data->getCargoID() << ",";
	}
	//cout << arr[getCount() - 1].data->getCargoID();
}


	 void printarrTruck()
	 {
		 if (getCount() >= 0)
		 {
			 for (int i = 0; i < getCount(); i++) {
				 cout << arr[i].data->getTrucID() << ",";
			
				 for (int j=0;j< arr[i].data->getListCount();j++)
				 {
					 cout << "{  ";
					 int cargotype = arr[i].data->peekCargo()->getCargoType();
					 switch (cargotype) {
					 case 1:
						 cout << "[ " << arr[i].data->DeleiverCargo()->getCargoID() << "], ";
						 break;
					 case 2:
						 cout << "( " << arr[i].data->DeleiverCargo()->getCargoID() << "), ";
						 break;
					 case 3:
						 cout << "{ " << arr[i].data->DeleiverCargo()->getCargoID() << "}, ";
					 default:
						 break;
					 }
					 cout << "}";
				 }
				
			 }
			 //cout << arr[getCount() - 1].data->getTrucID();
		 }
	 }
};