#pragma once
#include "Events.h"
#include "Cargo.h"
#include"LinkedListCargo.h"
#include"defns.h"
//template <typename T>

class Promote :public Events
{
private:
	double ExtraMoney;
public:
	Promote(int ID, int etD, int etH, double ExtraMoney) : Events(3,ID, etD, etH, 1) ,ExtraMoney(ExtraMoney) {}
	double	getExtraMoney() { return ExtraMoney; }
	void	setExtramoney(int y) { ExtraMoney = y; }
	//I edited here also , will leave ooooooo in parts i edit
	// i am editing this to make it into a virtual function as it is required
	//ooooooo
    void Execute(LinkedList<Cargo*> &Normal,LinkedQueue<Cargo*> &SpecialList, PriorityQueueArr<Cargo*> &VipList) override
		{
		Cargo* c = Normal.FindCargo(getID());
			if (c)
			{
				c->setCost(c->getCost() + ExtraMoney);
				VipList.insert(c);
				Normal.DeleteNode(c);
			}
		}
};
