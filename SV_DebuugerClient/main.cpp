#include "interface.h"
#include <Windows.h>
#include <iostream>

int main()
{

	// Debug Mode***************************
	// 0: ��� Debug log ��� X
	// 1: Debug log ��� o , function log ��� x
	// 2: Debug log ��� o , function log ��� o
	SV_Interface_InitGame(500, 0);

	SV_Interface_PlayGame();


	//for (int i = 0; i < 2; i++)
	//{
	//	Sleep(500);
	//	//message = SV_Interface_GetData();

	//	std::cout << "====================" << std::endl;
	//	std::cout << "���� Game Data (JSON)" << std::endl;
	//	std::cout << (const char*) message << std::endl;
	//    std::cout << "====================" << std::endl;

	//	//SV_Interface_EnforcePolicy(CountryCode::KOR, IndustryPolicyCode::Carbontax);
	//	//SV_Interface_EnforcePolicy(CountryCode::USA, IndustryPolicyCode::CER);
	//}

	Sleep(2000);
	cout << "===== KOR ====" << endl;
	cout << "����: " << SV_GetBudget(KOR) << endl;
	cout << "GDP: " << SV_GetGDP(KOR) << endl;
	cout << "�α���: " << SV_GetPopulation(KOR) << endl;
	cout << "ź�ҹ��ⷮ: " << SV_GetCarbonEmission(KOR) << endl;
	cout << "����: " << SV_GetTaxRate(KOR) << endl;
	cout << endl;

	cout << "===== USA ====" << endl;
	cout << "����: " << SV_GetBudget(USA) << endl;
	cout << "GDP: " << SV_GetGDP(USA) << endl;
	cout << "�α���: " << SV_GetPopulation(USA) << endl;
	cout << "ź�ҹ��ⷮ: " << SV_GetCarbonEmission(USA) << endl;
	cout << "����: " << SV_GetTaxRate(USA) << endl;
	cout << endl;

	cout << "===== world ====" << endl;
	cout << "���� ��� �µ�: " << SV_GetWorldTemperature() << endl;
	cout << "���� ź�� ���ⷮ: " << SV_GetWorldCarbonEmission() << endl;
	cout << "���� ź�� ��: " << SV_GetWorldCarbonPPM() << endl;
	cout << "���� �� �α���: " << SV_GetWorldPopulation() << endl;



	Sleep(2000);
	cout << "===== KOR ====" << endl;
	cout << "����: " << SV_GetBudget(KOR) << endl;
	cout << "GDP: " << SV_GetGDP(KOR) << endl;
	cout << "�α���: " << SV_GetPopulation(KOR) << endl;
	cout << "ź�ҹ��ⷮ: " << SV_GetCarbonEmission(KOR) << endl;
	cout << "����: " << SV_GetTaxRate(KOR) << endl;
	cout << endl;

	cout << "===== USA ====" << endl;
	cout << "����: " << SV_GetBudget(USA) << endl;
	cout << "GDP: " << SV_GetGDP(USA) << endl;
	cout << "�α���: " << SV_GetPopulation(USA) << endl;
	cout << "ź�ҹ��ⷮ: " << SV_GetCarbonEmission(USA) << endl;
	cout << "����: " << SV_GetTaxRate(USA) << endl;
	cout << endl;

	cout << "===== world ====" << endl;
	cout << "���� ��� �µ�: " << SV_GetWorldTemperature() << endl;
	cout << "���� ź�� ���ⷮ: " << SV_GetWorldCarbonEmission() << endl;
	cout << "���� ź�� ��: " << SV_GetWorldCarbonPPM() << endl;
	cout << "���� �� �α���: " << SV_GetWorldPopulation() << endl;


	SV_Interface_EndGame();
	

}