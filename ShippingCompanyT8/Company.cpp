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
			WaitingSpecialCargo , WaitingNormalCargo , WatitingVipCargo , AvailbleNormalTrucks , AvailbleSpecialTrucks ,
			AvailbleVipTrucks , DeliveredSpecialCargo , DeliveredVipCargo , DeliveredNormalCargo);

		etd = Eventhappening->getETD();
		eth= Eventhappening->getETH();

		//cout << "Day :" << UniversalTime.CurrentDay << " Hour : " << UniversalTime.CurrentHour << endl;

		
			while (etd <= UniversalTime.CurrentDay && eth <= UniversalTime.CurrentHour && flag == 0) {

				if (!EventsList.dequeue(Eventhappening)) {
					flag = 1;
				}
			//	cout << etd << "	" << eth << endl;
				Eventhappening->Execute(WaitingNormalCargo, WaitingSpecialCargo, WatitingVipCargo);
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

					if (WatitingVipCargo.Pop(CargoToBeMoved)) {
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
	//int numCargos = DeliveredCargo.getCount();
	//for (int i = 0; i < numCargos; i++) {
	//	DeliveredCargo.dequeue(CargoToBeMoved);
		//cout << CargoToBeMoved->getCargoID() << endl;}
	
	

}

//these functions are for moving items from a list to another 

//void Company::MoveToOtherList(LinkedQueue<Cargo*> CameFromHere , PriorityQueueArr<Cargo*> GoingThere) {
//	Cargo* Thecargo;
//	CameFromHere.peek(Thecargo);
//	if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//		CameFromHere.dequeue(Thecargo);
//		GoingThere.insert(Thecargo , 1); //this number here shall be replaced with the function that gets loadtimes
//	}
//}
//
//void Company::MoveToOtherList(PriorityQueueArr<Cargo*> CameFromHere, PriorityQueueArr<Cargo*> GoingThere) {
//	Cargo* Thecargo;
//	CameFromHere.peek(Thecargo);
//	if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//		CameFromHere.Pop(Thecargo);
//		GoingThere.insert(Thecargo, 1); //this number here shall be replaced with the function that gets loadtimes
//	}
//}
//
////this function is for moving from linked list to a queue it needs to be revised
//void Company::MoveToOtherList(LinkedList<Cargo*> CameFromHere, LinkedQueue<Cargo*> GoingThere) {
//	Cargo* Thecargo;
//	Thecargo = CameFromHere.getHead();
//	if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//		Thecargo = CameFromHere.removeFirstelement();
//		GoingThere.enqueue(Thecargo); 
//	}
//}
//
//void Company::MoveToOtherList(PriorityQueueArr<Cargo*> CameFromHere, PriorityQueueArr<Cargo*> GoingThere) {
//	Cargo* Thecargo;
//	CameFromHere.peek(Thecargo);
//	if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//		CameFromHere.Pop(Thecargo);
//		GoingThere.insert(Thecargo, 1); //this number here shall be replaced with the function that gets loadtimes
//	}
//}
//
//
//void Company::MoveToOtherList(LinkedQueue<Cargo*> CameFromHere, LinkedQueue<Cargo*> GoingThere) {
//	Cargo* Thecargo;
//	CameFromHere.peek(Thecargo);
//	if (UniversalTime.CurrentDay >= Thecargo->getPrepDay() && UniversalTime.CurrentHour >= Thecargo->getPrepHour()) {
//		CameFromHere.dequeue(Thecargo);
//		GoingThere.insert(Thecargo, 1); //this number here shall be replaced with the function that gets loadtimes
//	}
//}






	//Funcitons needed:
	//printTime(hours,days);
	//PrintWaitingCargo(Linkedlist,LinkedQueue,PriortiyQueueArr);
	//PrintLoadingCargo(Linkedqueue,LinkedQueue,LinkedQueue);
	//PrintmovingCArgo(Linkedqueue,LinkedQueue,LinkedQueue);
	//PrintDeleiverdCargo(Linkedqueue,LinkedQueue,LinkedQueue);
	//PrintavailableTrucks(LinkedQeue,LinkedQueue,LinkedQueue);
	//There might be a better way to do this but i am not sure yet :(
	//we can also do it in a way where we add a fourth paramter to indicate the thing that should be before
	//the lists as they are only lists in the end so just to avoud repating ourselves



//implemenations of functions that do the ccheck then based on it it moves them or not 
//this code shall be continued but in phase 2
void Company::LoadCheck()
{
	//vip first then normal and special
	Truck* ThePTruck;
	int TC;
	if (AvailbleVipTrucks.getCount() > 0) {
		AvailbleVipTrucks.peek(ThePTruck);
		TC = ThePTruck->getTruckCapacity();
		//checking if there is cargo more than the truck capacity then it is loaded
		if (WatitingVipCargo.getCount() >= TC) {
			for (int i = 0; i < TC; i++) {
				//MoveToOtherList(WatitingVipCargo, LoadingVipCargo);
			}
			//MoveToOtherList(AvailbleVipTrucks, LoadingVipTrucks);
		}
	}
	else if (AvailbleNormalTrucks.getCount() > 0) {
		AvailbleNormalTrucks.peek(ThePTruck);
		TC = ThePTruck->getTruckCapacity();
	}
	else if (AvailbleSpecialTrucks.getCount() > 0) {

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


//UI UITest;
//UITest.StartInteractiveMode(getCurrentDay(), getCurrentHour(), WaitingSpecialCargo, WaitingNormalCargo, WaitingVIPCargo, AvailbleNormalTrucks,
	//AvailbleSpecialTrucks, AvailbleVipTrucks,
	//DeliveredSpecialCargo, DeliveredVipCargo, DeliveredNormalCargo);
