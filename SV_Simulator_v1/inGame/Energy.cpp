#include "Energy.h"
#include <iostream>


///<summary>
///#�Լ����� : �ʱ�ȭ �Լ�
///</summary>
void Energy::init_Energy(int _firePlants, int _greenPlants)
{
	/*
	�ʱ�ȭ �Ǿ�� �ϴ� �κ�
		- �� ������ ����
		- ����������� ������ ����
		- ��źȭ�¹����� ����
		- ������ �� �����ϴ� ��������
		- ��źȭ�¹����� ź�ҹ��ⷮ
	*/
	this->firePowerPlants = _firePlants;
	this->greenPowerPlants = _greenPlants;
	this->totalPowerPlants = (_firePlants + _greenPlants);
	this->produce = 1000000;
	this->carbonPerProduce = 10000;
}
