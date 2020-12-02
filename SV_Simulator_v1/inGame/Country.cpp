#include <iostream>
#include "Country.h"
#include "Industry.h"
#include "Life.h"
#include "Energy.h"
using namespace std;

///<summary>
///#함수 역할 : 초기화 함수
///</summary>
void Country::init_Country(CountryCode _code, long long _budget, float _taxRate, long long _population, int _forest, float _refugeeRate, long long _food, float _removeForest,
	float workingRate_st, float workingRate_oil, float workingRate_sv, float workingRate_mf, float workingRate_ag,
	float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson,
	int _firePlants, int _greenPlants)
{
	this->countryCode = _code;
	this->gdp = 0; //달러($)단위
	this->taxRate = _taxRate;
	this->budget = _budget;
	this->defaultPopulation = _population;
	this->countryForest = _forest;
	this->supportRate = 0.1;
	this->recognitionRate = 0.1;
	this->refugeeRate = _refugeeRate;
	this->deadRate = 0;
	this->food = _food;
	this->removeForest = _removeForest;


	this->industries = new Industry[INDUSTRY_NUM];
	//산업코드, 산업 1일 단위생산당gdp, 산업 1일 단위생산당 탄소배출량, 산업 1일 단위생산당 에너지사용량, 산업 종사자비율
	//init_Industry(IndustryCode _code, int _gdp, int _carbon, int _energy, float _workingRate);

	industries[STEEL].init_Industry(STEEL, 50000, 10, 10, workingRate_st);
	industries[OIL].init_Industry(OIL, 50000, 10, 10, workingRate_oil);
	industries[SERVICE].init_Industry(SERVICE, 50000, 10, 10, workingRate_sv);
	industries[MANUFACTURING].init_Industry(MANUFACTURING, 50000, 10, 10, workingRate_mf);
	industries[AGRICULTURE].init_Industry(AGRICULTURE, 50000, 10, 10, workingRate_ag);
	//산업에서 국가별로 다른 것은 종사자비율 뿐. <- 종사자비율은 init_country에서 매개변수로 받기

	life.init_Life(_carPerPerson, _ecocarRatio, _houses, _greenhouses, _sunhouses, _carbonPerPerson, _day_energyPerPerson);
	energies.init_Energy(_firePlants, _greenPlants);
}

///<summary>
///#함수 역할 : 산업발생 국가 총 gdp 누적
///</summary>
void Country::add_totalGDP()
{
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		this->gdp += (this->industries[i].day_gdpPerProduce * this->industries[i].workingRate * this->population);
		//연간 총 gdp는 매일의 산업 gdp를 계속하여 합산해 나간다. 결국 1년 뒤에는 연 총 생산량.
	}
}


///<summary>
///#함수 역할 : 산업+생활+에너지 발생 탄소배출량 합산(일 단위 리셋)
///</summary>
void Country::add_totalCarbonEmission()
{
	this->carbonEmission = 0;
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{//산업 당 생산단위 당 일일탄소배출량 * 종사자 수
		this->carbonEmission += (long long)(this->industries[i].day_carbonPerProduce * this->industries[i].workingRate * this->population);
	}
	this->carbonEmission += (long long)(this->energies.carbonPerProduce * this->energies.firePowerPlants);
	//석탄화력발전소 개수* 발전소 개당 일일 탄소배출량
	this->carbonEmission += (long long)(this->life.carPerPerson * this->population * (1 - this->life.ecocarRatio) * this->life.carbonPerCar);
	//1명당 자동차 소유 비율*인구수*화석연료자동차비율*자동차 1대 당 일일탄소배출량
	this->carbonEmission += (long long)(this->life.houses * (1 - this->life.greenhouses) * (1 - this->life.sunhouses) * this->life.carbonPerHouse);
	//총 건물 개수*그린 리모델링과 태양광패널 미설치 건물 비율*건물 당 일일 탄소배출량
	this->carbonEmission += (long long)(this->life.houses * (1 - this->life.greenhouses) * (this->life.sunhouses) * this->life.carbonPerHouse * 0.65);
	//총 건물 개수*태양광패널 설치 건물 비율*건물 당 일일 탄소배출량*65%
	this->carbonEmission += (long long)(this->life.carbonPerPerson * this->population);
	//1인당 일상속 탄소배출량*인구수

}

///<summary>
///#함수 역할 : 국가 총 인구수 합산 (일-사망자반영)
///</summary>
void Country::add_totalPopulation()
{
	this->population = (long long)(this->defaultPopulation * (1 - this->deadRate));
}

