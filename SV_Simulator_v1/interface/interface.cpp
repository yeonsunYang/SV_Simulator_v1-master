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

int Inter_InitGame(long long _cycle, int _debugMode)
{
	SV_Sim::DebugLog("Inter_InitGame()", LogType::Func);

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
int Inter_PlayGame()
{
	SV_Sim::DebugLog("Inter_PlayGame()", LogType::Func);

	if (SV_Sim::simState != SimState::WaitPlay)
		return static_cast<int> (SV_Sim::simState);


	SV_Sim::simState = SimState::InitThread;

	//Thread ���� �� detach********************
	std::thread Simulator(SV_Sim::Run);
	Simulator.detach();
	//****************************************

	return 0;
}
int Inter_Pause()
{
	SV_Sim::DebugLog("Inter_Pause()", LogType::Func);

	if(SV_Sim::simState == SimState::Work)
		SV_Sim::simState = SimState::Pause;

	return 0;
}
int Inter_Resume()
{
	SV_Sim::DebugLog("Inter_Resume()", LogType::Func);

	if (SV_Sim::simState == SimState::Pause)
		SV_Sim::simState = SimState::Work;

	return 0;
}
int Inter_EndGame()
{
	SV_Sim::DebugLog("Inter_EndGame()", LogType::Func);


	time_t start = clock();

	SV_Sim::simState = SimState::WaitEnd;

	//**************************
	// game ����
	// thread�� �۵� �� �̸� 50ms�� �ִ� 3�� ���
	while (SV_Sim::simState != SimState::EndThread)
	{
		Sleep(50);

		if (clock() - start > 3000) {
			SV_Sim::ErrorLog("Inter_EndGame(): Thread�� ������� �ʾƼ� game�����͸� ������ �� �����ϴ�.");
			return -1;
		}
	}

	if (SV_Sim::game == nullptr) {
		SV_Sim::ErrorLog("Inter_EndGame(): nullptr�� �����Ϸ��� �õ��� �մϴ�.");
		return -2;
	}

	delete SV_Sim::game;
	SV_Sim::game = nullptr;

	SV_Sim::simState = SimState::Disable;

	return 0;
	//**************************

}
int Inter_DoubleSpeed()
{
	SV_Sim::DebugLog("Inter_DoubleSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Double;
	return 0;
}
int Inter_QuadSpeed()
{
	SV_Sim::DebugLog("Inter_QuadSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Quad;
	return 0;
}
int Inter_OctoSpeed()
{
	SV_Sim::DebugLog("Inter_OctoSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Octo;
	return 0;
}
int Inter_NormalSpeed()
{
	SV_Sim::DebugLog("Inter_NormalSpeed()", LogType::Func);

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

int Inter_Today()
{
	return SV_Sim::game->Today();
}
long long Inter_GetBudget(int _countryCode)
{
	return SV_Sim::game->GetBudget(static_cast<CountryCode> (_countryCode));
}
long long Inter_GetGDP(int _countryCode)
{
	return SV_Sim::game->GetGDP(static_cast<CountryCode> (_countryCode));
}
long long Inter_GetPopulation(int _countryCode)
{
	return SV_Sim::game->GetPopulation(static_cast<CountryCode> (_countryCode));
}
long long Inter_GetCarbonEmission(int _countryCode)
{
	return SV_Sim::game->GetCarbonEmission(static_cast<CountryCode> (_countryCode));
}
float Inter_GetTaxRate(int _countryCode)
{
	return SV_Sim::game->GetTaxRate(static_cast<CountryCode> (_countryCode));
}
float Inter_GetWorldTemperature()
{
	return SV_Sim::game->GetWorldTemperature();
}
long long Inter_GetWorldCarbonEmission()
{
	return SV_Sim::game->GetWorldCarbonEmission();
}
long long Inter_GetWorldPopulation()
{
	return SV_Sim::game->GetWorldPopulation();
}
float Inter_GetWorldCarbonPPM()
{
	return SV_Sim::game->GetWorldCarbonPPM();
}

