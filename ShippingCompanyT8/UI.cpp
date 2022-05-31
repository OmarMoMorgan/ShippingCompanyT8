#include "UI.h"
#include <iostream>
//#include "Company.h"
//#include "Truck.h"



int UIClass::getTotalEmptytrucks(LinkedQueue<Truck*> &lq1, LinkedQueue<Truck*> &lq2, PriorityQueueArr<Truck*> &pq)
{
	return lq1.getCount() + lq2.getCount() + pq.getCount();
}

int UIClass::getTotalLoadingCargo(LinkedQueue<Cargo*> &lq1, LinkedQueue<Cargo*> &lq2, LinkedQueue<Cargo*> &lq3)
{
	return lq1.getCount() + lq2.getCount() + lq3.getCount();
}

int UIClass::getTotalWaitingCargo(PriorityQueueArr<Cargo*> &pq, LinkedList<Cargo*> &ll, LinkedQueue<Cargo*> &lq)
{
	return pq.getCount() + ll.getCount() + lq.getCount();
}

int UIClass::getTotalMovingCargo(PriorityQueueArr<Cargo*> &pq)
{
	return  pq.getCount();
}

int UIClass::getTotalDelieveredCargo(LinkedQueue<Cargo*> &lq1, LinkedQueue<Cargo*> &lq2, LinkedQueue<Cargo*> &lq3)
{
	return lq1.getCount() + lq2.getCount() + lq3.getCount();
}



void UIClass::SetCurrentMode()
{
	std::cout << "Enter 1 for Interactive Mode \nor 2 for Step By Step Mode \nor 3 for Silent Mode \n";
	int x;
	std::cin >> x;
	switch (x) {
	case 1:
		//StartInteractiveMode();
		this->AppMode = x;
		break;

	case 2:
		//StartStepByStepMode();
		this->AppMode = x;
		break;

	case 3:
		//StartSilentMode();
		this->AppMode = x;
		break;


	default:
		std::cout << "Invalide choice \n";
	}


}


void UIClass::setFileName()
{
	std::string y;
	cin >> y;
	this->FileName = y;
}

std::string UIClass::getFileName()
{
	return this->FileName;
}

int UIClass::getCurrentMode()
{
	return this->AppMode;
}
void UIClass::StartInteractiveMode(int D, int H, LinkedQueue<Cargo*> &WaitingSpecialCargo, LinkedList<Cargo*> &WaitingNormalCargo,
	PriorityQueueArr<Cargo*> &WaitingVIPCargo, LinkedQueue<Truck*> &AvailbleNormalTrucks,
	LinkedQueue<Truck*> &AvailbleSpecialTrucks, PriorityQueueArr<Truck*> &AvailbleVipTrucks,
	LinkedQueue<Cargo*> &DeliveredSpecialCargo, LinkedQueue<Cargo*> &DeliveredVipCargo, 
	LinkedQueue<Cargo*> &DeliveredNormalCargo, PriorityQueueArr<Truck*> &LoadingTrucks, PriorityQueueArr<Truck*>& movingtruck, PriorityQueueArr<Truck*>& returningback, PriorityQueueArr<Truck*>& fixingtruck)

{
	{
		cout << "Current Time " << "(Day " << D << " : " << H << " Hour) \n";
		cout << std::string(20, '_');

		std::cout << getTotalWaitingCargo(WaitingVIPCargo, WaitingNormalCargo, WaitingSpecialCargo);
		std::cout << "Waiting Cargos: ";
		std::cout << std::string(20, '_') << endl;
		std::cout << "[ "; WaitingNormalCargo.PrintListCargo(); cout << "]" << "  " << "("; WaitingSpecialCargo.PrintQueue(); cout << ")" << " " << "{"; WaitingVIPCargo.printarrCargo(); cout << "}";


		//std::cout<<getTotalDelieveredCargo(delievedCargo);

		std::cout << "delieverd Cargos: ";
		std::cout << std::string(20, '_') << endl;
		std::cout << "[ "; DeliveredNormalCargo.PrintQueue(); cout << "]" << "  " << "("; DeliveredSpecialCargo.PrintQueue(); cout << ")" << " " << "{"; DeliveredVipCargo.PrintQueue(); cout << "}";


		/*std::cout << getTotalLoadingCargo(LoadingNormalCargo, LoadingVipCargo, LoadingSpecialCargo);
		std::cout << "Loading Cargos: ";*/
		//std::cout << "[", LoadingNormalTrucks.PrintList(), "]   ", "(", LoadingSpecialTrucks.PrintList(), ")   ", "{", LoadingVIPTrucks.PrintList(), "} \n";
	/*	std::cout << std::string(20, '_') << endl;*/


		std::cout << getTotalEmptytrucks(AvailbleNormalTrucks, AvailbleSpecialTrucks, AvailbleVipTrucks);
		std::cout << "Empty Trucks: ";
		std::cout << "[ "; AvailbleNormalTrucks.PrintQueue(); cout << "]" << "  " << "("; AvailbleSpecialTrucks.PrintQueue(); cout << ")" << " " << "{"; AvailbleVipTrucks.printarrTruck(); cout << "}";
		std::cout << std::string(20, '_') << endl;

		cout << "LoadingTrucks" << " ";
		LoadingTrucks.getCount();
		LoadingTrucks.printarrTruck();
		std::cout << std::string(20, '_') << endl;
		
		cout << "movingTrucks" << " ";
		movingtruck.getCount();
		movingtruck.printarrTruck();
		std::cout << std::string(20, '_') << endl;
		cout << "Returning Trucks" << " ";
		returningback.getCount();
		returningback.printarrTruck();
		std::cout << std::string(20, '_') << endl;

		cout << "fixing Trucks" << " ";
		fixingtruck.getCount();
		fixingtruck.printarrTruck();
		//std::cout << std::string(20, '_') << endl;
		//cout << "movingTrucks" << " ";
		//movingtruck.getCount();
		//movingtruck.printarrTruck();
		//std::cout << std::string(20, '_') << endl;



	/*	std::cout << std::string(20, '_') << endl;*/


		//std::cin >> m;
	}
}

	//void UI::StartStepByStepMode(){}






















































































































































































































































































































































	void UIClass::StartSilentMode()
	{
		std::cout << "Silent Mode \n Simulation Starts.. \n";
	}
