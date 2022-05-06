#pragma once
#include "PriorirtyQueueArr.h"


enum  eTruckType
{
	VipTruck,
	SpecialTruck,
	NormalTruck
};

class Truck
{
private:

	int truckId;
	//1 for normal , 2 for special , 3 for vip
	int truckType;
	int truckCapacity;
	int maintenanceTime;
	int journeys_to_maintenance;     //Rename for same convention.		
	int breakdownNum;				//Number of journeys before the truck needs to be checked
	int truckSpeed;
	double deleieryInterval;
	int activeTime;  //Can be increased with each activity.
	int tDC = 0;  //Total Cargos Delievered, to be increased with each
	int totalJourneys = 0;  //Total journeys by the truck.
	int MoveTimeHR; //time at which truck starts to move this is for hours
	int MoveTimeDAY; //time at which truck starts to move this is for Days

	//lists for the cargo that is being loaded into the truck and being moved by the truck
	//PriorityQueueArr<Cargo*> LoadingCargo{truckCapacity};
	PriorityQueueArr<Cargo*> CargoinTruck{truckCapacity};

public:
	Truck(int ttype,int speed, int capacity, int J, int maintt);
	
	void setTruckCapacity(int c);
	void setMaintenanceTime(int t);
	void setBreakDownNum(int n);
	void setSpeed(int s);   //Perhaps we can add the 3 speeds in an outer lvl...
	//void setDelieveryInterval(double i);  //Think more..
	void setTruckType(int t);
	void setActiveTime(int at);
	void setJtm(int J);
	void setTDC(int new_tDC);
	void setTotalJourneys(int tj);

	int getType()const { return truckType; };
	int getTruckCapacity()const;
	int getMaintenanceTime()const;
	int getBreakDownNum()const;
	int getSpeed()const;
	double getDelieveryInterval()const;
	int getActiveTime()const;
	int getJtm()const;
	int getTDC()const;
	int getTotalJourneys()const;

	int getTrucID();

	int calcTruckUtilization(int TSim);

	//void MoveLoadingToMoving();
	void insertCargo(Cargo* Cargoin);
	int getMoveTime() const;
	void setMoveTime(int hr , int dy);
	int getListCount();
	Cargo* DeleiverCargo();
	//void DeleiverCargos(LinkedQueue<Cargo*> &TOdeliverTo);
};

