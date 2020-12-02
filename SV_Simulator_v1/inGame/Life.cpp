#include "Life.h"
#include <iostream>

///<summary>
///#함수역할 : 초기화 함수
///</summary>
void Life::init_Life(float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson)
{
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
	this->carPerPerson = _carPerPerson;
	this->ecocarRatio = _ecocarRatio;
	this->houses = _houses;
	this->greenhouses = _greenhouses;
	this->sunhouses = _sunhouses;
	this->carbonPerHouse = 10;
	this->carbonPerCar = 10;
	this->carbonPerPerson = _carbonPerPerson;
	this->taxHouse = 0;
	this->taxLife = 0;
	this->taxTransport = 0;
	this->day_energyPerHouse = 500;
	this->day_energyPerPerson = _day_energyPerPerson;

}

