#pragma once
#include <string>
#include "CountryCode.h"
#include "IndustryCode.h"
#define INDUSTRY_NUM 1
class Industry;

class Country
{
private:
	friend class World;

	CountryCode countryCode; //국가코드
	long long budget; //국가 보유예산
	long long gdp; //국가 gdp
	long long population; //국가 인구수
	long long carbonEmission; //국가 탄소배출량
	Industry* industries; //국가 산업부문 포인터
	float taxRate; //국가 세율

public:
/*#####################################
1. 초기화 되어야 하는 부분
	# 초기화 함수 (!= 생성자 함수)
		-국가코드 초기화
		-국가보유예산 초기화 (2020기준-달러)
		-국가 GDP초기화 (2020기준-달러)
		-국가 탄소배출량 (2020기준)
		-국가 산업 생성
		-국가 세율 (2020기준)

2. 주기 별로 계산이 필요한 함수
	<day>
	# 산업에서 발생한 국가 총 GDP누적
	# 산업과 생활에서 발생한 탄소배출량 총합(일 단위로 리셋)

	<month>
	# 세금에 따른 예산 추가

	<year>
	# 1년 예산 책정
	# 1년 단위로 GDP 0으로 갱신

3. 이벤트 함수
	# 예산 변화되는 이벤트 시 호출 (갱신)

#########################################*/
	///<summary>
	///#함수 역할 : 초기화 함수
	///</summary>
	void init_Country(CountryCode _code, long long _gdp, float _taxRate, long long _population, long long _carbonEmission);


	///<summary>
	///#함수 역할 : 산업발생 국가 총 gdp 누적 (일)
	///</summary>
	void add_totalGDP();

///<summary>
///#함수 역할 : gdp 0으로 reset (년)
///</summary>
	void reset_annualGDP();


	///<summary>
	///#함수 역할 : 산업과 생활 발생 탄소배출량 합산(일-리셋)
	///</summary>
	void add_totalCarbonEmission();

	///<summary>
	///#함수 역할 : 월 탄소세 및 정책세금에 따른 예산 추가 (월)
	///</summary>
	void add_monthTax();

	///<summary>
	///#함수 역할 : gdp에 세율을 적용하여 1년 국가 예산을 할당하는 함수 (년)
	///</summary>
	void calculator_budget();

	///<summary>
	///#함수 역할 : 예산 사용 이벤트 발생 시 예산 갱신 (이벤트)
	///</summary>
	void use_budget(long long _use_budget);


	///<summary>
	///#함수 역할 : 디버깅 용 테스트 함수
	///</summary>
	void printStatus();
	
};