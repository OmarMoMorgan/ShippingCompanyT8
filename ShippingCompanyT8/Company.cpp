#include "Company.h"


void Company::LoadFile() {
	ifstream Line;
	Line.open("File needed.txt");
	if (!Line) {
		//should be replaced with ui function
		cout << "error couldn't open file";
	}
	
	//reading normal lines here before events
	Line >> NumberNormalTrucks >> NumberSpecialTrucks >> NumberVipTrucks;
	Line >> DummyNSpeed >> DummySSpeed >> DummyVSpeed;
	Line >> DummyNCap >> DummySCap >> DummyVCap;
	Line >> DummyNCap >> DummySCap >> DummyVCap >> DummyNumJourneys;

	Line >> AutoP >> MaxW;
	Line >> NumberEvents;

	string eventtype;
	string cargotype;
	string hourfromfile;
	//from here these stuff shall be repolaced with other stuff from the cargo anad truck class
	int id;
	int dist;
	int LT;
	int cost;


	int day;
	int hr;

	Events* pEvent;
	//reading events here 
	for (int i = 0; i < NumberEvents; i++) {
		Line >> eventtype;
		//cout << "here i am file loading" << endl;
		if (eventtype == "R") {

			Line >> cargotype >> hourfromfile >> id >> dist >> LT >> cost;


			day = convertString<int>(hourfromfile.substr(0, 2));
			hr = convertString<int>(hourfromfile.substr(2, 4));
			int cargot;
			if (cargotype == "N") {
				cargot = 1;
			}
			else if (cargotype == "S") {
				cargot = 2;
			}
			else if (cargotype == "V") {
				cargot = 3;
			}

			Ready* nReady = new Ready(id, cost, day, hr, LT, dist, cargot);
			//pEvent = nReady;
			EventsList.enqueue(nReady);
			//cout << "Ready " << "day " << day << " hour " << hr << endl;
		}
		else if (eventtype == "X") {
			Line >> hourfromfile >> id;
			day = convertString<int>(hourfromfile.substr(0, 2));
			hr = convertString<int>(hourfromfile.substr(2, 4));
			Cancel* ncanel = new Cancel(id, day, hr);
			EventsList.enqueue(ncanel);
			//cout << "cancel " << "day " << day << " hour " << hr << endl;
		}
		else if (eventtype == "P") {
			Line >> hourfromfile >> id >> cost;
			day = convertString<int>(hourfromfile.substr(0, 2));
			hr = convertString<int>(hourfromfile.substr(2, 4));
			Promote* nPromote = new Promote(id, day, hr, cost);
			EventsList.enqueue(nPromote);
			//cout << "promote " << "day " << day << " hour " << hr << endl;
		}
		

		//int actualid = stoi(id);
		
		
		maxid = id;
		//cout<<"here is the num" << maxid << endl;
	}

	Line.close();	
}



//----------------------------------------------




