#pragma once
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
	enum class eCargoType    //Should be moved to smth like defs.
	{
		VIPCargo,
		specialCargo,
		normalCargo
	};
	eCargoType cargoType;

	double deleiveryDistance;
	double Cost;

	int maxW;

public:
	Cargo();
	Cargo(eCargoType TYP, int ETD, int ETH, int ID, double DIST, int LT, double cost);
	bool isWaiting()const;
	bool waitedForMax();

	//bool operator> (Cargo& C_cw)const;

	void setPrepDay(int pd);
	void setPrepHour(int ph);
	void setLoadTime(int lt);
	void setUnloadTime(int ut);
	void setCargoType(eCargoType t);
	void setDelieveryDistance(double dd);
	void setCost(double c);
	void setMaxW(int mw);
	void setCargoID(int id);

	int getPrepDay() const;
	int getPrepHour() const;
	int getLoadTime() const;
	int getunloadTime() const;
	eCargoType getCargoType() const { return cargoType; }
	double getDelieveryDistance() const;
	double getCost() const;
	int getCargoID() const;
	int getMaxW() const;
};

