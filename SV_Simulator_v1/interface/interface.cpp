#include "pch.h"
#include "interface.h"


void SV_Run()
{
	SV_DebugLog("SV_Run() - start", FuncType);

	thread_run = true;

	while (!thread_exit)
	{
		if (oneDayCycle < MINCYCLE) {
			SV_ErrorLog("SV_Run(): oneDayCycle�� ũ�Ⱑ MINCYCLE ���� �۽��ϴ�.");
			break;
		}

		Sleep(oneDayCycle);

		if (game == nullptr) {
			SV_ErrorLog("SV_Run(): game �ν��Ͻ��� nullptr ���� ���� �õ��� �Ͽ�, Thread�� �����մϴ�.");
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
		SV_ErrorLog("SV_WriteJson(): nullptr�� ���ٽõ��� �մϴ�.");
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
		SV_ErrorLog("thread�� �۵����϶� InitGame()�� ȣ��Ǿ����ϴ�.");
		return;
	}

	//**************************
	//game ���� �� �ʱ�ȭ

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

	//Thread ���� �� detach********************
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
	//game ����
	// thread�� �۵����̸� 0.1ms�� 30ȸ ���. �ִ� 3�� ���

	for (int i = 0; i < 30; i++) {

		if (thread_run)
			Sleep(100);
		else {
			if (game == nullptr) {
				SV_ErrorLog("SV_Interface_EndGame(): nullptr�� �����Ϸ��� �õ��� �մϴ�.");
				return;
			}
			cout <<(i * 100) << "ms ��� �� ���� �Ǿ����ϴ�." << endl;
			delete game;
			game = nullptr;
			return;
		}
	}

	SV_ErrorLog("SV_Interface_EndGame(): Thread�� ������� �ʾƼ� game�����͸� ������ �� �����ϴ�.");

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
	cout << "����ġ ���� ��Ȳ�Դϴ�. ����ڿ��� �������ּ���." << endl;
	cout << "SV_ERO: "<<_str << endl;
	cout << "***************************************************************" << endl;

}