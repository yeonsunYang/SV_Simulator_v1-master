#pragma once
#include "IndustryCode.h"

class Industry
{
	friend class Country;
	friend class IndustryPolicy;
	Industry();

private:

	IndustryCode industryCode; //��� �ڵ�
	int day_gdpPerProduce; //��������� 1�� gdp��, �����ڼ�* gpdPerProduce = industry GDP
	int day_carbonPerProduce; //��������� ź�ҹ��ⷮ
	int day_energyPerProduce; //��������� ��������뷮
	float taxIndex;//��������
	float workingRate; //������ ����

public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# �ʱ�ȭ �Լ� (!= ������ �Լ�)
			- ��� �ڵ� (�ǵ帱 �� ���� ����)
			- ��������� gdp (�ǵ帱 �� ���� ����)
			- ��������� ź�ҹ��ⷮ
			- ��������� ��������뷮
			- ������ ����
			- ����� �ΰ��� �������� 0 �ʱ�ȭ

	#########################################*/

	///<summary>
	///#�Լ����� : �ʱ�ȭ �Լ�
	///</summary>
	void init_Industry(IndustryCode _code, int _gdp, int _carbon, int _energy, float _workingRate);

};