//---------------------------------------------------------
void Company::SimTest() {
	
	LoadFile();

	Events* Eventhappening;
	Cargo* CargoToBeMoved;

	//some checkers here
	int etd ;
	int eth ;

	int flag = 0;
	UIController = new UIClass();
	while (EventsList.getCount() >= 0 && (DeliveredNormalCargo.getCount() + DeliveredSpecialCargo.getCount() + DeliveredVipCargo.getCount())  != maxid && flag < 3) {

		UniversalTime.MoveOneunit();
		EventsList.peek(Eventhappening);

		UIController->StartInteractiveMode(UniversalTime.CurrentDay , UniversalTime.CurrentHour , 
			WaitingSpecialCargo , WaitingNormalCargo , WaitingVipCargo, AvailbleNormalTrucks , AvailbleSpecialTrucks ,
			AvailbleVipTrucks , DeliveredSpecialCargo , DeliveredVipCargo , DeliveredNormalCargo, LoadingTrucks);

		etd = Eventhappening->getETD();
		eth= Eventhappening->getETH();

		//cout << "Day :" << UniversalTime.CurrentDay << " Hour : " << UniversalTime.CurrentHour << endl;

		
			while (etd <= UniversalTime.CurrentDay && eth <= UniversalTime.CurrentHour && flag == 0) {

				if (!EventsList.dequeue(Eventhappening)) {
					flag = 1;
				}
			//	cout << etd << "	" << eth << endl;
				Eventhappening->Execute(WaitingNormalCargo, WaitingSpecialCargo, WaitingVipCargo);
				//delete Eventhappening;
				EventsList.peek(Eventhappening);
				etd = Eventhappening->getETD();
				eth = Eventhappening->getETH();
			}
		
			
				if ((UniversalTime.CurrentDay + UniversalTime.CurrentHour) % 5 == 0) {
					//if(WaitingNormalCargo.getHead(). >= UniversalTime.CurrentDay && WaitingNormalCargo)
					//WaitingNormalCargo.PrintList();
					if (WaitingNormalCargo.removeFirstelement(CargoToBeMoved)) {
						DeliveredNormalCargo.enqueue(CargoToBeMoved);
						
						//cout << "Cargo added id : " << CargoToBeMoved->getCargoID() << endl;
						//WaitingNormalCargo.PrintList();
					}

					if (WaitingSpecialCargo.dequeue(CargoToBeMoved)) {
						DeliveredSpecialCargo.enqueue(CargoToBeMoved);
						
						//cout << "Cargo added id : " << CargoToBeMoved->getCargoID() << endl;
					}

					if (WaitingVipCargo.Pop(CargoToBeMoved)) {
						DeliveredVipCargo.enqueue(CargoToBeMoved);
						//cout << "Cargo added id : " << CargoToBeMoved->getCargoID() << endl;
					}

					
					if (flag == 1) {
						flag = 3;
					}
				}
		//cout << "test" << endl;
		//cout << DeliveredCargo.getCount();
	}
}




//void Company::MoveTomaintace()
//{
//	Truck* Ptruck;
//	MovingTrucks.peek(Ptruck);
//	if (Ptruck->getTotalJourneys() % Ptruck->getJtm() == 0 && cu)
//	{
//		MovingTrucks.Pop(Ptruck);
//		FixingTrucks.dequeue(Ptruck);
//	}
//}

void Company::MoveToTrucks() {
	int maxloadingTime;

	Truck* pTruck;
	Cargo* pCargo;

	int counter = 0;

	//vip first it is here assumed they are in the correct order with right priorties
	while (!isOffHours())
	{
		if (WaitingVipCargo.getCount() > 0) {
			AvailbleVipTrucks.peek(pTruck);
			WaitingVipCargo.peek(pCargo);
			if (AvailbleVipTrucks.getCount() > pTruck->getTruckCapacity()) {
				//Move Truck to Loading
				pTruck = AvailbleVipTrucks.Pop();
				LoadingTrucks.insert(pTruck, 1);
				//Move to the truck
				//it also determines the move time of the truck
				for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
					pCargo = WaitingVipCargo.Pop();
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
				}
				pTruck->setMoveTime(maxloadingTime, UniversalTime.CurrentDay);
			}

			else if (AvailbleNormalTrucks.getCount() > 0) {
				AvailbleNormalTrucks.peek(pTruck);
				if (WaitingVipCargo.getCount() > pTruck->getTruckCapacity()) {
					//Move Truck to Loading
					AvailbleNormalTrucks.dequeue(pTruck);
					LoadingTrucks.insert(pTruck, 1);
					//Move to the truck
					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
						pCargo = WaitingVipCargo.Pop();
						pTruck->insertCargo(WaitingVipCargo.Pop());
						maxloadingTime = pCargo->getLoadTime();
					}
					pTruck->setMoveTime(maxloadingTime, UniversalTime.CurrentDay);
				}
			}
			else if (AvailbleSpecialTrucks.getCount() > 0) {
				AvailbleSpecialTrucks.peek(pTruck);
				if (WaitingVipCargo.getCount() > pTruck->getTruckCapacity()) {
					//move truck to loading 
					AvailbleSpecialTrucks.dequeue(pTruck);
					LoadingTrucks.insert(pTruck, 1);
					//Move to the truck
					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
						pCargo = WaitingVipCargo.Pop();
						pTruck->insertCargo(WaitingVipCargo.Pop());
						maxloadingTime = pCargo->getLoadTime();
					}
					pTruck->setMoveTime(maxloadingTime, UniversalTime.CurrentDay);
				}
			}

			else if (pCargo->getWaitTime() > MaxW) {
				while (WaitingVipCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
					WaitingVipCargo.Pop(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
					counter++;
				}
			}
		}

		//special cargo

		if (AvailbleSpecialTrucks.getCount() > 0) {
			AvailbleSpecialTrucks.peek(pTruck);
			WaitingSpecialCargo.peek(pCargo);
			if (WaitingSpecialCargo.getCount() > pTruck->getTruckCapacity()) {
				//Move trucks to Loading
				AvailbleSpecialTrucks.dequeue(pTruck);
				LoadingTrucks.insert(pTruck, 1);
				//Move to the truck
				for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
					WaitingSpecialCargo.dequeue(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
				}
				pTruck->setMoveTime( maxloadingTime, UniversalTime.CurrentDay);
			}
			else if (pCargo->getWaitTime() > MaxW) {
				while (WaitingSpecialCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
					WaitingSpecialCargo.dequeue(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
					counter++;
				}
			}
		}

		//Normal cargo
		if (AvailbleNormalTrucks.getCount() > 0) {
			AvailbleNormalTrucks.peek(pTruck);
			if (WaitingNormalCargo.getCount() > pTruck->getTruckCapacity()) {
				//Move to loading trucks
				AvailbleNormalTrucks.dequeue(pTruck);
				LoadingTrucks.insert(pTruck, 1);
				//Move to the truck
				for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
					WaitingNormalCargo.removeFirstelement(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
				}
				pTruck->setMoveTime(maxloadingTime, UniversalTime.CurrentDay);
			}
			else if (WaitingVipCargo.getCount() > pTruck->getTruckCapacity()) {
				//Move to loading trucks
				pTruck = AvailbleVipTrucks.Pop();
				LoadingTrucks.insert(pTruck, 1);
				//Move to the truck
				for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
					WaitingNormalCargo.removeFirstelement(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
				}
				pTruck->setMoveTime(maxloadingTime, UniversalTime.CurrentDay);
			}
			else if (WaitingNormalCargo.peek()->getWaitTime() > MaxW) {
				while (WaitingNormalCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
					WaitingNormalCargo.removeFirstelement(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
					counter++;
				}
			}

			if (WaitingNormalCargo.peek()->getWaitTime() > AutoP) {
				WaitingNormalCargo.removeFirstelement(pCargo);
				//shoudl be replaced later
				WaitingVipCargo.insert(pCargo, 1);
			}
		}

	}
}





