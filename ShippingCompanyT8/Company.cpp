#include "Company.h"
//#include<iomanip>
//
//#include "windows.h."


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
	Line >> DummyNumJourneys >> DummyNumJourneysN >> DummyNumJourneysS >> DummyNumJourneysV;

	
	

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
				this->NCargos++;
			}
			else if (cargotype == "S") {
				cargot = 2;
				this->SCargos++;
			}
			else if (cargotype == "V") {
				cargot = 3;
				this->VCargos++;
			}

			Ready* nReady = new Ready(id, cost, day, hr, LT, dist, cargot);
			//pEvent = nReady;
			EventsList.enqueue(nReady);
			//cout << "Ready " << "day " << day << " hour " << hr << endl;
		}
		else if (eventtype == "X") {
			this->NCargos--;
			Line >> hourfromfile >> id;
			day = convertString<int>(hourfromfile.substr(0, 2));
			hr = convertString<int>(hourfromfile.substr(2, 4));
			Cancel* ncanel = new Cancel(id, day, hr);
			EventsList.enqueue(ncanel);
			//cout << "cancel " << "day " << day << " hour " << hr << endl;
		}
		else if (eventtype == "P") {
			this-> NCargos--;
			this->VCargos++;
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


	//adding trucks to their lists 
	Truck* pTruck; 
	int speedStep = -5;
	int capStep = -2;
	for (int i = 0; i < NumberNormalTrucks; i++) {
		/*
		int speedToAssign;
		int capacityToAssign;
		if (capStep > 2) capStep = -2;
		if (speedStep > 5) speedStep = -5;
		speedToAssign = DummyNSpeed + speedStep;
		capacityToAssign = DummyNCap + capStep;
		speedStep++;
		capStep++;
		*/
		pTruck = new Truck(1, DummyNSpeed, DummyNCap, DummyNumJourneys, DummyNumJourneysN);
		AvailbleNormalTrucks.enqueue(pTruck);
	}

	for (int i = 0; i < NumberSpecialTrucks; i++) {
		/*
		int speedToAssign;
		int capacityToAssign;
		if (capStep > 2) capStep = -2;
		if (speedStep > 5) speedStep = -5;
		speedToAssign = DummySSpeed + speedStep;
		capacityToAssign = DummySCap + capStep;
		speedStep++;
		capStep++;
		*/
		pTruck = new Truck(2, DummyNSpeed, DummyNCap, DummyNumJourneys, DummyNumJourneysS);
		AvailbleSpecialTrucks.enqueue(pTruck);
	}

	for (int i = 0; i < NumberVipTrucks; i++) {
		/*
		int speedToAssign;
		int capacityToAssign;
		if (capStep > 2) capStep = -2;
		if (speedStep > 5) speedStep = -5;
		speedToAssign = DummyVpeed + speedStep;
		capacityToAssign = DummyVCap + capStep;
		speedStep++;
		capStep++;
		*/
		pTruck = new Truck(3, DummyVSpeed, DummyVCap, DummyNumJourneys, DummyNumJourneysV);
		AvailbleVipTrucks.insert(pTruck);
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

		UIController->StartInteractiveMode(UniversalTime.CurrentDay, UniversalTime.CurrentHour,
			WaitingSpecialCargo, WaitingNormalCargo, WaitingVipCargo, AvailbleNormalTrucks, AvailbleSpecialTrucks,
			AvailbleVipTrucks, DeliveredSpecialCargo, DeliveredVipCargo, DeliveredNormalCargo, LoadingTrucks ,MovingTrucks, ReturnBackTruck,FixingTrucks)
			;
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
		
			/*FinsihDeleivery();*/
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
		/*cout << "test" << endl;
		cout << DeliveredCargo.getCount();*/
	}
}




void Company::switchTrucksAvailable(Truck* t)
{
	int truckType = t->getType();
	switch (truckType)
	{
	case 1:
		AvailbleNormalTrucks.enqueue(t);
		break;
	case 2:
		AvailbleSpecialTrucks.enqueue(t);
		break;
	case 3:
		AvailbleVipTrucks.insert(t);
		break;
	default:
		break;
	}
}

