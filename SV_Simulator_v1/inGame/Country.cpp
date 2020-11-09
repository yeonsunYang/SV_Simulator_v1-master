#include "Country.h"
#include "Industry.h"
///<summary>
///#함수 역할 : 초기화 함수
///</summary>
void Country::init_Country(CountryCode c, int _industryNum)
{
	this->industryNum = _industryNum;
	industries = new Industry[industryNum];
	for (int i = 0; i < industryNum; i++)
	{
		//this->industries[i].init(); //init할 것임.
	}
	this->name = c;
	this->gdp = 
}

///<summary>
///#함수 역할 : gdp에 세율을 적용하여 국가 예산을 할당하는 함수
///</summary>
void calculator_budget();

///<summary>
///#함수 역할 : 탄소배출량 증감 함수
///</summary>
void renew_carbonEmission(long margin_carbonEmission);

///<summary>
///#함수 역할 : 탄소흡수량 증감 함수
///</summary>
void renew_carbonAbsorbing(long margin_carbonAbsorbing);