#include "interface.h"
#include <iostream>

int main()
{
	// Debug Mode***************************
	// 0: ��� Debug log ��� X
	// 1: msg log ��� o , function log ��� x
	// 2: msg log ��� o , function log ��� o
	Inter_InitGame(8000, 2);

	Inter_PlayGame();

	int i;

	Inter_DoubleSpeed();

	cout << endl;
	cout << "=======2���=====" << endl;
	cout << "4�ʴ� 1ȸ ����" << endl;
	for (i = 1; i <= 20; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		cout << "today: " << Inter_Today() << endl;
	}
	Inter_Pause();

	for (; i <= 25; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		std::cout <<"today: " << Inter_Today() << " < pause >" << endl;
	}
	Inter_Resume();
	Inter_QuadSpeed();

	cout << endl;
	cout << "=======4���=====" << endl;
	cout << "2�ʴ� 1ȸ ����" << endl;
	for (; i <= 45; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		cout << "today: " << Inter_Today() << endl;
	}
	Inter_OctoSpeed();

	cout << endl;
	cout << "=======8���=====" << endl;
	cout << "1�ʴ� 1ȸ ����" << endl;
	for (; i <= 65; i++)
	{
		Sleep(1000);
		cout << i << " �� ��� > ";
		cout << "today: " << Inter_Today() << endl;
	}

	Inter_Pause();

	Inter_EndGame();
	
}