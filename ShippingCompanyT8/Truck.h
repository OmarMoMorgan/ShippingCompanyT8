#pragma once
class Truck
{
private:
	enum eTruckType
	{
		VipTruck,
		SpecialTruck,
		NormalTruck
	};

	int truckCapacity;
	int maintenceTime;
	//Number of journeys before the truck needs to be checked
	int breakdownNum;

	float speed;
	float deleieryInterval;
};

