#include "Energy.h"
#include <iostream>


///<summary>
///#함수역할 : 초기화 함수
///</summary>
void Energy::init_Energy(int _firePlants, int _greenPlants)
{
	/*
	초기화 되어야 하는 부분
		- 총 발전소 개수
		- 신재생에너지 발전소 개수
		- 석탄화력발전소 개수
		- 발전소 당 생산하는 에너지양
		- 석탄화력발전소 탄소배출량
	*/
	this->firePowerPlants = _firePlants;
	this->greenPowerPlants = _greenPlants;
	this->totalPowerPlants = (_firePlants + _greenPlants);
	this->produce = 1000000;
	this->carbonPerProduce = 10000;
}
