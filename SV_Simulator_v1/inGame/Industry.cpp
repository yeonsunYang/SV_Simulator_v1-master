#include "Industry.h"
#include <iostream>

void Industry::init_Industry(IndustryCode _code, long long _gdp, long long _carbon, float _workingRate)
{
	this->industryCode = _code;
	this->day_gdpPerProduce = _gdp;
	this->day_carbonPerProduce = _carbon;
	this->workingRate = _workingRate;
	this->taxIndex = 0; //산업 정책 시행 시 산업세 부과
}

///<summary>
///#함수역할 : 탄소배출량 변화
///</summary>
void Industry::change_carbonPerProduce(float _rateOfChange_carbon)
{
	// ex) 매개변수로 0.3이 들어온다면 일 탄소배출량이 30% 증가한다
	// ex) 매개변수로 -0.2가 들어온다면 일 탄소배출량이 20% 감소한다
	long long temp = this->day_carbonPerProduce * _rateOfChange_carbon;
	this->day_carbonPerProduce += temp;
}

///<summary>
///#함수역할 : 종사자비율 변화
///</summary>
void Industry::change_workingRate(float _rateOfChange_working)
{
	//이미 실수 형태이므로 %의 증감으로 식이 나타난다.
	// ex) 매개변수로 0.01이 들어온다면 종사자비율은 0.01 증가한다.
	this->workingRate += _rateOfChange_working;

	if (this->workingRate > 1)
	{
		this->workingRate = 1;
	} //종사자비율 100 초과일 경우 100으로 다시 조정
}

///<summary>
///#함수역할 : 세금지수 변화
///</summary>
void Industry::change_taxIndex(float _rateOfChange_tax)
{
	//이미 실수 형태이므로 %의 증감으로 식이 나타난다.
	// ex) 매개변수로 0.01이 들어온다면 세금비율은 0.01 증가한다.
	this->taxIndex += _rateOfChange_tax;
}
