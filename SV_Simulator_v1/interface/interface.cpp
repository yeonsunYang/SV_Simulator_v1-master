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
		//Pause() 체크
		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		start = clock();
		// work() 호출
		SV_Sim::Work();
		if(SV_Sim::simState == SimState::WaitEnd)
			break;
		end = clock();
		delta = end - start;


		waitTime = static_cast<time_t> (oneDayCycle / static_cast<long long> (SV_Sim::playSpeed));

		// 연산이 매우 길어져서 연산에 소요된 시간이 waitTime보다 길어질 경우.

		if (delta > waitTime)
			delta = waitTime;

		//Pause() 체크
		if (SV_Sim::simState == SimState::Pause)
			SV_Sim::Pause();

		// Wait() 호출
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

int InitGame(long long _cycle, int _debugMode)
{
	SV_Sim::DebugLog("InitGame()", LogType::Func);

	if (SV_Sim::simState != SimState::Disable)
		return static_cast<int> (SV_Sim::simState);

	//**************************
	//game 생성 및 초기화

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
int PlayGame()
{
	SV_Sim::DebugLog("PlayGame()", LogType::Func);

	if (SV_Sim::simState != SimState::WaitPlay)
		return static_cast<int> (SV_Sim::simState);


	SV_Sim::simState = SimState::InitThread;

	//Thread 생성 및 detach********************
	std::thread Simulator(SV_Sim::Run);
	Simulator.detach();
	//****************************************

	return 0;
}
int Pause()
{
	SV_Sim::DebugLog("Pause()", LogType::Func);

	if(SV_Sim::simState == SimState::Work)
		SV_Sim::simState = SimState::Pause;

	return 0;
}
int Resume()
{
	SV_Sim::DebugLog("Resume()", LogType::Func);

	if (SV_Sim::simState == SimState::Pause)
		SV_Sim::simState = SimState::Work;

	return 0;
}
int EndGame()
{
	SV_Sim::DebugLog("EndGame()", LogType::Func);


	time_t start = clock();

	SV_Sim::simState = SimState::WaitEnd;

	//**************************
	// game 해제
	// thread가 작동 중 이면 50ms씩 최대 3초 대기
	while (SV_Sim::simState != SimState::EndThread)
	{
		Sleep(50);

		if (clock() - start > 3000) {
			SV_Sim::ErrorLog("EndGame(): Thread가 종료되지 않아서 game포인터를 해제할 수 없습니다.");
			return -1;
		}
	}

	if (SV_Sim::game == nullptr) {
		SV_Sim::ErrorLog("EndGame(): nullptr을 해제하려는 시도를 합니다.");
		return -2;
	}

	delete SV_Sim::game;
	SV_Sim::game = nullptr;

	SV_Sim::simState = SimState::Disable;

	return 0;
	//**************************

}
int DoubleSpeed()
{
	SV_Sim::DebugLog("DoubleSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Double;
	return 0;
}
int QuadSpeed()
{
	SV_Sim::DebugLog("QuadSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Quad;
	return 0;
}
int OctoSpeed()
{
	SV_Sim::DebugLog("OctoSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Octo;
	return 0;
}
int NormalSpeed()
{
	SV_Sim::DebugLog("NormalSpeed()", LogType::Func);

	SV_Sim::playSpeed = PlaySpeed::Normal;
	return 0;
}

void SV_Sim::DebugLog(const char* _str, LogType _type)
{
	// debugMode 0: log 출력 안함.
	// debugMode 1: msg log만 출력.
	// debugMode 2: msg, func log 둘다 출력.
	if (SV_Sim::debugMode > static_cast<int> (_type))
		cout << "SV_LOG: " << _str << endl;

}
void SV_Sim::ErrorLog(const char* _str)
{
	cout << "***************************************************************" << endl;
	cout << "예기치 못한 상황입니다. 담당자에게 보고해주세요." << endl;
	cout << "SV_ERO: "<<_str << endl;
	cout << "***************************************************************" << endl;
}

int Today()
{
	return SV_Sim::game->Today();
}

//******************************** world class data

// 전세계 평균 온도 반환
float GetWorldTemperature()
{
	return 13.0f;
}
// 전세계 평균탄소농도 반환
float GetWorldCarbonPPM()
{
	return 14.0f;
}
// 전세계 탄소배출량(일 단위) 반환
long long GetWorldCarboneEmission()
{
	return 15;
}
// 전세계 탄소 흡수량(일 단위) 반환
long long GetWorldCarbonAbsorbed()
{
	return 16;
}
// 전세계 산림 면적 반환
long long GetWorldForest()
{
	return 17;
}
// 전세계 인구 수 반환
long long GetWorldPopulation()
{
	return 18;
}
// 전세계 사만자 수 반환
long long GetWorldDead()
{
	return 19;
}
// 전세계 기후난민 수 반환
long long GetWorldRefugees()
{
	return 20;
}
// 전세계 작물생산량 (단위는 '몇 인분')
long long GetWorldFood()
{
	return 21;
}


//// 재난 발생확률
//float GetDisasterProbability();
//// 작물생산량 임계점 (초기화 필요)
//long long GetFoodCriticalPoint();
//// 평균온도 임계점 (초기화 필요)
//float GetTempCriticalPoint();

//********************************************************

//******************************** country class 개요 패널
// 해당 국가의 예산 반환
long long GetBudget(int _countryCode)
{
	return 22 + static_cast<long long> (_countryCode);
}
// 해당 국가의 GDP 반환
long long GetGDP(int _countryCode)
{
	return 23 + static_cast<long long> (_countryCode);
}
// 해당 국가의 세율 반환
float GetTaxRate(int _countryCode)
{
	return 24.0f + static_cast<float>(_countryCode);
}
// 해당 국가의 식량 생산량
long long GetFood(int _countryCode)
{
	return 25 + static_cast<long long> (_countryCode);
}
// 해당 국가의 탄소배출량 반환
long long GetCarbonEmission(int _countryCode)
{
	return 26 + static_cast<long long> (_countryCode);
}
// 해당 국가의 산림면적 반환
int GetCountryForest(int _countryCode)
{
	return 27 + _countryCode;
}
// 해당 국가의 총 인구수 반환
long long GetPopulation(int _countryCode)
{
	return 28 + static_cast<long long> (_countryCode);
}
// 해당 국가의 국가 사망자 비율 반환
float GetDeadRate(int _countryCode)
{
	return 29 + _countryCode;
}
// 해당 국가의 기후난민 비율 반환
float GetRefugeeRate(int _countryCode)
{
	return 30.0f + static_cast<float>(_countryCode);
}
// 해당 국가의 국가 사망자수 반환
long long GetDead(int _countryCode)
{
	return 31 + static_cast<long long>(_countryCode);
}
// 해당 국가의 기후난민수 반환
long long GetRefugees(int _countryCode)
{
	return 32 + static_cast<long long>(_countryCode);
}
// 해당 국가에서의 기후에 대한 인식율 반환
float GetRecognitionRate(int _countryCode)
{
	return 33.0f + static_cast<float>(_countryCode);
}
// 해당 국가에서의 플레이어 지지도 반환
float GetSupportRate(int _countryCode)
{
	return 34.0f + static_cast<float>(_countryCode);
}

	
	
//// 해당 국가의 벌목률 반환
//float GetRemoveForest(int _countryCode);
	
//************************************* Country class Energy 패널
// 해당 국가의 산업에서 요구 에너지 반환
int GetIndustryEnergy(int _countryCode)
{
	return 35 + _countryCode;
}
// 해당 국가의 생활 요구 에너지 반환
int GetLifeEnergy(int _countryCode)
{
	return 36 + _countryCode;
}
// 해당 국가의 총 발전소 개수 반환
int GetTotalPowerPlants(int _countryCode)
{
	return 37 + _countryCode;
}
// 해당 국가의 신재생에너지 발전소 개수 반환
int GetGreenPowerPlants(int _countryCode)
{
	return 38 + _countryCode;
}
// 해당 국가의 석탄화력 발전소 개수 반환
int GetFirePowerPlants(int _countryCode)
{
	return 39 + _countryCode;
}
// 해당 국가의 발전소당 발전량(발전효율) 반환
int GetProduce(int _countryCode)
{
	return 40 + _countryCode;
}
// 해당 국가의 석탄발전소 당 탄소배출량 반환
long long GetCarbonPerProduce(int _countryCode)
{
	return 41 + static_cast<long long> (_countryCode);
}


//************************************* Country class Life 패널

// 해당 국가의 1인당 자동차 소유 비율
float GetCarPerPerson(int _countryCode)
{
	return 42.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 총 차량 수
long long GetCars(int _countryCode)
{
	return 43 + static_cast<long long> (_countryCode);
}
// 해당 국가의 내연기관 자동차 비율
float GetFossilFuelCarsRatio(int _countryCode)
{
	return 44.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 친환경 자동차 비율
float GetEcocarRation(int _countryCode)
{
	return 45.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 자동차 당 일일 탄소 배출량
long long GetCarbonPerCar(int _countryCode)
{
	return 46 + static_cast<long long> (_countryCode);
}
// 해당 국가의 교통 탄소세
float GetTaxTransprot(int _countryCode)
{
	return 47.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 총 집의 개수
long long GetHouses(int _countryCode)
{
	return 48 + static_cast<long long> (_countryCode);
}
// 해당 국가의 일반 집의 비율
float GetGrayHouses(int _countryCode)
{
	return 49.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 그린리모델링 비율
float GetGreenHouses(int _countryCode)
{
	return 50.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 태양관 패널 설치 비율
float GetSunHouses(int _countryCode)
{
	return 51.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 건물 당 일일 탄소 배출량
long long GetCarbonPerHouse(int _countryCode)
{
	return 52 + static_cast<long long> (_countryCode);
}
// 해당 국가의 주거 탄소세
float GetTaxHouse(int _countryCode)
{
	return 53.0f + static_cast <float> (_countryCode);
}
// 해당 국가의 일상속 1인당 탄소 배출
long long GetCarbonPerPerson(int _countryCode)
{
	return 54 + static_cast<long long> (_countryCode);
}
// 해당 국가의 생활에서 발생하는 일일 총 탄소량
long long GetLifeCarbonEmission(int _countryCode)
{
	return 55 + static_cast<long long> (_countryCode);
}
// 해당 국가의 생활속 탄소세지수
float GetTaxLife(int _countryCode)
{
	return 56.0f + static_cast <float> (_countryCode);
}
