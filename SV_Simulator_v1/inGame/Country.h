#pragma once
#include "World.h"

class Country {
public:

	~Country();
	Country();

	void DataInit(int _population, int _fire, int _green);

	int Population() {return population;}
	int Live() { return live; }
	int Dead() { return dead; }
	int DDead() { return dailyDead; }

	int NeedEnergy() { return needEnergy; }
	int DNeedEnergy() { return deltaNeedEnergy; }
	int SupplyEnergy() { return supplyEnergy; }
	int DSupplyEnergy() { return deltaSupplyEnergy; }
	int FirePlants() { return firePlants; }
	int DFIrePlants() { return deltaFirePlants; }
	int GreenPlants() { return greenPlants; }
	int DGreenPlants() { return deltaGreenPlants; }
	int DEmission() { return dailyEmission; }
	int TEmission() { return totalEmission; }

	int DGold() { return dailyGold; }
	int TGold() { return totalGold; }
	int Support() { return support; }
	int DSupport() { return deltaSupport; }
	int Recognition() { return recognition; }
	int DRecognition() { return deltaRecognition; }


	void CalEnergy();
	void CalEmission();
	void CalDeath();
	void CalRecognition();
	void CalSupport();
	void ReceiveGold();


private:


	World* world;

	int population;
	int live;
	int dead;
	int dailyDead;

	int needEnergy;
	int deltaNeedEnergy;
	int supplyEnergy;
	int deltaSupplyEnergy;

	int firePlants;
	int deltaFirePlants;
	int greenPlants;
	int deltaGreenPlants;

	int dailyEmission;
	int totalEmission;

	int dailyGold;
	int totalGold;
	int support;
	int deltaSupport;
	int recognition;
	int deltaRecognition;
	
};