#include "interface.h"
#include <iostream>

int main()
{
	// Debug Mode***************************
	// 0: ��� Debug log ��� X
	// 1: msg log ��� o , function log ��� x
	// 2: msg log ��� o , function log ��� o
	InitGame(8000, 2);

	PlayGame();
	Sleep(100);

	int i;

	OctoSpeed();

	cout << endl;
	cout << "=======2���=====" << endl;
	cout << "4�ʴ� 1ȸ ����" << endl;
	for (i = 1; i <= 20; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		cout << "today: " << Today() << endl;
	}
	Pause();

	for (; i <= 25; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		std::cout <<"today: " << Today() << " < pause >" << endl;
	}
	Resume();
	OctoSpeed();

	cout << endl;
	cout << "=======4���=====" << endl;
	cout << "2�ʴ� 1ȸ ����" << endl;
	for (; i <= 45; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		cout << "today: " << Today() << endl;
	}
	OctoSpeed();

	cout << endl;
	cout << "=======8���=====" << endl;
	cout << "1�ʴ� 1ȸ ����" << endl;
	for (; i <= 65; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		cout << "today: " << Today() << endl;
	}

	Pause();

	EndGame();
	
}