#pragma once
#include <string>
#include "LinkedList.h"
#include "LinkedQueue.h"
//#include "LinkedListCargo.h"
#include "PriorirtyQueueArr.h"
#include <iostream>
using namespace std;


class UIClass
{
private:

	// AppMode determines whether (Interactive / Step by step / Silent)
	int AppMode = 0;
	std::string FileName;

public:
	int getTotalLoadingCargo(LinkedQueue<Cargo*>& lq1, LinkedQueue<Cargo*>& lq2, LinkedQueue<Cargo*>& lq3);
	int getTotalWaitingCargo(PriorityQueueArr<Cargo*>& pq, LinkedList<Cargo*>& ll, LinkedQueue<Cargo*>& lq);
	int getTotalMovingCargo(PriorityQueueArr<Cargo*>& pq);
	int getTotalDelieveredCargo(LinkedQueue<Cargo*>& lq1, LinkedQueue<Cargo*>& lq2, LinkedQueue<Cargo*>& lq3);
	int getTotalEmptytrucks(LinkedQueue<Truck*>& lq1, LinkedQueue<Truck*>& lq2, PriorityQueueArr<Truck*>& pq);

	//UIClass() {};


	void SetCurrentMode();
	int getCurrentMode();


	void setFileName();
	std::string getFileName();



	// StartInteractiveMode();
	void StartStepByStepMode();
	void StartSilentMode();

	//try making the StartInteractiveMode function take many arguments, when called from the company

	void StartInteractiveMode(int D, int H, LinkedQueue<Cargo*>& WaitingSpecialCargo, LinkedList<Cargo*>& WaitingNormalCargo,
		PriorityQueueArr<Cargo*>& WaitingVIPCargo, LinkedQueue<Truck*>& AvailbleNormalTrucks,
		LinkedQueue<Truck*>& AvailbleSpecialTrucks, PriorityQueueArr<Truck*>& AvailbleVipTrucks,
		LinkedQueue<Cargo*>& DeliveredSpecialCargo, LinkedQueue<Cargo*>& DeliveredVipCargo,
		LinkedQueue<Cargo*>& DeliveredNormalCargo, PriorityQueueArr<Truck*>& LoadingTrucks, PriorityQueueArr<Truck*>& movingtruck, PriorityQueueArr<Truck*>& returningback, PriorityQueueArr<Truck*>& fixingtruck);
};