void Company::MoveTofixed()
{
	Truck* Ltruck;
	int currentTime = getCurrentDay() * 24 + getCurrentHour();
	if (FixingTrucks.getCount()>0) {
		FixingTrucks.peek(Ltruck);
		
			if (currentTime>=Ltruck->getMaintenanceTime() + Ltruck->getReturnTime() )
		{
				/*cout << "REALLY that fast";*/ //debugging
			switchTrucksAvailable(Ltruck);

			FixingTrucks.Pop(Ltruck);

		}
	}
}

void Company::ReturnToCompany()
{
	Truck* Ptruck;
			int currentTime = getCurrentDay() * 24 + getCurrentHour();
	if (ReturnBackTruck.getCount() > 0) {
		ReturnBackTruck.peek(Ptruck);
		// add to maintance or availabe
		if (currentTime >= Ptruck->getReturnTime())
		{	ReturnBackTruck.Pop(Ptruck);
			if (Ptruck->getTotalJourneys() %Ptruck->getJtm() == 0)
			{
				Ptruck->setReturnTime(currentTime);
				FixingTrucks.insert(Ptruck,1);
			}
			else
			{
				switchTrucksAvailable(Ptruck);
			}
		}
	}
	// Remove from maintance

}


//void Company::MoveToTrucks() {
//	int maxloadingTime;
//
//	Truck* pTruck;
//	Cargo* pCargo;
//
//	int counter = 0;
//	//vip first it is here assumed they are in the correct order with right priorties
//	if (!isOffHours())
//	{
//		if (WaitingVipCargo.getCount() > 0) {
//			AvailbleVipTrucks.peek(pTruck);
//			WaitingVipCargo.peek(pCargo);
//			if (AvailbleVipTrucks.getCount() > pTruck->getTruckCapacity()) {
//				//Move Truck to Loading
//				pTruck = AvailbleVipTrucks.Pop(pTruck);
//				LoadingTrucks.insert(pTruck, 1);
//				//Move to the truck
//				//it also determines the move time of the truck
//				for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
//					pCargo = WaitingVipCargo.Pop(pCargo);
//					pTruck->insertCargo(pCargo);
//					maxloadingTime = pCargo->getLoadTime();
//				}
//				pTruck->setMoveTime(maxloadingTime+ getCurrentHour(), UniversalTime.CurrentDay);
//			}
//
//			else if (AvailbleNormalTrucks.getCount() > 0) {
//				AvailbleNormalTrucks.peek(pTruck);
//				if (WaitingVipCargo.getCount() > pTruck->getTruckCapacity()) {
//					//Move Truck to Loading
//					AvailbleNormalTrucks.dequeue(pTruck);
//					LoadingTrucks.insert(pTruck, 1);
//					//Move to the truck
//					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
//						pCargo = WaitingVipCargo.Pop(pTruck);
//						pTruck->insertCargo(WaitingVipCargo.Pop(pCargo));
//						maxloadingTime = pCargo->getLoadTime();
//					}
//					pTruck->setMoveTime(maxloadingTime+ getCurrentHour(), UniversalTime.CurrentDay);
//				}
//			}
//			else if (AvailbleSpecialTrucks.getCount() > 0) {
//				AvailbleSpecialTrucks.peek(pTruck);
//				if (WaitingVipCargo.getCount() > pTruck->getTruckCapacity()) {
//					//move truck to loading 
//					AvailbleSpecialTrucks.dequeue(pTruck);
//					LoadingTrucks.insert(pTruck, 1);
//					//Move to the truck
//					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
//						pCargo = WaitingVipCargo.Pop();
//						pTruck->insertCargo(WaitingVipCargo.Pop(pCargo));
//						maxloadingTime = pCargo->getLoadTime();
//					}
//					pTruck->setMoveTime(maxloadingTime+ getCurrentHour(), UniversalTime.CurrentDay);
//				}
//			}
//
//			else if (pCargo->getWaitTime() > MaxW) {
//				while (WaitingVipCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
//					WaitingVipCargo.Pop(pCargo);
//					pTruck->insertCargo(pCargo);
//					maxloadingTime = pCargo->getLoadTime();
//					counter++;
//				}
//			}
//		}

		//special cargo

	//	if (AvailbleSpecialTrucks.getCount() > 0) {
	//		AvailbleSpecialTrucks.peek(pTruck);
	//		WaitingSpecialCargo.peek(pCargo);
	//		if (WaitingSpecialCargo.getCount() > pTruck->getTruckCapacity()) {
	//			//Move trucks to Loading
	//			AvailbleSpecialTrucks.dequeue(pTruck);
	//			LoadingTrucks.insert(pTruck, 1);
	//			//Move to the truck
	//			for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
	//				WaitingSpecialCargo.dequeue(pCargo);
	//				pTruck->insertCargo(pCargo);
	//				maxloadingTime = pCargo->getLoadTime();
	//			}
	//			pTruck->setMoveTime( maxloadingTime+ getCurrentHour(), UniversalTime.CurrentDay);
	//		}
	//		else if (pCargo->getWaitTime() > MaxW) {
	//			while (WaitingSpecialCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
	//				WaitingSpecialCargo.dequeue(pCargo);
	//				pTruck->insertCargo(pCargo);
	//				maxloadingTime = pCargo->getLoadTime();
	//				counter++;
	//			}
	//		}
	//	}

	//	//Normal cargo
	//	if (AvailbleNormalTrucks.getCount() > 0) {
	//		AvailbleNormalTrucks.peek(pTruck);
	//		if (WaitingNormalCargo.getCount() > pTruck->getTruckCapacity()) {
	//			//Move to loading trucks
	//			AvailbleNormalTrucks.dequeue(pTruck);
	//			LoadingTrucks.insert(pTruck, 1);
	//			//Move to the truck
	//			for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
	//				WaitingNormalCargo.removeFirstelement(pCargo);
	//				pTruck->insertCargo(pCargo);
	//				maxloadingTime = pCargo->getLoadTime();
	//			}
	//			pTruck->setMoveTime(maxloadingTime, UniversalTime.CurrentDay);
	//		}
	//		else if (WaitingVipCargo.getCount() > pTruck->getTruckCapacity()) {
	//			//Move to loading trucks
	//			pTruck = AvailbleVipTrucks.Pop();
	//			LoadingTrucks.insert(pTruck, 1);
	//			//Move to the truck
	//			for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
	//				WaitingNormalCargo.removeFirstelement(pCargo);
	//				pTruck->insertCargo(pCargo);
	//				maxloadingTime = pCargo->getLoadTime();
	//			}
	//			pTruck->setMoveTime(maxloadingTime, UniversalTime.CurrentDay);
	//		}
	//		else if (WaitingNormalCargo.peek()->getWaitTime() > MaxW) {
	//			while (WaitingNormalCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
	//				WaitingNormalCargo.removeFirstelement(pCargo);
	//				pTruck->insertCargo(pCargo);
	//				maxloadingTime = pCargo->getLoadTime();
	//				counter++;
	//			}
	//		}

		//	if (WaitingNormalCargo.peek()->getWaitTime() > AutoP) {
		//		WaitingNormalCargo.removeFirstelement(pCargo);
		//		//shoudl be replaced later
		//		WaitingVipCargo.insert(pCargo, 1);
		//	}
		//}

	//}
