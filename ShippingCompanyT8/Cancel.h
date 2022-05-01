#pragma once

#include "Events.h"
#include "Cargo.h"
//#include"LinkedListCargo.h"

//#include"defns.h"


using namespace std;
//template <typename T>

class Cancel :public Events
{
public:
	Cancel(int ID, int etD, int etH ) : Events(2, ID, etD, etH, 1) {}
	void Execute(LinkedList<Cargo*> &Normal  , LinkedQueue<Cargo*> &SpecialList
		, PriorityQueueArr<Cargo*> &VipList)
     {
		//Cargo* c = nullptr;
		//c = Normal.FindCargo(getID());
		if (Normal.FindCargo(getID()))
		{
			Normal.NewDeleteNode(Normal.FindCargo(getID()));
			//return true;
			//cout << "list cancled";
		}
		//else {
			//cout << "came but no sucess";
		//}

		//else
			//return false;

	}
};
//i chaneged reyturn type for this function

