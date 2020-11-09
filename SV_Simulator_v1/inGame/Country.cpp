#include "Country.h"
#include "Industry.h"
///<summary>
///#함수 역할 : 초기화 함수
///</summary>
void Country::init_Country(CountryCode c, int _industryNum, long long _gdp, float _taxRate, long long _population, long long _carbonEmission, long long _carbonAbsorbing)
{
	this->industryNum = _industryNum;
	industries = new Industry[industryNum];
	
	//industries[Steel].init_Industry();
	
	this->name = c;
	this->gdp = _gdp; //달러($)단위
	this->taxRate = _taxRate;
	calculator_budget(); //초기화 gdp대비 초기화 세율로 예산 책정
	this->population = _population;
	this->carbonEmission = _carbonEmission; //톤(t)단위
	this->carbonAbsorbing = _carbonAbsorbing;
}

///<summary>
///#함수 역할 : gdp에 세율을 적용하여 국가 예산을 할당하는 함수
///</summary>
void Country::calculator_budget()
{
	this->budget += (gdp * taxRate)/365; //1일 주기로 환산한 식
}

///<summary>
///#함수 역할 : 탄소배출량 증감 함수
///</summary>
void Country::renew_carbonEmission(long margin_carbonEmission)
{
	this->carbonEmission += margin_carbonEmission;
}

///<summary>
///#함수 역할 : 탄소흡수량 증감 함수
///</summary>
void Country::renew_carbonAbsorbing(long margin_carbonAbsorbing)
{
	this->carbonAbsorbing += margin_carbonAbsorbing;
}

///<summary>
///#함수 역할 : 예산 증감 함수
///</summary>
void Country::renew_budget(long margin_budget)
{
	this->budget += margin_budget;
}