//}

void Company::LoadVip() {
	int maxloadingTime = 0;

	Truck* pTruck;
	Cargo* pCargo;

	int counter = 0;
	//vip first it is here assumed they are in the correct order with right priorties
	
		if (WaitingVipCargo.getCount() > 0) {
			WaitingVipCargo.peek(pCargo);
			if (AvailbleVipTrucks.getCount() > 0) {
				AvailbleVipTrucks.peek(pTruck);
				if (WaitingVipCargo.getCount() >= pTruck->getTruckCapacity()) {
					//Move Truck to Loading
					AvailbleVipTrucks.Pop(pTruck);
					LoadingTrucks.insert(pTruck, 1);
					pTruck->setLoadTime(getCurrentDay() * 24 + getCurrentHour());
					//Move to the truck
					//it also determines the move time of the truck
					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
						WaitingVipCargo.Pop(pCargo);
						pTruck->insertCargo(pCargo);
						pCargo->setTruckId(pTruck->getTrucID());
						maxloadingTime = pCargo->getLoadTime();
					}
					pTruck->setMoveTime(maxloadingTime+ getCurrentHour(), UniversalTime.CurrentDay);
					
					//this is for debiugging only 
					cout << "in a vip truck";
					pTruck->printcargosdebug();
					cout << endl;
				}
			}

			else if (AvailbleNormalTrucks.getCount() > 0) {
				AvailbleNormalTrucks.peek(pTruck);
				if (WaitingVipCargo.getCount() >= pTruck->getTruckCapacity()) {
					//Move Truck to Loading
					AvailbleNormalTrucks.dequeue(pTruck);
					LoadingTrucks.insert(pTruck, 1);
					pTruck->setLoadTime(getCurrentDay() * 24 + getCurrentHour());

					//Move to the truck
					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
						WaitingVipCargo.Pop(pCargo);
						pTruck->insertCargo(pCargo);
						pCargo->setTruckId(pTruck->getTrucID());
						maxloadingTime = pCargo->getLoadTime();
					}
					pTruck->setMoveTime(maxloadingTime+ getCurrentHour(), UniversalTime.CurrentDay);
					//this is for debiugging only 
					cout << "in a normal truck";
					pTruck->printcargosdebug();
				}
			}
			else if (AvailbleSpecialTrucks.getCount() > 0) {
				AvailbleSpecialTrucks.peek(pTruck);
				if (WaitingVipCargo.getCount() >= pTruck->getTruckCapacity()) {
					//move truck to loading 
					AvailbleSpecialTrucks.dequeue(pTruck);
					LoadingTrucks.insert(pTruck, 1);
					//Move to the truck
					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
						WaitingVipCargo.Pop(pCargo);
						pTruck->insertCargo(pCargo);
						pCargo->setTruckId(pTruck->getTrucID());
						maxloadingTime = pCargo->getLoadTime();
					}
					pTruck->setMoveTime(maxloadingTime	+ getCurrentHour(), UniversalTime.CurrentDay);
					//this is for debiugging only 
					cout << "in a special truck";
					pTruck->printcargosdebug();
				}
			}

			/*else if (pCargo->getWaitTime() > MaxW) {
				while (WaitingVipCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
					WaitingVipCargo.Pop(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
					counter++;
				}
			}*/
		}
}



