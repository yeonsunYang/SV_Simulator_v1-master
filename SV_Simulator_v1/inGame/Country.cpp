#include "Country.h"
#include "Industry.h"
///<summary>
///#�Լ� ���� : �ʱ�ȭ �Լ�
///</summary>
void Country::init_Country(CountryCode c, int _industryNum)
{
	this->industryNum = _industryNum;
	industries = new Industry[industryNum];
	for (int i = 0; i < industryNum; i++)
	{
		//this->industries[i].init(); //init�� ����.
	}
	this->name = c;
	this->gdp = 
}

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