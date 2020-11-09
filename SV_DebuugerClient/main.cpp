#include "interface.h"
#include <Windows.h>
#include <iostream>
#include <json/json.h>

int main()
{
	LPCTSTR message;

	// Debug Mode***************************
	// 0: 모든 Debug log 출력 X
	// 1: Debug log 출력 o , function log 출력 x
	// 2: Debug log 출력 o , function log 출력 o
	SV_Interface_InitGame(500, 1);

	SV_Interface_PlayGame();

	for (int i = 0; i < 5; i++)
	{
		Sleep(500);
		message = SV_Interface_GetData();

		std::cout << "====================" << std::endl;
		std::cout << "현재 Game Data (JSON)" << std::endl;
		std::cout << (const char*) message << std::endl;
		std::cout << "====================" << std::endl;

		SV_Interface_EnforcePolicy(CountryCode::KOR, IndustryPolicyCode::CarbonTax);
		SV_Interface_EnforcePolicy(CountryCode::USA, IndustryPolicyCode::CER);
	}

	message = SV_Interface_GetData();

	std::cout << "====================" << std::endl;
	std::cout << "최종 Game Data (JSON)" << std::endl;
	std::cout << (const char*)message << std::endl;
	std::cout << "====================" << std::endl;


	SV_Interface_EndGame();
	
}