///<summary>
///#함수역할 : 산업에서 필요로 하는 에너지양 계산
///</summary>
void Country::total_industryEnergy()
{
	this->industryEnergy = 0;

	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		this->industryEnergy += (int)(this->industries[i].day_energyPerProduce * this->industries[i].workingRate * this->population);
		//필요로 하는 에너지양 += 각 산업의 단위생산당 에너지사용량 * 종사자수
	}
}


///<summary>
///#함수역할 : 생활에서 필요로 하는 에너지양 계산
///</summary>
void Country::total_lifeEnergy()
{
	this->lifeEnergy = 0;

	this->lifeEnergy += (int)(this->life.day_energyPerHouse * this->life.houses * (1 - this->life.greenhouses) * (1 - this->life.sunghouses));
	//그린리모델링과 태양광 패널 설치 하지 않은 건물 수 * 건물 당 에너지소모양
	this->lifeEnergy += (int)(this->life.day_energyPerHouse * 0.65 * this->life.houses * (1 - this->life.greenhouses) * (this->life.sunhouses));
	//태양광 패널 설치한 건물 수 * 건물 당 에너지 소모양 65%
	this->lifeEnergy += (int)(this->life.day_energyPerPerson * this->population);
	//인구수 * 1인당 생활에 필요한 에너지양
}


///<summary>
///#함수역할 : 총 필요로 하는 에너지양 계산
///</summary>
void Country::total_needEnergy()
{
	this->total_needEnergy = (this->industryEnergy + this->lifeEnergy);
}


///<summary>
///#함수 역할 : 월 탄소세 및 정책세금에 따른 예산 추가
///</summary>
void Country::add_monthTax()
{
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		//@ 월 단위 호출 주기를 갖지만 test에서는 하루 단위로 환산하므로 나누기 30수행했음.
		this->budget += (long long)(this->industries[i].taxIndex * this->industries[i].day_gdpPerProduce * 30 * industries[i].workingRate * this->population);
		// 월 추가 예산 += 산업 세금비율 * 일일 생산당 gdp * 30일 * 산업 종사자수
		//이 때 아직 정책에 의해 산업에 추가 부과된 탄소세 없으면 *0으로 추가 예산 할당 없음
		// 단 정책에 의한 탄소세 부과는 정책 실행 다음달부터 효력 발생하도록 알림문구 넣기

		this->budget += (long long)(this->life.taxTransport * this->life.carPerPerson * (1 - this->life.ecocarRatio) * this->population);
		//석유에너지 자동차 대수만큼 교통 세금지수 부과
		this->budget += (long long)(this->life.taxHouse * this->life.houses * (1 - this->life.greenhouses) * (1 - this->life.sunhouses));
		//그린 리모델링도 안하고, 태양광 패널도 설치 안한 건물 수만큼 주거 세금지수 부과
		this->budget += (long long)(this->life.taxHouse * 0.65 * this->life.houses * (1 - this->life.greenhouses) * (this->life.sunhouses));
		//그린 리모델링은 안했지만, 태양광 패널은 설치한 건물에 주거 세금지수의 65%만 세금 부과
		this->budget += (long long)(this->life.taxLife * this->population);
		//생활에 부과된 세금지수를 전 국민에게 걷음.

		//@주의 사항 : industry의 세금지수는 float이지만, life의 세금지수는 달러 단위임에 주의하자.
		//(왜냐하면 industry는 산업발생 gdp라는 수치가 있기에 비율을 곱할 수 있지만, life는 그럴 수 없기 때문)

	}

}

///<summary>
///#함수 역할 : 벌목에 따른 산림량 변화 (월)
///</summary>
void Country::calculator_monthForest()
{
	this->countryForest = (int)(this->countryForest * (1 - this->removeForest));
}


///<summary>
///#함수 역할 : gdp에 세율을 적용하여 국가 예산을 할당하는 함수
///</summary>
void Country::calculator_budget()
{
	this->budget += (gdp * taxRate); //@ 연 단위 호출 주기를 갖지만 test에서는 1일 주기로 환산했으므로 나누기 360
}

///<summary>
///#함수 역할 : gdp 0으로 reset (년)
///</summary>
void Country::reset_annualGDP()
{
	this->gdp = 0;
}


void Country::printStatus()
{
	cout << "***CountryCode : " << countryCode << endl;//나라
	cout << "***population : " << population << " 명" << endl; //인구수
	cout << "***GDP : $ " << gdp << endl; //국내총생산
	cout << "***taxRate : " << taxRate << " % " << endl;// 세율
	cout << "***budget: $ " << budget << endl; //국가 예산
	cout << "***carbonEmission : " << carbonEmission << " (t)" << endl; //탄소배출량

}


///<summary>
///#함수 역할 : 소멸자 함수
///</summary>
Country::~Country()
{
	delete[] industries;
}