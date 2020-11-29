#pragma once
#include "World.h"
#include "Country.h"
#include "Industry.h"
#include "IndustryPolicyCode.h"
#include "CountryCode.h"

class IndustryPolicy
{
private:
	IndustryPolicyCode policyCode; //��å�ڵ�
	IndustryCode industryCode; //����ڵ�
	bool isAccept[COUNTRY_NUM]; //������ ��å���࿩��
	long long needBudget; //�ҿ俹��
	float rateOfChange_tax; //�������� ��ȭ��
	float rateOfChange_working; //�����ں��� ��ȭ��
	float rateOfChange_carbon; //ź�ҹ��ⷮ ��ȭ��

public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# ������ �Լ�
			- policyCode
			- industryCode
			- ������ ��å���࿩�� (isPolicyAccept)
			- �ʿ� ����
			- �������� ����
			- ź�ҹ��ⷮ ����
			- �����ں��� ����

	2. �̺�Ʈ �Լ�
		# ź�ҹ��ⷮ ����
		# ���� ���
		# ������ ��å���࿩�� ����
		# �������� ����
		# �����ں��� ����
	#########################################*/

	///<summary>
	///#�Լ����� : ������ �Լ�
	///</summary>
	IndustryPolicy(IndustryPolicyCode _pCode, IndustryCode _iCode, long long _needBudget, float _rateOfChange_tax, float _rateOfChange_working, float _rateOfChange_carbon);

	///<summary>
	///#�Լ����� : ��å �����Լ�
	///</summary>
	void enforce(Country country);

	///<summary>
	///#�Լ����� : ��å �����Լ� - ���� ����
	///</summary>
	void enforce_budget(Country country);

	///<summary>
	///#�Լ����� : ��å �����Լ� - ź�ҹ��ⷮ ����
	///</summary>
	void enforce_carbonEmission(Country country);

	///<summary>
	///#�Լ����� : ��å �����Լ� - ������� ����
	///</summary>
	void enforce_tax(Country country);

	///<summary>
	///#�Լ����� : ��å �����Լ� - �����ں��� ����
	///</summary>
	void enforce_working(Country country);
};