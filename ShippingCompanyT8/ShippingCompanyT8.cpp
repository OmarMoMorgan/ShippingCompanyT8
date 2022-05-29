// ShippingCompanyT8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "PriorirtyQueueArr.h"
#include "Company.h"
//#include "LinkedList.h"
int Truck::counter = 0;
int main()
{
   /* PriorityQueueArr<int> p1;
    p1.insert(5,2);
    p1.insert(7, 10);
    p1.insert(1, 3);
    p1.insert(4, 12);
    p1.Pop();

    //p1.printarr();*/
    Company c;
    c.Simulator();
    //c.Simulator();
    ////c.SimTest();
    //c.outputStatistics();
    //LinkedList<int> l;
   /* l.insertback(1);
    l.insertback(2);
    l.insertback(3);
    l.insertback(4);
    l.PrintList();*/
  //  Cargo * c1= new Cargo(1, 15, 300, 20, 16);
  //  Cargo* c4 = new Cargo(1, 18, 300, 20, 16);

  //  Cargo* c2 = new Cargo(2, 16, 300, 20, 16);
  //  Cargo* c3 = new Cargo(2, 17, 300, 20, 16);


  //  Truck* t1=new Truck( 1, 200, 20,3, 5);
  //  Truck* t2 = new Truck(2, 200, 20, 3, 5);
  //  cout << t1->getTrucID() << " " << t2->getTrucID();
  //  cout << t1->getListCount() << endl;
  //  t1->insertCargo(c1);
  //t1->insertCargo(c4);
  //cout << t1->getListCount() << endl;
  //cout << t1->DeleiverCargo()->getCargoID() << endl;
  //cout << t1->peekCargo()->getCargoID() << "hmm";
  //cout << t1->getListCount() << endl;


  //cout << t1->DeleiverCargo()->getCargoID();
  // /* t2->insertCargo(c2);
  //  t2->insertCargo(c3);*/
  //  PriorityQueueArr<Truck*> q;

//
//    q.insert(t1);
////q.insert(t2);
//q.printarrTruck();   //std::cout << "Hello World!\n";

  //  int p;
  //LinkedList<int> l;
  //  l.insertback(5);
  //  l.insertback(3);
  //  ////l.removeFelement(p);
  //  //

  //  l.insertback(2);
  //  l.removeFirstelement(p);
  //  l.PrintList();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
