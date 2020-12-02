#pragma once
#include <string>
#include "CountryCode.h"
#include "IndustryCode.h"
#define INDUSTRY_NUM 5
class Industry;
class Energy;
class Life;

class Country
{
private:
	friend class World;
	friend class IndustryPolicy;

	CountryCode countryCode; //국가코드
	long long budget; //국가 보유예산
	long long gdp; //국가 gdp
	long long population; //국가 인구수
	long long defaultPopulation; //국가 초기 인구수
	long long carbonEmission; //국가 탄소배출량
	int countryForest; //국가 산림 면적
	Industry* industries; //국가 산업부문 포인터
	Energy energies; //국가 에너지부문 
	Life life; //국가 생활부문 
	float taxRate; //국가 세율
	float supportRate; //지지도
	float recognitionRate; //인식률
	float refugeeRate; //국가 기후난민 비율
	float deadRate; //국가 사망자 비율
	long long food; //작물생산량 (몇명 분량인지)
	float removeForest; //벌목률
	int industryEnergy; //산업에서 필요로 하는 에너지양(일일)
	int lifeEnergy; //생활에서 필요로 하는 에너지양(일일)
	int total_needEnergy; //총 필요로 하는 에너지양(일일)

public:
	/*#####################################
	1. 초기화 되어야 하는 부분
		# 초기화 함수 (!= 생성자 함수)
			-국가코드 초기화
			-보유예산 초기화
			-초기인구수 초기화
			-산림면적 초기화
			-산업 초기화
			-에너지 초기화
			-생활 초기화
			-국가 세율 초기화
			-지지도 10 초기화
			-인식률 10 초기화
			-기후난민비율 5 초기화
			-사망자 0 초기화
			-작물생산량 인구수 만큼 초기화
			-벌목률 5 초기화

	2. 주기 별로 계산이 필요한 함수
		<day>
		# 산업에서 발생한 국가 총 GDP누적
		# 산업과 생활에서 발생한 탄소배출량 총합(일 단위로 리셋)
		# 국가 인구수 계산 (사망자 반영하여)
		# 산업에서 필요로 하는 에너지양 계산
		# 생활에서 필요로 하는 에너지양 계산
		# 총 필요한 에너지양 계산

		<month>
		# 세금에 따른 예산 추가
		# 벌목에 따른 산림량 변화

		<year>
		# 1년 예산 책정
		# 1년 단위로 GDP 0으로 갱신

	#########################################*/
	///<summary>
	///#함수 역할 : 초기화 함수
	///</summary>
	void init_Country(CountryCode _code, long long _budget, float _taxRate, long long _population, int _forest, float _refugeeRate, long long _food, float _removeForest,
		float workingRate_st, float workingRate_oil, float workingRate_sv, float workingRate_mf, float workingRate_ag,
		float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson,
		int _firePlants, int _greenPlants);


	///<summary>
	///#함수 역할 : 산업발생 국가 총 gdp 누적 (일)
	///</summary>
	void add_totalGDP();


	///<summary>
	///#함수 역할 : 국가 총 인구수 합산 (일-사망자반영)
	///</summary>
	void add_totalPopulation();


	///<summary>
	///#함수 역할 : 산업+생활+에너지 발생 탄소배출량 합산(일-리셋)
	///</summary>
	void add_totalCarbonEmission();



	///<summary>
	///#함수역할 : 산업에서 필요로 하는 에너지양 계산
	///</summary>
	void total_industryEnergy();


	///<summary>
	///#함수역할 : 생활에서 필요로 하는 에너지양 계산
	///</summary>
	void total_lifeEnergy();


	///<summary>
	///#함수역할 : 총 필요로 하는 에너지양 계산
	///</summary>
	void total_needEnergy();

	///<summary>
	///#함수 역할 : 월 탄소세 및 정책세금에 따른 예산 추가 (월)
	///</summary>
	void add_monthTax();


	///<summary>
	///#함수 역할 : 벌목에 따른 산림량 변화 (월)
	///</summary>
	void calculator_monthForest();


	///<summary>
	///#함수 역할 : gdp 0으로 reset (년)
	///</summary>
	void reset_annualGDP();


	///<summary>
	///#함수 역할 : gdp에 세율을 적용하여 1년 국가 예산을 할당하는 함수 (년)
	///</summary>
	void calculator_budget();


	///<summary>
	///#함수 역할 : 디버깅 용 테스트 함수
	///</summary>
	void printStatus();

};