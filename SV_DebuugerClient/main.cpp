#include "interface.h"
#include <iostream>

int main()
{
	// Debug Mode***************************
	// 0: 모든 Debug log 출력 X
	// 1: msg log 출력 o , function log 출력 x
	// 2: msg log 출력 o , function log 출력 o
	InitGame(500, 2);

	PlayGame();



	Sleep(100000);


	EndGame();
	
}