#pragma once
#include "IndustryCode.h"

class Industry
{
	friend class Country;
	friend class IndustryPolicy;
private:

	IndustryCode industryCode; //��� �ڵ�
	long long day_gdpPerProduce; //��������� 1�� gdp��, �����ڼ�* gpdPerProduce = industry GDP
	long long day_carbonPerProduce; //��������� ź�ҹ��ⷮ
	float taxIndex;//��������
	float workingRate; //������ ����

public:
/*#####################################
1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
	# �ʱ�ȭ �Լ� (!= ������ �Լ�)
		- ��� �ڵ� (�ǵ帱 �� ���� ����)
		- ��������� gdp (�ǵ帱 �� ���� ����)
		- ��������� ź�ҹ��ⷮ
		- ������ ����
		- ����� �ΰ��� ��������

2. �̺�Ʈ �Լ�
	# ź�ҹ��ⷮ ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
	# ������ ���� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
	# ���� ���� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)

#########################################*/

	///<summary>
	///#�Լ����� : �ʱ�ȭ �Լ�
	///</summary>
	void init_Industry(IndustryCode _code, long long _gdp, long long _carbon, float _workingRate);
	
	///<summary>
	///#�Լ����� : ź�ҹ��ⷮ ��ȭ
	///</summary>
	void change_carbonPerProduce(float _rateOfChange_carbon);

	///<summary>
	///#�Լ����� : �����ں��� ��ȭ
	///</summary>
	void change_workingRate(float _rateOfChange_working);

	///<summary>
	///#�Լ����� : �������� ��ȭ
	///</summary>
	void change_taxIndex(float _rateOfChange_tax);

};