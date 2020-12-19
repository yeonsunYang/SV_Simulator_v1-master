#include "interface.h"
#include <iostream>

int main()
{
	// Debug Mode***************************
	// 0: 모든 Debug log 출력 X
	// 1: msg log 출력 o , function log 출력 x
	// 2: msg log 출력 o , function log 출력 o
	InitGame(1000, 0);

	PlayGame();

	for (int i = 0; i < 10; i++) {

		cout << "today: "<<Today() << endl;;

		Sleep(1000);

	}
	//EndGame();
	
	cout << "return: " << ResetGame() << endl;;

	//PlayGame();

	for (int i = 0; i < 10; i++) {

		cout << "today: " << Today() << endl;;

		Sleep(1000);

	}

	EndGame();

}