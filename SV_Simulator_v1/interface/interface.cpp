#include "pch.h"
#include "interface.h"


int SV_Sim::Run()
{
	SV_Sim::DebugLog("Run()", LogType::Func);

	if (SV_Sim::simState != SimState::InitThread)
		return static_cast<int> (SV_Sim::simState);

	time_t delta, start, end, waitTime;


	SV_Sim::simState = SimState::Work;


	while (SV_Sim::simState != SimState::WaitEnd)
	{
		//Pause() 체크
		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		start = clock();
		// work() 호출
		SV_Sim::Work();
		//system("cls");


		//cout << "===================================================" << endl;
		//cout << "===                 Survival 1.5                ===" << endl;
		//cout << "===================================================" << endl;

		//SV_Sim::game->PrintDate();
		//SV_Sim::game->PrintPlayer();
		//SV_Sim::game->PrintWorld();
		//SV_Sim::game->PrintCountriesAll();


		if(SV_Sim::simState == SimState::WaitEnd)
			break;
		end = clock();
		delta = end - start;

		//cout << "연산시간: " << delta << "(ms)" << endl;


		waitTime = static_cast<time_t> (oneDayCycle / static_cast<long long> (SV_Sim::playSpeed));

		// 연산이 매우 길어져서 연산에 소요된 시간이 waitTime보다 길어질 경우.

		if (delta > waitTime)
			delta = waitTime;

		//Pause() 체크
		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		// Wait() 호출
		SV_Sim::Wait(waitTime - delta);


		if (SV_Sim::simState == SimState::WaitEnd)
			break;
	}

	SV_Sim::simState = SimState::EndThread;

	SV_Sim::DebugLog("Run() - end", LogType::Func);

	return 0;
}
int SV_Sim::Work()
{
	SV_Sim::DebugLog("Work()", LogType::Func);

	if (SV_Sim::simState == SimState::WaitEnd) {
		return 0;
	}
	game->OneDay();


	return 0;
}
int SV_Sim::Wait(time_t _waitTime)
{
	SV_Sim::DebugLog("Wait()", LogType::Func);

	while (_waitTime > 50)
	{
		if (SV_Sim::simState == SimState::WaitEnd) {
			return static_cast<int> (SV_Sim::simState);
		}

		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		Sleep(50);
		_waitTime -= 50;
	}

	Sleep(static_cast<DWORD> (_waitTime));

	if (SV_Sim::simState == SimState::WaitEnd) {
		return static_cast<int> (SV_Sim::simState);
	}

	if (SV_Sim::simState == SimState::Pause)
		SV_Sim::Pause();

	return 0;

}
int SV_Sim::Pause()
{
	SV_Sim::DebugLog("Pause()", LogType::Func);

	while (simState == SimState::Pause)
	{
		Sleep(50);
	}

	return 0;
}

