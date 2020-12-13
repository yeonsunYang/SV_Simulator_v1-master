#pragma once
#include "Plants.h"

class FirePlantsInfo : public Plants{
public:
	// 화력발전소의 비용 / 반환금 / 공급량 / 탄소배출량
	FirePlantsInfo() : Plants(10, 2, 100, 10) {};
};