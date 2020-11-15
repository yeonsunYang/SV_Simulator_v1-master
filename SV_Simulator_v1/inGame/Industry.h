#pragma once

class Industry
{
	friend class Country;
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
		- 단위생산당 gdp
		- 단위생산당 탄소배출량
		- 종사자 비율
		- 산업에 부과된 세금지수

2. 이벤트 함수
	# 탄소배출량 변화되는 이벤트 시 호출 (갱신)
	# gdp 변화되는 이벤트 시 호출 (갱신)
	# 종사자 비율 변화되는 이벤트 시 호출 (갱신)
	# 세금 지수 변화되는 이벤트 시 호울 (갱신)

#########################################*/

	///<summary>
	///#함수역할 : 
	///</summary>
	void init_Industry();
	///<summary>
	///#함수역할 : 
	///</summary>
	void change_carbonPerProduce();
	void change_gdpPerProduce();
	void change_workingRate();
	void change_taxIndex();


};