void Company::LoadSpecial() {
	int maxloadingTime = 0;

	Truck* pTruck;
	Cargo* pCargo;

	int counter = 0;
	int numwaiting = WaitingSpecialCargo.getCount();
	
		//AvailbleSpecialTrucks.getCount() > 0
		if (numwaiting > 0 && AvailbleSpecialTrucks.getCount() > 0) {
			AvailbleSpecialTrucks.peek(pTruck);
			//WaitingSpecialCargo.peek(pCargo);
			if (numwaiting >= pTruck->getTruckCapacity()) {
				//Move trucks to Loading
				AvailbleSpecialTrucks.dequeue(pTruck);
				LoadingTrucks.insert(pTruck, 1);
				pTruck->setLoadTime(getCurrentDay() * 24 + getCurrentHour());
				//Move to the truck
				for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
					WaitingSpecialCargo.dequeue(pCargo);
					pTruck->insertCargo(pCargo);
					pCargo->setTruckId(pTruck->getTrucID());
					maxloadingTime = pCargo->getLoadTime();
				}
				pTruck->setMoveTime(maxloadingTime+getCurrentHour(), UniversalTime.CurrentDay);
			}

		}
}

void Company::LoadNormal() {
	int maxloadingTime = 0;

	Truck* pTruck;
	Cargo* pCargo;

	int counter = 0;
	
		if (WaitingNormalCargo.getCount() > 0) {
			if (AvailbleNormalTrucks.getCount() > 0) {
				AvailbleNormalTrucks.peek(pTruck);
				if (WaitingNormalCargo.getCount() >= pTruck->getTruckCapacity()) {
					//Move to loading trucks
					AvailbleNormalTrucks.dequeue(pTruck);
					LoadingTrucks.insert(pTruck, 1);
					pTruck->setLoadTime(getCurrentDay() * 24 + getCurrentHour());
					//Move to the truck
					for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
						WaitingNormalCargo.removeFirstelement(pCargo);
						pTruck->insertCargo(pCargo);
						pCargo->setTruckId(pTruck->getTrucID());
						maxloadingTime = pCargo->getLoadTime();
					}
					pTruck->setMoveTime(maxloadingTime + getCurrentHour() , UniversalTime.CurrentDay);
					

					pTruck->printcargosdebug();
				}
			}
			else {
				if (AvailbleVipTrucks.getCount() > 0) {
					AvailbleVipTrucks.peek(pTruck);
					if (WaitingNormalCargo.getCount() >= pTruck->getTruckCapacity()) {
						//Move to loading trucks
						AvailbleVipTrucks.Pop(pTruck);
						LoadingTrucks.insert(pTruck, 1);
						//Move to the truck
						for (int i = 0; i < pTruck->getTruckCapacity(); i++) {
							WaitingNormalCargo.removeFirstelement(pCargo);
							pTruck->insertCargo(pCargo);
							pCargo->setTruckId(pTruck->getTrucID());
							maxloadingTime = pCargo->getLoadTime();
						}
						pTruck->setMoveTime(maxloadingTime + getCurrentDay(), UniversalTime.CurrentDay);
					}
				}
			}
		}		
}

