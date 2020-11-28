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

/// <summary>
/// ���� ���� ���� �ݵ�� ȣ��. ���� �� �� �ѹ��� ȣ�� ����. flag ���� �ʱ�ȭ. game ���� �ʱ�ȭ
/// </summary>
/// <param name="_cycle"> oneday�� ȣ�� �ֱ� (ms ����), 500�̻� ���� ��ȿ��. </param>
/// <param name="_debugMode">Debug ��� (0 ~ 2) </param>
/// <returns></returns>
extern "C" SV_SIMULATOR_API int Inter_InitGame(long long _cycle, int _debugMode);

/// <summary>
/// thread_exit = false�� �ʱ�ȭ, thread ���� �� detach 
/// </summary>
/// <returns></returns>
extern "C" SV_SIMULATOR_API int Inter_PlayGame();

/// <summary>
/// ���� ���Ḧ ���ؼ� �ݵ�� ȣ��. ������ ����, flag ���� �ʱ�ȭ, Game ���� �� ����
/// </summary>
/// <returns></returns>
extern "C" SV_SIMULATOR_API int Inter_EndGame();
extern "C" SV_SIMULATOR_API long long Inter_GetData();
extern "C" SV_SIMULATOR_API int Inter_Pause();
extern "C" SV_SIMULATOR_API int Inter_Resume();
extern "C" SV_SIMULATOR_API int Inter_EnforcePolicy(int _countryCode, int _policyCode);
//***************************************************************************************


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


// type of Debug Log


/// <summary>
/// true: thread ���� / InitGame()ȣ��� false / PlayGame()ȣ��� false / EndGame() ȣ�� �� true
/// </summary>
//bool thread_exit = false;

/// <summary>
/// true: thread ���� �� / Run() ���Խ� true, ��ȯ �� false 
/// </summary>
//bool thread_run = false;

/// <summary>
/// true: �ʱ�ȭ ����� ��� / false�� ��� ��� �Լ��� ����� �� ����. / EndGame() ȣ�� �� false
/// </summary>
//bool isInit = false;

/// <summary>
/// true: Debug�� Log ��� / initGame�� �Ű������� ����
/// </summary>
//bool lDebugMode = false;

/// <summary>
/// true: Debug�� �Լ� �̸� ��� / initGame�� �Ű������� ����
/// </summary>
//bool fDebugMode = false;



// game ������ ����
