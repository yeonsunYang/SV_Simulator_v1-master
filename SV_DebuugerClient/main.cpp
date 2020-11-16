#include "interface.h"
#include <Windows.h>
#include <iostream>

int main()
{

	// Debug Mode***************************
	// 0: 모든 Debug log 출력 X
	// 1: Debug log 출력 o , function log 출력 x
	// 2: Debug log 출력 o , function log 출력 o
	SV_Interface_InitGame(500, 0);

	SV_Interface_PlayGame();


	//for (int i = 0; i < 2; i++)
	//{
	//	Sleep(500);
	//	//message = SV_Interface_GetData();

	//	std::cout << "====================" << std::endl;
	//	std::cout << "현재 Game Data (JSON)" << std::endl;
	//	std::cout << (const char*) message << std::endl;
	//    std::cout << "====================" << std::endl;

	//	//SV_Interface_EnforcePolicy(CountryCode::KOR, IndustryPolicyCode::Carbontax);
	//	//SV_Interface_EnforcePolicy(CountryCode::USA, IndustryPolicyCode::CER);
	//}

	Sleep(2000);
	cout << "===== KOR ====" << endl;
	cout << "예산: " << SV_GetBudget(KOR) << endl;
	cout << "GDP: " << SV_GetGDP(KOR) << endl;
	cout << "인구수: " << SV_GetPopulation(KOR) << endl;
	cout << "탄소배출량: " << SV_GetCarbonEmission(KOR) << endl;
	cout << "세율: " << SV_GetTaxRate(KOR) << endl;
	cout << endl;

	cout << "===== USA ====" << endl;
	cout << "예산: " << SV_GetBudget(USA) << endl;
	cout << "GDP: " << SV_GetGDP(USA) << endl;
	cout << "인구수: " << SV_GetPopulation(USA) << endl;
	cout << "탄소배출량: " << SV_GetCarbonEmission(USA) << endl;
	cout << "세율: " << SV_GetTaxRate(USA) << endl;
	cout << endl;

	cout << "===== world ====" << endl;
	cout << "세계 평균 온도: " << SV_GetWorldTemperature() << endl;
	cout << "세계 탄소 배출량: " << SV_GetWorldCarbonEmission() << endl;
	cout << "세계 탄소 농도: " << SV_GetWorldCarbonPPM() << endl;
	cout << "세계 총 인구수: " << SV_GetWorldPopulation() << endl;



	Sleep(2000);
	cout << "===== KOR ====" << endl;
	cout << "예산: " << SV_GetBudget(KOR) << endl;
	cout << "GDP: " << SV_GetGDP(KOR) << endl;
	cout << "인구수: " << SV_GetPopulation(KOR) << endl;
	cout << "탄소배출량: " << SV_GetCarbonEmission(KOR) << endl;
	cout << "세율: " << SV_GetTaxRate(KOR) << endl;
	cout << endl;

	cout << "===== USA ====" << endl;
	cout << "예산: " << SV_GetBudget(USA) << endl;
	cout << "GDP: " << SV_GetGDP(USA) << endl;
	cout << "인구수: " << SV_GetPopulation(USA) << endl;
	cout << "탄소배출량: " << SV_GetCarbonEmission(USA) << endl;
	cout << "세율: " << SV_GetTaxRate(USA) << endl;
	cout << endl;

	cout << "===== world ====" << endl;
	cout << "세계 평균 온도: " << SV_GetWorldTemperature() << endl;
	cout << "세계 탄소 배출량: " << SV_GetWorldCarbonEmission() << endl;
	cout << "세계 탄소 농도: " << SV_GetWorldCarbonPPM() << endl;
	cout << "세계 총 인구수: " << SV_GetWorldPopulation() << endl;


	SV_Interface_EndGame();
	

}