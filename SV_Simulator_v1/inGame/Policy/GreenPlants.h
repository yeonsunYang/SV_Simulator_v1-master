#pragma once
#include "Plants.h"

class GreenPlantsInfo : public Plants
{
public:
	// 재생에너지발전소의 비용 / 반환금 / 공급량 / 탄소배출량
	GreenPlantsInfo() : Plants(15, 5, 60, 0) {}
};