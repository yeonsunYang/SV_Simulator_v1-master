#include "World.h"
#include "Country.h"
#include <iostream>
using namespace std;
///<summary>
	///#함수 역할 : 멤버변수들을 초기화시켜주는 생성자 함수 
	///#매개변수 countiryNum : 생성할 국가 개수
	///</summary>
World::World()
{
	/*
	(1)국가 생성
	(2)초기평균온도 값 저장(이를 위해 산림면적합산, 흡수량계산, 배출량계산, 농도계산)
	(3)초기작물생산량 값 저장(이를 위해 전세계 작물생산량 합산)
	(4)재난발생확률 초기화
	*/

	//(1)
	countries = new Country[COUNTRY_NUM];

	/*init_Country(CountryCode _code, long long _budget, float _taxRate, long long _population, int _forest, float _refugeeRate, long long _food, float _removeForest,
	float workingRate_st, float workingRate_oil, float workingRate_sv, float workingRate_mf, float workingRate_ag,
		float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson,
		int _firePlants, int _greenPlants)*/

	countries[South_Korea].init_Country(South_Korea, 16190000, 0.3, 51640000, 411290, 0.02, 50000000, 0.03, 0.1, 0.05, 0.2, 0.1, 0.01, 1.2, 0.01, 5000000, 0.01, 0.09, 15, 15, 5, 1);
	countries[United_States_of_America].init_Country(United_States_of_America, 205400000, 0.2, 328200000, 5269520, 0.08, 120000000, 0.06, 0.12, 0.09, 0.3, 0.06, 0.07, 1.8, 0.05, 12000000, 0.1, 0.12, 30, 30, 10, 5);

	//(2)
	total_ForestOfCountries();
	total_CarbonAbsorbedOfCountries();
	total_CarbonEmissionOfCountries();
	calculator_worldCarbonPPM();
	calculator_worldTemperature();
	this->defaultWorldTemperature = this->worldTemperature;

	//(3)
	total_FoodOfCountries();
	this->defaultWorldFood = this->worldFood;

	//(4)
	this->disasterProbability = 0.01;
}


///<summary>
///#함수 역할 : 모든 국가의 탄소배출량을 합산하는 함수 (1일 단위로 갱신)
///</summary>
void World::total_CarbonEmissionOfCountries()
{
	this->worldCarbonEmission = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldCarbonEmission += this->countries[i].carbonEmission;
	}
}


///<summary>
///#함수 역할 : 모든 국가의 산림면적을 합산하는 함수
///</summary>
void World::total_ForestOfCountries()
{
	this->worldForest = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldForest += this->countries[i].countryForest;
	}
}


///<summary>
///#함수 역할 : 모든 국가의 탄소흡수량을 합산하는 함수
///</summary>
void World::total_CarbonAbsorbedOfCountries()
{
	this->worldCarbonAbsorbed = (long long)(this->worldForest * 0.001);
}

///<summary>
///#함수 역할 : 모든 국가의 인구수를 합산하는 함수
///</summary>
void World::total_PopulationOfCountries()
{
	this->worldPopulation = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldPopulation += this->countries[i].population;
	}
}

///<summary>
///#함수 역할 : 모든 국가의 난민수를 합산하는 함수
///</summary>
void World::total_RefugeesOfCountries()
{
	this->worldRefugees = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldRefugees += this->countries[i].refugeeRate * this->countries[i].population;
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
	this->worldCarbonPPM = 0.001 * (this->worldCarbonEmission - this->worldCarbonAbsorbed);
}

///<summary>
///#함수 역할 : 평균온도의 임계점을 검사하는 함수
///</summary>
void World::check_worldTemperature()
{
	/*
	(1)초기 온도에서 현재 온도의 증가량이 임계점을 넘었는지 검사
	(2)넘었다면, 재난발생확률 증가하며 모든 국가의 작물생산량이 감소
	(3)모든 국가의 인식률 증가
	(4)초기온도 갱신
	*/

	if ((this->worldTemperature - this->defaultWorldTemperature) >= 0.1)
	{
		//초기 온도에서 0.1도 증가했다면, 
		this->disasterProbability += 0.05;
		for (int i = 0; i < COUNTRY_NUM; i++)
		{
			this->countries[i].recognitionRate += 0.08; //인식률 증가
			this->countries[i].food -= (long long)(this->countries[i].food * 0.1);//식량감소
		}
	}
	this->defaultWorldTemperature += 0.1;
}

