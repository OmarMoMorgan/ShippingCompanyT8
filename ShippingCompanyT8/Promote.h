#pragma once
#include "Events.h"
#include "Cargo.h"
#include"LinkedListCargo.h"
#include"defns.h"
template <typename T>

class Promote :public Events
{
private:
	double ExtraMoney;
public:
	Promote(int ID, int etD, int etH, double ExtraMoney) : Events(P,ID, etD, etH, normalCargo) ,ExtraMoney(ExtraMoney) {}
	double	getExtraMoney() { return ExtraMoney; }
	void	setExtramoney(int y) { ExtraMoney = y; }
    void execute(LinkedListCargo<Cargo*> Normal, LinkedListCargo<Cargo*> VIP, Cargo* c)
		{
			if (Normal.FindCargo(c->getCargoID()))
			{
				c->setCost(c->getCost() + ExtraMoney);
				VIP.InsertSorted(c) ;
				Normal.DeleteNode(c);
			}
		}
};
