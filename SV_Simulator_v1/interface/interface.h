#pragma once
#include "..\inGame\Game.h"
#include "pch.h"

#define MINCYCLE 500
#define MAXCYCLE 5000

#define SV_SIMULATOR_API __declspec(dllexport)

enum class SimState {
	Disable = 10, WaitPlay, InitThread, Work, WaitEnd, EndThread, Pause
};

enum class LogType {
	Msg, Func
};
// Interface Method ����****************************************************************

extern "C" {
	/// <summary>
	/// ���� ���� ���� �ݵ�� ȣ��. ���� �� �� �ѹ��� ȣ�� ����. game ���� �ʱ�ȭ.
	/// state�� WaitPlay�� ����
	/// </summary>
	/// <param name="_cycle"> oneday�� ȣ�� �ֱ� (ms ����), 500�̻� ~ 5000 ���� ���� ��ȿ��. </param>
	/// <param name="_debugMode">Debug ��� (0 ~ 2) </param>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_InitGame(long long _cycle, int _debugMode);

	/// <summary>
	/// thread ���� �� detach. state�� InitThread ���·� ����.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_PlayGame();

	/// <summary>
	/// ���� ���Ḧ ���ؼ� �ݵ�� ȣ��. game ������ ����. state�� WaitEnd ���·� ���� ��, EndGame�� �ɶ� ���� ���. EndGame Ȯ�� �� Disable�� ����
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_EndGame();
	/// <summary>
	/// ���� �Ͻ�����. state�� Pause ���·� ����.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_Pause();
	/// <summary>
	/// ���� �簳. state�� work ���·� ����.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_Resume();
	
	SV_SIMULATOR_API int Inter_Today();
	SV_SIMULATOR_API long long Inter_GetBudget(int _countryCode);
	SV_SIMULATOR_API long long Inter_GetGDP(int _countryCode);
	SV_SIMULATOR_API long long Inter_GetPopulation(int _countryCode);
	SV_SIMULATOR_API long long Inter_GetCarbonEmission(int _countryCode);
	SV_SIMULATOR_API float Inter_GetTaxRate(int _countryCode);
	
	SV_SIMULATOR_API float Inter_GetWorldTemperature();
	SV_SIMULATOR_API long long Inter_GetWorldCarbonEmission();
	SV_SIMULATOR_API long long Inter_GetWorldPopulation();
	SV_SIMULATOR_API float Inter_GetWorldCarbonPPM();
	
	
	//SV_SIMULATOR_API int Inter_EnforcePolicy(int _countryCode, int _policyCode);
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
}
//************************************************

