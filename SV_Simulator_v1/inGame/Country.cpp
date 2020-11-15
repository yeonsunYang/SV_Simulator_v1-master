#include <iostream>
#include "Country.h"
#include "Industry.h"
using namespace std;

///<summary>
///#�Լ� ���� : �ʱ�ȭ �Լ�
///</summary>
void Country::init_Country(CountryCode _code, long long _gdp, float _taxRate, long long _population, long long _carbonEmission)
{
	industries = new Industry[INDUSTRY_NUM];
	
	industries[Steel].init_Industry();
	
	this->countryCode = _code;
	this->gdp = _gdp; //�޷�($)����
	this->taxRate = _taxRate;
	this->budget = (gdp*taxRate)/360; 
	this->population = _population;
	this->carbonEmission = _carbonEmission; //��(t)����
}

///<summary>
///#�Լ� ���� : ����߻� ���� �� gdp ����
///</summary>
void Country::add_totalGDP()
{
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		this->gdp += (this->industries[i].day_gdpPerProduce * this->industries[i].workingRate * this->population);
		//���� �� gdp�� ������ ��� gdp�� ����Ͽ� �ջ��� ������. �ᱹ 1�� �ڿ��� �� �� ���귮.
	}
}

///<summary>
///#�Լ� ���� : gdp 0���� reset (��)
///</summary>
void Country::reset_annualGDP()
{
	this->gdp = 0;
}

///<summary>
///#�Լ� ���� : ����� ��Ȱ �߻� ź�ҹ��ⷮ �ջ�(�� ���� ����)
///</summary>
void Country::add_totalCarbonEmission()
{
	this->carbonEmission = 0;
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		this->carbonEmission += this->industries[i].day_carbonPerProduce * this->industries[i].workingRate * this->population;
	}
}

///<summary>
///#�Լ� ���� : �� ź�Ҽ� �� ��å���ݿ� ���� ���� �߰�
///</summary>
void Country::add_monthTax()
{
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		this->budget += this->industries[i].taxIndex * this->industries[i].day_gdpPerProduce * 30 * industries[i].workingRate * this->population;
		// �� �߰� ���� += ��� ���ݺ��� * ���� ����� gdp * 30�� * ��� �����ڼ�
		//�� �� ���� ��å�� ���� ����� �߰� �ΰ��� ź�Ҽ� ������ *0���� �߰� ���� �Ҵ� ����
		// �� ��å�� ���� ź�Ҽ� �ΰ��� ��å ���� �����޺��� ȿ�� �߻��ϵ��� �˸����� �ֱ�
	}
}

///<summary>
///#�Լ� ���� : gdp�� ������ �����Ͽ� ���� ������ �Ҵ��ϴ� �Լ�
///</summary>
void Country::calculator_budget()
{
	this->budget += (gdp * taxRate)/360; //1�� �ֱ�� ȯ���� ��
}


///<summary>
///#�Լ� ���� : ���� ��� �̺�Ʈ �߻� �� ���� ����
///</summary>
void Country::use_budget(long long _use_budget)
{
	this->budget -= _use_budget;
}


void Country::printStatus()
{
	cout << "CountryCode : " << countryCode << endl;//����
	cout << "population : " << population << " ��"<<endl; //�α���
	cout << "GDP : $ " << gdp << endl; //�����ѻ���
	cout << "taxRate : " << taxRate <<" % "<<endl;// ����
	cout << "budget: $ " << budget << endl; //���� ����
	cout<<"carbonEmission : " << carbonEmission<<" (t)"<<endl; //ź�ҹ��ⷮ

}