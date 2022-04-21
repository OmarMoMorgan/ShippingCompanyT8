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


//shall we make it so that it is not a moving list inside all the company or make it such that it is in 
//never mind i think we should go with haing them there as it has less compleity 
//log n vs n thus now we shouldn't overload the operators

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
		PriorityQueueArr<Cargo*> MoivingNormalCargo;
		LinkedQueue<Cargo*> DeliveredNormalCargo;
		
		//Special Cargo
		LinkedQueue<Cargo*> WaitingSpecialCargo;
		LinkedQueue<Cargo*> LoadingSpecialCargo;
		PriorityQueueArr<Cargo*> MoivingSpecialCargo;
		LinkedQueue<Cargo*> DeliveredSpecialCargo;

		//Vip Cargo
		PriorityQueueArr<Cargo*> WatitingVipCargo;
		LinkedQueue<Cargo*> LoadingVipCargo;
		PriorityQueueArr<Cargo*> MovingVipCargo;
		LinkedQueue<Cargo*> DeliveredVipCargo;
		
		//Events list it is a queue as each one comes after the other
		LinkedQueue<Event*> EventsList;

		//Trucks lists
		LinkedQueue<Truck*> AvailbleNormalTrucks;
		PriorityQueueArr<Truck*> LoadingNormalTrucks;
		PriorityQueueArr<Truck*> MovingNormalTrucks;
		
		LinkedQueue<Truck*> AvailbleSpecialTrucks;
		PriorityQueueArr<Truck*> LoadingSpecialTrucks;
		PriorityQueueArr<Truck*> MovingSpecialTrucks;

		PriorityQueueArr<Truck*> AvailbleVipTrucks;
		PriorityQueueArr<Truck*> LoadingVipTrucks;
		PriorityQueueArr<Truck*> MovingVipTrucks;
		
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


		//Time struct declrtionis here
		Time UniversalTime;

public:
	//function to load the file 
	void LoadFile();

	//SimTEst is a function for phase 1 to test that everything is working correctly
	void SimTest();

	//this function moves cargos from moving cargos to delievered cargos
	void MoveToDeleiverd();

	//this function moves cargos from waiting cargos into loading cargos
	void MoveToLoading(LinkedQueue<Cargo*> , PriorityQueueArr<Cargo*>);
	//overriding the function here so that it can accept more than type 
	void MoveToLoading(PriorityQueueArr<Cargo*>, PriorityQueueArr<Cargo*>);

	//This funciton counts the number of items in a given linked list / queue / priority queue
	//int CountListItems(LinkedQueue<>);
	
	//The function to produce output file
	void OutgoingFile();
};

