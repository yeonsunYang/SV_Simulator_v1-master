#pragma once

class Energy
{
	friend class Country;
	friend class EnergyPolicy;
private:

	int totalPowerPlants; //총 발전소 개수
	int greenPowerPlants; //신재생에너지 발전소 개수
	int firePowerPlants; //석탄화력발전소 개수
	int produce; //발전소 개당 생산하는 에너지양(일일)
	long long carbonPerProduce; //석탄화력발전소 당 탄소배출량(일일)

public:
	/*#####################################
	1. 초기화 되어야 하는 부분
		# 초기화 함수 (!= 생성자 함수)
			-총 발전소 개수
			-신재생에너지 발전소 개수
			-석탄화력발전소 개수
			-발전소 당 생산하는 에너지양
			-석탄화력발전소 탄소배출량

	#########################################*/

	///<summary>
	///#함수역할 : 초기화 함수
	///</summary>
	void init_Energy(int _firePlants, int _greenPlants);

	int GetTotalPowerPlants() { return totalPowerPlants; } //총 발전소 개수
	int GetGreenPowerPlants() { return greenPowerPlants; } //신재생에너지 발전소 개수
	int GetFirePowerPlants() { return greenPowerPlants; } //석탄화력발전소 개수
	int GetProduce() { return produce; } //발전소 개당 생산하는 에너지양(일일)
	long long GetCarbonPerProduce() { return carbonPerProduce; } //석탄화력발전소 당 탄소배출량(일일)
};

