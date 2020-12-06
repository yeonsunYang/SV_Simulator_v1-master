#pragma once
#include "..\inGame\Game.h"
#include "pch.h"

#define MINCYCLE 500
#define MAXCYCLE 100000

#define SV_SIMULATOR_API __declspec(dllexport)

enum class SimState {
	Disable = 10, WaitPlay, InitThread, Work, WaitEnd, EndThread, Pause
};

enum class LogType {
	Msg, Func
};
enum class PlaySpeed {
	Normal = 1, Double = 2, Quad = 4, Octo = 8 
};
// Interface Method ����****************************************************************

extern "C" {
	/// <summary>
	/// ���� ���� ���� �ݵ�� ȣ��. ���� �� �� �ѹ��� ȣ�� ����. game ���� �ʱ�ȭ.
	/// state�� WaitPlay�� ����
	/// </summary>
	/// <param name="_cycle"> oneday�� ȣ�� �ֱ� (ms ����), 500�̻� ~ 100,000 ���� ���� ��ȿ��. </param>
	/// <param name="_debugMode">Debug ��� (0 ~ 2) </param>
	/// <returns></returns>
	SV_SIMULATOR_API int InitGame(long long _cycle, int _debugMode);

	// thread ���� �� detach. state�� InitThread ���·� ����.
	SV_SIMULATOR_API int PlayGame();

	// ���� ���Ḧ ���ؼ� �ݵ�� ȣ��. game ������ ����. state�� WaitEnd ���·� ���� ��, EndGame�� �ɶ� ���� ���. EndGame Ȯ�� �� Disable�� ����
	SV_SIMULATOR_API int EndGame();
	// ���� �Ͻ�����. state�� Pause ���·� ����.
	SV_SIMULATOR_API int Pause();
	// ���� �簳. state�� work ���·� ����.
	SV_SIMULATOR_API int Resume();
	// �ùķ����� �ӵ��� 2��� ����
	SV_SIMULATOR_API int DoubleSpeed();
	// �ùķ����� �ӵ��� 4��� ����
	SV_SIMULATOR_API int QuadSpeed();
	// �ùķ����� �ӵ��� 8��� ����
	SV_SIMULATOR_API int OctoSpeed();
	// �ùķ����� �ӵ��� ���� �ӵ��� ����
	SV_SIMULATOR_API int NormalSpeed();
	// ���� ��¥ ��ȯ
	SV_SIMULATOR_API int Today();
	
	SV_SIMULATOR_API int GetWTemperature_p2();
	SV_SIMULATOR_API float GetWTemperature();
	SV_SIMULATOR_API int GetWElevatedTemperature_p2();
	SV_SIMULATOR_API float GetWElevatedTemperature();
	SV_SIMULATOR_API int GetWCarbonPPM_p2();
	SV_SIMULATOR_API float GetWCarbonPPM();
	SV_SIMULATOR_API int GetPTGold();
	SV_SIMULATOR_API int GetPDGold();
	SV_SIMULATOR_API int GetPSupport();
	SV_SIMULATOR_API int GetPDSupport();
	SV_SIMULATOR_API long long GetWPopulation();
	SV_SIMULATOR_API long long GetWLive();
	SV_SIMULATOR_API long long GetWDead();
	SV_SIMULATOR_API long long GetWDDead();
	SV_SIMULATOR_API int GetWDEmission();
	SV_SIMULATOR_API int GetWTEmission();
	SV_SIMULATOR_API int GetWNeedEnergy();
	SV_SIMULATOR_API int GetWDNeedEnergy();
	SV_SIMULATOR_API int GetWSupplyEnergy();
	SV_SIMULATOR_API int GetWDSupplyEnergy();
	SV_SIMULATOR_API int GetWRecognition();
	SV_SIMULATOR_API int GetWDRecognition();

	SV_SIMULATOR_API long long GetPopulation(int _countryCode);
	SV_SIMULATOR_API long long GetLive(int _countryCode);
	SV_SIMULATOR_API long long GetDead(int _countryCode);
	SV_SIMULATOR_API long long GetDDead(int _countryCode);
	SV_SIMULATOR_API int GetDGold(int _countryCode);
	SV_SIMULATOR_API int GetTGold(int _countryCode);
	SV_SIMULATOR_API int GetDSupport(int _countryCode);
	SV_SIMULATOR_API int GetSupport(int _countryCode);
	SV_SIMULATOR_API int GetDRecognition(int _countryCode);
	SV_SIMULATOR_API int GetRecognition(int _countryCode);
	SV_SIMULATOR_API int GetNeedEnergy(int _countryCode);
	SV_SIMULATOR_API int GetDNeedEnergy(int _countryCode);
	SV_SIMULATOR_API int GetSupplyEnergy(int _countryCode);
	SV_SIMULATOR_API int GetDSupplyEnergy(int _countryCode);
	SV_SIMULATOR_API int GetFirePlants(int _countryCode);
	SV_SIMULATOR_API int GetDFirePlants(int _countryCode);
	SV_SIMULATOR_API int GetGreenPlants(int _countryCode);
	SV_SIMULATOR_API int GetDGreenPlants(int _countryCode);

	//***************************************************************************************
}

// only Dll Method (DLL ���ο����� �۵��ϴ� �Լ�)****
namespace SV_Sim {
	int Run();
	int Work();
	int Pause();
	int Wait(time_t);
	void DebugLog(const char*, LogType);
	void ErrorLog(const char*);

	Game* game;
	World* world;
	Player* player;

	// oneDay�� ȣ�� �ֱ� ms ����, MINCYCLE �̻��� ���� �Էµ�.
	static time_t oneDayCycle;
	static SimState simState = SimState::Disable;
	int debugMode;
	PlaySpeed playSpeed;
}
//************************************************

