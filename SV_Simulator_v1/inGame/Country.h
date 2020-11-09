#pragma once
#include <string>
class Industry;

class Country
{
	friend World;
private:
	std::string name; //국가명
	long long budget; //국가 보유예산
	long long gdp; //국가 gdp
	long long population; //국가 인구수
	long carbonEmission; //국가 탄소배출량
	long carbonAbsorbing; //국가 탄소흡수량
	Industry* industry; //국가 산업부문 포인터
	float taxRate; //국가 세율

public:
/*#####################################
1. 초기화 되어야 하는 부분
	# 생성자
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

};