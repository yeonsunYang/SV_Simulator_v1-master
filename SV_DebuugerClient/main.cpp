#include "interface.h"
#include <iostream>

int main()
{

	// Debug Mode***************************
	// 0: 모든 Debug log 출력 X
	// 1: msg log 출력 o , function log 출력 x
	// 2: msg log 출력 o , function log 출력 o
	Inter_InitGame(500, 2);

	Inter_PlayGame();


	for (int i = 0; i < 5; i++)
	{
		Sleep(500);
		cout << "today: " << Inter_Today() << endl;
		

	}
	Inter_Pause();

	for (int i = 0; i < 10; i++)
	{
		Sleep(300);

		std::cout <<"today: " << Inter_Today() << " < pause >" << endl;
	}
	Inter_Resume();


	for (int i = 0; i < 5; i++)
	{
		Sleep(500);
		cout << "today: " << Inter_Today() << endl;

	}

	Inter_Pause();

	Inter_EndGame();
	
}