#include "interface.h"
#include <iostream>

int main()
{
	// Debug Mode***************************
	// 0: 모든 Debug log 출력 X
	// 1: msg log 출력 o , function log 출력 x
	// 2: msg log 출력 o , function log 출력 o
	InitGame(8000, 2);

	PlayGame();
	Sleep(100);

	int i;

	OctoSpeed();

	cout << endl;
	cout << "=======2배속=====" << endl;
	cout << "4초당 1회 연산" << endl;
	for (i = 1; i <= 20; i++)
	{
		Sleep(1000);
		cout << i << " 초 경과 > ";
		cout << "today: " << Today() << endl;
	}
	Pause();

	for (; i <= 25; i++)
	{
		Sleep(1000);
		cout << i << " 초 경과 > ";
		std::cout <<"today: " << Today() << " < pause >" << endl;
	}
	Resume();
	OctoSpeed();

	cout << endl;
	cout << "=======4배속=====" << endl;
	cout << "2초당 1회 연산" << endl;
	for (; i <= 45; i++)
	{
		Sleep(1000);
		cout << i << " 초 경과 > ";
		cout << "today: " << Today() << endl;
	}
	OctoSpeed();

	cout << endl;
	cout << "=======8배속=====" << endl;
	cout << "1초당 1회 연산" << endl;
	for (; i <= 65; i++)
	{
		Sleep(1000);
		cout << i << " 초 경과 > ";
		cout << "today: " << Today() << endl;
	}

	Pause();

	EndGame();
	
}