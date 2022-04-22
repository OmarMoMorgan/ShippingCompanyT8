#pragma once
#include "Events.h"
//#include "Cargo.h"
#include"LinkedListCargo.h"
//#include"defns.h"
//template <typename T>

class Ready:public Events
{
private:
	int distance; // distance to be travelled (Km)
	double cost;
	int LoadingTime; // loading/unloading time(hours)
	
public:
	Ready(int ID,int cost, int etD, int etH, int lT, int dis, int cl): Events(1,ID, etD, etH,cl),distance(dis)
		,cost(cost),LoadingTime(lT)
	{
	}
	virtual void Execute(LinkedList<Cargo*> &Normal  , LinkedQueue<Cargo*> &SpecialList
		, PriorityQueueArr<Cargo*> &VipList)
	{
		Cargo* c = new Cargo(getCType(),getID(), distance,LoadingTime,cost);
		//Cargo* Cargopointer = c;
		if (getCType() == 1) { 
			Normal.insertback(c); 
		}
		else if (getCType() == 2) {
			SpecialList.enqueue(c);
		}
		else if (getCType() == 3) {
			VipList.insert(c);
		}
	}


	int	getLoadTime()
	{
		return LoadingTime;
	}
	int	getDistance()
	{
		return distance;
	}
	int	getCost()
	{
		return cost;
	}

	void setLoadTime(int v)
	{
		LoadingTime= v;
	}
	void setDistance(int v)
	{
		distance = v;
	}
	void setCost(int cost)
	{
		cost = cost;
	}
};

