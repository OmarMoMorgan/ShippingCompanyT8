#include "Truck.h"
Truck::Truck(int ttype, int speed, int capacity, int J, int maintt)
{
	this->setTruckType(ttype);
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
void Truck::setTruckType(int t) { truckType = t; }
void Truck::setActiveTime(int at) { activeTime = at; }
void Truck::setJtm(int J) { journeys_to_maintenance = J; }
void Truck::setTDC(int new_tDC) { tDC = new_tDC; }
void Truck::setTotalJourneys(int tj) { totalJourneys = tj; }

//eTruckType Truck::getType()const { return truckType; }
int Truck::getTruckCapacity()const { return truckCapacity; }
int Truck::getMaintenanceTime()const { return maintenanceTime; }
int Truck::getBreakDownNum()const { return breakdownNum; }
int Truck::getSpeed()const { return truckSpeed; }
double Truck::getDelieveryInterval()const { return deleieryInterval; }
int Truck::getActiveTime()const { return activeTime; }
int Truck::getJtm() const { return journeys_to_maintenance; }
int Truck::getTDC() const{ return tDC; }
int Truck::getTotalJourneys() const{ return totalJourneys; }
int  Truck::getTrucID() { return truckId; }


int Truck::calcTruckUtilization(int TSim)
{
	int utilization = 0;
	if (totalJourneys == 0) utilization = 0;
	else
	{
		utilization = tDC / ((truckCapacity * totalJourneys) * (activeTime / TSim));

		return utilization;
	}
}

void Truck::MoveLoadingToMoving() {
	for (int i = 0; i < truckCapacity; i++) {
		MovingCargo.insert(LoadingCargo.Pop());
	}
}