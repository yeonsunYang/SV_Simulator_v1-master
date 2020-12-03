#pragma once

class Energy
{
	friend class Country;
	friend class EnergyPolicy;
private:

	int totalPowerPlants; //�� ������ ����
	int greenPowerPlants; //����������� ������ ����
	int firePowerPlants; //��źȭ�¹����� ����
	int produce; //������ ���� �����ϴ� ��������(����)
	long long carbonPerProduce; //��źȭ�¹����� �� ź�ҹ��ⷮ(����)

public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# �ʱ�ȭ �Լ� (!= ������ �Լ�)
			-�� ������ ����
			-����������� ������ ����
			-��źȭ�¹����� ����
			-������ �� �����ϴ� ��������
			-��źȭ�¹����� ź�ҹ��ⷮ

	#########################################*/

	///<summary>
	///#�Լ����� : �ʱ�ȭ �Լ�
	///</summary>
	void init_Energy(int _firePlants, int _greenPlants);

	int GetTotalPowerPlants() { return totalPowerPlants; } //�� ������ ����
	int GetGreenPowerPlants() { return greenPowerPlants; } //����������� ������ ����
	int GetFirePowerPlants() { return greenPowerPlants; } //��źȭ�¹����� ����
	int GetProduce() { return produce; } //������ ���� �����ϴ� ��������(����)
	long long GetCarbonPerProduce() { return carbonPerProduce; } //��źȭ�¹����� �� ź�ҹ��ⷮ(����)
};

