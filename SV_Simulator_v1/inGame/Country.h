#pragma once
#include <string>
#include "CountryCode.h"
class Industry;

class Country
{
private:
	friend class World;

	CountryCode name; //국가명
	int industryNum; //(+)추가변수 : 산업 개수
	long long budget; //국가 보유예산
	long long gdp; //국가 gdp
	long long population; //국가 인구수
	long carbonEmission; //국가 탄소배출량
	long carbonAbsorbing; //국가 탄소흡수량
	Industry* industries; //국가 산업부문 포인터
	float taxRate; //국가 세율

public:
/*#####################################
1. 초기화 되어야 하는 부분
	# 초기화 함수 (!= 생성자 함수)
		-국가명 초기화
		-국가보유예산 초기화 (2020기준-달러)
		-국가 GDP초기화 (2020기준-달러)
		-국가 탄소배출량 (2020기준)
		-국가 탄소흡수량 (2020기준)
		-국가 산업 생성
		-국가 세율 (2020기준)

2. 주기 별로 계산이 필요한 함수
	# 1년 단위
		- 예산 세율에 따라 계산

3. 이벤트 함수
	# 탄소배출량 변화되는 이벤트 시 호출 (갱신)
	# 탄소흡수량 변화되는 이벤트 시 호출 (갱신)

#########################################*/
	///<summary>
	///#함수 역할 : 초기화 함수
	///</summary>
	void init_Country(CountryCode c, int _industryNum);

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
	
};