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

	/// <summary>
	/// thread ���� �� detach. state�� InitThread ���·� ����.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int PlayGame();

	/// <summary>
	/// ���� ���Ḧ ���ؼ� �ݵ�� ȣ��. game ������ ����. state�� WaitEnd ���·� ���� ��, EndGame�� �ɶ� ���� ���. EndGame Ȯ�� �� Disable�� ����
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int EndGame();
	/// <summary>
	/// ���� �Ͻ�����. state�� Pause ���·� ����.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Pause();
	/// <summary>
	/// ���� �簳. state�� work ���·� ����.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Resume();
	SV_SIMULATOR_API int DoubleSpeed();
	SV_SIMULATOR_API int QuadSpeed();
	SV_SIMULATOR_API int OctoSpeed();
	SV_SIMULATOR_API int NormalSpeed();

	
	//******************************** world class data
	// ���� ��¥ ��ȯ
	SV_SIMULATOR_API int Today();
	// ������ ��� �µ� ��ȯ
	SV_SIMULATOR_API float GetWorldTemperature();
	// ������ ���ź�ҳ� ��ȯ
	SV_SIMULATOR_API float GetWorldCarbonPPM();
	// ������ ź�ҹ��ⷮ(�� ����) ��ȯ
	SV_SIMULATOR_API long long GetWorldCarboneEmission();
	// ������ ź�� �����(�� ����) ��ȯ
	SV_SIMULATOR_API long long GetWorldCarbonAbsorbed();
	// ������ �긲 ���� ��ȯ
	SV_SIMULATOR_API long long GetWorldForest();
	// ������ �α� �� ��ȯ
	SV_SIMULATOR_API long long GetWorldPopulation();
	// ������ �縸�� �� ��ȯ
	SV_SIMULATOR_API long long GetWorldDead();
	// ������ ���ĳ��� �� ��ȯ
	SV_SIMULATOR_API long long GetWorldRefugees();
	// ������ �۹����귮 (������ '�� �κ�')
	SV_SIMULATOR_API long long GetWorldFood();
	// �糭 �߻�Ȯ��
	SV_SIMULATOR_API float GetDisasterProbability();
	// �۹����귮 �Ӱ��� (�ʱ�ȭ �ʿ�)
	SV_SIMULATOR_API long long GetFoodCriticalPoint();
	// ��տµ� �Ӱ��� (�ʱ�ȭ �ʿ�)
	SV_SIMULATOR_API float GetTempCriticalPoint();

	//********************************************************

	//******************************** country class data
	// �ش� ������ ���� ��ȯ
	SV_SIMULATOR_API long long GetBudget(int _countryCode);
	// �ش� ������ GDP ��ȯ
	SV_SIMULATOR_API long long GetGDP(int _countryCode);
	// �ش� ������ �� �α��� ��ȯ
	SV_SIMULATOR_API long long GetPopulation(int _countryCode);
	// �ش� ������ ź�ҹ��ⷮ ��ȯ
	SV_SIMULATOR_API long long GetCarbonEmission(int _countryCode);
	// �ش� ������ �긲���� ��ȯ
	SV_SIMULATOR_API int GetCountryForest();
	// �ش� ������ ���� ��ȯ
	SV_SIMULATOR_API float GetTaxRate(int _countryCode);
	// �ش� ���������� �÷��̾� ������ ��ȯ
	SV_SIMULATOR_API float GetSupportRate(int _countryCode);
	// �ش� ���������� ���Ŀ� ���� �ν��� ��ȯ
	SV_SIMULATOR_API float GetRecognitionRate(int _countryCode);
	// �ش� ������ ���ĳ��� ���� ��ȯ
	SV_SIMULATOR_API float GetRefugeeRate(int _countryCode);
	// �ش� ������ ���� ����� ���� ��ȯ
	SV_SIMULATOR_API float GetDeadRate(int _countryCode);
	// �ش� ������ �۹� ���귮 ��ȯ
	SV_SIMULATOR_API long long GetFood(int _countryCode);
	// �ش� ������ ����� ��ȯ
	SV_SIMULATOR_API float GetRemoveForest(int _countryCode);
	
	
	//SV_SIMULATOR_API int EnforcePolicy(int _countryCode, int _policyCode);
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

	Game* game = nullptr;
	// oneDay�� ȣ�� �ֱ� ms ����, MINCYCLE �̻��� ���� �Էµ�.
	static time_t oneDayCycle;
	static SimState simState = SimState::Disable;
	int debugMode;
	PlaySpeed playSpeed;
}
//************************************************

