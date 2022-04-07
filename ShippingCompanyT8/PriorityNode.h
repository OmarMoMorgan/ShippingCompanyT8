#pragma once
#include "Node.h"

template <typename T>
class PriorirityNode
{
	private:
		int priority;
		T item; // A data item
		
		PriorirityNode<T> *Left;
		PriorirityNode<T> *Right;
		PriorirityNode<T>* Head;
	public:
		PriorirityNode() {
			Left = nullptr;
			Right = nullptr;
		}
		PriorirityNode(const T &n_item) {
			item = n_item;
			Left = nullptr;
			Right = nullptr;
		}

		PriorirityNode(const T& n_item,const int &n_prioirity) {
			item = n_item;
			priority = n_prioirity;
			Left = nullptr;
			Right = nullptr;
		}

		void SetLeft(PriorirityNode* n_left) {
			Left = n_left;
		}

		void SetRight(PriorirityNode* n_Right) {
			Rigth = n_Right;
		}

		PriorirityNode GetLeft() {
			return *Left;
		}


		void SetHead(PriorirityNode* n_Head) {
			Head = n_Head;
		}

		PriorirityNode GetHead() {
			return *Head;
		}


		PriorirityNode GetRight() {
			return *Right;
		}

		void SetPriority(int n_priority) {
			priority = n_priority;
		}

		int GetPrioirty() {
			return priority;
		}

		void SetItem(const T& n_item) {
			item = n_item;
		}

};
