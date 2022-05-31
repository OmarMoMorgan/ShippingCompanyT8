#pragma once
#include "Cargo.h"
#include "Events.h"
#include "Cancel.h"
#include "Ready.h"
#include "Promote.h"
#include "Truck.h"
#include "UI.h"
#include "LinkedList.h"
#include "PriorirtyQueueArr.h"
#include "LinkedQueue.h"
//#include "LinkedListCargo.h"
#include <iostream>
#include <fstream>
#include <sstream>


//shall we make it so that it is not a moving list inside all the company or make it such that it is in 
//never mind i think we should go with haing them there as it has less compleity 
//log n vs n thus now we shouldn't overload the operators

// I added returnbacktrucks priorityqueue


class Company
{
	private:
		

		//current time and hour This funciton can only add less than 24 hours now
		struct Time
		{
			int CurrentHour = 0;
			int CurrentDay = 0;
			void IncTime(int n_hour_to_add) {
				if (CurrentHour < 24-n_hour_to_add) {
					CurrentHour = CurrentHour + n_hour_to_add;
					
				}
				else {
					CurrentDay++;
					CurrentHour = (CurrentHour + n_hour_to_add) - 24;
				}
			}
			void MoveOneunit() {
				if (CurrentHour < 23) {
					CurrentHour++;
				}
				else {
					CurrentDay++;
					CurrentHour = 0;
				}
			}
		};
		

		//method to split time 
		template <typename T>
		T convertString(std::string str) {
			T ret;
			std::stringstream ss(str);
			ss >> ret;
			return ret;
		}

		//Ecah list for cargo type they are seperated from each other and are divided
		//into 3 lists one for miving one for waiting one for deliveried
		//Normal cargo
		LinkedList<Cargo*> WaitingNormalCargo;
		//LinkedQueue<Cargo*> LoadingNormalCargo;
		//PriorityQueueArr<Cargo*> MoivingNormalCargo;
		LinkedQueue<Cargo*> DeliveredNormalCargo;
		
		//Special Cargo
		LinkedQueue<Cargo*> WaitingSpecialCargo;
		//LinkedQueue<Cargo*> LoadingSpecialCargo;
		//PriorityQueueArr<Cargo*> MoivingSpecialCargo;
		LinkedQueue<Cargo*> DeliveredSpecialCargo;

		//Vip Cargo
		PriorityQueueArr<Cargo*> WaitingVipCargo;
		//LinkedQueue<Cargo*> LoadingVipCargo;
		//PriorityQueueArr<Cargo*> MovingVipCargo;
		LinkedQueue<Cargo*> DeliveredVipCargo;

		//the list for all the deleivred cargos look for changing this to a stack
		//this is also the lsit for all the moving cargos
		//LinkedQueue<Cargo*> DeliveredCargo;
		//PriorityQueueArr<Cargo*> MovingCargos;
		
		//Events list it is a queue as each one comes after the other
		LinkedQueue<Events*> EventsList;

		//Trucks lists
		LinkedQueue<Truck*> AvailbleNormalTrucks;
		//PriorityQueueArr<Truck*> LoadingNormalTrucks;
		//PriorityQueueArr<Truck*> MovingNormalTrucks;
		
		LinkedQueue<Truck*> AvailbleSpecialTrucks;
		//PriorityQueueArr<Truck*> LoadingSpecialTrucks;
		//PriorityQueueArr<Truck*> MovingSpecialTrucks;

		PriorityQueueArr<Truck*> AvailbleVipTrucks;
		//PriorityQueueArr<Truck*> LoadingVipTrucks;
		//PriorityQueueArr<Truck*> MovingVipTrucks;
		
		PriorityQueueArr<Truck*> LoadingTrucks;
		PriorityQueueArr<Truck*> MovingTrucks;
		PriorityQueueArr<Truck*> FixingTrucks;
		PriorityQueueArr<Truck*> ReturnBackTruck;
		PriorityQueueArr<Cargo*> AllDelieverdCargos;
		//some variabeles that might be neeeded later
		int NumberNormalTrucks;
		int NumberSpecialTrucks;
		int NumberVipTrucks;
		int NumberEvents;

		//stuff needed for simulation
		int AutoP;
		int MaxW;


		
		//this is the pointer to interact wtih the ui class
		UIClass *UIController;

		//These are dummy variables and shall be removed later after Truck class is ready
		int DummyNSpeed;
		int DummySSpeed;
		int DummyVSpeed;

		int DummyNCap;
		int DummySCap;
		int DummyVCap;
		int isNightshift(Truck* T1)
		{
			if (T1->getSpeed() > 100)
			{
				return 1;
			}
			else 
				return 0;
		}

		int DummyNumJourneys;
		int DummyNumJourneysN;
		int DummyNumJourneysS;
		int DummyNumJourneysV;

		int maxid;
		void switchTrucksAvailable(Truck* t);

		//Time struct declrtionis here
		Time UniversalTime;

		//Variables for statistics:
		int NCargos = 0;
		int SCargos = 0;
		int VCargos = 0;
		int cargTotalWait = 0;
		int cargAvgWait = 0;
		int autoPromoted = 0;
		/*int NTrucks = 0;
		int STrucks = 0;
		int VTrucks = 0;*/
		int truckTotalActive = 0;
		int truckAvgActive = 0;
		int truckTotalUtilization = 0;
		int truckAvgUtilization = 0;


		void MoveTofixed();
		void ReturnToCompany();
		void movefromFixed();
		void MoveToTrucks();
		void MoveTrucktoMoving();
		void FinsihDeleivery();

		void LoadVip();
		void LoadNormal();
		void LoadSpecial();

		void MaxwNormalSpecial();
		void AutoUpgradeToVip();
		

		bool AllEnded();
		PriorityQueueArr<Cargo*> makeOneDelieverdQueue(LinkedQueue<Cargo*> normal, LinkedQueue<Cargo*> q1special, LinkedQueue<Cargo*> vip);

public:
	//function to load the file 
	void LoadFile();

	//SimTEst is a function for phase 1 to test that everything is working correctly
	void SimTest();

	
	
	//The function to produce output file
	void OutgoingFile();


	//these functions are used to make the required checks to actullay move items on certain conditions from
	//a list to another 

	//For checking the loading of cargos thus from waiting to loading 
	void LoadCheck(
		);

	//For checking the Moving of cargos thus from loading to moving
	void MoveCheck(LinkedQueue<Cargo*>& LoadingN , PriorityQueueArr<Cargo*> &MovingN,
		 LinkedQueue <Cargo*>& LoadingS , PriorityQueueArr<Cargo*> &MovingS, 
		 LinkedQueue <Cargo*>& LoadingV , PriorityQueueArr<Cargo*> &MovingV
	);

	//For checking the Moving of cargos thus from loading to moving
	void DeleviredCheck( PriorityQueueArr<Cargo*>& MovingN, 
		 PriorityQueueArr<Cargo*>& MovingS,
		 PriorityQueueArr<Cargo*>& MovingV , LinkedQueue<Cargo*> &Deleveried
	);


	void Simulator();


	////***functions needed for the UI***
	//int getNumberNormalTrucks();
	//int getNumberSpecialTrucks();
	//int getNumberVipTrucks();

	int getCurrentDay();
	int getCurrentHour();
	bool isOffHours();





	void checktoAvailable(int enteringDay, int enteringHr);
	void movingtoAvailable(int enteringDay, int enteringHr);

	void outputStatistics();
};

