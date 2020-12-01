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
// Interface Method ����****************************************************************

extern "C" {
	/// <summary>
	/// ���� ���� ���� �ݵ�� ȣ��. ���� �� �� �ѹ��� ȣ�� ����. game ���� �ʱ�ȭ.
	/// state�� WaitPlay�� ����
	/// </summary>
	/// <param name="_cycle"> oneday�� ȣ�� �ֱ� (ms ����), 500�̻� ~ 100,000 ���� ���� ��ȿ��. </param>
	/// <param name="_debugMode">Debug ��� (0 ~ 2) </param>
	/// <returns></returns>
	SV_SIMULATOR_API int InitGame(long long _cycle, int _debugMode);

	// thread ���� �� detach. state�� InitThread ���·� ����.
	SV_SIMULATOR_API int PlayGame();

	// ���� ���Ḧ ���ؼ� �ݵ�� ȣ��. game ������ ����. state�� WaitEnd ���·� ���� ��, EndGame�� �ɶ� ���� ���. EndGame Ȯ�� �� Disable�� ����
	SV_SIMULATOR_API int EndGame();
	// ���� �Ͻ�����. state�� Pause ���·� ����.
	SV_SIMULATOR_API int Pause();
	// ���� �簳. state�� work ���·� ����.
	SV_SIMULATOR_API int Resume();
	// �ùķ����� �ӵ��� 2��� ����
	SV_SIMULATOR_API int DoubleSpeed();
	// �ùķ����� �ӵ��� 4��� ����
	SV_SIMULATOR_API int QuadSpeed();
	// �ùķ����� �ӵ��� 8��� ����
	SV_SIMULATOR_API int OctoSpeed();
	// �ùķ����� �ӵ��� ���� �ӵ��� ����
	SV_SIMULATOR_API int NormalSpeed();

	// ���� ��¥ ��ȯ
	SV_SIMULATOR_API int Today();
	
	//******************************** world class data

	// ������ ��� �µ� ��ȯ
	SV_SIMULATOR_API float GetWorldTemperature();
	// ������ ���ź�ҳ� ��ȯ
	SV_SIMULATOR_API float GetWorldCarbonPPM();
	// ������ ź�ҹ��ⷮ(�� ����) ��ȯ
	SV_SIMULATOR_API long long GetWorldCarboneEmission();
	// ������ ź�� �����(�� ����) ��ȯ
	SV_SIMULATOR_API long long GetWorldCarbonAbsorbed();
	// ������ �긲 ���� ��ȯ
	SV_SIMULATOR_API long long GetWorldForest();
	// ������ �α� �� ��ȯ
	SV_SIMULATOR_API long long GetWorldPopulation();
	// ������ �縸�� �� ��ȯ
	SV_SIMULATOR_API long long GetWorldDead();
	// ������ ���ĳ��� �� ��ȯ
	SV_SIMULATOR_API long long GetWorldRefugees();
	// ������ �۹����귮 (������ '�� �κ�')
	SV_SIMULATOR_API long long GetWorldFood();


	//// �糭 �߻�Ȯ��
	//SV_SIMULATOR_API float GetDisasterProbability();
	//// �۹����귮 �Ӱ��� (�ʱ�ȭ �ʿ�)
	//SV_SIMULATOR_API long long GetFoodCriticalPoint();
	//// ��տµ� �Ӱ��� (�ʱ�ȭ �ʿ�)
	//SV_SIMULATOR_API float GetTempCriticalPoint();

	//********************************************************

	//******************************** country class ���� �г�
	// �ش� ������ ���� ��ȯ
	SV_SIMULATOR_API long long GetBudget(int _countryCode);
	// �ش� ������ GDP ��ȯ
	SV_SIMULATOR_API long long GetGDP(int _countryCode);
	// �ش� ������ ���� ��ȯ
	SV_SIMULATOR_API float GetTaxRate(int _countryCode);
	// �ش� ������ �ķ� ���귮
	SV_SIMULATOR_API long long GetFood(int _countryCode);
	// �ش� ������ ź�ҹ��ⷮ ��ȯ
	SV_SIMULATOR_API long long GetCarbonEmission(int _countryCode);
	// �ش� ������ �긲���� ��ȯ
	SV_SIMULATOR_API int GetCountryForest(int _countryCode);
	// �ش� ������ �� �α��� ��ȯ
	SV_SIMULATOR_API long long GetPopulation(int _countryCode);
	// �ش� ������ ���� ����� ���� ��ȯ
	SV_SIMULATOR_API float GetDeadRate(int _countryCode);
	// �ش� ������ ���ĳ��� ���� ��ȯ
	SV_SIMULATOR_API float GetRefugeeRate(int _countryCode);
	// �ش� ������ ���� ����ڼ� ��ȯ
	SV_SIMULATOR_API long long GetDead(int _countryCode);
	// �ش� ������ ���ĳ��μ� ��ȯ
	SV_SIMULATOR_API long long GetRefugees(int _countryCode);
	// �ش� ���������� ���Ŀ� ���� �ν��� ��ȯ
	SV_SIMULATOR_API float GetRecognitionRate(int _countryCode);
	// �ش� ���������� �÷��̾� ������ ��ȯ
	SV_SIMULATOR_API float GetSupportRate(int _countryCode);

	
	
	//// �ش� ������ ����� ��ȯ
	//SV_SIMULATOR_API float GetRemoveForest(int _countryCode);
	
	//************************************* Country class Energy �г�
	// �ش� ������ ������� �䱸 ������ ��ȯ
	SV_SIMULATOR_API int GetIndustryEnergy(int _countryCode);
	// �ش� ������ ��Ȱ �䱸 ������ ��ȯ
	SV_SIMULATOR_API int GetLifeEnergy(int _countryCode);
	// �ش� ������ �� ������ ���� ��ȯ
	SV_SIMULATOR_API int GetTotalPowerPlants(int _countryCode);
	// �ش� ������ ����������� ������ ���� ��ȯ
	SV_SIMULATOR_API int GetGreenPowerPlants(int _countryCode);
	// �ش� ������ ��źȭ�� ������ ���� ��ȯ
	SV_SIMULATOR_API int GetFirePowerPlants(int _countryCode);
	// �ش� ������ �����Ҵ� ������(����ȿ��) ��ȯ
	SV_SIMULATOR_API int GetProduce(int _countryCode);
	// �ش� ������ ��ź������ �� ź�ҹ��ⷮ ��ȯ
	SV_SIMULATOR_API long long GetCarbonPerProduce(int _countryCode);


	//************************************* Country class Life �г�

	// �ش� ������ 1�δ� �ڵ��� ���� ����
	SV_SIMULATOR_API float GetCarPerPerson(int _countryCode);
	// �ش� ������ �� ���� ��
	SV_SIMULATOR_API long long GetCars(int _countryCode);
	// �ش� ������ ������� �ڵ��� ����
	SV_SIMULATOR_API float GetFossilFuelCarsRatio(int _countryCode);
	// �ش� ������ ģȯ�� �ڵ��� ����
	SV_SIMULATOR_API float GetEcocarRation(int _countryCode);
	// �ش� ������ �ڵ��� �� ���� ź�� ���ⷮ
	SV_SIMULATOR_API long long GetCarbonPerCar(int _countryCode);
	// �ش� ������ ���� ź�Ҽ�
	SV_SIMULATOR_API float GetTaxTransprot(int _countryCode);
	// �ش� ������ �� ���� ����
	SV_SIMULATOR_API long long GetHouses(int _countryCode);
	// �ش� ������ �Ϲ� ���� ����
	SV_SIMULATOR_API float GetGrayHouses(int _countryCode);
	// �ش� ������ �׸����𵨸� ����
	SV_SIMULATOR_API float GetGreenHouses(int _countryCode);
	// �ش� ������ �¾�� �г� ��ġ ����
	SV_SIMULATOR_API float GetSunHouses(int _countryCode);
	// �ش� ������ �ǹ� �� ���� ź�� ���ⷮ
	SV_SIMULATOR_API long long GetCarbonPerHouse(int _countryCode);
	// �ش� ������ �ְ� ź�Ҽ�
	SV_SIMULATOR_API float GetTaxHouse(int _countryCode);

	// �ش� ������ �ϻ�� 1�δ� ź�� ����
	SV_SIMULATOR_API long long GetCarbonPerPerson(int _countryCode);
	// �ش� ������ ��Ȱ���� �߻��ϴ� ���� �� ź�ҷ�
	SV_SIMULATOR_API long long GetLifeCarbonEmission(int _countryCode);
	// �ش� ������ ��Ȱ�� ź�Ҽ�����
	SV_SIMULATOR_API float GetTaxLife(int _countryCode);



	
	//SV_SIMULATOR_API int EnforcePolicy(int _countryCode, int _policyCode);
	//***************************************************************************************
}

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
	PlaySpeed playSpeed;
}
//************************************************

