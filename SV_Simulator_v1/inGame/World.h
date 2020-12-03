#pragma once
#include <string>
#include <time.h>
#include <stdlib.h>
#define COUNTRY_NUM 175
//#define COUNTRY_NUM 175

class Country;

class World
{
	friend class Game;
private:
	Country* countries[COUNTRY_NUM]; //전세계 모든 국가 포인터
	float worldTemperature; //전세계 평균온도
	float worldCarbonPPM; //전세계 평균탄소농도(ppm)
	long long worldCarbonEmission; //전세계 탄소배출량(일 단위)
	long long worldCarbonAbsorbed; //전세계 탄소흡수량(일 단위)
	long long worldForest; //전세계 산림면적
	long long worldPopulation; //전세계 인구 수
	long long worldDead; //전세계 사망자 수
	long long worldRefugees; //전세계 기후난민 수
	long long worldFood; //전세계 작물생산량
	float disasterProbability; //재난발생확률
	long long foodCriticalPoint; //작물생산량 임계점
	long long defaultWorldFood; //초기 작물생산량 값 (임계점 비교 위한 변수)
	float tempCriticalPoint; //평균온도 임계점
	float defaultWorldTemperature; //초기 평균온도 (임계점 비교 위한 변수)

public:
	/*#####################################
	1. 초기화 되어야 하는 부분
		# 생성자
			-국가 생성
			-초기평균온도 값 저장(이를 위해 산림면적합산, 흡수량계산, 배출량계산, 농도계산)
			-초기작물생산량 값 저장(이를 위해 전세계 작물생산량 합산)
			-재난발생확률 초기화


	2. 주기 별로 계산이 필요한 함수
		<day>
		# 전세계 산림면적 합산
		# 전세계 탄소흡수량 계산
		# 전세계 탄소배출량 합산
		# 탄소 농도 계산
		# 전세계 평균온도 계산
		# 평균온도 임계점 검사
		# 전세계 작물생산량 합산
		# 작물생산량 임계점 검사
		# 재난 발생
		# 전세계 인구수 합산
		# 전세계 난민수 합산

	#########################################*/

	///<summary>
	///#함수 역할 : 멤버변수들을 초기화시켜주는 생성자 함수 
	///#매개변수 countiryNum : 생성할 국가 개수
	///</summary>
	World();

	///<summary>
	///#함수 역할 : 모든 국가의 산림면적을 합산하는 함수
	///</summary>
	void total_ForestOfCountries();

	///<summary>
	///#함수 역할 : 모든 국가의 탄소배출량을 합산하는 함수
	///</summary>
	void total_CarbonEmissionOfCountries();

	///<summary>
	///#함수 역할 : 모든 국가의 탄소흡수량을 합산하는 함수
	///</summary>
	void total_CarbonAbsorbedOfCountries();

	///<summary>
	///#함수 역할 : 모든 국가의 인구수를 합산하는 함수
	///</summary>
	void total_PopulationOfCountries();

	///<summary>
	///#함수 역할 : 모든 국가의 난민수를 합산하는 함수
	///</summary>
	void total_RefugeesOfCountries();

	///<summary>
	///#함수 역할 : 세계 온도를 계산하는 함수
	///#w1 = 0.008984563 , b=12.366367558
	///</summary>
	void calculator_worldTemperature();

	///<summary>
	///#함수 역할 : 세계 탄소 농도를 계산하는 함수
	///#w1 = 1 b=0
	///</summary>
	void calculator_worldCarbonPPM();

	///<summary>
	///#함수 역할 : 평균온도의 임계점을 검사하는 함수
	///</summary>
	void check_worldTemperature();

	///<summary>
	///#함수 역할 : 모든 국가의 작물생산량을 합산하는 함수
	///</summary>
	void total_FoodOfCountries();

	///<summary>
	///#함수 역할 : 작물생산량의 임계점을 검사하는 함수
	///</summary>
	void check_worldFood();

	///<summary>
	///#함수 역할 : 확률에 따라 재난이 발생하는 함수
	///</summary>
	void random_disaster();

	///<summary>
	///#함수 역할 : 디버깅 용 테스트 함수
	///</summary>
	void printStatus();


	///<summary>
	///#함수 역할 : 소멸자 함수 
	///</summary>
	~World();
};