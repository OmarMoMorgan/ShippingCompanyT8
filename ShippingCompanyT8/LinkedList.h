#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>
#include"Cargo.h"
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:

	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}
	
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}
	
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list


	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T key){
		Node<T>* P = Head;
		//P->setNext(Head);
		while(P != nullptr){
			if (P->getItem() == key) {
				return true;
			}else { 
				P = P->getNext(); 
			}
		}
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list

	//[4] DeleteFirst
	//Deletes the first node in the list

	//[5] DeleteLast
	//Deletes the last node in the list

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(T value){
		Node<T>* P = Head;
		if (Head == nullptr) {
			return false;
		}
		if (P->getNext()->getNext() == nullptr) {
			if(P->getItem() == value){
				delete P;
				Head = nullptr;
			}
		}
			while (P->getNext()) {
				if (P->getNext()->getItem() == value) {
					P->setNext(P->getNext()->getNext());
					delete P->getNext();
					return true;
				}
				else {
					P = P->getNext();
				}
			}
		
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)

	bool InsertSorted(T value){
		Node<T>* P = Head;
		//T prev = P->getItem();
		if (P->getNext() == nullptr) {
			if (value == P->getNext()->getItem()) {
				return false;
			}else if(P->getNext()->getItem() > value){
				Node<T> *R = new Node<T>(value);
				P->setNext(R);
				return true;
			}
			else {
				Node<T>* R = new Node<T>(value);
				R->setNext(P);
				Head = R;
				return true;
			}
		}
		if (value < P->getItem()) {
			Node<T>* R = new Node<T>(value);
			R->setNext(P);
			P->setNext(R);
			return true;
		}
		while (P->getNext()) {

			if (P->getItem() < value && P->getNext()->getItem() > value) {
				Node<T>* R = new Node<T>(value);
				R->setNext(P->getNext());
				cout << "Ireache here";
				P->setNext(R);
				return true;
			}
			else {
				P = P->getNext();
			}
		}
		if (P->getItem() < value) {
			Node<T>* R = new Node<T>(value);
			P->setNext(R);
			return true;
		}
		return false;
	}

	void ShfitLargest() {
		if (Head) {
			Node<T>* P = Head;
			P->setNext(Head);
			Node<T>* Holder;
			if (P->getNext()->getNext()) {
				while (P->getNext()->getNext()) {
					if (P->getNext()->getItem() > P->getNext()->getNext()->getItem()) {
						Holder = P->getNext();
						P->getNext()->setNext(P->getNext()->getNext());
						Holder->setNext(P->getNext());
						P->setNext(Holder);
					}
					P = P->getNext();
				}
			}

		}
		else { return; }
	}

	int getCounter() {
		int counter = 0;
		if (Head) {
			counter++;
		}
		Node* mover;
		mover = Head->getNext();
		while (mover)
		{
			counter++;
			mover = mover->getNext();
		}
		return counter;
	}
};

#endif	
//class LinkedList<Cargo>
//{
//	Node<Cargo>* FindCargo(int Id) {
//
//		Cargo* P = Head;
//		//P->setNext(Head);
//		while (P != nullptr) {
//			if (P->getCargoID() == id) {
//				return P;
//			}
//			else {
//				P = P->getNext();
//			}
//		}
//		return nullptr;
//	}
//}
