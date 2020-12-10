#include "Country.h"
#include <cmath>
#include <ctime>

Country::Country()
{

}

Country::~Country()
{

}

void Country::DataInit(int _population, int _fire, int _green)
{
	world = World::GetInstance();

	population = _population;
	live = _population;
	dead = 0;
	dailyDead = 0;

	needEnergy = 0;
	deltaNeedEnergy = 0;
	supplyEnergy = 0;
	deltaSupplyEnergy = 0;

	firePlants = _fire;
	deltaFirePlants = 0;
	greenPlants = _green;
	deltaGreenPlants = 0;

	dailyEmission = 0;
	totalEmission = 0;

	dailyGold = 0;
	totalGold = 0;
	support = 30;
	deltaSupport = 0;
	recognition = 20;
	deltaRecognition = 0;

	CalEnergy();

	srand(static_cast<unsigned int> (time(0)));
}


void Country::CalEnergy()
{
	int enrgy = firePlants * 100 + greenPlants * 60;

	deltaNeedEnergy = live - needEnergy;
	deltaSupplyEnergy = enrgy - supplyEnergy;

	needEnergy = live;
	supplyEnergy = enrgy;
}

void Country::CalEmission()
{
	dailyEmission = firePlants * 10;
	totalEmission += dailyEmission;
}

void Country::CalDeath()
{

	if (world->ElevatedTemperature() > 1.5f) {
		dailyDead = static_cast<int> (population * 0.07 * (rand() % 4));
		dead += dailyDead;
		live = population - dead;
	}
	else if (world->ElevatedTemperature() > 1.0f) {
		dailyDead = static_cast<int> (population * 0.005 * (rand() % 3));
		dead += dailyDead;
		live = population - dead;
	}

	else if (world->ElevatedTemperature() > 0.5f) {
		dailyDead = static_cast<int> (population * 0.001 * (rand() % 2));
		dead += dailyDead;
		live = population - dead;
	}
}


void Country::CalRecognition()
{

}
void Country::CalSupport()
{
	deltaSupport = 0;

	if (population <= 0)
		return;

	if (static_cast<float> (dailyDead) / population > 0.07) {
		if (rand() % 100 < 50)
			deltaSupport -= 1;

	}else if (static_cast<float> (dailyDead) / population > 0.005) {
		if (rand() % 100 < 35)
			deltaSupport -= 1;

	}else if (static_cast<float> (dailyDead) / population > 0.0001) {
		if (rand() % 100 < 25)
			deltaSupport -= 1;
	}

	int lackEnergy = needEnergy - supplyEnergy;

	if (lackEnergy > 0)
		if (rand() % 100 < 20)
			deltaSupport -= 1;

	support += deltaSupport;
}
void Country::ReceiveGold()
{
	if (population <= 0)
		return;

	int liveRate = (live * 100) / population;

	//20 * 100 ~ 0 * 20
	if (liveRate > 70) {
		dailyGold = (recognition / 7) * (rand() % 2);
	} else if (liveRate > 45) {
		dailyGold = (recognition / 11) * (rand() % 2);
	} else if (liveRate > 15)
		dailyGold = (recognition / 17)* (rand() % 2);


	totalGold += dailyGold;
}