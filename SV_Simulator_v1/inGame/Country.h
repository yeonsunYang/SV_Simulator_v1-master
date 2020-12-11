#pragma once
#include "World.h"
#include "Policy\EnforcedPolicy.h"

class Country {
public:

	~Country();
	Country();

	void DataInit(int _population, int _fire, int _green, int _recognition, int _needEnergyPerson);

	int Population() { return population; }
	int Live() { return live; }
	int Dead() { return dead; }
	int DDead() { return dailyDead; }

	int NeedEnergy() { return needEnergy; }
	int DNeedEnergy() { return deltaNeedEnergy; }
	int SupplyEnergy() { return supplyEnergy; }
	int SavingEnergy() { return savingEnergy; }
	int NeedEnergyPerson() { return needEnergyPerson; }
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



	int CountEduPolicy(int _eduPolicyCode);
	int CountLifePolicy(int _lifePolicyCode);


	void CalEnergy();
	void CalEmission();
	void CalDeath();
	void CalRecognition();
	void CalSupport();
	void ReceiveGold();

	void EnforceEduPolicy(int _eduPolicyCode, int _effect);
	void EnforceLifePolicy(int _lifePolicyCode, int _effect, int _effec2);

	void BuildFirePlants(int _numBuild);
	void BuildGreenPlants(int _numBuild);
	void DestroyFirePlants(int _numDestroy);
	void DestroyGreenPlants(int _numDestroy);



private:


	World* world;

	int population;
	int live;
	int dead;
	int dailyDead;

	int needEnergy;
	int needEnergyPerson;

	int deltaNeedEnergy;
	int supplyEnergy;
	int deltaSupplyEnergy;
	int savingEnergy;


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

	EnforcedPolicy lifePolicy [LIFE_POLICY_NUM] ;
	EnforcedPolicy eduPolicy [EDU_POLICY_NUM];


};