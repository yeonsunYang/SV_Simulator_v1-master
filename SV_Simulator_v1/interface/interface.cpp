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
		//Pause() üũ
		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		start = clock();
		// work() ȣ��
		SV_Sim::Work();
		if(SV_Sim::simState == SimState::WaitEnd)
			break;
		end = clock();
		delta = end - start;


		waitTime = static_cast<time_t> (oneDayCycle / static_cast<long long> (SV_Sim::playSpeed));

		// ������ �ſ� ������� ���꿡 �ҿ�� �ð��� waitTime���� ����� ���.

		if (delta > waitTime)
			delta = waitTime;

		//Pause() üũ
		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		// Wait() ȣ��
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
	game->Oneday();

	if (game->Today() % 30 == 0)
		game->OneMonth();

	if (game->Today() % 360 == 0)
		game->OneYear();

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

	//**************************
	//game ���� �� �ʱ�ȭ

	if(SV_Sim::game == nullptr)
		SV_Sim::game = new Game();

	//**************************


	if (_cycle < MINCYCLE)
		SV_Sim::oneDayCycle = MINCYCLE;
	else if (_cycle > MAXCYCLE)
		SV_Sim::oneDayCycle = MAXCYCLE;
	else
		SV_Sim::oneDayCycle = static_cast<time_t>(_cycle);

	SV_Sim::debugMode = _debugMode;

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

	//Thread ���� �� detach********************
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

	//**************************
	// game ����
	// thread�� �۵� �� �̸� 50ms�� �ִ� 3�� ���
	for (int i = 0; i < 60; i++)
	{
		Sleep(50);
		if (SV_Sim::simState == SimState::EndThread)
		{
			break;
		}
		else if (i == 59) {
			SV_Sim::ErrorLog("EndGame(): Thread�� ������� �ʾƼ� game�����͸� ������ �� �����ϴ�.");
			return -1;
		}
	}

	if (SV_Sim::game == nullptr) {
		SV_Sim::ErrorLog("EndGame(): nullptr�� �����Ϸ��� �õ��� �մϴ�.");
		return -2;
	}

	delete SV_Sim::game;
	SV_Sim::game = nullptr;

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
	// debugMode 0: log ��� ����.
	// debugMode 1: msg log�� ���.
	// debugMode 2: msg, func log �Ѵ� ���.
	if (SV_Sim::debugMode > static_cast<int> (_type))
		cout << "SV_LOG: " << _str << endl;

}
void SV_Sim::ErrorLog(const char* _str)
{
	cout << "***************************************************************" << endl;
	cout << "����ġ ���� ��Ȳ�Դϴ�. ����ڿ��� �������ּ���." << endl;
	cout << "SV_ERO: "<<_str << endl;
	cout << "***************************************************************" << endl;
}

int Today()
{
	return SV_Sim::game->Today();
}

//******************************** world class data

// ������ ��� �µ� ��ȯ
float GetWorldTemperature()
{
	return 13.0f;
}
// ������ ���ź�ҳ� ��ȯ
float GetWorldCarbonPPM()
{
	return 14.0f;
}
// ������ ź�ҹ��ⷮ(�� ����) ��ȯ
long long GetWorldCarbonEmission()
{
	return 15;
}
// ������ ź�� �����(�� ����) ��ȯ
long long GetWorldCarbonAbsorbed()
{
	return 16;
}
// ������ �긲 ���� ��ȯ
long long GetWorldForest()
{
	return 17;
}
// ������ �α� �� ��ȯ
long long GetWorldPopulation()
{
	return 18;
}
// ������ �縸�� �� ��ȯ
long long GetWorldDead()
{
	return 19;
}
// ������ ���ĳ��� �� ��ȯ
long long GetWorldRefugees()
{
	return 20;
}
// ������ �۹����귮 (������ '�� �κ�')
long long GetWorldFood()
{
	return 21;
}


//// �糭 �߻�Ȯ��
//float GetDisasterProbability();
//// �۹����귮 �Ӱ��� (�ʱ�ȭ �ʿ�)
//long long GetFoodCriticalPoint();
//// ��տµ� �Ӱ��� (�ʱ�ȭ �ʿ�)
//float GetTempCriticalPoint();

//********************************************************