int InitGame(long long _cycle, int _debugMode)
{
	SV_Sim::DebugLog("InitGame()", LogType::Func);

	if (SV_Sim::simState != SimState::Disable)
		return static_cast<int> (SV_Sim::simState);


	if (_cycle < MINCYCLE)
		SV_Sim::oneDayCycle = MINCYCLE;
	else if (_cycle > MAXCYCLE)
		SV_Sim::oneDayCycle = MAXCYCLE;
	else
		SV_Sim::oneDayCycle = static_cast<time_t>(_cycle);

	SV_Sim::debugMode = _debugMode;


	SV_Sim::game = Game::GetInstance();
	SV_Sim::world = World::GetInstance();
	SV_Sim::player = Player::GetInstance();
	SV_Sim::policyManager = PolicyManager::GetInstance();

	SV_Sim::game->Init();


	SV_Sim::simState = SimState::WaitPlay;
	SV_Sim::playSpeed = PlaySpeed::Normal;
	return 0;
}
int PlayGame()
{
	SV_Sim::DebugLog("PlayGame()", LogType::Func);

	if (SV_Sim::simState != SimState::WaitPlay)
		return static_cast<int> (SV_Sim::simState);


	SV_Sim::simState = SimState::InitThread;

	//Thread 생성 및 detach********************
	std::thread Simulator(SV_Sim::Run);
	Simulator.detach();
	//****************************************

	return 0;
}
int Pause()
{
	SV_Sim::DebugLog("Pause()", LogType::Func);

	if(SV_Sim::simState == SimState::Work)
		SV_Sim::simState = SimState::Pause;

	return 0;
}
int Resume()
{
	SV_Sim::DebugLog("Resume()", LogType::Func);

	if (SV_Sim::simState == SimState::Pause)
		SV_Sim::simState = SimState::Work;

	return 0;
}
int EndGame()
{
	SV_Sim::DebugLog("EndGame()", LogType::Func);


	time_t start = clock();

	SV_Sim::simState = SimState::WaitEnd;


	for (int i = 0; i < 60; i++)
	{
		Sleep(50);
		if (SV_Sim::simState == SimState::EndThread)
		{
			break;
		}
		else if (i == 59) {
			SV_Sim::ErrorLog("EndGame(): Thread가 종료되지 않아서 game포인터를 해제할 수 없습니다.");
			return -1;
		}
	}


	SV_Sim::simState = SimState::Disable;

	return 0;
	//**************************

}
int DoubleSpeed()
{
	SV_Sim::DebugLog("DoubleSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Double;
	return 0;
}
int QuadSpeed()
{
	SV_Sim::DebugLog("QuadSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Quad;
	return 0;
}
int OctoSpeed()
{
	SV_Sim::DebugLog("OctoSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Octo;
	return 0;
}
int NormalSpeed()
{
	SV_Sim::DebugLog("NormalSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Normal;
	return 0;
}

void SV_Sim::DebugLog(const char* _str, LogType _type)
{
	// debugMode 0: log 출력 안함.
	// debugMode 1: msg log만 출력.
	// debugMode 2: msg, func log 둘다 출력.
	if (SV_Sim::debugMode > static_cast<int> (_type))
		cout << "SV_LOG: " << _str << endl;

}
void SV_Sim::ErrorLog(const char* _str)
{
	cout << "***************************************************************" << endl;
	cout << "예기치 못한 상황입니다. 담당자에게 보고해주세요." << endl;
	cout << "SV_ERO: "<<_str << endl;
	cout << "***************************************************************" << endl;
}

int Today()
{
	return SV_Sim::game->Today();
}


int GetWTemperature_p2()
{
	return SV_Sim::world->Temperature_p2();
}
float GetWTemperature()
{
	return SV_Sim::world->Temperature();
}
int GetWElevatedTemperature_p2()
{
	return SV_Sim::world->ElevatedTemperature_p2();
}
float GetWElevatedTemperature()
{
	return SV_Sim::world->ElevatedTemperature();
}
int GetWCarbonPPM_p2()
{
	return SV_Sim::world->CarbonPPM_p2();
}
float GetWCarbonPPM()
{
	return SV_Sim::world->CarbonPPM();
}
int GetPTGold()
{
	return SV_Sim::player->TGold();
}
int GetPDGold()
{
	return SV_Sim::player->DGold();
}
int GetPSupport()
{
	return SV_Sim::player->Support();
}
int GetPDSupport()
{
	return SV_Sim::player->DSupport();
}
long long GetWPopulation()
{
	return SV_Sim::world->Population();
}
long long GetWLive()
{
	return SV_Sim::world->Live();
}
long long GetWDead()
{
	return SV_Sim::world->Dead();
}
long long GetWDDead()
{
	return SV_Sim::world->DDead();
}
int GetWDEmission()
{
	return SV_Sim::world->DEmission();
}
int GetWTEmission()
{
	return SV_Sim::world->TEmission();
}
int GetWNeedEnergy()
{
	return SV_Sim::world->NeedEnergy();
}
int GetWDNeedEnergy()
{
	return SV_Sim::world->DNeedEnergy();
}
int GetWSupplyEnergy()
{
	return SV_Sim::world->SupplyEnergy();
}
int GetWDSupplyEnergy()
{
	return SV_Sim::world->DSupplyEnergy();
}
int GetWRecognition()
{
	return SV_Sim::world->Recognition();
}
int GetWDRecognition()
{
	return SV_Sim::world->DRecognition();
}

long long GetPopulation(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->Population();
}
long long GetLive(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->Live();
}
long long GetDead(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->Dead();
}
long long GetDDead(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DDead();
}
int GetDGold(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DGold();
}
int GetTGold(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->TGold();
}
int GetDSupport(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DSupport();
}
int GetSupport(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->Support();
}
int GetDRecognition(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DRecognition();
}
int GetRecognition(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->Recognition();
}
int GetNeedEnergy(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->NeedEnergy();
}
int GetNeedEnergyPerson(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->NeedEnergyPerson();
}
int GetDNeedEnergy(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DNeedEnergy();
}
int GetSupplyEnergy(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->SupplyEnergy();
}
int GetDSupplyEnergy(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DSupplyEnergy();
}
int GetSavingEnergy(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->SavingEnergy();
}
int GetFirePlants(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->FirePlants();
}
int GetDFirePlants(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DFIrePlants();
}
int GetGreenPlants(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->GreenPlants();
}
int GetDGreenPlants(int _countryCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->DGreenPlants();
}

int GetCountEduPolicy(int _countryCode, int _eduCode)
{
	return SV_Sim::game->CountryInstance(_countryCode)->CountEduPolicy(_eduCode);
}
int EnforceEduPolicy(int _countryCode, int _eduCode)
{
	return SV_Sim::policyManager->EnforceEduPolicy(_countryCode, _eduCode);
}
int GetCostEduPolicy(int _eduCode)
{
	return SV_Sim::policyManager->CostEduPolicy(_eduCode);
}
int GetEffectEduPolicy(int _eduCode)
{
	return SV_Sim::policyManager->EffectEduPolicy(_eduCode);
}
int BuildFirePlants(int _countryCode, int _numBuild)
{
	return SV_Sim::policyManager->BuildFirePlants(_countryCode, _numBuild);
}
int DestroyFirePlants(int _countryCode, int _numDestroy)
{
	return SV_Sim::policyManager->DestroyFirePlants(_countryCode, _numDestroy);
}
int GetCostFirePlants()
{
	return SV_Sim::policyManager->CostFirePlants();
}
int GetRefundFirePlants()
{
	return SV_Sim::policyManager->RefundFirePlants();
}
int GetEmissionFirePlants()
{
	return 10;
}
int GetSupplyFirePlants()
{
	return 100;
}
int BuildGreenPlants(int _countryCode, int _numBuild)
{
	return SV_Sim::policyManager->BuildGreenPlants(_countryCode, _numBuild);
}
int DestroyGreenPlatns(int _countryCode, int _numDestroy)
{
	return SV_Sim::policyManager->DestroyGreenPlants(_countryCode, _numDestroy);
}
int GetCostGreenPlants()
{
	return SV_Sim::policyManager->CostGreenPlants();
}
int GetRefundGreenPlants()
{
	return SV_Sim::policyManager->RefundGreenPlants();
}
int GetEmissionGreenPlants()
{
	return 0;
}
int GetSupplyGreenPlants()
{
	return 60;
}

int EnforceLifePolicy(int _countryCode, int _lifeCode)
{
	return SV_Sim::policyManager->EnforceLifePolicy(_countryCode, _lifeCode);
}
int GetCountLifePolicy(int _countryCode, int _lifeCode)
{
	return SV_Sim::policyManager->CountLifePolicy(_countryCode, _lifeCode);
}
int GetNeedRecognition(int _lifeCode)
{
	return SV_Sim::policyManager->NeedRecoLifePolicy(_lifeCode);
}
int GetCostLifePolicy(int _lifeCode)
{
	return SV_Sim::policyManager->CostLifePolicy(_lifeCode);
}
int GetEffectLifePolicy(int _lifeCode)
{
	return SV_Sim::policyManager->EffectLifePolicy(_lifeCode);
}

int GetEffect2LifePolicy(int _lifeCode)
{
	return SV_Sim::policyManager->Effect2LifePolicy(_lifeCode);
}