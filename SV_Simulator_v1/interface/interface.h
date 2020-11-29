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
	SV_SIMULATOR_API int Inter_DoubleSpeed();
	SV_SIMULATOR_API int Inter_QuadSpeed();
	SV_SIMULATOR_API int Inter_OctoSpeed();
	SV_SIMULATOR_API int Inter_NormalSpeed();

	
	//******************************** world class data
	// 현재 날짜 반환
	SV_SIMULATOR_API int Inter_Today();
	// 전세계 평균 온도 반환
	SV_SIMULATOR_API float Inter_GetWorldTemperature();
	// 전세계 평균탄소농도 반환
	SV_SIMULATOR_API float Inter_GetWorldCarbonPPM();
	// 전세계 탄소배출량(일 단위) 반환
	SV_SIMULATOR_API long long Inter_GetWorldCarboneEmission();
	// 전세계 탄소 흡수량(일 단위) 반환
	SV_SIMULATOR_API long long Inter_GetWorldCarbonAbsorbed();
	// 전세계 산림 면적 반환
	SV_SIMULATOR_API long long Inter_GetWorldForest();
	// 전세계 인구 수 반환
	SV_SIMULATOR_API long long Inter_GetWorldPopulation();
	// 전세계 사만자 수 반환
	SV_SIMULATOR_API long long Inter_GetWorldDead();
	// 전세계 기후난민 수 반환
	SV_SIMULATOR_API long long Inter_GetWorldRefugees();
	// 전세계 작물생산량 (단위는 '몇 인분')
	SV_SIMULATOR_API long long Inter_GetWorldFood();
	// 재난 발생확률
	SV_SIMULATOR_API float Inter_GetDisasterProbability();
	// 작물생산량 임계점 (초기화 필요)
	SV_SIMULATOR_API long long Inter_GetFoodCriticalPoint();
	// 평균온도 임계점 (초기화 필요)
	SV_SIMULATOR_API float Inter_GetTempCriticalPoint();

	//********************************************************

	//******************************** country class data
	// 해당 국가의 예산 반환
	SV_SIMULATOR_API long long Inter_GetBudget(int _countryCode);
	// 해당 국가의 GDP 반환
	SV_SIMULATOR_API long long Inter_GetGDP(int _countryCode);
	// 해당 국가의 총 인구수 반환
	SV_SIMULATOR_API long long Inter_GetPopulation(int _countryCode);
	// 해당 국가의 탄소배출량 반환
	SV_SIMULATOR_API long long Inter_GetCarbonEmission(int _countryCode);
	// 해당 국가의 산림면적 반환
	SV_SIMULATOR_API int Inter_GetCountryForest();
	// 해당 국가의 세율 반환
	SV_SIMULATOR_API float Inter_GetTaxRate(int _countryCode);
	// 해당 국가에서의 플레이어 지지도 반환
	SV_SIMULATOR_API float Inter_GetSupportRate(int _countryCode);
	// 해당 국가에서의 기후에 대한 인식율 반환
	SV_SIMULATOR_API float Inter_GetRecognitionRate(int _countryCode);
	// 해당 국가의 기후난민 비율 반환
	SV_SIMULATOR_API float Inter_GetRefugeeRate(int _countryCode);
	// 해당 국가의 국가 사망자 비율 반환
	SV_SIMULATOR_API float Inter_GetDeadRate(int _countryCode);
	// 해당 국가의 작물 생산량 반환
	SV_SIMULATOR_API long long Inter_GetFood(int _countryCode);
	// 해당 국가의 벌목률 반환
	SV_SIMULATOR_API float Inter_GetRemoveForest(int _countryCode);
	
	
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
	PlaySpeed playSpeed;
}
//************************************************

