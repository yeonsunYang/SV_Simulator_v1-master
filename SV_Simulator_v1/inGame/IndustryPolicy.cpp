#include "IndustryPolicy.h"
#include <iostream>
using namespace std;

///<summary>
///#함수역할 : 생성자 함수
///</summary>
IndustryPolicy::IndustryPolicy(IndustryPolicyCode _pCode, IndustryCode _iCode, long long _needBudget, float _rateOfChange_tax, float _rateOfChange_working, float _rateOfChange_carbon)
{
	this->policyCode = _pCode;
	this->industryCode = _iCode;
	this->needBudget = _needBudget;
	this->rateOfChange_tax = _rateOfChange_tax;
	this->rateOfChange_working = _rateOfChange_working;
	this->rateOfChange_carbon = _rateOfChange_carbon;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		isAccept[i] = false;
	}
}

///<summary>
///#함수역할 : 정책 실행함수
///</summary>
void IndustryPolicy::enforce(Country country)
{
	isAccept[country.countryCode] = true; //해당 국가 어느 산업에 해당하는 본 정책 실행 true
	if (this->needBudget != 0)
	{
		enforce_budget(country);
	}
	if (this->rateOfChange_tax != 0)
	{
		enforce_tax(country);
	}
	if (this->rateOfChange_working != 0)
	{
		enforce_working(country);
	}
	if (this->rateOfChange_carbon != 0)
	{
		enforce_carbonEmission(country);
	}
}

///<summary>
///#함수역할 : 정책 실행함수 - 예산 수정
///</summary>
void IndustryPolicy::enforce_budget(Country country)
{
	if (country.budget < this->needBudget)
	{
		cout<<"예산이 부족합니다.\n";
	}
	else
	{
		country.use_budget(this->needBudget);
	}

}

///<summary>
///#함수역할 : 정책 실행함수 - 탄소배출량 수정
///</summary>
void IndustryPolicy::enforce_carbonEmission(Country country)
{
	//해당 국가 산업 포인터에서 탄소배출량 변화 함수 호출
	country.industries[this->industryCode].change_carbonPerProduce(this->rateOfChange_carbon);
}

///<summary>
///#함수역할 : 정책 실행함수 - 산업세율 수정
///</summary>
void IndustryPolicy::enforce_tax(Country country)
{
	//해당 국가 산업 포인터에서 세금지수 변화 함수 호출
	country.industries[this->industryCode].change_taxIndex(this->rateOfChange_tax);
}

///<summary>
///#함수역할 : 정책 실행함수 - 종사자비율 수정
///</summary>
void IndustryPolicy::enforce_working(Country country)
{
	//해당 국가 산업 포인터에서 종사자비율 변화 함수 호출
	country.industries[this->industryCode].change_workingRate(this->rateOfChange_working);
}