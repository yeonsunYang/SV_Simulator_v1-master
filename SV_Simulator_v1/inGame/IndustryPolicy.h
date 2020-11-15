#pragma once
#include "World.h"
#include "IndustryPolicyCode.h"
#define INDUSTRY_NUM 1

class IndustryPolicy
{
private:
	IndustryPolicyCode policyCode; //��å�ڵ�
	bool isAccept[INDUSTRY_NUM][COUNTRY_NUM]; //������ ��å���࿩��
	long long needBudget; //�ҿ俹��
	float rateOfChange_tax; //�������� ��ȭ��
	float rateOfChange_working; //�����ں��� ��ȭ��
	float rateOfChange_carbon; //ź�ҹ��ⷮ ��ȭ��

public:
/*#####################################
1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
	# ������ �Լ�
		- policyCode
		- ������ ��å���࿩�� (isPolicyAccept)
		- �ʿ� ����
		- �������� ����
		- ź�ҹ��ⷮ ����

2. �̺�Ʈ �Լ�
	# ź�ҹ��ⷮ ����
	# ���� ���
	# ������ ��å���࿩�� ����
	# �������� ����
	# �����ں��� ����

#########################################*/
};