//******************************** country class ���� �г�
// �ش� ������ ���� ��ȯ
long long GetBudget(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetBudget();
}
// �ش� ������ GDP ��ȯ
long long GetGDP(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetGdp();
}
// �ش� ������ ���� ��ȯ
float GetTaxRate(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetTaxRate();
}
// �ش� ������ �ķ� ���귮
long long GetFood(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetFood();
}
// �ش� ������ ź�ҹ��ⷮ ��ȯ
long long GetCarbonEmission(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetCarbonEmission();
}
// �ش� ������ �긲���� ��ȯ
int GetCountryForest(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetCountryForest();
}
// �ش� ������ �� �α��� ��ȯ
long long GetPopulation(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetPopulation();
}
// �ش� ������ ���� ����� ���� ��ȯ
float GetDeadRate(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetDeadRate();
}
// �ش� ������ ���ĳ��� ���� ��ȯ
float GetRefugeeRate(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetRefugeeRate();
}
// �ش� ������ ���� ����ڼ� ��ȯ
long long GetDead(int _countryCode)
{
	float deadRate = SV_Sim::game->GetCountry(_countryCode)->GetDeadRate();
	long long population = SV_Sim::game->GetCountry(_countryCode)->GetDefaultPopulation();

	return static_cast<long long> (population * deadRate);
}
// �ش� ������ ���ĳ��μ� ��ȯ
long long GetRefugees(int _countryCode)
{
	float refugeesRate = SV_Sim::game->GetCountry(_countryCode)->GetRefugeeRate();
	long long population = SV_Sim::game->GetCountry(_countryCode)->GetPopulation();
	return static_cast<long long> (refugeesRate * population);
}
// �ش� ���������� ���Ŀ� ���� �ν��� ��ȯ
float GetRecognitionRate(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetRecognitionRate();
}
// �ش� ���������� �÷��̾� ������ ��ȯ
float GetSupportRate(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetSupportRate();
}

	
	
//// �ش� ������ ����� ��ȯ
//float GetRemoveForest(int _countryCode);
	
//************************************* Country class Energy �г�
// �ش� ������ ������� �䱸 ������ ��ȯ
int GetIndustryEnergy(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetIndustryEnergy();
}
// �ش� ������ ��Ȱ �䱸 ������ ��ȯ
int GetLifeEnergy(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->GetLifeEnergy();
}
// �ش� ������ �� ������ ���� ��ȯ
int GetTotalPowerPlants(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->energies.GetTotalPowerPlants();
}
// �ش� ������ ����������� ������ ���� ��ȯ
int GetGreenPowerPlants(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->energies.GetGreenPowerPlants();
}
// �ش� ������ ��źȭ�� ������ ���� ��ȯ
int GetFirePowerPlants(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->energies.GetFirePowerPlants();
}
// �ش� ������ �����Ҵ� ������(����ȿ��) ��ȯ
int GetProduce(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->energies.GetProduce();
}
// �ش� ������ ��ź������ �� ź�ҹ��ⷮ ��ȯ
long long GetCarbonPerProduce(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->energies.GetCarbonPerProduce();
}


//************************************* Country class Life �г�

// �ش� ������ 1�δ� �ڵ��� ���� ����
float GetCarPerPerson(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetCarPerPerson();
}
// �ش� ������ �� ���� ��
long long GetCars(int _countryCode)
{
	float carPerPerson = SV_Sim::game->GetCountry(_countryCode)->life.GetCarPerPerson();
	long long population = SV_Sim::game->GetCountry(_countryCode)->GetPopulation();
	return static_cast<long long> (static_cast<float> (population) * carPerPerson);
}
// �ش� ������ ������� �ڵ��� ����
float GetFossilFuelCarsRatio(int _countryCode)
{
	return 1.0f - SV_Sim::game->GetCountry(_countryCode)->life.GetEcocarRatio();
}
// �ش� ������ ģȯ�� �ڵ��� ����
float GetEcocarRation(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetEcocarRatio();
}
// �ش� ������ �ڵ��� �� ���� ź�� ���ⷮ
long long GetCarbonPerCar(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetCarbonPerCar();
}
// �ش� ������ ���� ź�Ҽ�
int GetTaxTransprot(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetTaxTransport();
}
// �ش� ������ �� ���� ����
long long GetHouses(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetHouses();

}
// �ش� ������ �Ϲ� ���� ����
float GetGrayHouses(int _countryCode)
{
	float greenhouses = SV_Sim::game->GetCountry(_countryCode)->life.GetGreenhouses();
	float sunhouses = SV_Sim::game->GetCountry(_countryCode)->life.GetSunhouses();

	return 1.0f - greenhouses - sunhouses;
}
// �ش� ������ �׸����𵨸� ����
float GetGreenHouses(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetGreenhouses();
}
// �ش� ������ �¾�� �г� ��ġ ����
float GetSunHouses(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetSunhouses();
}
// �ش� ������ �ǹ� �� ���� ź�� ���ⷮ
long long GetCarbonPerHouse(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetCarbonPerHouse();
}
// �ش� ������ �ְ� ź�Ҽ�
int GetTaxHouse(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetTaxHouse();
}
// �ش� ������ �ϻ�� 1�δ� ź�� ����
long long GetCarbonPerPerson(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetCarbonPerPerson();
}
// �ش� ������ ��Ȱ���� �߻��ϴ� ���� �� ź�ҷ� (������� �ʱ�� ��.)
long long GetLifeCarbonEmission(int _countryCode)
{
	return -1;
}
// �ش� ������ ��Ȱ�� ź�Ҽ�����
int GetTaxLife(int _countryCode)
{
	return SV_Sim::game->GetCountry(_countryCode)->life.GetTaxLife();
}
