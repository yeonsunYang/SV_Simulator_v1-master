#include "IndustryPolicy.h"
#include <iostream>
using namespace std;

///<summary>
///#�Լ����� : ������ �Լ�
///</summary>
IndustryPolicy::IndustryPolicy(IndustryPolicyCode _pCode, IndustryCode _iCode, long long _needBudget, float _rateOfChange_tax, float _rateOfChange_working, float _rateOfChange_carbon)
{
	this->policyCode = _pCode;
	this->industryCode = _iCode;
	this->needBudget = _needBudget;
	this->rateOfChange_tax = _rateOfChange_tax;
	this->rateOfChange_working = _rateOfChange_working;
	this->rateOfChange_carbon = _rateOfChange_carbon;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		isAccept[i] = false;
	}
}

///<summary>
///#�Լ����� : ��å �����Լ�
///</summary>
void IndustryPolicy::enforce(Country country)
{
	isAccept[country.countryCode] = true; //�ش� ���� ��� ����� �ش��ϴ� �� ��å ���� true
	if (this->needBudget != 0)
	{
		enforce_budget(country);
	}
	if (this->rateOfChange_tax != 0)
	{
		enforce_tax(country);
	}
	if (this->rateOfChange_working != 0)
	{
		enforce_working(country);
	}
	if (this->rateOfChange_carbon != 0)
	{
		enforce_carbonEmission(country);
	}
}

///<summary>
///#�Լ����� : ��å �����Լ� - ���� ����
///</summary>
void IndustryPolicy::enforce_budget(Country country)
{
	if (country.budget < this->needBudget)
	{
		cout<<"������ �����մϴ�.\n";
	}
	else
	{
		country.use_budget(this->needBudget);
	}

}

///<summary>
///#�Լ����� : ��å �����Լ� - ź�ҹ��ⷮ ����
///</summary>
void IndustryPolicy::enforce_carbonEmission(Country country)
{
	//�ش� ���� ��� �����Ϳ��� ź�ҹ��ⷮ ��ȭ �Լ� ȣ��
	country.industries[this->industryCode].change_carbonPerProduce(this->rateOfChange_carbon);
}

///<summary>
///#�Լ����� : ��å �����Լ� - ������� ����
///</summary>
void IndustryPolicy::enforce_tax(Country country)
{
	//�ش� ���� ��� �����Ϳ��� �������� ��ȭ �Լ� ȣ��
	country.industries[this->industryCode].change_taxIndex(this->rateOfChange_tax);
}

///<summary>
///#�Լ����� : ��å �����Լ� - �����ں��� ����
///</summary>
void IndustryPolicy::enforce_working(Country country)
{
	//�ش� ���� ��� �����Ϳ��� �����ں��� ��ȭ �Լ� ȣ��
	country.industries[this->industryCode].change_workingRate(this->rateOfChange_working);
}