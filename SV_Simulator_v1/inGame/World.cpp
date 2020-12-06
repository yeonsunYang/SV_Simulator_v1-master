#include "World.h"

World* World::instance = nullptr;

World::World()
{
	needEnergy = 0;
	deltaNeedEnergy = 0;
	supplyEnergy = 0;
	deltaSupplyEnergy = 0;

	firePlants = 0;
	greenPlants = 0;

	population = 0;
	live = 0;
	dead = 0;
	dailyDead = 0;

	dailyEmission = 0;
	totalEmission = 0;
	carbonPPM_p2 = 40000;

	temperature_p2 = 0;
	startTemperature_p2 = 0;

	recognition = 20;
	deltaRecognition = 0;

}
World::World(const World& other) 
{

}
World::~World() 
{

}

void World::SetPopulation(int _population, int _live, int _dead)
{
	dailyDead = _dead - dead;
	population = _population;
	live = _live;
	dead = _dead;
}
void World::SetEnergy(int _needEnergy, int _supplyEnergy)
{
	deltaNeedEnergy = _needEnergy - needEnergy;
	deltaSupplyEnergy = _supplyEnergy - supplyEnergy;
	needEnergy = _needEnergy;
	supplyEnergy = _supplyEnergy;
		
}

void World::SetPlants(int _firePlants, int _greenPlants)
{
	firePlants = _firePlants;
	greenPlants = _greenPlants;
}
void World::SetEmission(int _emission)
{
	dailyEmission = _emission;
	totalEmission += dailyEmission;
}

void World::CalTemperature()
{
	carbonPPM_p2 += dailyEmission / 10;
	temperature_p2 = static_cast<int> (carbonPPM_p2 * 0.008984) + 1236;
}
void World::SetStartTemperature()
{
	startTemperature_p2 = temperature_p2;
}

void World::SetRecognition(int _recognition)
{
	deltaRecognition = _recognition - recognition;
	recognition = _recognition;
}