void Company::MoveTrucktoMoving() {
	Truck* pTruck = LoadingTrucks.Pop();
	if (UniversalTime.CurrentHour == (pTruck->getMoveTime() - UniversalTime.CurrentDay * 24)) {
		pTruck = LoadingTrucks.Pop();
		//should be replaced with leaev time
		MovingTrucks.insert(pTruck, 1);
	}
}



void Company::FinsihDeleivery() {
	Truck* pTruck;
	Cargo* pCargo;
	int cargoType = 0;
	pTruck = MovingTrucks.Pop();
	int x = pTruck->getListCount();
	for (int i = 0; i < x; i++) {
		pCargo = pTruck->DeleiverCargo();
		pCargo->getCargoType();
		switch (cargoType)
		{
		case 1 :
			DeliveredNormalCargo.enqueue(pCargo);
			break;
		case 2:
			DeliveredSpecialCargo.enqueue(pCargo);
			break;
		case 3:
			DeliveredVipCargo.enqueue(pCargo);
			break;
		default:
			break;
		}
	}

	//this should be replaced here to make sure that the car gets to checkup list
	int truckType = 0;
	switch (truckType)
	{
	case 1 :
		AvailbleNormalTrucks.enqueue(pTruck);
		break;
	case 2:
		AvailbleSpecialTrucks.enqueue(pTruck);
		break;
	case 3:
		AvailbleVipTrucks.insert(pTruck);
		break;
	default:
		break;
	}
}


int Company::getCurrentDay()
{
	return UniversalTime.CurrentDay;
}

int Company::getCurrentHour()
{
	return UniversalTime.CurrentHour;
}

bool Company::isOffHours()
{
	if (getCurrentHour() < 24 || getCurrentHour() >= 5)
		return false;
	else
		return true;
}


//UI UITest;
//UITest.StartInteractiveMode(getCurrentDay(), getCurrentHour(), WaitingSpecialCargo, WaitingNormalCargo, WaitingVIPCargo, AvailbleNormalTrucks,
	//AvailbleSpecialTrucks, AvailbleVipTrucks,
	//DeliveredSpecialCargo, DeliveredVipCargo, DeliveredNormalCargo);



