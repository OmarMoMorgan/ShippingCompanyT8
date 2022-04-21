#pragma once
#include"Cargo.h"
#include"LinkedList.h"
template <typename T>
class LinkedListCargo:public LinkedList<T>, Cargo
{
private:
	Node<Cargo*>* Head;
public:

	LinkedListCargo() :LinkedList< Cargo* >() {}
	Cargo* FindCargo(int Id) {

		Node<Cargo*>* P = Head;
		while (P != nullptr) {
			if (P->getItem()->getCargoID() == Id) {
				return P;
			}
			else {
				P = P->getNext();
			}
		}
		return nullptr;
	}


};

