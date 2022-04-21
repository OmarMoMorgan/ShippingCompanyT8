#pragma once
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

public:
	PriorityQueueArr() {
		arr = new Node[16];
		size = -1;
	}

	PriorityQueueArr(int maxSize) {
		arr = new Node[maxSize];
		size = -1;
	}

	void insert(T n_item) {
		Node n_node;
		n_node.data = n_item;
		size++;
	}

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

	void insert(T n_data,int p)
	{
		size = size + 1;
		arr[size].data = n_data;
		arr[size].priority = p;

		// Shift Up to maintain heap property
		shiftUp(size);
	}

	//this method is mainly for debuggging right now
	void printarr() {
		for (int i = 0; i < 5;i++) {
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

	int getCount() {
		return size + 1;
	}
	
};