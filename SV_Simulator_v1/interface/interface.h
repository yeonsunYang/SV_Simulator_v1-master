#pragma once
#include "..\inGame\Game.h"
#include "pch.h"

#define MINCYCLE 500

#define SV_SIMULAYOR_API __declspec(dllexport)

// Interface Method ����****************************************************************

/// <summary>
/// ���� ���� ���� �ݵ�� ȣ��. ���� �� �� �ѹ��� ȣ�� ����. flag ���� �ʱ�ȭ. game ���� �ʱ�ȭ
/// </summary>
/// <param name="_cycle"> oneday�� ȣ�� �ֱ� (ms ����), 500�̻� ���� ��ȿ��. </param>
/// <param name="_debugMode">Debug ��� (0 ~ 2) </param>
/// <returns></returns>
extern "C" SV_SIMULAYOR_API void SV_Interface_InitGame(unsigned int _cycle, int _debugMode);

/// <summary>
/// thread_exit = false�� �ʱ�ȭ, thread ���� �� detach 
/// </summary>
/// <returns></returns>
extern "C" SV_SIMULAYOR_API void SV_Interface_PlayGame();

/// <summary>
/// ���� ���Ḧ ���ؼ� �ݵ�� ȣ��. ������ ����, flag ���� �ʱ�ȭ, Game ���� �� ����
/// </summary>
/// <returns></returns>
extern "C" SV_SIMULAYOR_API void SV_Interface_EndGame();
extern "C" SV_SIMULAYOR_API LPCTSTR SV_Interface_GetData();
extern "C" SV_SIMULAYOR_API LPCTSTR SV_Interface_EnforcePolicy(int _countryCode, int _policyCode);
//***************************************************************************************


// only Dll Method (DLL ���ο����� �۵��ϴ� �Լ�)****
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
/// true: thread ���� / InitGame()ȣ��� false / PlayGame()ȣ��� false / EndGame() ȣ�� �� true
/// </summary>
bool thread_exit = false;

/// <summary>
/// true: thread ���� �� / Run() ���Խ� true, ��ȯ �� false 
/// </summary>
bool thread_run = false;

/// <summary>
/// true: �ʱ�ȭ ����� ��� / false�� ��� ��� �Լ��� ����� �� ����. / EndGame() ȣ�� �� false
/// </summary>
bool isInit = false;

/// <summary>
/// true: Debug�� Log ��� / initGame�� �Ű������� ����
/// </summary>
bool lDebugMode = false;

/// <summary>
/// true: Debug�� �Լ� �̸� ��� / initGame�� �Ű������� ����
/// </summary>
bool fDebugMode = false;



std::string jsonDocument;
Json::Value root;
Json::StreamWriterBuilder wbuilder;

// game ������ ����
Game* game = nullptr;

// oneDay�� ȣ�� �ֱ� ms ����, MINCYCLE �̻��� ���� �Էµ�.
unsigned int oneDayCycle;