#pragma once
#include "Cargo.h"

// setmovetime should be called in company.cpp when the truck carrying the ref cargo move
Cargo::Cargo()
{
	this->setCargoType(1);
	//this-> setPrepDay(ETD);
	//this->setPrepHour(ETH);
	this->setCargoID(0);
	this->setDelieveryDistance(0);
	this->setLoadTime(0);
	this->setCost(0);
	this ->setMovetime(0);
	loadTime = 0;
	unloadTime = 0;
}


//Constructor Arguments: Same order as in the input file:
//Cargo(Type , PrepTime DAY,PrepTime HOUR, ID, Distance, Load time, CargoCost)
Cargo:: Cargo(int icomingCargoType, int prepD, int prepH, int ID, double DIST, int LT, double cost)
{
	this->setCargoType(icomingCargoType);
	this-> setPrepDay(prepD);
	this->setPrepHour(prepH);
	this->setCargoID(ID);
	this->setDelieveryDistance(DIST);
	this->setLoadTime(LT);
	this->setCost(cost);
	this->setMovetime(0);
}

bool Cargo:: isWaiting() const
{
	if (prepDay > curDay)
		return true;
	else if (prepDay == curDay && prepHour >= prepHour)
		return true;
	return false;
}
/*
bool Cargo::waitedForMax()
{
	//Check it..
	if (this->isWaiting())
	{
		if ((prepDay - curDay) == maxW)   //Assume maxW is the max waiting (((days))).
 			return true;
		return false;
	}
	return false;


}
*/
/*
bool Cargo:: operator>(Cargo* C_cw) const
{
	int thisC = 0;
	int cwC = 0;
	if (this->waitedForMax() && (!C_cw->waitedForMax()))
		return 1;
	else if(C_cw->waitedForMax() && (!this->waitedForMax()))
	else
	{
		if (this->getPrepDay() > C_cw->getPrepDay())
	}


}
*/
//Setters
void Cargo::setPrepDay(int pd) { prepDay = pd;}
void Cargo::setPrepHour(int ph) { prepHour = ph; }
void Cargo::setLoadTime(int lt) { loadTime = lt; }
void Cargo::setUnloadTime(int ut) { unloadTime = ut; }
//void Cargo::setCargoType(eCargoType t) { this->cargoType = t; }
void Cargo::setCargoType(int t) { CarTyp = t; }
void Cargo::setDelieveryDistance(double dd) { deleiveryDistance = dd; }
void Cargo::setCost(double c) { Cost = c; }
void Cargo::setCargoID(int id) { cargoID = id; }
void Cargo::setMovetime(int x)
{
	movetime = x;
}

void Cargo::setWaitedTimeByMove(int mt)
{
	waitedTime = mt- ((24*prepDay) +prepHour );
}

int Cargo::getMoveTime() const /// we didnot use it in company so I added movetime parameter in CDT
{
	return movetime;
}

//Getters
int Cargo::getPrepDay() const { return prepDay; }
int Cargo::getPrepHour() const { return prepHour; }
int Cargo::getLoadTime() const { return loadTime; }
int  Cargo::getunloadTime() const { return unloadTime; }
int Cargo::getCDT(int truckspeed, int movetime) const //calculates time after cargo delvierly
{
	return movetime + getunloadTime() + getDelieveryDistance() / truckspeed;
}
//eCargoType Cargo::getCargoType() const { return cargoType; }
double Cargo::getDelieveryDistance() const { return deleiveryDistance; }
double Cargo::getCost() const { return Cost; }
int Cargo::getCargoID() const { return cargoID; }

int Cargo::getCurWaitTime(int curDay, int curHr) const {
	return ( (24* curDay) +curHour ) - ( (prepDay * 24) + prepHour );
}

int Cargo::getVIPPriority() const
{
	if (CarTyp != 3) //Make sure that is the number for VIP...
		return 0;
	else
	{
		int priority = 100* (  (1 / getDelieveryDistance())  + 2/((24*prepDay)+prepHour) + (5 * getCost()) );
		return priority;
	}

}

int Cargo::getWaitedTime() const { return waitedTime; }