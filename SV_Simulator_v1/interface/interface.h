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
// Interface Method 선언****************************************************************

extern "C" {
	/// <summary>
	/// 게임 시작 직후 반드시 호출. 게임 중 단 한번만 호출 가능. game 생성 초기화.
	/// state를 WaitPlay로 설정
	/// </summary>
	/// <param name="_cycle"> oneday의 호출 주기 (ms 단위), 500이상 ~ 100,000 이하 값만 유효함. </param>
	/// <param name="_debugMode">Debug 모드 (0 ~ 2) </param>
	/// <returns></returns>
	SV_SIMULATOR_API int InitGame(long long _cycle, int _debugMode);

	// thread 생성 및 detach. state를 InitThread 상태로 설정.
	SV_SIMULATOR_API int PlayGame();

	// 게임 종료를 위해서 반드시 호출. game 포인터 해제. state를 WaitEnd 상태로 설정 후, EndGame이 될때 까지 대기. EndGame 확인 후 Disable로 설정
	SV_SIMULATOR_API int EndGame();
	// 게임 일시정지. state를 Pause 상태로 설정.
	SV_SIMULATOR_API int Pause();
	// 게임 재개. state를 work 상태로 설정.
	SV_SIMULATOR_API int Resume();
	// 시뮬레이터 속도를 2배로 증가
	SV_SIMULATOR_API int DoubleSpeed();
	// 시뮬레이터 속도를 4배로 증가
	SV_SIMULATOR_API int QuadSpeed();
	// 시뮬레이터 속도를 8배로 증가
	SV_SIMULATOR_API int OctoSpeed();
	// 시뮬레이터 속도를 원래 속도로 변경
	SV_SIMULATOR_API int NormalSpeed();
	// 현재 날짜 반환
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

// only Dll Method (DLL 내부에서만 작동하는 함수)****
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

	// oneDay의 호출 주기 ms 단위, MINCYCLE 이상의 값만 입력됨.
	static time_t oneDayCycle;
	static SimState simState = SimState::Disable;
	int debugMode;
	PlaySpeed playSpeed;
}
//************************************************

