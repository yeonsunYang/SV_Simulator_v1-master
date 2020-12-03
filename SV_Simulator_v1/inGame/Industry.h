#pragma once
#include "IndustryCode.h"

class Industry
{
	friend class Country;
	friend class IndustryPolicy;
	Industry();

private:

	IndustryCode industryCode; //산업 코드
	int day_gdpPerProduce; //단위생산당 1일 gdp로, 종사자수* gpdPerProduce = industry GDP
	int day_carbonPerProduce; //단위생산당 탄소배출량
	int day_energyPerProduce; //단위생산당 에너지사용량
	float taxIndex;//세금지수
	float workingRate; //종사자 비율

public:
	/*#####################################
	1. 초기화 되어야 하는 부분
		# 초기화 함수 (!= 생성자 함수)
			- 산업 코드 (건드릴 일 없는 변수)
			- 단위생산당 gdp (건드릴 일 없는 변수)
			- 단위생산당 탄소배출량
			- 단위생산당 에너지사용량
			- 종사자 비율
			- 산업에 부과된 세금지수 0 초기화

	#########################################*/

	///<summary>
	///#함수역할 : 초기화 함수
	///</summary>
	void init_Industry(IndustryCode _code, int _gdp, int _carbon, int _energy, float _workingRate);

};