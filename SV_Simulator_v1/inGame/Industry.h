#pragma once

class Industry
{
	friend class Country;
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
		- ��������� gdp
		- ��������� ź�ҹ��ⷮ
		- ������ ����
		- ����� �ΰ��� ��������

2. �̺�Ʈ �Լ�
	# ź�ҹ��ⷮ ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
	# gdp ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
	# ������ ���� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
	# ���� ���� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)

#########################################*/

	///<summary>
	///#�Լ����� : 
	///</summary>
	void init_Industry();
	///<summary>
	///#�Լ����� : 
	///</summary>
	void change_carbonPerProduce();
	void change_gdpPerProduce();
	void change_workingRate();
	void change_taxIndex();


};