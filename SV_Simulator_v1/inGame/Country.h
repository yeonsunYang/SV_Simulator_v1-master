#pragma once
#include <string>
#include "CountryCode.h"
#include "IndustryCode.h"
#define INDUSTRY_NUM 1
class Industry;

class Country
{
private:
	friend class World;

	CountryCode countryCode; //�����ڵ�
	long long budget; //���� ��������
	long long gdp; //���� gdp
	long long population; //���� �α���
	long long carbonEmission; //���� ź�ҹ��ⷮ
	Industry* industries; //���� ����ι� ������
	float taxRate; //���� ����

public:
/*#####################################
1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
	# �ʱ�ȭ �Լ� (!= ������ �Լ�)
		-�����ڵ� �ʱ�ȭ
		-������������ �ʱ�ȭ (2020����-�޷�)
		-���� GDP�ʱ�ȭ (2020����-�޷�)
		-���� ź�ҹ��ⷮ (2020����)
		-���� ��� ����
		-���� ���� (2020����)

2. �ֱ� ���� ����� �ʿ��� �Լ�
	<day>
	# ������� �߻��� ���� �� GDP����
	# ����� ��Ȱ���� �߻��� ź�ҹ��ⷮ ����(�� ������ ����)

	<month>
	# ���ݿ� ���� ���� �߰�

	<year>
	# 1�� ���� å��
	# 1�� ������ GDP 0���� ����

3. �̺�Ʈ �Լ�
	# ���� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)

#########################################*/
	///<summary>
	///#�Լ� ���� : �ʱ�ȭ �Լ�
	///</summary>
	void init_Country(CountryCode _code, long long _gdp, float _taxRate, long long _population, long long _carbonEmission);


	///<summary>
	///#�Լ� ���� : ����߻� ���� �� gdp ���� (��)
	///</summary>
	void add_totalGDP();

///<summary>
///#�Լ� ���� : gdp 0���� reset (��)
///</summary>
	void reset_annualGDP();


	///<summary>
	///#�Լ� ���� : ����� ��Ȱ �߻� ź�ҹ��ⷮ �ջ�(��-����)
	///</summary>
	void add_totalCarbonEmission();

	///<summary>
	///#�Լ� ���� : �� ź�Ҽ� �� ��å���ݿ� ���� ���� �߰� (��)
	///</summary>
	void add_monthTax();

	///<summary>
	///#�Լ� ���� : gdp�� ������ �����Ͽ� 1�� ���� ������ �Ҵ��ϴ� �Լ� (��)
	///</summary>
	void calculator_budget();

	///<summary>
	///#�Լ� ���� : ���� ��� �̺�Ʈ �߻� �� ���� ���� (�̺�Ʈ)
	///</summary>
	void use_budget(long long _use_budget);


	///<summary>
	///#�Լ� ���� : ����� �� �׽�Ʈ �Լ�
	///</summary>
	void printStatus();
	
};