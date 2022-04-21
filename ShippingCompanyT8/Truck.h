#pragma once
enum  eTruckType
{
	VipTruck,
	SpecialTruck,
	NormalTruck
};

class Truck
{
private:

	eTruckType truckType;
	int truckCapacity;
	int maintenanceTime;
	int journeys_to_maintenance;     //Rename for same convention.		
	int breakdownNum;				//Number of journeys before the truck needs to be checked
	int truckSpeed;
	double deleieryInterval;
	int activeTime;  //Can be increased with each activity.
	int tDC = 0;  //Total Cargos Delievered, to be increased with each
	int totalJourneys = 0;  //Total journeys by the truck.

public:
	Truck(eTruckType t,int speed, int capacity, int J, int maintt);
	
	void setTruckCapacity(int c);
	void setMaintenanceTime(int t);
	void setBreakDownNum(int n);
	void setSpeed(int s);   //Perhaps we can add the 3 speeds in an outer lvl...
	//void setDelieveryInterval(double i);  //Think more..
	void setTruckType(eTruckType t);
	void setActiveTime(int at);
	void setJtm(int J);
	void setTDC(int new_tDC);
	void setTotalJourneys(int tj);

	eTruckType getType()const { return truckType; };
	int getTruckCapacity()const;
	int getMaintenanceTime()const;
	int getBreakDownNum()const;
	int getSpeed()const;
	int getDelieveryInterval()const;
	int getActiveTime()const;
	int getJtm()const;
	int getTDC()const;
	int getTotalJourneys()const;
};

