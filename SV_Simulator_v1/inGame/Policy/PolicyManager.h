#pragma once
#include "EduPolicy.h"
#include "LifePolicy.h"
#include "Plants.h"
#include "..\Game.h"
#include "..\Country.h"

class PolicyManager
{
public:
	static PolicyManager* GetInstance()
	{
		if (instance == nullptr) {
			instance = new PolicyManager();
		}
		return instance;
	}

	int EnforceEduPolicy(int _countryCode, int _eduPolicyCode);
	int CountEduPolicy(int _countryCode, int _eduPolicyCode);
	int CostEduPolicy(int _eduPolicyCode);
	int EffectEduPolicy(int _eduPolicyCode);

	int EnforceLifePolicy(int _countryCode, int _lifePolicyCode);
	int CountLifePolicy(int _countryCode, int _lifePolicyCode);
	int CostLifePolicy(int _lifePolicyCode);
	int EffectLifePolicy(int _lifePolicyCode);

	int BuildFirePlants(int _countryCode, int _numBuild);
	int DestroyFirePlants(int _countryCode, int _numDestroy);
	int CostFirePlants() { return firePlants->Cost(); }
	int RefundFirePlants() { return firePlants->Refund(); }

	int BuildGreenPlants(int _countryCode, int _numBuild);
	int DestroyGreenPlants(int _countryCode, int _numDestroy);
	int CostGreenPlants() { return greenPlants->Cost(); }
	int RefundGreenPlants() { return greenPlants->Refund(); }




private:
	static PolicyManager* instance;

	World* world;
	Player* player;
	Game* game;
	Country* countries[COUNTRY_NUM];

	EduPolicy* edu[EDU_POLICY_NUM];
	LifePolicy* life[LIFE_POLICY_NUM];
	Plants* firePlants;
	Plants* greenPlants;



	PolicyManager();
	PolicyManager(const PolicyManager& other);
	~PolicyManager();
};

