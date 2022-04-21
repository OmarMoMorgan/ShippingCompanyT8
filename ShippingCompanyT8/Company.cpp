#include "Company.h"


void Company::LoadFile() {
	ifstream Line;
	Line.open("File needed.txt");
	if (!Line) {
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
	string id;
	int dist;
	int LT;
	int cost;

	//reading events here 
	for (int i = 0; i < NumberEvents; i++) {
		Line >> eventtype >> cargotype >> hourfromfile >> id >> dist >> LT >> cost;
		//you should instantiate the stuff needed here ie event type so a constructor with the data shall be ready
		maxid = id;
	}

	Line.close();	
}



//----------------------------------------------

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



//---------------------------------------------------------
void Company::SimTest() {
	//call print current time funciton here to print the current hour 
	//you should think about hving a funciton in the event class wwhere it associates the lists needed
	//instead of passing them each time to the function
	//To avoid reading this code look at the last commented part to get function needed exactly
	
	//Time ActualTime;
	// Time LAstAction;
	// LoadFile();
	// for (int i = 0;i<EventsList.getLength();i++){
	// ActualTime.IncTime(5);
	// UIController.printTime(ActualTime.CurrentDay,ActualTime.CurrentHour);
	// UIController.printLists();
	//while(TAtualime.hours >= EventsList.peek().gethour() && ActualTime.day >= EventsList.peek().getDay()){
	// Event ItemExectution = EventsList.enque();
	// ItemExecution.ExecuteAction();
	// }
	// if(WaitingNormalCargo.getsize() >= AvailableNormalTrucks.getCapacity()){
	// if(ActualTime.hours >= Lastaction + WaitingNormalCargo.peek().LoadTime()){
	// LoadingNormalCargo.queue(WaitingNormalCargo.head());
	// 
	// WaitingNormalCargo.delete(0);}
	// 
	// }
	// }
	//
	//

	Event* Eventhappening;
	while (EventsList.getCount() > 0 && DeliveredCargo.getCount() == stoi(maxid)) {
		UniversalTime.MoveOneunit();
		EventsList.peek(Eventhappening);
		//if (UniversalTime.CurrentDay >= Eventhappening.getTime() && UniversalTime.CurrentHour >= Eventhappening.getTime()) { EventsList.dequeue(Eventhappening); }
		//PrepareEvent *eve = dynmaic_cast<PrepareEvent*>(Eventhappening);
		//if(eve){
	//
	//}
	}


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
}


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
				MoveToOtherList(WatitingVipCargo, LoadingVipCargo);
			}
			MoveToOtherList(AvailbleVipTrucks, LoadingVipTrucks);
		}
	}
	else if (AvailbleNormalTrucks.getCount() > 0) {
		AvailbleNormalTrucks.peek(ThePTruck);
		TC = ThePTruck->getTruckCapacity();
	}
	else if (AvailbleSpecialTrucks.getCount() > 0) {

	}
}

