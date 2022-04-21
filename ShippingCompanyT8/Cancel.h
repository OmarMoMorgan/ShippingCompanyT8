#include "Events.h"
#include "Cargo.h"
#include"LinkedListCargo.h"

#include"defns.h"
#pragma once

using namespace std;
template <typename T>
#pragma once
class Cancel :public Events
{
public:
	Cancel(int ID, int etD, int etH ) : Events(X, ID, etD, etH, normalCargo) {}
	bool execute(LinkedListCargo<Cargo*> Normal ,Cargo* c)
     {
		if (Normal.FindCargo(c->getCargoID()))
		{
			Normal.DeleteNode(c);
			return true;
		}
		else
			return false;

	}
};

