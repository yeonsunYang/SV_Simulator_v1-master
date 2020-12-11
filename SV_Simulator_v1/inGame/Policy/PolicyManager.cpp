#include "PolicyManager.h"

PolicyManager* PolicyManager::instance = nullptr;

PolicyManager::PolicyManager()
{
	world = World::GetInstance();
	game = Game::GetInstance();
	player = Player::GetInstance();
	



	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		countries[i] = game->CountryInstance(i);
	}

	// 순서대로 (비용, 인식도 증가 효과)
	edu[static_cast<int>(EduPolicyCode::edu1)] = new EduPolicy(10, 10);
	edu[static_cast<int>(EduPolicyCode::edu2)] = new EduPolicy(15, 20);
	edu[static_cast<int>(EduPolicyCode::edu3)] = new EduPolicy(20, 30);

	// 순서대로 (비용, 에너지 소비량 감소 효과, 1인당 에너지 소비량 감소 효과, 요구되는 인식률)
	life[static_cast<int>(LifePolicyCode::life1)] = new LifePolicy(10, 100, 2, 30);
	life[static_cast<int>(LifePolicyCode::life2)] = new LifePolicy(15, 200, 2, 40);
	life[static_cast<int>(LifePolicyCode::life3)] = new LifePolicy(20, 300, 3, 50);

	// 비용, 반환금
	firePlants = new Plants(10, 2);
	greenPlants = new Plants(15, 4);
}
PolicyManager::PolicyManager(const PolicyManager& other) 
	: PolicyManager::PolicyManager()
{

}
PolicyManager::~PolicyManager()
{

}

int PolicyManager::EnforceEduPolicy(int _countryCode, int _eduCode)
{
	int effect = edu[_eduCode]->Effect();
	int cost = edu[_eduCode]->Cost();

	if (_eduCode >= EDU_POLICY_NUM || _eduCode < 0)
		return -2;

	if (player->TGold() < cost)
		return -1;

	countries[_countryCode]->EnforceEduPolicy(_eduCode, effect);
	player->PayGold(cost);

	return 0;
}
int PolicyManager::CountEduPolicy(int _countryCode, int _eduCode)
{

	return 	countries[_countryCode]->CountEduPolicy(_eduCode);
}

int PolicyManager::CostEduPolicy(int _eduPolicyCode)
{
	return edu[_eduPolicyCode]->Cost();
}
int PolicyManager::EffectEduPolicy(int _eduPolicyCode)
{
	return edu[_eduPolicyCode]->Effect();
}



int PolicyManager::EnforceLifePolicy(int _countryCode, int _lifeCode)
{
	int effect = life[_lifeCode]->Effect();
	int effect2 = life[_lifeCode]->Effect2();
	int cost = life[_lifeCode]->Cost();

	if (_lifeCode >= LIFE_POLICY_NUM || _lifeCode < 0)
		return -2;

	if (player->TGold() < cost)
		return -1;

	int reco = countries[_countryCode]->Recognition();
	int needReco = life[_lifeCode]->NeedRecognition();

	if (reco <= needReco)
		return -3;



	countries[_countryCode]->EnforceLifePolicy(_lifeCode, effect, effect2);
	player->PayGold(cost);

	return 0;
}
int PolicyManager::CountLifePolicy(int _countryCode, int _eduCode)
{
	return 	countries[_countryCode]->CountLifePolicy(_eduCode);
}

int PolicyManager::CostLifePolicy(int _lifePolicyCode)
{
	return life[_lifePolicyCode]->Cost();
}
int PolicyManager::EffectLifePolicy(int _lifePolicyCode)
{
	return life[_lifePolicyCode]->Effect();
}
int PolicyManager::Effect2LifePolicy(int _lifePolicyCode)
{
	return life[_lifePolicyCode]->Effect2();
}
int PolicyManager::NeedRecoLifePolicy(int _lifePolicyCode)
{
	return life[_lifePolicyCode]->NeedRecognition();
}

int PolicyManager::BuildFirePlants(int _countryCode, int _numBuild)
{
	if (_numBuild <= 0)
		return -2;

	// 건설비용 총 합계 (비용 * 건설 갯수)
	int amount = firePlants->Cost() * _numBuild;

	if (player->TGold() < amount)
		return -1;

	countries[_countryCode]->BuildFirePlants(_numBuild);
	player->PayGold(amount);
		
	return 0;
}

int PolicyManager::DestroyFirePlants(int _countryCode, int _numDestory)
{
	if (_numDestory <= 0)
		return -2;

	int amount = greenPlants->Refund() * _numDestory;

	if (countries[_countryCode]->FirePlants() < _numDestory)
		return -1;

	countries[_countryCode]->DestroyFirePlants(_numDestory);

	player->RefundGold(amount);

	return 0;
}


int PolicyManager::BuildGreenPlants(int _countryCode, int _numBuild)
{
	if (_numBuild <= 0)
		return -2;

	// 건설비용 총 합계 (비용 * 건설 갯수)
	int amount = greenPlants->Cost() * _numBuild;

	if (player->TGold() < amount)
		return -1;

	countries[_countryCode]->BuildGreenPlants(_numBuild);
	player->PayGold(amount);

	return 0;
}

int PolicyManager::DestroyGreenPlants(int _countryCode, int _numDestory)
{
	if (_numDestory <= 0)
		return -2;

	int amount = greenPlants->Refund() * _numDestory;

	if (countries[_countryCode]->GreenPlants() < _numDestory)
		return -1;

	countries[_countryCode]->DestroyGreenPlants(_numDestory);

	player->RefundGold(amount);

	return 0;
}