#pragma once
class Cargo
{
private:
	int prepDay;
	int prepHour;
	//Load time is in hours
	int Load;
	int unload;
	enum eCargoType
	{
		vipCargo,
		specialCargo,
		NormalCargo
	};

	float deleiveryDistance;
	float cost;

};