void Company::MaxwNormalSpecial() {
	Truck* pTruck;
	Cargo* pCargo;
	int maxloadingTime;
	int counter = 0;

	//Normal cargo maxw
	
	if (WaitingNormalCargo.getCount() > 0) {
		if (AvailbleNormalTrucks.getCount() > 0) {
			AvailbleNormalTrucks.peek(pTruck);
			if (WaitingNormalCargo.peek()->getCurWaitTime(UniversalTime.CurrentDay, UniversalTime.CurrentHour) > MaxW) {
				while (WaitingNormalCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
					WaitingNormalCargo.removeFirstelement(pCargo);
					pTruck->insertCargo(pCargo);
						pCargo->setTruckId(pTruck->getTrucID());
					maxloadingTime = pCargo->getLoadTime();
					counter++;
				}
			}
		}
	}

	//Special Cargo maxw
	if (WaitingSpecialCargo.getCount() > 0) {
		if(AvailbleSpecialTrucks.getCount() > 0){
			AvailbleSpecialTrucks.peek(pTruck);
			WaitingSpecialCargo.peek(pCargo);
			if (pCargo->getCurWaitTime(UniversalTime.CurrentDay, UniversalTime.CurrentHour) > MaxW) {
				while (WaitingSpecialCargo.getCount() > 0 && pTruck->getTruckCapacity() > counter) {
					WaitingSpecialCargo.dequeue(pCargo);
					pTruck->insertCargo(pCargo);
					maxloadingTime = pCargo->getLoadTime();
					counter++;
				}
			}
	}
	}
}


void Company::AutoUpgradeToVip() {

	Cargo* pCargo;
	if (WaitingNormalCargo.getCount() > 0) {
		if (WaitingNormalCargo.peek()->getCurWaitTime(UniversalTime.CurrentDay, UniversalTime.CurrentHour) > AutoP) {
			//pCargo = WaitingNormalCargo.peek();
			WaitingNormalCargo.removeFirstelement(pCargo);
			pCargo->setCargoType(3);
			//shoudl be replaced later
			WaitingVipCargo.insert(pCargo, 1);
			this->autoPromoted++;
		}
	}
}



void Company::MoveTrucktoMoving() {
	Truck* pTruck;
	if (LoadingTrucks.getCount() > 0) {
		LoadingTrucks.peek(pTruck);
		if (UniversalTime.CurrentHour == (pTruck->getMoveTime() - UniversalTime.CurrentDay * 24)) {
			LoadingTrucks.Pop(pTruck);
			//should be replaced with leaev time
			MovingTrucks.insert(pTruck, pTruck->peekCargo()->getCDT(pTruck->getSpeed(),- pTruck->getMoveTime()));
			//this is for debiugging only 
			cout << endl << "debug test starts here";
			pTruck->printcargosdebug();
			cout << endl;
			MovingTrucks.printarrTruck();
			cout << endl;
		}
		
	}

}




