#pragma once
#include"Cargo.h"
#include"LinkedList.h"
template <typename T>
class LinkedListCargo:public LinkedList<Cargo*>, Cargo
{
private:
	Node<Cargo*>* Head;
	//T getHead();
public:

	LinkedListCargo() :LinkedList< Cargo* >() {}
	Cargo* FindCargo(int Id) {

		Node<Cargo*>* P = Head;
		while (P != nullptr) {
			if (P->getItem()->getCargoID() == Id) {
				return P->getItem();
			}
			else {
				P = P->getNext();
			}
		}
		return nullptr;
	}


};

