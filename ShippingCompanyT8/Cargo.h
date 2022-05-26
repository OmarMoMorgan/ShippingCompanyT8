#pragma once
//for the time being there will be no enums as it is hard to pass them around
//1 will be for normal
//2will be for special
//3 will be for vip
//enum  eCargoType    //Should be moved to smth like defs.
//{
//	VIPCargo,
//	specialCargo,
//	normalCargo
//};
//ooooooos
class Cargo
{
private:
	int curDay;  //current, to be removed with in the main
	int curHour;
	int prepDay;
	int prepHour;
	int cargoID; //Sequence from the input
	//Load time is in hours
	int loadTime;
	int unloadTime;

	//eCargoType cargoType;

	int movetime;
	double deleiveryDistance;
	double Cost;

	int maxW;

	//this is the type of the cargo might be reomved later
	int CarTyp;

public:
	Cargo();
	Cargo(int icomingCargoType, /*int ETD, int ETH,*/ int ID, double DIST, int LT, double cost);
	bool isWaiting()const;
	bool waitedForMax();

	//bool operator> (Cargo& C_cw)const;

	/*void setPrepDay(int pd);
	void setPrepHour(int ph);*/
	void setLoadTime(int lt);
	void setUnloadTime(int ut);
	//void setCargoType(eCargoType t);
	void setCargoType(int t);
	void setDelieveryDistance(double dd);
	void setCost(double c);
	void setMaxW(int mw);
	void setCargoID(int id);
	void setMovetime(int);

	/*int getPrepDay() const;
	int getPrepHour() const;*/
	int getMoveTime() const;
	int getLoadTime() const;
	int getunloadTime() const;
	int getCDT(int truckspeed) const; /// I added getmovetime func so it doesnot take it as a parameter but we should setmovetime for all cargos in same truck in the main
	//eCargoType getCargoType() const { return cargoType; }
	int getCargoType() const { return CarTyp; }
	double getDelieveryDistance() const;
	double getCost() const;
	int getCargoID() const;
	int getMaxW() const;
	int getWaitTime() const;
	int getVIPPriority() const;
};

