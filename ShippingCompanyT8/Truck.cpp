#include "Truck.h"
Truck::Truck(int ttype, int speed, int capacity, int J, int maintt)
{
	counter++;
	this->setTruckType(ttype);
	this->setSpeed(speed);
	this->setTruckCapacity(capacity);
	this->setJtm(J);
	this->setMaintenanceTime(maintt);
	currentJourney = 0;
	this->setTruckId(counter);
	loadtime = 0;
	activeTime = 0;
	delivery_Interval = 0;
	returntime = 0;
}

void Truck:: setTruckCapacity(int c) { truckCapacity = c; }
void Truck:: setMaintenanceTime(int t) { maintenanceTime = t; }
void Truck:: setBreakDownNum(int n) { breakdownNum = n; }
void Truck::setSpeed(int s) { truckSpeed = s; }
void Truck::setfinishTime(int x) 
{
	//int finishtime = 0;
	//Cargo* Pcargo;
	//for (int i = 0; i < CargoinTruck.getCount(); i++)
	//{
	//	CargoinTruck.Pop(Pcargo);
	//	int cdt = Pcargo->getCDT(getSpeed(), getMoveTime());
	//	if (cdt > finishtime)
	//		finishtime = cdt;
	//}
	finishTime = x;


}
void Truck::setDelieveryInterval(int x) // could be removed
{
	
	delivery_Interval = x;
	
}

int Truck::getfinishTime()
{
	return finishTime;
}



void Truck::incrementJourney(){currentJourney++;	}
void Truck::setTruckType(int t) { truckType = t; }
void Truck::setTruckId(int x){truckId = x;}

void Truck::setActiveTime() { //could be removed
	//Cargo* Pcargo;
	//int total_loadAndunload_cargos_Time = 0;
	//int farthest_distance_cargo = 10000; 
	//for (int i = 0; i < CargoinTruck.getCount(); i++)
	//{
	//	CargoinTruck.Pop(Pcargo);
	//	total_loadAndunload_cargos_Time = total_loadAndunload_cargos_Time + Pcargo->getLoadTime()+Pcargo->getunloadTime();
	//	if (farthest_distance_cargo < Pcargo->getDelieveryDistance())
	//		farthest_distance_cargo = Pcargo->getDelieveryDistance();

	//}
	//activeTime = activeTime+ total_loadAndunload_cargos_Time + farthest_distance_cargo/getSpeed(); 
}
void Truck::setJtm(int J) { journeys_to_maintenance = J; }
void Truck::setTDC(int new_tDC) { tDC = new_tDC; }
void Truck::setTotalJourneys(int tj) { currentJourney = tj; }

//eTruckType Truck::getType()const { return truckType; }
int Truck::getTruckCapacity()const { return truckCapacity; }
int Truck::getMaintenanceTime()const { return maintenanceTime; }
int Truck::getBreakDownNum()const { return breakdownNum; }
int Truck::getSpeed()const { return truckSpeed; }
int Truck::getDelieveryInterval() {
	delivery_Interval = getfinishTime() - getMoveTime();
	return delivery_Interval;
}
int Truck::getActiveTime() { 
	activeTime = activeTime+ getLoadTime()-getfinishTime()+getReturnTime();
	return activeTime; }
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

void Truck::setReturnTime(int x)
{
	returntime=x;
}

int Truck::getReturnTime()
{
	return returntime;
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
	return MoveTimeDAY*24 + MoveTimeHR;
}

void Truck::setMoveTime(int hr , int dy) {
	MoveTimeDAY = dy;
	MoveTimeHR = hr;
}

int Truck::getListCount() {
	return CargoinTruck.getCount();
}

Cargo* Truck::DeleiverCargo() {
	Cargo* pcargo= peekCargo();
	CargoinTruck.Pop(pcargo);
	return pcargo;
}

Cargo* Truck::peekCargo()
{
	Cargo* Pcargo;
	 CargoinTruck.peek(Pcargo);
	 return Pcargo;
}


void Truck::setLoadTime(int x)
{
	loadtime = x;
}

int Truck::getLoadTime() const
{
	return loadtime;
}

void Truck::setCargosWaitedTime(int moveTime)
{
	int count = CargoinTruck.getCount();

	Cargo** arrTemp = new Cargo* [count];
	while (count != 0)
	{
		Cargo* C;
		this->CargoinTruck.Pop(C);
		C->setWaitedTimeByMove(moveTime);
		arrTemp[count-1] = C;
		count--;
	}

	for (int i = count; i > 0; i--)
	{
		CargoinTruck.insert(arrTemp[i]);
	}
	delete[] arrTemp;
	arrTemp = nullptr;
}

void Truck::printcargosdebug() {
	CargoinTruck.printarrCargo();
}