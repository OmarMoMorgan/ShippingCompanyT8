#pragma once
#include "Events.h"
#include "Cargo.h"
#include"LinkedListCargo.h"
#include"defns.h"
template <typename T>

class Ready:public Events
{
private:
	int distance; // distance to be travelled (Km)
	double cost;
	int LoadingTime; // loading/unloading time(hours)
public:
	Ready(int ID,int cost, int etD, int etH, int lT, int dis, eCargoType cl): Events(R,ID, etD, etH,cl),distance(dis)
		,cost(cost),LoadingTime(lT)
	{
	}
	void execute(LinkedListCargo<Cargo*> Normal)
	{
		Cargo c(cargo,ID, distance,LoadingTime,cost);
		Cargo* Cargopointer = c*;
			Normal.InsertBeg(Cargopointer);
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

