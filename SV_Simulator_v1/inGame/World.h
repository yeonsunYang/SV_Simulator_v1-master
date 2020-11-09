#pragma once
#include <string>

class Country;

class World
{
private:
	Country* countries; //전세계 모든 국가 포인터
	float worldTemperature; //전세계 평균온도
	long worldCarbonEmission; //전세계 탄소배출량
	long long worldPopulation; //전세계 인구수
	long worldCarbonAbsorbing; //전세계 탄소흡수량
	float worldCarbonPPM; //전세계 평균탄소농도(ppm)
	
public:
	/*#####################################
	1. 초기화 되어야 하는 부분
		# 생성자 
			-국가 생성
			-평균 온도 초기화 
			-탄소배출량 초기화
			-인구수 초기화 
			-탄소흡수량 초기화
			-탄소농도초기화
	
	2. 주기 별로 계산이 필요한 함수
		# 전세계 평균온도 계산 (탄소 농도 필요)
		# 탄소농도계산 (탄소배출량과 흡수량 필요)
		# 전세계 탄소배출량 합산
		# 전세계 탄소흡수량 합산
	
	3. 이벤트 함수
		# 탄소배출량 변화되는 이벤트 시 호출 (갱신)
			- 농도 다시 계산 (?)
			- 온도 다시 계산 (?) 그냥 주기때만 다시 계산해도 충분하지 않을까??
		# 탄소흡수량 변화되는 이벤트 시 호출 (갱신)
		
	#########################################*/
};