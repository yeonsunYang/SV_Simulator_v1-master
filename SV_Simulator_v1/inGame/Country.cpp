#include "Country.h"
#include "Industry.h"
///<summary>
///#�Լ� ���� : �ʱ�ȭ �Լ�
///</summary>
void Country::init_Country(CountryCode c, int _industryNum, long long _gdp, float _taxRate, long long _population, long long _carbonEmission, long long _carbonAbsorbing)
{
	this->industryNum = _industryNum;
	industries = new Industry[industryNum];
	
	//industries[Steel].init_Industry();
	
	this->name = c;
	this->gdp = _gdp; //�޷�($)����
	this->taxRate = _taxRate;
	calculator_budget(); //�ʱ�ȭ gdp��� �ʱ�ȭ ������ ���� å��
	this->population = _population;
	this->carbonEmission = _carbonEmission; //��(t)����
	this->carbonAbsorbing = _carbonAbsorbing;
}

///<summary>
///#�Լ� ���� : gdp�� ������ �����Ͽ� ���� ������ �Ҵ��ϴ� �Լ�
///</summary>
void Country::calculator_budget()
{
	this->budget += (gdp * taxRate)/365; //1�� �ֱ�� ȯ���� ��
}

///<summary>
///#�Լ� ���� : ź�ҹ��ⷮ ���� �Լ�
///</summary>
void Country::renew_carbonEmission(long margin_carbonEmission)
{
	this->carbonEmission += margin_carbonEmission;
}

///<summary>
///#�Լ� ���� : ź������� ���� �Լ�
///</summary>
void Country::renew_carbonAbsorbing(long margin_carbonAbsorbing)
{
	this->carbonAbsorbing += margin_carbonAbsorbing;
}

///<summary>
///#�Լ� ���� : ���� ���� �Լ�
///</summary>
void Country::renew_budget(long margin_budget)
{
	this->budget += margin_budget;
}