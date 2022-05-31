#pragma once
#include "PriorirtyQueueArr.h"

// Very important in order for getfinishtime to wotk, we need to set in company. the move time for each cargo.
// active time is moving+loadingtime, should be done after truck finishes loading
// delivery interval time is moving +returning time is calculated after truck finishes loading
// finish time is the time when cargo gets back to company so is movetime of truck+ DI,  is calculated after truck finishes loading 

// i added peekCargo to get cargo in top of queue

enum  eTruckType
{
	VipTruck,
	SpecialTruck,
	NormalTruck
};


class Truck
{
private:
	int loadtime; //to know when it starts loading
	static  int counter; //to give an Id for trucks;
	int returntime;
	//int farthest_distance_Cargo;
	int currentJourney; // this is used to keep track of undergoing journeys to calculate return time if there is maintance or not
	int truckId;
	//1 for normal , 2 for special , 3 for vip
	int truckType;
	int truckCapacity;
	int maintenanceTime;
	int journeys_to_maintenance;     // This is the max journey number read from input file
	//int maintenanceTime;				//ASSUME its all hrs
	//int journeys_to_maintenance;     //Rename for same convention.	// This is the max journey number	
	int breakdownNum;				//Number of journeys before the truck needs to be checked
	int truckSpeed;
	int delivery_Interval;
	int activeTime;  //Can be increased with each activity.
	int tDC = 0;  //Total Cargos Delievered, to be increased with each
	int MoveTimeHR; //time at which truck starts to move this is for hours
	int MoveTimeDAY; //time at which truck starts to move this is for Days
	
	//lists for the cargo that is being loaded into the truck and being moved by the truck
	//PriorityQueueArr<Cargo*> LoadingCargo{truckCapacity};
	PriorityQueueArr<Cargo*> CargoinTruck;
	int finishTime;
public:

		Truck(int ttype,int speed, int capacity, int J, int maintt);
	
	void setTruckCapacity(int c);
	void setMaintenanceTime(int t);
	void setBreakDownNum(int n);
	void setSpeed(int s);   //Perhaps we can add the 3 speeds in an outer lvl...
	  //Think more..
	void setTruckType(int t);

	void setJtm(int J);
	void setTDC(int new_tDC);
	void setTotalJourneys(int tj); // 

	void setTruckId(int x);
	void setActiveTime();   /// I changed it to increase with each journey and not take it an int as a parameter
	void incrementJourney(); /// This is a new function that should be called in the main to increase journey number
	void setfinishTime(int);
	void  setDelieveryInterval(int);
	
	int getfinishTime();
	int getType()const { return truckType; };
	int getTruckCapacity()const;
	int getMaintenanceTime()const;
	int getBreakDownNum()const;
	int getSpeed()const;
	int getDelieveryInterval();
	int getActiveTime();
	int getJtm()const;
	int getTDC()const;
	int getTotalJourneys()const; //total journeys done by truck since the beginning of the sim
	int getTrucID();
	int calcTruckUtilization(int TSim);
	void	setReturnTime(int x);
	int getReturnTime();
	//void MoveLoadingToMoving();
	void insertCargo(Cargo* Cargoin);
	int getMoveTime() const;
	void setMoveTime(int hr , int dy);
	int getListCount();
	Cargo* DeleiverCargo();
	//void DeleiverCargos(LinkedQueue<Cargo*> &TOdeliverTo);
	Cargo* peekCargo();

	void setLoadTime(int);
	int getLoadTime() const;

	void setCargosWaitedTime(int currentTime);

	void printcargosdebug();
	int getTruckPriority();
};

