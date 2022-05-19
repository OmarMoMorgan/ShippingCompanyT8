#include "Truck.h"
Truck::Truck(int ttype, int speed, int capacity, int J, int maintt)
{
	this->setTruckType(ttype);
	this->setSpeed(speed);
	this->setTruckCapacity(capacity);
	this->setJtm(J);
	this->setMaintenanceTime(maintt);
	currentJourney = 0;
}

void Truck:: setTruckCapacity(int c) { truckCapacity = c; }
void Truck:: setMaintenanceTime(int t) { maintenanceTime = t; }
void Truck:: setBreakDownNum(int n) { breakdownNum = n; }
void Truck::setSpeed(int s) { truckSpeed = s; }
void Truck::setfinishTime()
{
	int finishtime = 0;
	Cargo* Pcargo;
	for (int i = 0; i < CargoinTruck.getCount(); i++)
	{
		CargoinTruck.Pop(Pcargo);

		if (Pcargo->getCDT(getSpeed()) > finishtime)
			finishtime = Pcargo->getCDT(getSpeed());
	}
	finishTime = finishtime;


}
void Truck::setDelieveryInterval()
{
	Cargo* Pcargo;
	
	int total_unload_cargos_Time = 0;
    int	farthest_distance_cargo=0;
	for (int i = 0; i < CargoinTruck.getCount(); i++)
	{
		CargoinTruck.Pop(Pcargo);
		total_unload_cargos_Time = total_unload_cargos_Time +Pcargo->getunloadTime();
		if (farthest_distance_cargo < Pcargo->getDelieveryDistance())
			farthest_distance_cargo = Pcargo->getDelieveryDistance() ;
	}
	if (currentJourney%journeys_to_maintenance==0)
		delivery_Interval = farthest_distance_cargo*2 / getSpeed() + getMaintenanceTime() + total_unload_cargos_Time;
	else
		delivery_Interval = farthest_distance_cargo*2 / getSpeed()   + total_unload_cargos_Time;
	
}



void Truck::incrementJourney()
{
		currentJourney++;
	
}

void Truck::setTruckType(int t) { truckType = t; }
void Truck::setActiveTime() { 
	Cargo* Pcargo;
	int total_loadAndunload_cargos_Time = 0;
	int farthest_distance_cargo = 0; 
	for (int i = 0; i < CargoinTruck.getCount(); i++)
	{
		CargoinTruck.Pop(Pcargo);
		total_loadAndunload_cargos_Time = total_loadAndunload_cargos_Time + Pcargo->getLoadTime()+Pcargo->getunloadTime();
		if (farthest_distance_cargo < Pcargo->getDelieveryDistance())
			farthest_distance_cargo = Pcargo->getDelieveryDistance();

	}
	activeTime = activeTime+ total_loadAndunload_cargos_Time + farthest_distance_cargo/getSpeed(); 
}
void Truck::setJtm(int J) { journeys_to_maintenance = J; }
void Truck::setTDC(int new_tDC) { tDC = new_tDC; }
void Truck::setTotalJourneys(int tj) { currentJourney = tj; }

//eTruckType Truck::getType()const { return truckType; }
int Truck::getTruckCapacity()const { return truckCapacity; }
int Truck::getMaintenanceTime()const { return maintenanceTime; }
int Truck::getBreakDownNum()const { return breakdownNum; }
int Truck::getSpeed()const { return truckSpeed; }
int Truck::getDelieveryInterval()const { return delivery_Interval; }
int Truck::getActiveTime()const { return activeTime; }
int Truck::getJtm() const { return journeys_to_maintenance; }
int Truck::getTDC() const{ return tDC; }
int Truck::getTotalJourneys() const{ return currentJourney; }
int  Truck::getTrucID() { return truckId; }


int Truck::calcTruckUtilization(int TSim)
{
	int utilization = 0;
	if (currentJourney == 0) utilization = 0;
	else
	{
		utilization = tDC / ((truckCapacity * currentJourney) * (activeTime / TSim));

		return utilization;
	}
}

//void Truck::MoveLoadingToMoving() {
//	for (int i = 0; i < truckCapacity; i++) {
//		MovingCargo.insert(LoadingCargo.Pop());
//	}
//}

void Truck::insertCargo(Cargo* cargoin) {
	//will be replaced with cargo funciton that get actual time 
	CargoinTruck.insert(cargoin, 1);
}

int Truck::getMoveTime() const {
	return MoveTimeDAY + MoveTimeHR;
}

void Truck::setMoveTime(int hr , int dy) {
	MoveTimeDAY = dy;
	MoveTimeHR = hr;
}

int Truck::getListCount() {
	return CargoinTruck.getCount();
}

Cargo* Truck::DeleiverCargo() {
	return CargoinTruck.Pop();
}