void Company::FinsihDeleivery() {
	Truck* pTruck;
	Cargo* pCargo;
	int cargoType = 0;
	int current_time_Hours = getCurrentDay() * 24 + getCurrentHour();
	if (MovingTrucks.getCount() > 0) {
		MovingTrucks.peek(pTruck);
		pCargo = pTruck->peekCargo();
		
		if (current_time_Hours >= pCargo->getCDT(pTruck->getSpeed(), pTruck->getMoveTime()))
		{
			MovingTrucks.Pop(pTruck);
			cargoType=	pCargo->getCargoType();
			switch (cargoType)
			{
			case 1:
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
			pTruck->DeleiverCargo();
			if (pTruck->getListCount() > 0)
				MovingTrucks.insert(pTruck);
			else {
				pTruck->setfinishTime(current_time_Hours);
				pTruck->incrementJourney();
				pTruck->setReturnTime((pCargo->getDelieveryDistance()+100)/ pTruck->getSpeed()+ current_time_Hours); //+100 as getdistance was so small it returned zero
				ReturnBackTruck.insert(pTruck, pTruck->getReturnTime());
			}
		}
	}
}

		//this should be replaced here to make sure that the car gets to checkup list
		//int truckType = 0;
		//switch (truckType)
		//{
		//case 1:
		//	AvailbleNormalTrucks.enqueue(pTruck);
		//	break;
		//case 2:
		//	AvailbleSpecialTrucks.enqueue(pTruck);
		//	break;
		//case 3:
		//	AvailbleVipTrucks.insert(pTruck);
		//	break;
		//default:
		//	break;
		//}
	



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
	if (getCurrentHour() < 24 && getCurrentHour() >= 5)
		return false;
	else
		return true;
}







void Company::Simulator() {
	LoadFile();

	Events* Eventhappening;
	Cargo* CargoToBeMoved;

	//some checkers here
	int etd;
	int eth;

	int flag = 0;
	UIController = new UIClass();

	EventsList.peek(Eventhappening);
	etd = Eventhappening->getETD();
	eth = Eventhappening->getETH();

	while (flag < 2){

		UniversalTime.MoveOneunit();
		//this is for debiugging only 
		//cout << "Current Time " << "(Day " << UniversalTime.CurrentDay << " : " << UniversalTime.CurrentHour << " Hour) \n";
		//EventsList.peek(Eventhappening);


		UIController->StartInteractiveMode(UniversalTime.CurrentDay, UniversalTime.CurrentHour,
			WaitingSpecialCargo, WaitingNormalCargo, WaitingVipCargo, AvailbleNormalTrucks, AvailbleSpecialTrucks,
			AvailbleVipTrucks, DeliveredSpecialCargo, DeliveredVipCargo, DeliveredNormalCargo, LoadingTrucks, MovingTrucks,ReturnBackTruck,FixingTrucks);
		//Executing events
	
		if (flag ==0) {
			while (etd <= UniversalTime.CurrentDay && eth <= UniversalTime.CurrentHour) {
				Eventhappening->Execute(WaitingNormalCargo, WaitingSpecialCargo, WaitingVipCargo);
				EventsList.dequeue(Eventhappening);
				delete Eventhappening;
				if (EventsList.getCount() == 0) {
					flag = 1;
					break;
				}
				EventsList.peek(Eventhappening);
				etd = Eventhappening->getETD();
				eth = Eventhappening->getETH();
				
			}			
		}


		/*do
		{
			EventsList.peek(Eventhappening);
			etd = Eventhappening->getETD();
			eth = Eventhappening->getETH();
			if (etd <= UniversalTime.CurrentDay && eth <= UniversalTime.CurrentHour) {
				Eventhappening->Execute(WaitingNormalCargo, WaitingSpecialCargo, WaitingVipCargo);
				EventsList.dequeue(Eventhappening);
				delete Eventhappening;
			}
			else {
				flag = -1;
			}
			if (EventsList.getCount() == 0) {
				flag = 1;
				etd = 1000000;
				eth = 1000000;
				}
			else {
				EventsList.peek(Eventhappening);
				etd = Eventhappening->getETD();
				eth = Eventhappening->getETH();
			}
		}
		while (flag == 0);*/
		
		
		//all of the below lines are for debugging purposes only:
		//this is for debiugging only 
	/*	cout << "[ "; WaitingNormalCargo.PrintListCargo(); 
		cout << "]" << "  " << "(";
		WaitingSpecialCargo.PrintQueue();
		cout << ")" << " " << "{";
		WaitingVipCargo.printarrCargo(); cout << "}";
		cout << endl;*/
		//cout << "oamr test starts from here" "\n";
		//WaitingNormalCargo.PrintListCargo();
		//cout << "\n" " it eneded here \n";
		//simulation starts from here
		if (!isOffHours()) {
			LoadVip();
			LoadSpecial();
			LoadNormal();
			MaxwNormalSpecial();
			AutoUpgradeToVip();

		
 /*	ReturnToCompany()*/;
			//complete here for the rest of the functions
		}
		MoveTrucktoMoving();
		FinsihDeleivery();
		ReturnToCompany();
		
		MoveTofixed();
		if (AllEnded()) {
		
		AllDelieverdCargos	=makeOneDelieverdQueue(DeliveredNormalCargo, DeliveredSpecialCargo, DeliveredVipCargo);
		//this is just as final check that all is empty 
		UIController->StartInteractiveMode(UniversalTime.CurrentDay, UniversalTime.CurrentHour,
			WaitingSpecialCargo, WaitingNormalCargo, WaitingVipCargo, AvailbleNormalTrucks, AvailbleSpecialTrucks,
			AvailbleVipTrucks, DeliveredSpecialCargo, DeliveredVipCargo, DeliveredNormalCargo, LoadingTrucks, MovingTrucks, ReturnBackTruck, FixingTrucks);
			flag = 2;
			outputStatistics();
		}
	}
}



