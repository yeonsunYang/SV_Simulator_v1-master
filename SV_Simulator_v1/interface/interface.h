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
// Interface Method 선언****************************************************************

extern "C" {
	/// <summary>
	/// 게임 시작 직후 반드시 호출. 게임 중 단 한번만 호출 가능. game 생성 초기화.
	/// state를 WaitPlay로 설정
	/// </summary>
	/// <param name="_cycle"> oneday의 호출 주기 (ms 단위), 500이상 ~ 5000 이하 값만 유효함. </param>
	/// <param name="_debugMode">Debug 모드 (0 ~ 2) </param>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_InitGame(long long _cycle, int _debugMode);

	/// <summary>
	/// thread 생성 및 detach. state를 InitThread 상태로 설정.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_PlayGame();

	/// <summary>
	/// 게임 종료를 위해서 반드시 호출. game 포인터 해제. state를 WaitEnd 상태로 설정 후, EndGame이 될때 까지 대기. EndGame 확인 후 Disable로 설정
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_EndGame();
	/// <summary>
	/// 게임 일시정지. state를 Pause 상태로 설정.
	/// </summary>
	/// <returns></returns>
	SV_SIMULATOR_API int Inter_Pause();
	/// <summary>
	/// 게임 재개. state를 work 상태로 설정.
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

// only Dll Method (DLL 내부에서만 작동하는 함수)****
namespace SV_Sim {
	int Run();
	int Work();
	int Pause();
	int Wait(time_t);
	void DebugLog(const char*, LogType);
	void ErrorLog(const char*);


	Game* game = nullptr;

	// oneDay의 호출 주기 ms 단위, MINCYCLE 이상의 값만 입력됨.
	static time_t oneDayCycle;
	static SimState simState = SimState::Disable;
	int debugMode;
}
//************************************************

