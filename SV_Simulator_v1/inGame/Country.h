#pragma once
#include "World.h"
#include "Policy\EnforcedPolicy.h"
#include "Policy\FirePlants.h"
#include "Policy\GreenPlants.h"

class Country {
public:

	~Country();
	Country();

	void DataInit(int _population, int _fire, int _green, int _recognition, int _needEnergyPerson);//인구수,화력발전소수,재생에너지수,인식률,1인당에너지소요량 초기화

	int Population() { return population; }//인구수리턴
	int Live() { return live; }//살아있는사람수리턴
	int Dead() { return dead; }//죽은사람수누적리턴
	int DDead() { return dailyDead; }//오늘죽은사람수리턴

	int NeedEnergy() { return needEnergy; }//에너지소요량리턴
	int DNeedEnergy() { return deltaNeedEnergy; }//delta에너지소요량리턴
	int SupplyEnergy() { return supplyEnergy; }//에너지공급량리턴
	int SavingEnergy() { return savingEnergy; }//에너지절약량리턴
	int NeedEnergyPerson() { return needEnergyPerson; }//1인당에너지소요량리턴
	int DSupplyEnergy() { return deltaSupplyEnergy; }//delta에너지공급량리턴
	int FirePlants() { return firePlants; }//화력발전소개수리턴
	int DFIrePlants() { return deltaFirePlants; }//delta화력발전소개수리턴
	int GreenPlants() { return greenPlants; }//재생에너지발전소개수리턴
	int DGreenPlants() { return deltaGreenPlants; }//delta재생에너지발전소개수리턴
	int DEmission() { return dailyEmission; }//국가하루배출량리턴
	int TEmission() { return totalEmission; }//국가총배출량리턴

	int DGold() { return dailyGold; }//국가하루골드량리턴
	int TGold() { return totalGold; }//국가총골드량리턴
	int Support() { return support; }//국가지지도리턴
	int DSupport() { return deltaSupport; }//delta국가지지도리턴
	int Recognition() { return recognition; }//국가인식률리턴
	int DRecognition() { return deltaRecognition; }//delta국가인식률리턴



	int CountEduPolicy(int _eduPolicyCode);//국가교육정책실행횟수리턴
	int CountLifePolicy(int _lifePolicyCode);//국가생활정책실행횟수리턴


	void CalEnergy();//에너지계산
	void CalEmission();//배출량계산
	void CalDeath();//사망자수계산
	void CalRecognition();//인식률계산
	void CalSupport();//지지도계산
	void ReceiveGold();//얻은골드수계산

	void EnforceEduPolicy(int _eduPolicyCode, int _effect);//이국가에교육정책을어떻게실행
	void EnforceLifePolicy(int _lifePolicyCode, int _effect, int _effec2);//이국가에생활정책을어떻게실행

	void BuildFirePlants(int _numBuild);//화력발전소짓기
	void BuildGreenPlants(int _numBuild);//재생에너지발전소짓기
	void DestroyFirePlants(int _numDestroy);//화력발전소파괴
	void DestroyGreenPlants(int _numDestroy);//재생에너지발전소파괴



private:

	void ReCalEnergy();

	World* world;

	int population;//국가인구수
	int live;//국가살아있는사람수
	int dead;//국가죽은사람수누적
	int dailyDead;//하루죽은사람수

	int needEnergy;//에너지소요량
	int needEnergyPerson;//1인당에너지소요량

	int deltaNeedEnergy;//delta에너지소요량
	int supplyEnergy;//에너지공급량
	int deltaSupplyEnergy;//delta에너지공급량
	int savingEnergy;//에너지절약량


	int firePlants;//화력발전소개수
	int deltaFirePlants;//delta화력발전소개수
	int greenPlants;//재생에너지발전소개수
	int deltaGreenPlants;//delta재생에너지발전소개수

	int dailyEmission;//일일탄소배출량
	int totalEmission;//총탄소배출량

	int dailyGold;//하루골드수급량
	int totalGold;//전체골드수급량
	int support;//지지도
	int deltaSupport;//delta지지도
	int recognition;//인식률
	int deltaRecognition;//deta지지도

	EnforcedPolicy lifePolicy [LIFE_POLICY_NUM]; //생활정책
	EnforcedPolicy eduPolicy [EDU_POLICY_NUM]; //교육정책

	FirePlantsInfo fireInfo;
	GreenPlantsInfo greenInfo;

};