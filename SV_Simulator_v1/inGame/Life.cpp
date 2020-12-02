#include "Life.h"
#include <iostream>

///<summary>
///#�Լ����� : �ʱ�ȭ �Լ�
///</summary>
void Life::init_Life(float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson)
{
	/*
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�

		- �ڵ��� ���� ����
		- ģȯ�� �ڵ��� ����
		- �� �ǹ� ����
		- �׸� ���𵨸� ����
		- �¾籤 �г� ��ġ ����
		- �ǹ� �� ź�ҹ��ⷮ �ʱ�ȭ
		- �ڵ��� �� ź�ҹ��ⷮ �ʱ�ȭ
		- �ϻ� �α� 1��� ź�ҹ��ⷮ
		- �������� ��� 0���� �ʱ�ȭ
		- �ǹ� �� ä�� �������� �ʱ�ȭ
		- 1�δ� �ϻ� ��������

		//@-�ʱ�ȭ ��� ���� �׸� �ܴ̿� ��� �Ű������� �ʱ�ȭ ���ֱ�
	*/
	this->carPerPerson = _carPerPerson;
	this->ecocarRatio = _ecocarRatio;
	this->houses = _houses;
	this->greenhouses = _greenhouses;
	this->sunhouses = _sunhouses;
	this->carbonPerHouse = 10;
	this->carbonPerCar = 10;
	this->carbonPerPerson = _carbonPerPerson;
	this->taxHouse = 0;
	this->taxLife = 0;
	this->taxTransport = 0;
	this->day_energyPerHouse = 500;
	this->day_energyPerPerson = _day_energyPerPerson;

}

