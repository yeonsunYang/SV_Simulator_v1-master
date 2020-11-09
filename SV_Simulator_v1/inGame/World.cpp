#include "World.h"
#include "Country.h"
///<summary>
	///#함수 역할 : 멤버변수들을 초기화시켜주는 생성자 함수 
	///#매개변수 countiryNum : 생성할 국가 개수
	///</summary>
World::World(int _countryNum)
{
	this->countryNum = _countryNum;
	countries = new Country[countryNum];
	
	//매개변수 : 국가코드 / 산업개수 / gdp / 세율 / 인구 수 / 탄소배출량 / 탄소흡수량
	countries[KOR].init_Country(KOR,1,1619000000000, 0.3, 51640000, 616096687, 0);
	countries[USA].init_Country(USA,1,20540000000000, 0.2, 328200000, 5269529513, 0);

	this->worldCarbonPPM = 411.29; //(2020년 9월 기준 농도)
	calculator_worldTemperature(); //초기화한 농도 기준으로 평균온도 적용
	total_CarbonEmissionOfCountries();//전세계 탄소배출량 합산값으로 초기화
	total_CarbonAbsorbingOfCountries(); //전세계 탄소흡수량 합산값으로 초기화
	total_PopulationOfCountries(); //전세계 인구수 합산값으로 초기화

}


///<summary>
///#함수 역할 : 모든 국가의 인구수를 합산하는 함수
///</summary>
void World::total_PopulationOfCountries()
{
	this->worldPopulation = 0;
	for (int i = 0; i < this->countryNum; i++)
	{
		this->worldPopulation += this->countries[i].population;
	}
}
///<summary>
///#함수 역할 : 모든 국가의 탄소배출량을 합산하는 함수
///</summary>
void World::total_CarbonEmissionOfCountries()
{
	this->worldCarbonEmission = 0;
	for (int i = 0; i < this->countryNum; i++)
	{
		this->worldCarbonEmission += this->countries[i].carbonEmission;
	}
}

///<summary>
///#함수 역할 : 모든 국가의 탄소흡수량을 합산하는 함수
///</summary>
void World::total_CarbonAbsorbingOfCountries()
{
	this->worldCarbonAbsorbing = 0;
	for (int i = 0; i < this->countryNum; i++)
	{
		this->worldCarbonAbsorbing += this->countries[i].carbonAbsorbing;
	}
}

///<summary>
///#함수 역할 : 세계 온도를 계산하는 함수
///#w1 = 0.008984563 , b=12.366367558
///</summary>
void World::calculator_worldTemperature()
{
	this->worldTemperature = 0.008984563 * this->worldCarbonPPM + 12.366367558;
}

///<summary>
///#함수 역할 : 세계 탄소 농도를 계산하는 함수
///#w1 = 1.2 b=0
///</summary>
void World::calculator_worldCarbonPPM()
{
	this->worldCarbonPPM = 1.2 * (this->worldCarbonEmission - this->worldCarbonAbsorbing);
}