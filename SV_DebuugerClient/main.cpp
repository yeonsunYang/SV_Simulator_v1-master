#include "interface.h"
#include <iostream>

int main()
{
	// Debug Mode***************************
	// 0: ��� Debug log ��� X
	// 1: msg log ��� o , function log ��� x
	// 2: msg log ��� o , function log ��� o
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