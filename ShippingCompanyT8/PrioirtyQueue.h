#pragma once
#include "PriorityNode.h"

//this is a max heap priority queue

template <typename T>
class PriorityQueue
{
private:
	PriorirityNode<T>* root;
	PriorirityNode<T>* tail;
	void swapupwards(PriorirityNode<T>* n1);
public:
	PriorityQueue();
	PriorityQueue(const T &n_item);
	~PriorityQueue();
	

	void insert(const T& n_item , const int& n_priority);

};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	root = nullptr;
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const T &n_item)
{
	root = new PriorirityNode(n_item);
	tail = root->GetLeft();
}

template <typename T>
void PriorityQueue<T>::insert(const T& n_item , const int& n_priority) {
		
}

template <typename T>
void PriorityQueue<T>::swapupwards(PriorirityNode<T>* n1) {
	PriorirityNode<T>* n1left = n1->GetLeft();
	PriorirityNode<T>* n1Right = n1->GetRight();

	PriorirityNode<T>* n2 = n1->GetHead();
	if (n1->GetPrioirty() > n2->GetPrioirty()) {
		if (n2->GetHead() != nullptr) {
			if ((n2->GetHead()).GetLeft == n2) {
				(n2->GetHead()).SetLeft(n1);

			}
			else {
				(n2->GetHead()).SetRight(n1);
			}

		}
		else {
			root = n1;
		}

		if (n2->GetLeft() == n1) {
			n1->SetRight() = n2->GetRight();
			n1->SetLeft() = n2;
		}
		else {
			n1->SetLeft() = n2->GetLeft();
			n1->SetRight() = n2;
		}
		n2->SetLeft() = n1left;
		n2->SetRight() = n1Right;
	}
}


template <typename T>
PriorityQueue<T>::~PriorityQueue() {

}


