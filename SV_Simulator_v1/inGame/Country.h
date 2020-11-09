#pragma once
#include <string>
#include "CountryCode.h"
#include "IndustryCode.h"
class Industry;

class Country
{
private:
	friend class World;

	CountryCode name; //������
	int industryNum; //(+)�߰����� : ��� ����
	long long budget; //���� ��������
	long long gdp; //���� gdp
	long long population; //���� �α���
	long long carbonEmission; //���� ź�ҹ��ⷮ
	long long carbonAbsorbing; //���� ź�������
	Industry* industries; //���� ����ι� ������
	float taxRate; //���� ����

public:
/*#####################################
1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
	# �ʱ�ȭ �Լ� (!= ������ �Լ�)
		-������ �ʱ�ȭ
		-������������ �ʱ�ȭ (2020����-�޷�)
		-���� GDP�ʱ�ȭ (2020����-�޷�)
		-���� ź�ҹ��ⷮ (2020����)
		-���� ź������� (2020����)
		-���� ��� ����
		-���� ���� (2020����)

2. �ֱ� ���� ����� �ʿ��� �Լ�
	# 1�� ����
		- ���� ������ ���� ���

3. �̺�Ʈ �Լ�
	# ź�ҹ��ⷮ ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
	# ź������� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
	# ���� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)

#########################################*/
	///<summary>
	///#�Լ� ���� : �ʱ�ȭ �Լ�
	///</summary>
	void init_Country(CountryCode c, int _industryNum, long long _gdp, float _taxRate, long long _population, long long _carbonEmission, long long _carbonAbsorbing);

	///<summary>
	///#�Լ� ���� : gdp�� ������ �����Ͽ� ���� ������ �Ҵ��ϴ� �Լ�
	///</summary>
	void calculator_budget();

	///<summary>
	///#�Լ� ���� : ź�ҹ��ⷮ ���� �Լ�
	///</summary>
	void renew_carbonEmission(long margin_carbonEmission);

	///<summary>
	///#�Լ� ���� : ź������� ���� �Լ�
	///</summary>
	void renew_carbonAbsorbing(long margin_carbonAbsorbing);

	///<summary>
	///#�Լ� ���� : ���� ���� �Լ�
	///</summary>
	void renew_budget(long margin_budget);

	void printStatus();
	
};