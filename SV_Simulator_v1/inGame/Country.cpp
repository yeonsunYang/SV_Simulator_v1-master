#include <iostream>
#include "Country.h"
#include "Industry.h"
using namespace std;

///<summary>
///#함수 역할 : 초기화 함수
///</summary>
void Country::init_Country(CountryCode _code, long long _gdp, float _taxRate, long long _population, long long _carbonEmission)
{
	industries = new Industry[INDUSTRY_NUM];
	
	//산업코드, 산업 1일 단위생산당gdp, 산업 1일 단위생산당 탄소배출량, 산업 종사자비율
	industries[Steel].init_Industry(Steel, 50000, 10, 0.1);
	
	this->countryCode = _code;
	this->gdp = _gdp; //달러($)단위
	this->taxRate = _taxRate;
	this->budget = (gdp*taxRate)/360; 
	this->population = _population;
	this->carbonEmission = _carbonEmission; //톤(t)단위
}
Country::~Country()
{
	delete[] industries;
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
///#함수 역할 : gdp 0으로 reset (년)
///</summary>
void Country::reset_annualGDP()
{
	this->gdp = 0;
}

///<summary>
///#함수 역할 : 산업과 생활 발생 탄소배출량 합산(일 단위 리셋)
///</summary>
void Country::add_totalCarbonEmission()
{
	this->carbonEmission = 0;
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		this->carbonEmission += this->industries[i].day_carbonPerProduce * this->industries[i].workingRate * this->population;
	}
}

///<summary>
///#함수 역할 : 월 탄소세 및 정책세금에 따른 예산 추가
///</summary>
void Country::add_monthTax()
{
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		//@ 월 단위 호출 주기를 갖지만 test에서는 하루 단위로 환산하므로 나누기 30수행했음.
		this->budget += (this->industries[i].taxIndex * this->industries[i].day_gdpPerProduce * 30 * industries[i].workingRate * this->population/30);
		// 월 추가 예산 += 산업 세금비율 * 일일 생산당 gdp * 30일 * 산업 종사자수
		//이 때 아직 정책에 의해 산업에 추가 부과된 탄소세 없으면 *0으로 추가 예산 할당 없음
		// 단 정책에 의한 탄소세 부과는 정책 실행 다음달부터 효력 발생하도록 알림문구 넣기
	}
	
}

///<summary>
///#함수 역할 : gdp에 세율을 적용하여 국가 예산을 할당하는 함수
///</summary>
void Country::calculator_budget()
{
	this->budget += (gdp * taxRate)/360; //@ 연 단위 호출 주기를 갖지만 test에서는 1일 주기로 환산했으므로 나누기 360
}


///<summary>
///#함수 역할 : 예산 사용 이벤트 발생 시 예산 갱신
///</summary>
void Country::use_budget(long long _use_budget)
{
	this->budget -= _use_budget;
}


void Country::printStatus()
{
	cout << "***CountryCode : " << countryCode << endl;//나라
	cout << "***population : " << population << " 명"<<endl; //인구수
	cout << "***GDP : $ " << gdp << endl; //국내총생산
	cout << "***taxRate : " << taxRate <<" % "<<endl;// 세율
	cout << "***budget: $ " << budget << endl; //국가 예산
	cout<<"***carbonEmission : " << carbonEmission<<" (t)"<<endl; //탄소배출량

}