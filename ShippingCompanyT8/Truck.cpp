#include "Truck.h"
Truck::Truck(eTruckType t, int speed, int capacity, int J, int maintt)
{
	this->setTruckType(t);
	this->setSpeed(speed);
	this->setTruckCapacity(capacity);
	this->setJtm(J);
	this->setMaintenanceTime(maintt);
}

void Truck:: setTruckCapacity(int c) { truckCapacity = c; }
void Truck:: setMaintenanceTime(int t) { maintenanceTime = t; }
void Truck:: setBreakDownNum(int n) { breakdownNum = n; }
void Truck::setSpeed(int s) { truckSpeed = s; }
//void setDelieveryInterval(double i);  //Think more..
void Truck::setTruckType(eTruckType t) { truckType = t; }
void Truck::setActiveTime(int at) { activeTime = at; }
void Truck::setJtm(int J) { journeys_to_maintenance = J; }
void Truck::setTDC(int new_tDC) { tDC = new_tDC; }
void Truck::setTotalJourneys(int tj) { totalJourneys = tj; }

//eTruckType Truck::getType()const { return truckType; }
int Truck::getTruckCapacity()const { return truckCapacity; }
int Truck::getMaintenanceTime()const { return maintenanceTime; }
int Truck::getBreakDownNum()const { return breakdownNum; }
int Truck::getSpeed()const { return truckSpeed; }
int Truck::getDelieveryInterval()const { return deleieryInterval; }
int Truck::getActiveTime()const { return activeTime; }
int Truck::getJtm() const { return journeys_to_maintenance; }
int Truck::getTDC() const{ return tDC; }
int Truck::getTotalJourneys() const{ return totalJourneys; }
