#pragma once

class Life
{
	friend class Country;
	friend class LifePolicy;
private:

	float carPerPerson; //�α� 1��� �ڵ��� ���� ����
	float ecocarRatio; // ģȯ�� �ڵ��� ���� (ź�ҹ��ⷮ : 0)
	long long houses; //�� �ǹ� ����
	float greenhouses; //�׸� ���𵨸� ���� (ź�ҹ��ⷮ : 0)
	float sunhouses; //�¾籤 �г� ��ġ ���� (ź�ҹ��ⷮ 35% ����)
	long long carbonPerHouse; //�ǹ� �� ���� ź�ҹ��ⷮ
	long long carbonPerCar; //�ڵ��� �� ���� ź�ҹ��ⷮ
	long long carbonPerPerson; //�ϻ󿡼� �α� 1��� ź�ҹ��ⷮ
	int taxTransport; //���뿡 �ΰ��� �������� (�޷� ����)
	int taxHouse; //�ְſ� �ΰ��� �������� (�޷� ����)
	int taxLife; //�ϻ� �ΰ��� �������� (�޷� ����)
	int day_energyPerHouse; //�ǹ� �� ä �� ��������
	int day_energyPerPerson; //1�� �� �ϻ� ��������

public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# �ʱ�ȭ �Լ� (!= ������ �Լ�)
			-�ڵ��� ���� ����
			-ģȯ�� �ڵ��� ����
			-�� �ǹ� ����
			-�׸� ���𵨸� ����
			-�¾籤 �г� ��ġ ����
			-�ǹ� �� ź�ҹ��ⷮ �ʱ�ȭ
			-�ڵ��� �� ź�ҹ��ⷮ �ʱ�ȭ
			-�ϻ� �α� 1��� ź�ҹ��ⷮ
			-�������� ��� 0���� �ʱ�ȭ
			-�ǹ� �� ä�� �������� �ʱ�ȭ
			-1�δ� �ϻ� ��������

			//@-�ʱ�ȭ ��� ���� �׸� �ܴ̿� ��� �Ű������� �ʱ�ȭ ���ֱ�

	2. �ֱ� ���� ����� �ʿ��� �Լ�
		<day>
		# �ǹ�,��, �ϻ󿡼� �߻��� ź�ҹ��ⷮ ���� (�ϴ��� ����)

	#########################################*/

	// ��ۺι� �ʱ�ȭ
	void init_Life_Transport(float _carPerPerson, float _ecocarRatio);

	// �ְźι� �ʱ�ȭ
	void init_Life_House(long long _houses, float _greenhouses, float _sunhouses);

	// ���� ��Ȱ �ι� �ʱ�ȭ
	void init_Life_Person(long long _carbonPerPerson, int _day_energyPerPerson);

	float GetCarPerPerson() { return carPerPerson; } //�α� 1��� �ڵ��� ���� ����
	float GetEcocarRatio() { return ecocarRatio; } // ģȯ�� �ڵ��� ���� (ź�ҹ��ⷮ : 0)
	long long GetHouses() { return houses; } //�� �ǹ� ����
	float GetGreenhouses() { return greenhouses; } //�׸� ���𵨸� ���� (ź�ҹ��ⷮ : 0)
	float GetSunhouses() { return sunhouses; } //�¾籤 �г� ��ġ ���� (ź�ҹ��ⷮ 35% ����)
	long long GetCarbonPerHouse() { return carbonPerHouse; } //�ǹ� �� ���� ź�ҹ��ⷮ
	long long GetCarbonPerCar() { return carbonPerCar; } //�ڵ��� �� ���� ź�ҹ��ⷮ
	long long GetCarbonPerPerson() { return carbonPerPerson; } //�ϻ󿡼� �α� 1��� ź�ҹ��ⷮ
	int GetTaxTransport() { return taxTransport; } //���뿡 �ΰ��� �������� (�޷� ����)
	int GetTaxHouse() { return taxHouse; } //�ְſ� �ΰ��� �������� (�޷� ����)
	int GetTaxLife() { return taxLife; } //�ϻ� �ΰ��� �������� (�޷� ����)
	int GetDay_energyPerHouse() { return day_energyPerHouse; } //�ǹ� �� ä �� ��������
	int GetDay_energyPerPerson() { return day_energyPerPerson; } //1�� �� �ϻ� ��������
};