bool Company::AllEnded() {
	int WN = WaitingNormalCargo.getCount();
	int WV = WaitingVipCargo.getCount();
	int WS = WaitingSpecialCargo.getCount();
	int FT = FixingTrucks.getCount();
	int LoadT = LoadingTrucks.getCount();
	int MoveT = MovingTrucks.getCount();
	int RT = ReturnBackTruck.getCount();
	int ev = EventsList.getCount();

	if (WN + WV + WS + LoadT + MoveT + ev+ FT+ RT == 0) {
		return true;
	}
	else {
		return false;
	}
}
PriorityQueueArr<Cargo*> Company::makeOneDelieverdQueue(LinkedQueue<Cargo*> normal, LinkedQueue<Cargo*> q1special, LinkedQueue<Cargo*> vip)
{
	Cargo* NormalCargo;
	Cargo* SpecialCargo;
	Cargo* VIPCargo;

	while (normal.dequeue(NormalCargo) || q1special.dequeue(SpecialCargo) || vip.dequeue(VIPCargo))
	{
		if (normal.dequeue(NormalCargo))
		{
			AllDelieverdCargos.insert(NormalCargo, NormalCargo->getCDTdebug());
		}
		if (q1special.dequeue(SpecialCargo))
		{
			AllDelieverdCargos.insert(SpecialCargo, SpecialCargo->getCDTdebug());
		}
		if (vip.dequeue(VIPCargo))
		{
			AllDelieverdCargos.insert(VIPCargo, VIPCargo->getCDTdebug());
		}


	}
	return PriorityQueueArr<Cargo*>();
}
//UI UITest;
//UITest.StartInteractiveMode(getCurrentDay(), getCurrentHour(), WaitingSpecialCargo, WaitingNormalCargo, WaitingVIPCargo, AvailbleNormalTrucks,
	//AvailbleSpecialTrucks, AvailbleVipTrucks,
	//DeliveredSpecialCargo, DeliveredVipCargo, DeliveredNormalCargo);

//void Company::checktoAvailable(int enteringDay, int enteringHr)
//{
//	Truck* cTruck;
//	int deltaTime=0;			//TBC...
//	  
//	this->FixingTrucks.peek(cTruck);
//	if ((24 * getCurrentDay() + getCurrentHour()) > (cTruck->getfinishTime()+cTruck->getMaintenanceTime()))
//	{
//		//1 for normal , 2 for special , 3 for vip
//		if (cTruck->getType() == 1)
//		{
//			FixingTrucks.dequeue(cTruck);
//			AvailbleNormalTrucks.enqueue(cTruck);
//		}
//		else if (cTruck->getType() == 2)
//		{
//			FixingTrucks.dequeue(cTruck);
//			AvailbleSpecialTrucks.enqueue(cTruck);
//
//		}
//		else if (cTruck->getType() == 3)
//		{
//			FixingTrucks.dequeue(cTruck);
//			AvailbleVipTrucks.insert(cTruck);
//		}
//	}
//}

