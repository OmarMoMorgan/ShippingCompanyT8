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
		UIClass *UIController;

		//These are dummy variables and shall be removed later after Truck class is ready
		int DummyNSpeed;
		int DummySSpeed;
		int DummyVSpeed;

		int DummyNCap;
		int DummySCap;
		int DummyVCap;

		int DummyNumJourneys;

		int maxid;

		//Time struct declrtionis here
		Time UniversalTime;

		void MoveTofixed();
		void MoveToTrucks();
		void MoveTrucktoMoving();
		void FinsihDeleivery();

		


public:
	//function to load the file 
	void LoadFile();

	//SimTEst is a function for phase 1 to test that everything is working correctly
	void SimTest();

	//this function moves cargos from waiting cargos into loading cargos
	//void MoveToOtherList(LinkedQueue<Cargo*> , PriorityQueueArr<Cargo*>);
	//overriding the function here so that it can accept more than type 
	//void MoveToOtherList(PriorityQueueArr<Cargo*>, PriorityQueueArr<Cargo*>);
	//another override

	//this function moves cargos from Loading cargos into Moving cargos
	//void MoveToOtherList(LinkedList<Cargo*>, LinkedQueue<Cargo*>);
	//overriding the function here so that it can accept more than type 
	//void MoveToOtherList(PriorityQueueArr<Cargo*>, LinkedQueue<Cargo*>);

	//void MoveToOtherList(LinkedQueue<Cargo*>, LinkedQueue<Cargo*>);


	//this function moves cargos from moving cargos to delievered cargos
	//void MoveToDeleiverd();

	//This funciton counts the number of items in a given linked list / queue / priority queue
	//int CountListItems(LinkedQueue<>);
	
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


	//this functions here are for moving items from a list to another the function shall be overriden
	//so that you don't need to know the type of list you are inserting each time 
	//also a template wil be used here so it can work for trucks and cargos
	//lol some stuff don't also work on trucks as you need to only move it 
	//thus this approach was not the best and the template is useless
//	template <typename T>
//	void MoveToOtherList(LinkedQueue<T> CameFromHere, PriorityQueueArr<T> GoingThere) {
//		T Thecargo;
//		CameFromHere.peek(Thecargo);
//		if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//			CameFromHere.dequeue(Thecargo);
//			GoingThere.insert(Thecargo, 1); //this number here shall be replaced with the function that gets loadtimes
//		}
//	}
//
//	template <typename T>
//	void MoveToOtherList(PriorityQueueArr<T> CameFromHere, PriorityQueueArr<T> GoingThere) {
//		T Thecargo;
//		CameFromHere.peek(Thecargo);
//		if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//			CameFromHere.Pop(Thecargo);
//			GoingThere.insert(Thecargo, 1); //this number here shall be replaced with the function that gets loadtimes
//		}
//	}
//
//	//this function is for moving from linked list to a queue it needs to be revised
//	template <typename T>
//	void MoveToOtherList(LinkedList<T> CameFromHere, LinkedQueue<T> GoingThere) {
//		T Thecargo;
//		Thecargo = CameFromHere.getHead();
//		if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//			Thecargo = CameFromHere.removeFirstelement();
//			GoingThere.enqueue(Thecargo);
//		}
//	}
//
//
//	template <typename T>
//	void MoveToOtherList(PriorityQueueArr<T> CameFromHere, LinkedQueue<T> GoingThere) {
//		T Thecargo;
//		CameFromHere.peek(Thecargo);
//		if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//			CameFromHere.Pop(Thecargo);
//			GoingThere.enque(Thecargo); 
//		}
//	}
//
//
//	template <typename T>
//	void MoveToOtherList(LinkedQueue<T> CameFromHere, LinkedQueue<T> GoingThere) {
//		T Thecargo;
//		CameFromHere.peek(Thecargo);
//		if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//			CameFromHere.dequeue(Thecargo);
//			GoingThere.enqueue(Thecargo);
//		}
//	}


	////***functions needed for the UI***
	//int getNumberNormalTrucks();
	//int getNumberSpecialTrucks();
	//int getNumberVipTrucks();

	int getCurrentDay();
	int getCurrentHour();

	bool isOffHours();
};

