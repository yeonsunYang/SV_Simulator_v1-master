#include "Country.h"
#include <cmath>
#include <ctime>

Country::Country()
{
	DataInit(0, 0, 0, 0, 0);
}

Country::~Country()
{

}

void Country::DataInit(int _population, int _fire, int _green, int _recognition, int _needEnergyPerson)
{
	world = World::GetInstance();

	population = _population;
	live = _population;
	dead = 0;
	dailyDead = 0;

	needEnergy = 0;
	needEnergyPerson = _needEnergyPerson;
	deltaNeedEnergy = 0;
	supplyEnergy = 0;
	deltaSupplyEnergy = 0;
	savingEnergy = 0;

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
	recognition = _recognition;
	deltaRecognition = 0;

	CalEnergy();

	srand(static_cast<unsigned int> (time(0)));
}


void Country::CalEnergy()
{
	int enrgy = (firePlants * fireInfo.Supply()) 
		+ (greenPlants * greenInfo.Supply());
	int newNeedEnergy = static_cast<int> ((live * needEnergyPerson) / 100) - savingEnergy;

	if (newNeedEnergy < 0)
		newNeedEnergy = 0;

	deltaNeedEnergy = newNeedEnergy - needEnergy;
	deltaSupplyEnergy = enrgy - supplyEnergy;

	needEnergy = newNeedEnergy;
	supplyEnergy = enrgy;
}
// 발전소 개수가 변화될 때만 사용하는 private 멤버함수
// CalEnergy와 delta~~~~ 변수 계산만 다름.
void Country::ReCalEnergy() 
{
	int enrgy = (firePlants * fireInfo.Supply())
		+ (greenPlants * greenInfo.Supply());
	int newNeedEnergy = static_cast<int> ((live * needEnergyPerson) / 100) - savingEnergy;

	if (newNeedEnergy < 0)
		newNeedEnergy = 0;

	deltaNeedEnergy += newNeedEnergy - needEnergy; 
	deltaSupplyEnergy += enrgy - supplyEnergy;

	needEnergy = newNeedEnergy;
	supplyEnergy = enrgy;
}

void Country::CalEmission()
{
	dailyEmission = firePlants * 10;
	totalEmission += dailyEmission;
}

void Country::CalDeath()
{
	if (live <= 0)
		return;

	int ElevatedTemp_p2 = world->ElevatedTemperature_p2();
	int newLive = 0;

	if (ElevatedTemp_p2  > 150) {
		dailyDead = static_cast<int> (population * 0.07 * (rand() % 4));
	}
	else if (ElevatedTemp_p2 > 100) {
		dailyDead = static_cast<int> (population * 0.005 * (rand() % 3));
;	}

	else if (ElevatedTemp_p2 > 50) {
		dailyDead = static_cast<int> (population * 0.001 * (rand() % 2));
	}

	dead += dailyDead;
	if (dead > population)
		dead = population;

	newLive = population - dead;

	live = newLive;
}


void Country::CalRecognition()
{
	deltaRecognition = 0;

	float dailyDeadRation = static_cast<float> (dailyDead) / population;
	if (population <= 0)
		return;

	if (dailyDeadRation > 0.07) {
		if (rand() % 100 < 50)
			deltaRecognition += 3;

	}
	else if (dailyDeadRation > 0.005) {
		if (rand() % 100 < 35)
			deltaRecognition += 3;

	}
	else if (dailyDeadRation > 0.0001) {
		if (rand() % 100 < 25)
			deltaRecognition += 3;
	}

	recognition += deltaRecognition;
}
void Country::CalSupport()
{
	deltaSupport = 0;
	float dailyDeadRation = static_cast<float> (dailyDead) / population;
	if (population <= 0)
		return;

	if (dailyDeadRation > 0.07) {
		if (rand() % 100 < 50)
			deltaSupport -= 1;

	}
	else if (dailyDeadRation > 0.005) {
		if (rand() % 100 < 35)
			deltaSupport -= 1;

	}
	else if (dailyDeadRation > 0.0001) {
		if (rand() % 100 < 25)
			deltaSupport -= 1;
	}

	int energyShortage = needEnergy - supplyEnergy;

	if (energyShortage > 0)
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
	if (liveRate > 90) {
		dailyGold = (recognition / 7) * (rand() % 2);
	}
	else if (liveRate > 45) {
		dailyGold = (recognition / 11) * (rand() % 2);
	}
	else if (liveRate > 15)
		dailyGold = (recognition / 17) * (rand() % 2);


	totalGold += dailyGold;
}
void Country::EnforceEduPolicy(int _eduPolicyCode, int _effect)
{
	if (_eduPolicyCode >= EDU_POLICY_NUM || _eduPolicyCode < 0)
		return;

	eduPolicy[_eduPolicyCode].Enforce();
	deltaRecognition += _effect;
	recognition += _effect;
}

int Country::CountEduPolicy(int _eduPolicyCode)
{
	if (_eduPolicyCode >= EDU_POLICY_NUM || _eduPolicyCode < 0)
		return -1;

	return eduPolicy[_eduPolicyCode].Count();
}

void Country::EnforceLifePolicy(int _lifePolicyCode, int _effect, int _effec2)
{
	if (_lifePolicyCode >= LIFE_POLICY_NUM || _lifePolicyCode < 0)
		return;

	lifePolicy[_lifePolicyCode].Enforce();
	savingEnergy += _effect;
	deltaNeedEnergy -= _effect;
	needEnergy -= _effect;
	needEnergyPerson -= _effec2;

	if (needEnergy < 0)
		needEnergy = 0;
	if (needEnergyPerson < 0)
		needEnergyPerson = 0;
	
}

int Country::CountLifePolicy(int _lifePolicyCode)
{
	if (_lifePolicyCode >= LIFE_POLICY_NUM || _lifePolicyCode < 0)
		return -1;

	return lifePolicy[_lifePolicyCode].Count();
}

void Country::BuildFirePlants(int _numPlants)
{
	firePlants += _numPlants;

	if(recognition > 35)
		for (int i = 0; i < _numPlants; i++)
		{
			if (rand() % 100 <= 10) {
				deltaSupport--;
				support--;
			}
		}
	ReCalEnergy();
}

void Country::BuildGreenPlants(int _numPlants)
{
	greenPlants += _numPlants;

	if(recognition < 35)
		for (int i = 0; i < _numPlants; i++)
		{
			if (rand() % 100 <= 10) {
				deltaSupport--;
				support--;
			}
		}
	ReCalEnergy();
}

void Country::DestroyFirePlants(int _numDestroy)
{
	firePlants -= _numDestroy;
	ReCalEnergy();

}

void Country::DestroyGreenPlants(int _numDestroy)
{
	greenPlants -= _numDestroy;
	ReCalEnergy();
}