#pragma once
#include "IndustryCode.h"

class Industry
{
	friend class Country;
	friend class IndustryPolicy;
private:

	IndustryCode industryCode; //산업 코드
	long long day_gdpPerProduce; //단위생산당 1일 gdp로, 종사자수* gpdPerProduce = industry GDP
	long long day_carbonPerProduce; //단위생산당 탄소배출량
	float taxIndex;//세금지수
	float workingRate; //종사자 비율

public:
/*#####################################
1. 초기화 되어야 하는 부분
	# 초기화 함수 (!= 생성자 함수)
		- 산업 코드 (건드릴 일 없는 변수)
		- 단위생산당 gdp (건드릴 일 없는 변수)
		- 단위생산당 탄소배출량
		- 종사자 비율
		- 산업에 부과된 세금지수

2. 이벤트 함수
	# 탄소배출량 변화되는 이벤트 시 호출 (갱신)
	# 종사자 비율 변화되는 이벤트 시 호출 (갱신)
	# 세금 지수 변화되는 이벤트 시 호출 (갱신)

#########################################*/

	///<summary>
	///#함수역할 : 초기화 함수
	///</summary>
	void init_Industry(IndustryCode _code, long long _gdp, long long _carbon, float _workingRate);
	
	///<summary>
	///#함수역할 : 탄소배출량 변화
	///</summary>
	void change_carbonPerProduce(float _rateOfChange_carbon);

	///<summary>
	///#함수역할 : 종사자비율 변화
	///</summary>
	void change_workingRate(float _rateOfChange_working);

	///<summary>
	///#함수역할 : 세금지수 변화
	///</summary>
	void change_taxIndex(float _rateOfChange_tax);

};