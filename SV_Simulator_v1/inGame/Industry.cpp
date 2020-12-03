#include "Industry.h"
//#include <iostream>

Industry::Industry()
{

}

void Industry::init_Industry(IndustryCode _code, int _gdp, int _carbon, int _energy, float _workingRate)
{
	this->industryCode = _code;
	this->day_gdpPerProduce = _gdp;
	this->day_carbonPerProduce = _carbon;
	this->day_energyPerProduce = _energy;
	this->workingRate = _workingRate;
	this->taxIndex = 0; //산업 정책 시행 시 산업세 부과
}