///<summary>
///#함수 역할 : 모든 국가의 작물생산량을 합산하는 함수
///</summary>
void World::total_FoodOfCountries()
{
	this->worldFood = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldFood += this->countries[i].food;
	}
}

///<summary>
///#함수 역할 : 작물생산량의 임계점을 검사하는 함수
///</summary>
void World::check_worldFood()
{
	/*
	(1)초기 작물생산량에서 현재 작물생산량이 임계점 넘었는지 검사
	(2)넘었다면, 모든 국가의 사망자수와 기후난민수 증가
	(3)모든 국가의 인식률 증가
	(4)초기 작물생산량 갱신
	*/

	if ((this->defaultWorldFood - this->worldFood) >= 50000000)
	{
		//임계점 넘었다면
		for (int i = 0; i < COUNTRY_NUM; i++)
		{
			this->countries[i].recognitionRate += 0.1; //인식률 증가
			this->countries[i].deadRate += 0.05; //사망자 비율 증가
			this->countries[i].refugeeRate += 0.08; //난민 비율 증가
		}
	}
	this->defaultWorldFood -= 50000000;
}

///<summary>
///#함수 역할 : 확률에 따라 재난이 발생하는 함수
///</summary>
void World::random_disaster()
{
	bool disaster[100] = { false };
	int probability = (int)(this->disasterProbability * 100);
	for (int i = 0; i < probability; i++)
	{
		disaster[i] = true;
	} //100일 중 재난이 발생할 확률의 날만큼 true로 변환

	srand(time(0));
	int temp;
	int rn;
	for (int i = 0; i < 99; i++)
	{
		rn = rand() % (100 - i) + i; //i부터 99사이의 임의의 정수 생성
		temp = disaster[i];
		disaster[i] = disaster[rn];
		disaster[rn] = temp; //랜덤하게 뽑은 index와 i번째 index 스왑.
	}//100개의 배열 셔플 알고리즘.

	int select_oneDay = rand() % 100; //재난발생확률에 맞게 랜덤으로 추출했을 때

	if (disaster[select_oneDay] == true)
	{
		//재난발생 (기후난민 수와 사망자 수 증가, 작물생산량 감소)
		int randomCountry = rand() % COUNTRY_NUM; //발생국 랜덤하게 선택
		float deadRate = (rand() % 6) / 100; //사망자 비율 6%안에서 랜덤하게
		float refugeeRate = (rand() % 12) / 100; //난민 비율 12% 안에서 랜덤하게

		this->countries[randomCountry].refugeeRate += refugeeRate; //난민 증가
		this->countries[randomCountry].deadRate += deadRate; //사망자수 증가
		this->countries[randomCountry].food -= (long long)(this->countries[randomCountry].food * 0.08);//식량감소
		this->countries[randomCountry].recognitionRate += (refugeeRate); //인식률 증가

	}
}


///<summary>
///#함수 역할 : 디버깅 용 테스트 함수
///</summary>
void World::printStatus()
{
	cout << "countryNum: " << COUNTRY_NUM << endl; // (+)추가변수 : 국가 개수
	cout << "worldTemperature: " << worldTemperature << endl; //전세계 평균온도
	cout << "worldCarbonEmission: " << worldCarbonEmission << endl; //전세계 탄소배출량
	cout << "worldPopulation: " << worldPopulation << endl; //전세계 인구수
	cout << "worldCarbonPPM: " << worldCarbonPPM << endl; //전세계 평균탄소농도(ppm)

}


///<summary>
///#함수 역할 : 소멸자 함수 
///</summary>
World::~World()
{
	delete[] countries;
}

