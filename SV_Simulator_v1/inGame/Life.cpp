#include "Life.h"

/*
1. 초기화 되어야 하는 부분

	- 자동차 소유 비율
	- 친환경 자동차 비율
	- 총 건물 개수
	- 그린 리모델링 비율
	- 태양광 패널 설치 비율
	- 건물 당 탄소배출량 초기화
	- 자동차 당 탄소배출량 초기화
	- 일상 인구 1명당 탄소배출량
	- 세금지수 모두 0으로 초기화
	- 건물 한 채당 에너지양 초기화
	- 1인당 일상 에너지양

	//@-초기화 라고 적힌 항목 이외는 모두 매개변수로 초기화 해주기
*/


// 운송부문 초기화
void Life::init_Life_Transport(float _carPerPerson, float _ecocarRatio)
{
	this->carPerPerson = _carPerPerson;
	this->ecocarRatio = _ecocarRatio;
	this->carbonPerCar = 10;
	this->taxTransport = 0;
}

// 주거부문 초기화
void Life::init_Life_House(long long _houses, float _greenhouses, float _sunhouses)
{
	this->houses = _houses;
	this->greenhouses = _greenhouses;
	this->sunhouses = _sunhouses;
	this->carbonPerHouse = 10;
	this->taxHouse = 0;
	this->day_energyPerHouse = 500;
}

// 국민 생활 부문 초기화
void Life::init_Life_Person(long long _carbonPerPerson, int _day_energyPerPerson)
{
	this->carbonPerPerson = _carbonPerPerson;
	this->taxLife = 0;
	this->day_energyPerPerson = _day_energyPerPerson;

}

