#include "interface.h"
#include <iostream>

int main()
{
	// Debug Mode***************************
	// 0: ��� Debug log ��� X
	// 1: msg log ��� o , function log ��� x
	// 2: msg log ��� o , function log ��� o
	InitGame(500, 2);

	PlayGame();



	Sleep(100000);


	EndGame();
	
}