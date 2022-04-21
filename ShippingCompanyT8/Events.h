#pragma once
#include"Cargo.h"

enum  event { R, X, P };

class Events: Cargo
{
private:
	eCargoType cargo;
	event e; // Type of the event 
	int ID; // Id number of cargo
	int etD; int etH;// current day and hour
public:
	Events(event e1, int Id, int etD,int etH,eCargoType k) :e(e1), ID(Id), etD(etD),  etH(etH), cargo(k){}

	int getETD()
	{
		return etD;
	}
	int getETH()
	{
		return etH;
	}
	int getEventType()
	{
		return e;
	}
	void setEventType(event f)
	{
		e = f;
	}

	void setETD(int f)
	{
		etD = f;
	}
	void setETH(int f)
	{
		etH = f;
	}

};

