#include "pch.h"
#include "interface.h"


void SV_Run()
{
	SV_DebugLog("SV_Run() - start", FuncType);

	thread_run = true;

	while (!thread_exit)
	{
		if (oneDayCycle < MINCYCLE) {
			SV_ErrorLog("SV_Run(): oneDayCycle의 크기가 MINCYCLE 보다 작습니다.");
			break;
		}

		Sleep(oneDayCycle);

		if (game == nullptr) {
			SV_ErrorLog("SV_Run(): game 인스턴스의 nullptr 값을 참조 시도를 하여, Thread를 종료합니다.");
			break;
		}
		game->Oneday();
	}

	thread_run = false;

	SV_DebugLog("SV_Run() - end", FuncType);
}

void SV_WriteJson()
{
	SV_DebugLog("SV_WriteJson", FuncType);

	if (game == nullptr) {
		SV_ErrorLog("SV_WriteJson(): nullptr에 접근시도를 합니다.");
		return;
	}
	root["Date"] = game->Today();
	jsonDocument = Json::writeString(wbuilder, root);
}

void SV_Interface_InitGame(unsigned int _cycle, int _debugMode)
{

	if (isInit)
		return;

	if (thread_run) {
		SV_ErrorLog("thread가 작동중일때 InitGame()이 호출되었습니다.");
		return;
	}

	//**************************
	//game 생성 및 초기화

	if(game == nullptr)
		game = new Game();

	//**************************

	switch (_debugMode) {
	case 2:
		fDebugMode = true;
		lDebugMode = true;
		break;

	case 1:
		fDebugMode = false;
		lDebugMode = true;
		break;

	default:
		fDebugMode = false;
		lDebugMode = false;
		break;
	}

	
	oneDayCycle = max(MINCYCLE, _cycle);

	thread_exit = false;
	thread_run = false;
	isInit = true;
}

void SV_Interface_PlayGame()
{
	SV_DebugLog("SV_Interface_PlayGame()", FuncType);

	if (!isInit)
		return;

	if (thread_run)
		return;


	thread_exit = false;

	//Thread 생성 및 detach********************
	std::thread Simulator(SV_Run);
	Simulator.detach();
	//****************************************
}
LPCTSTR SV_Interface_GetData()
{
	SV_DebugLog("SV_Interface_GetData()", FuncType);

	SV_WriteJson();

	return (LPCTSTR) jsonDocument.c_str();
}


LPCTSTR SV_Interface_EnforcePolicy(int _countryCode, int _policyCode)
{
	SV_DebugLog("SV_Interface_GetData()", FuncType);

	if (!isInit)
		return nullptr;
	if (!thread_run)
		return nullptr;

	game->EnforcePolicy(_countryCode, _policyCode);

	return SV_Interface_GetData();
}


void SV_Interface_EndGame()
{
	SV_DebugLog("SV_Interface_EndGame()", FuncType);

	thread_exit = true;
	isInit = false;
	lDebugMode = false;
	fDebugMode = false;

	//**************************
	//game 해제
	// thread가 작동중이면 0.1ms씩 30회 대기. 최대 3초 대기

	for (int i = 0; i < 30; i++) {

		if (thread_run)
			Sleep(100);
		else {
			if (game == nullptr) {
				SV_ErrorLog("SV_Interface_EndGame(): nullptr을 해제하려는 시도를 합니다.");
				return;
			}
			cout <<(i * 100) << "ms 대기 후 종료 되었습니다." << endl;
			delete game;
			game = nullptr;
			return;
		}
	}

	SV_ErrorLog("SV_Interface_EndGame(): Thread가 종료되지 않아서 game포인터를 해제할 수 없습니다.");

	//**************************

}

void SV_DebugLog(const char* _str, int _type)
{
	if (_type == FuncType && fDebugMode)
		cout << "SV_LOG: " << _str << endl;

	else if (_type == LogType && lDebugMode)
		cout << "SV_LOG: " << _str << endl;
}

void SV_ErrorLog(const char* _str)
{
	cout << "***************************************************************" << endl;
	cout << "예기치 못한 상황입니다. 담당자에게 보고해주세요." << endl;
	cout << "SV_ERO: "<<_str << endl;
	cout << "***************************************************************" << endl;

}