//void Company:: movingtoAvailable(int enteringDay, int enteringHr)
//{
//	Truck* mTruck;
//	int deltaTime=0;		//TBC...
//	this->MovingTrucks.peek(mTruck);
//	if (  (24*getCurrentDay()+getCurrentHour()) > mTruck->getfinishTime()   ) //current time>truck->finishtime
//	{
//		//1 for normal , 2 for special , 3 for vip
//		if (mTruck->getType() == 1)
//		{
//			FixingTrucks.dequeue(mTruck);
//			AvailbleNormalTrucks.enqueue(mTruck);
//		}
//
//		else if (mTruck->getType() == 2)
//		{
//			FixingTrucks.dequeue(mTruck);
//			AvailbleSpecialTrucks.enqueue(mTruck);
//
//		}
//
//		else if (mTruck->getType() == 3)
//		{
//			FixingTrucks.dequeue(mTruck);
//			AvailbleVipTrucks.insert(mTruck);
//		}
//	}
//	//Last part is repeated, so, it can be moved to a separate function, smth like "MoveTruck"... 
//	
//}
//void  Company::OutputFileFisrtP()
//{
	//std::cout << "Silent Mode \n Simulation Starts.. \n Simulation ends, Output file created";
	////
	//ofstream OutputFile("Output.txt");
	//if (!OutputFile.is_open()) {
	//	cout << "Unable to open the file.." << endl;
	//}

	//else {

	//	OutputFile << "CDT" << setw(10) << "ID" << setw(10) << "PT" << setw(10) << "WT" << setw(10) << "TID" << endl;

	//	Cargo* dc;


	//	while (AllDelieverdCargos.getCount() > 0) {
	//		AllDelieverdCargos.peek(dc);

	//		OutputFile <<dc->getCDTdebug()<< "  ";
	//		OutputFile << dc->getCargoID() << "  ";
	//		OutputFile << dc->getPrepDay() << ":" << dc->getPrepHour() << "  ";
	//		OutputFile << dc->getWaitedTime() << "  ";
	//		OutputFile << dc->getTruckID() << "  " << endl;

	//	}


	//	OutputFile << "........................................................................" << endl;
	//	OutputFile << "........................................................................" << endl;

	//	//ro be completed with the statistics
	//	OutputFile << "Cargos: " << endl;
	//	OutputFile << "Cargos Avg Wait: " << endl;
	//	OutputFile << "Auto-promoted Caros: " << "%" << endl;
	//	OutputFile << "Trucks: " << endl;
	//	OutputFile << "Avg Active time = " << "%" << endl;
	//	OutputFile << "Avg utilization = " << "%" << endl;
	//	OutputFile.close();
//	}
//}
	void Company::outputStatistics()
	{
		int totalTrucks = NumberNormalTrucks + NumberSpecialTrucks + NumberVipTrucks;
		ofstream of;
		of.open("testOut.txt");
		//In auto promoted u compared with all cargos, while only normal are promoted.  //Fixed.
		of << "Statistics: " << endl;
		of << "Cargos: " << (NCargos + SCargos + VCargos) << "[N: " << NCargos << ", S: " << SCargos << ", V:  " << VCargos << "]" << endl;
		of << "Auto Promoted Cargos: " << 100 * (autoPromoted / (NCargos + autoPromoted)) << "%" << endl;
		of << "Trucks: " << totalTrucks << "[N: " << NumberNormalTrucks << ", S: " << NumberSpecialTrucks << ", V:  " << NumberVipTrucks << "]" << endl;
		Truck* temp;
		for (int i = 0; i < NumberNormalTrucks; i++)
		{
			AvailbleNormalTrucks.dequeue(temp);
			
			truckTotalActive += temp->getActiveTime();
			int tsim = (24 * UniversalTime.CurrentDay) + UniversalTime.CurrentHour;
			truckTotalUtilization += temp->calcTruckUtilization(tsim);
		}
		for (int i = 0; i < NumberVipTrucks; i++)
		{
			
			AvailbleVipTrucks.Pop(temp);
		
			truckTotalActive += temp->getActiveTime();
			int tsim = (24 * UniversalTime.CurrentDay) + UniversalTime.CurrentHour;
			truckTotalUtilization += temp->calcTruckUtilization(tsim);
		}
		for (int i = 0; i < NumberSpecialTrucks; i++)
		{
			AvailbleSpecialTrucks.dequeue(temp);
			truckTotalActive += temp->getActiveTime();
			int tsim = (24 * UniversalTime.CurrentDay) + UniversalTime.CurrentHour;
			truckTotalUtilization += temp->calcTruckUtilization(tsim);
		}
		truckAvgActive = truckTotalActive / totalTrucks;
		truckAvgUtilization = truckTotalUtilization / totalTrucks;
		of << "Average Active Time: " << truckAvgActive<<endl;
		of << "Average Utilization: " << truckAvgUtilization<<endl;

		}
	
	


