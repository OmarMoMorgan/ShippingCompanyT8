#pragma once
#include "Cargo.h"
#include "Event.h"
#include "Truck.h"
#include "UI.h"
#include "LinkedList.h"
#include "PriorirtyQueueArr.h"
#include "LinkedQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
		};
		

		//Ecah list for cargo type they are seperated from each other and are divided
		//into 3 lists one for miving one for waiting one for deliveried
		//Normal cargo
		LinkedList<Cargo*> WaitingNormalCargo;
		LinkedQueue<Cargo*> LoadingNormalCargo;
		LinkedQueue<Cargo*> MoivingNormalCargo;
		LinkedQueue<Cargo*> DeliveredNormalCargo;
		
		//Special Cargo
		LinkedQueue<Cargo*> WaitingSpecialCargo;
		LinkedQueue<Cargo*> LoadingSpecialCargo;
		LinkedQueue<Cargo*> MoivingSpecialCargo;
		LinkedQueue<Cargo*> DeliveredSpecialCargo;

		//Vip Cargo
		PriorityQueueArr<Cargo*> WatitingVipCargo;
		LinkedQueue<Cargo*> LoadingVipCargo;
		LinkedQueue<Cargo*> MovingVipCargo;
		LinkedQueue<Cargo*> DeliveredVipCargo;
		
		//Events list it is a queue as each one comes after the other
		LinkedQueue<Event*> EventsList;

		//Trucks lists
		LinkedQueue<Truck*> AvailbleNormalTrucks;
		LinkedList<Truck*> MovingNormalTrucks;
		
		LinkedQueue<Truck*> AvailbleSpecialTrucks;
		LinkedList<Truck*> MovingSpecialTrucks;

		PriorityQueueArr<Truck*> AvailbleVipTrucks;
		LinkedList<Truck*> MovingVipTrucks;
		
		LinkedQueue<Truck*> FixingTrucks;


		//some variabeles that might be neeeded later
		int NumberNormalTrucks;
		int NumberSpecialTrucks;
		int NumberVipTrucks;
		int NumberEvents;

		//stuff needed for simulation
		int AutoP;
		int MaxW;



		//this is the pointer to interact wtih the ui class
		UI* UIController;

		//These are dummy variables and shall be removed later after Truck class is ready
		int DummyNSpeed;
		int DummySSpeed;
		int DummyVSpeed;

		int DummyNCap;
		int DummySCap;
		int DummyVCap;

		int DummyNumJourneys;


public:
	//function to load the file 
	void LoadFile();

	//SimTEst is a function for phase 1 to test that everything is working correctly
	void SimTest();

	//The function to produce output file
	void OutgoingFile();
};

