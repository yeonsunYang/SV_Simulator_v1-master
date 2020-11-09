#pragma once
#include "..\inGame\Game.h"
#include "pch.h"

#define MINCYCLE 500

#define SV_SIMULAYOR_API __declspec(dllexport)

// Interface Method 선언****************************************************************

/// <summary>
/// 게임 시작 직후 반드시 호출. 게임 중 단 한번만 호출 가능. flag 값들 초기화. game 생성 초기화
/// </summary>
/// <param name="_cycle"> oneday의 호출 주기 (ms 단위), 500이상 값만 유효함. </param>
/// <param name="_debugMode">Debug 모드 (0 ~ 2) </param>
/// <returns></returns>
extern "C" SV_SIMULAYOR_API void SV_Interface_InitGame(unsigned int _cycle, int _debugMode);

/// <summary>
/// thread_exit = false로 초기화, thread 생성 및 detach 
/// </summary>
/// <returns></returns>
extern "C" SV_SIMULAYOR_API void SV_Interface_PlayGame();

/// <summary>
/// 게임 종료를 위해서 반드시 호출. 쓰레드 종료, flag 값들 초기화, Game 해제 및 삭제
/// </summary>
/// <returns></returns>
extern "C" SV_SIMULAYOR_API void SV_Interface_EndGame();
extern "C" SV_SIMULAYOR_API LPCTSTR SV_Interface_GetData();
extern "C" SV_SIMULAYOR_API LPCTSTR SV_Interface_EnforcePolicy(int _countryCode, int _policyCode);
//***************************************************************************************


// only Dll Method (DLL 내부에서만 작동하는 함수)****
void SV_WriteJson();
void SV_Run();
void SV_DebugLog(const char*, int);
void SV_ErrorLog(const char*);
//************************************************


// type of Debug Log
enum {
	LogType, FuncType
};

/// <summary>
/// true: thread 종료 / InitGame()호출시 false / PlayGame()호출시 false / EndGame() 호출 시 true
/// </summary>
bool thread_exit = false;

/// <summary>
/// true: thread 실행 중 / Run() 도입시 true, 반환 전 false 
/// </summary>
bool thread_run = false;

/// <summary>
/// true: 초기화 실행된 경우 / false의 경우 어떠한 함수도 사용할 수 없다. / EndGame() 호출 시 false
/// </summary>
bool isInit = false;

/// <summary>
/// true: Debug용 Log 출력 / initGame의 매개변수에 종속
/// </summary>
bool lDebugMode = false;

/// <summary>
/// true: Debug용 함수 이름 출력 / initGame의 매개변수에 종속
/// </summary>
bool fDebugMode = false;



std::string jsonDocument;
Json::Value root;
Json::StreamWriterBuilder wbuilder;

// game 포인터 선언
Game* game = nullptr;

// oneDay의 호출 주기 ms 단위, MINCYCLE 이상의 값만 입력됨.
unsigned int oneDayCycle;