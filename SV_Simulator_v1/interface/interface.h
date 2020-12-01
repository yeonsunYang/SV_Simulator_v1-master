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
	
	//******************************** world class data

	// 전세계 평균 온도 반환
	SV_SIMULATOR_API float GetWorldTemperature();
	// 전세계 평균탄소농도 반환
	SV_SIMULATOR_API float GetWorldCarbonPPM();
	// 전세계 탄소배출량(일 단위) 반환
	SV_SIMULATOR_API long long GetWorldCarboneEmission();
	// 전세계 탄소 흡수량(일 단위) 반환
	SV_SIMULATOR_API long long GetWorldCarbonAbsorbed();
	// 전세계 산림 면적 반환
	SV_SIMULATOR_API long long GetWorldForest();
	// 전세계 인구 수 반환
	SV_SIMULATOR_API long long GetWorldPopulation();
	// 전세계 사만자 수 반환
	SV_SIMULATOR_API long long GetWorldDead();
	// 전세계 기후난민 수 반환
	SV_SIMULATOR_API long long GetWorldRefugees();
	// 전세계 작물생산량 (단위는 '몇 인분')
	SV_SIMULATOR_API long long GetWorldFood();


	//// 재난 발생확률
	//SV_SIMULATOR_API float GetDisasterProbability();
	//// 작물생산량 임계점 (초기화 필요)
	//SV_SIMULATOR_API long long GetFoodCriticalPoint();
	//// 평균온도 임계점 (초기화 필요)
	//SV_SIMULATOR_API float GetTempCriticalPoint();

	//********************************************************

	//******************************** country class 개요 패널
	// 해당 국가의 예산 반환
	SV_SIMULATOR_API long long GetBudget(int _countryCode);
	// 해당 국가의 GDP 반환
	SV_SIMULATOR_API long long GetGDP(int _countryCode);
	// 해당 국가의 세율 반환
	SV_SIMULATOR_API float GetTaxRate(int _countryCode);
	// 해당 국가의 식량 생산량
	SV_SIMULATOR_API long long GetFood(int _countryCode);
	// 해당 국가의 탄소배출량 반환
	SV_SIMULATOR_API long long GetCarbonEmission(int _countryCode);
	// 해당 국가의 산림면적 반환
	SV_SIMULATOR_API int GetCountryForest(int _countryCode);
	// 해당 국가의 총 인구수 반환
	SV_SIMULATOR_API long long GetPopulation(int _countryCode);
	// 해당 국가의 국가 사망자 비율 반환
	SV_SIMULATOR_API float GetDeadRate(int _countryCode);
	// 해당 국가의 기후난민 비율 반환
	SV_SIMULATOR_API float GetRefugeeRate(int _countryCode);
	// 해당 국가의 국가 사망자수 반환
	SV_SIMULATOR_API long long GetDead(int _countryCode);
	// 해당 국가의 기후난민수 반환
	SV_SIMULATOR_API long long GetRefugees(int _countryCode);
	// 해당 국가에서의 기후에 대한 인식율 반환
	SV_SIMULATOR_API float GetRecognitionRate(int _countryCode);
	// 해당 국가에서의 플레이어 지지도 반환
	SV_SIMULATOR_API float GetSupportRate(int _countryCode);

	
	
	//// 해당 국가의 벌목률 반환
	//SV_SIMULATOR_API float GetRemoveForest(int _countryCode);
	
	//************************************* Country class Energy 패널
	// 해당 국가의 산업에서 요구 에너지 반환
	SV_SIMULATOR_API int GetIndustryEnergy(int _countryCode);
	// 해당 국가의 생활 요구 에너지 반환
	SV_SIMULATOR_API int GetLifeEnergy(int _countryCode);
	// 해당 국가의 총 발전소 개수 반환
	SV_SIMULATOR_API int GetTotalPowerPlants(int _countryCode);
	// 해당 국가의 신재생에너지 발전소 개수 반환
	SV_SIMULATOR_API int GetGreenPowerPlants(int _countryCode);
	// 해당 국가의 석탄화력 발전소 개수 반환
	SV_SIMULATOR_API int GetFirePowerPlants(int _countryCode);
	// 해당 국가의 발전소당 발전량(발전효율) 반환
	SV_SIMULATOR_API int GetProduce(int _countryCode);
	// 해당 국가의 석탄발전소 당 탄소배출량 반환
	SV_SIMULATOR_API long long GetCarbonPerProduce(int _countryCode);


	//************************************* Country class Life 패널

	// 해당 국가의 1인당 자동차 소유 비율
	SV_SIMULATOR_API float GetCarPerPerson(int _countryCode);
	// 해당 국가의 총 차량 수
	SV_SIMULATOR_API long long GetCars(int _countryCode);
	// 해당 국가의 내연기관 자동차 비율
	SV_SIMULATOR_API float GetFossilFuelCarsRatio(int _countryCode);
	// 해당 국가의 친환경 자동차 비율
	SV_SIMULATOR_API float GetEcocarRation(int _countryCode);
	// 해당 국가의 자동차 당 일일 탄소 배출량
	SV_SIMULATOR_API long long GetCarbonPerCar(int _countryCode);
	// 해당 국가의 교통 탄소세
	SV_SIMULATOR_API float GetTaxTransprot(int _countryCode);
	// 해당 국가의 총 집의 개수
	SV_SIMULATOR_API long long GetHouses(int _countryCode);
	// 해당 국가의 일반 집의 비율
	SV_SIMULATOR_API float GetGrayHouses(int _countryCode);
	// 해당 국가의 그린리모델링 비율
	SV_SIMULATOR_API float GetGreenHouses(int _countryCode);
	// 해당 국가의 태양관 패널 설치 비율
	SV_SIMULATOR_API float GetSunHouses(int _countryCode);
	// 해당 국가의 건물 당 일일 탄소 배출량
	SV_SIMULATOR_API long long GetCarbonPerHouse(int _countryCode);
	// 해당 국가의 주거 탄소세
	SV_SIMULATOR_API float GetTaxHouse(int _countryCode);

	// 해당 국가의 일상속 1인당 탄소 배출
	SV_SIMULATOR_API long long GetCarbonPerPerson(int _countryCode);
	// 해당 국가의 생활에서 발생하는 일일 총 탄소량
	SV_SIMULATOR_API long long GetLifeCarbonEmission(int _countryCode);
	// 해당 국가의 생활속 탄소세지수
	SV_SIMULATOR_API float GetTaxLife(int _countryCode);



	
	//SV_SIMULATOR_API int EnforcePolicy(int _countryCode, int _policyCode);
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

