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
		
	}

	Line.close();	
}

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
