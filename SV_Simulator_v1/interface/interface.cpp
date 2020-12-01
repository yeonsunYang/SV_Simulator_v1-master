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
	while (SV_Sim::simState != SimState::EndThread)
	{
		Sleep(50);

		if (clock() - start > 3000) {
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
long long GetWorldCarboneEmission()
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
	return 22 + static_cast<long long> (_countryCode);
}
// �ش� ������ GDP ��ȯ
long long GetGDP(int _countryCode)
{
	return 23 + static_cast<long long> (_countryCode);
}
// �ش� ������ ���� ��ȯ
float GetTaxRate(int _countryCode)
{
	return 24.0f + static_cast<float>(_countryCode);
}
// �ش� ������ �ķ� ���귮
long long GetFood(int _countryCode)
{
	return 25 + static_cast<long long> (_countryCode);
}
// �ش� ������ ź�ҹ��ⷮ ��ȯ
long long GetCarbonEmission(int _countryCode)
{
	return 26 + static_cast<long long> (_countryCode);
}
// �ش� ������ �긲���� ��ȯ
int GetCountryForest(int _countryCode)
{
	return 27 + _countryCode;
}
// �ش� ������ �� �α��� ��ȯ
long long GetPopulation(int _countryCode)
{
	return 28 + static_cast<long long> (_countryCode);
}
// �ش� ������ ���� ����� ���� ��ȯ
float GetDeadRate(int _countryCode)
{
	return 29 + _countryCode;
}
// �ش� ������ ���ĳ��� ���� ��ȯ
float GetRefugeeRate(int _countryCode)
{
	return 30.0f + static_cast<float>(_countryCode);
}
// �ش� ������ ���� ����ڼ� ��ȯ
long long GetDead(int _countryCode)
{
	return 31 + static_cast<long long>(_countryCode);
}
// �ش� ������ ���ĳ��μ� ��ȯ
long long GetRefugees(int _countryCode)
{
	return 32 + static_cast<long long>(_countryCode);
}
// �ش� ���������� ���Ŀ� ���� �ν��� ��ȯ
float GetRecognitionRate(int _countryCode)
{
	return 33.0f + static_cast<float>(_countryCode);
}
// �ش� ���������� �÷��̾� ������ ��ȯ
float GetSupportRate(int _countryCode)
{
	return 34.0f + static_cast<float>(_countryCode);
}

	
	
//// �ش� ������ ����� ��ȯ
//float GetRemoveForest(int _countryCode);
	
//************************************* Country class Energy �г�
// �ش� ������ ������� �䱸 ������ ��ȯ
int GetIndustryEnergy(int _countryCode)
{
	return 35 + _countryCode;
}
// �ش� ������ ��Ȱ �䱸 ������ ��ȯ
int GetLifeEnergy(int _countryCode)
{
	return 36 + _countryCode;
}
// �ش� ������ �� ������ ���� ��ȯ
int GetTotalPowerPlants(int _countryCode)
{
	return 37 + _countryCode;
}
// �ش� ������ ����������� ������ ���� ��ȯ
int GetGreenPowerPlants(int _countryCode)
{
	return 38 + _countryCode;
}
// �ش� ������ ��źȭ�� ������ ���� ��ȯ
int GetFirePowerPlants(int _countryCode)
{
	return 39 + _countryCode;
}
// �ش� ������ �����Ҵ� ������(����ȿ��) ��ȯ
int GetProduce(int _countryCode)
{
	return 40 + _countryCode;
}
// �ش� ������ ��ź������ �� ź�ҹ��ⷮ ��ȯ
long long GetCarbonPerProduce(int _countryCode)
{
	return 41 + static_cast<long long> (_countryCode);
}


//************************************* Country class Life �г�

// �ش� ������ 1�δ� �ڵ��� ���� ����
float GetCarPerPerson(int _countryCode)
{
	return 42.0f + static_cast <float> (_countryCode);
}
// �ش� ������ �� ���� ��
long long GetCars(int _countryCode)
{
	return 43 + static_cast<long long> (_countryCode);
}
// �ش� ������ ������� �ڵ��� ����
float GetFossilFuelCarsRatio(int _countryCode)
{
	return 44.0f + static_cast <float> (_countryCode);
}
// �ش� ������ ģȯ�� �ڵ��� ����
float GetEcocarRation(int _countryCode)
{
	return 45.0f + static_cast <float> (_countryCode);
}
// �ش� ������ �ڵ��� �� ���� ź�� ���ⷮ
long long GetCarbonPerCar(int _countryCode)
{
	return 46 + static_cast<long long> (_countryCode);
}
// �ش� ������ ���� ź�Ҽ�
float GetTaxTransprot(int _countryCode)
{
	return 47.0f + static_cast <float> (_countryCode);
}
// �ش� ������ �� ���� ����
long long GetHouses(int _countryCode)
{
	return 48 + static_cast<long long> (_countryCode);
}
// �ش� ������ �Ϲ� ���� ����
float GetGrayHouses(int _countryCode)
{
	return 49.0f + static_cast <float> (_countryCode);
}
// �ش� ������ �׸����𵨸� ����
float GetGreenHouses(int _countryCode)
{
	return 50.0f + static_cast <float> (_countryCode);
}
// �ش� ������ �¾�� �г� ��ġ ����
float GetSunHouses(int _countryCode)
{
	return 51.0f + static_cast <float> (_countryCode);
}
// �ش� ������ �ǹ� �� ���� ź�� ���ⷮ
long long GetCarbonPerHouse(int _countryCode)
{
	return 52 + static_cast<long long> (_countryCode);
}
// �ش� ������ �ְ� ź�Ҽ�
float GetTaxHouse(int _countryCode)
{
	return 53.0f + static_cast <float> (_countryCode);
}
// �ش� ������ �ϻ�� 1�δ� ź�� ����
long long GetCarbonPerPerson(int _countryCode)
{
	return 54 + static_cast<long long> (_countryCode);
}
// �ش� ������ ��Ȱ���� �߻��ϴ� ���� �� ź�ҷ�
long long GetLifeCarbonEmission(int _countryCode)
{
	return 55 + static_cast<long long> (_countryCode);
}
// �ش� ������ ��Ȱ�� ź�Ҽ�����
float GetTaxLife(int _countryCode)
{
	return 56.0f + static_cast <float> (_countryCode);
}
