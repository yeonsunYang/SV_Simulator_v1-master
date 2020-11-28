#include "pch.h"
#include "interface.h"


int SV_Sim::Run()
{
	if (SV_Sim::simState != SimState::InitThread)
		return static_cast<int> (SV_Sim::simState);

	time_t delta, start, end;

	SV_Sim::DebugLog("SV_Run() - start", LogType::Func);


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

		// ������ �ſ� ������� oneDayCycle���� ����� ���.
		if (delta > oneDayCycle)
			delta = oneDayCycle;

		//Pause() üũ
		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		// Wait() ȣ��
		SV_Sim::Wait(SV_Sim::oneDayCycle - delta);


		if (SV_Sim::simState == SimState::WaitEnd)
			break;
	}

	SV_Sim::simState = SimState::EndThread;

	SV_Sim::DebugLog("SV_Run() - end", LogType::Func);
}

int SV_Sim::Work()
{
	if (SV_Sim::simState == SimState::WaitEnd) {
		return 0;
	}
	game->Oneday();

	return 0;
}
int SV_Sim::Wait(time_t _waitTime)
{
	while (_waitTime > 100)
	{
		if (SV_Sim::simState == SimState::WaitEnd) {
			return static_cast<int> (SV_Sim::simState);
		}

		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		Sleep(100);
		_waitTime -= 100;
	}

	Sleep(_waitTime);

	if (SV_Sim::simState == SimState::WaitEnd) {
		return static_cast<int> (SV_Sim::simState);
	}

	if (SV_Sim::simState == SimState::Pause)
		SV_Sim::Pause();

	return 0;

}
int SV_Sim::Pause()
{
	while (simState == SimState::Pause)
	{
		Sleep(50);
	}
}


int Inter_InitGame(long long _cycle, int _debugMode)
{
	SV_Sim::DebugLog("SV_Interface_PlayGame()", LogType::Func);

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

	return 0;
}

int Inter_PlayGame()
{
	SV_Sim::DebugLog("SV_Interface_PlayGame()", LogType::Func);

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
	if(SV_Sim::simState == SimState::Work)
		SV_Sim::simState = SimState::Pause;

	return 0;
}

int Inter_Resume()
{
	if (SV_Sim::simState == SimState::Pause)
		SV_Sim::simState = SimState::Work;

	return 0;
}


int Inter_EndGame()
{
	SV_Sim::DebugLog("SV_Interface_EndGame()", LogType::Func);


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

void SV_Sim::DebugLog(const char* _str, LogType _type)
{
	// debugMode 0: log ��� ����.
	// debugMode 1: msg log�� ���.
	// debugMode 2: msg, func log �Ѵ� ���.
	if (SV_Sim::debugMode > static_cast<int> (_type));
		cout << "SV_LOG: " << _str << endl;

}

void SV_Sim::ErrorLog(const char* _str)
{
	cout << "***************************************************************" << endl;
	cout << "����ġ ���� ��Ȳ�Դϴ�. ����ڿ��� �������ּ���." << endl;
	cout << "SV_ERO: "<<_str << endl;
	cout << "***************************************************************" << endl;
}