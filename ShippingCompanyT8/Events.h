#pragma once
#include "LinkedQueue.h"
#include "PriorirtyQueueArr.h"
#include "LinkedList.h"
//#include "LinkedListCargo.h"

//this enum will be removed for now or not used as it 
//is harder to know the value of the int or pass it as a parameter
//it will be replaced with an int called EventType
// 1 will mean Ready event
// 2 will mean Cancel event
// 3 will mean promote event
// also cargo enum will cahnge for the same reason
//1 will mean normal cargo 
// 2 will mean special event
// 3 will mean vip event
//enum  event { R, X, P };

//this calss shouldn't inhertit from cargo
//ooooooo
class Events
{
private:
	//eCargoType cargo;
	int e; // Type of the event 
	int ID; // Id number of cargo
	int etD; int etH;// current day and hour
	//here is the new int look upwards for more explantion
	int EventType;
	////here is the new int look upwards for more explantion
	int TypeOfCargo;
public:
	//ooooooo
	Events(int nType, int Id, int etD,int etH,int k) :EventType(nType), ID(Id), etD(etD),  etH(etH), TypeOfCargo(k){}

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
	void setEventType(int f)
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

	int getID() {
		return ID;
	}

	int  getCType() {
		return TypeOfCargo;
	}
	
	virtual void Execute(LinkedList<Cargo*> &NormalList, LinkedQueue<Cargo*> &SpecialList
		, PriorityQueueArr<Cargo*> &VipList) = 0;

};

