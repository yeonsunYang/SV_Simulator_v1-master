#include "Life.h"

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


// ��ۺι� �ʱ�ȭ
void Life::init_Life_Transport(float _carPerPerson, float _ecocarRatio)
{
	this->carPerPerson = _carPerPerson;
	this->ecocarRatio = _ecocarRatio;
	this->carbonPerCar = 10;
	this->taxTransport = 0;
}

// �ְźι� �ʱ�ȭ
void Life::init_Life_House(long long _houses, float _greenhouses, float _sunhouses)
{
	this->houses = _houses;
	this->greenhouses = _greenhouses;
	this->sunhouses = _sunhouses;
	this->carbonPerHouse = 10;
	this->taxHouse = 0;
	this->day_energyPerHouse = 500;
}

// ���� ��Ȱ �ι� �ʱ�ȭ
void Life::init_Life_Person(long long _carbonPerPerson, int _day_energyPerPerson)
{
	this->carbonPerPerson = _carbonPerPerson;
	this->taxLife = 0;
	this->day_energyPerPerson = _day_energyPerPerson;

}

