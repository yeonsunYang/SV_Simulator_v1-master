#include <iostream>
#include "Country.h"
#include "Industry.h"
#include "Life.h"
#include "Energy.h"
using namespace std;

///<summary>
///#�Լ� ���� : �ʱ�ȭ �Լ�
///</summary>
void Country::init_Country(CountryCode _code, long long _budget, float _taxRate, long long _population, int _forest, float _refugeeRate, long long _food, float _removeForest,
	float workingRate_st, float workingRate_oil, float workingRate_sv, float workingRate_mf, float workingRate_ag,
	float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson,
	int _firePlants, int _greenPlants)
{
	this->countryCode = _code;
	this->gdp = 0; //�޷�($)����
	this->taxRate = _taxRate;
	this->budget = _budget;
	this->defaultPopulation = _population;
	this->countryForest = _forest;
	this->supportRate = 0.1;
	this->recognitionRate = 0.1;
	this->refugeeRate = _refugeeRate;
	this->deadRate = 0;
	this->food = _food;
	this->removeForest = _removeForest;


	this->industries = new Industry[INDUSTRY_NUM];
	//����ڵ�, ��� 1�� ���������gdp, ��� 1�� ��������� ź�ҹ��ⷮ, ��� 1�� ��������� ��������뷮, ��� �����ں���
	//init_Industry(IndustryCode _code, int _gdp, int _carbon, int _energy, float _workingRate);

	industries[STEEL].init_Industry(STEEL, 50000, 10, 10, workingRate_st);
	industries[OIL].init_Industry(OIL, 50000, 10, 10, workingRate_oil);
	industries[SERVICE].init_Industry(SERVICE, 50000, 10, 10, workingRate_sv);
	industries[MANUFACTURING].init_Industry(MANUFACTURING, 50000, 10, 10, workingRate_mf);
	industries[AGRICULTURE].init_Industry(AGRICULTURE, 50000, 10, 10, workingRate_ag);
	//������� �������� �ٸ� ���� �����ں��� ��. <- �����ں����� init_country���� �Ű������� �ޱ�

	life.init_Life(_carPerPerson, _ecocarRatio, _houses, _greenhouses, _sunhouses, _carbonPerPerson, _day_energyPerPerson);
	energies.init_Energy(_firePlants, _greenPlants);
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
///#�Լ� ���� : ���+��Ȱ+������ �߻� ź�ҹ��ⷮ �ջ�(�� ���� ����)
///</summary>
void Country::add_totalCarbonEmission()
{
	this->carbonEmission = 0;
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{//��� �� ������� �� ����ź�ҹ��ⷮ * ������ ��
		this->carbonEmission += (long long)(this->industries[i].day_carbonPerProduce * this->industries[i].workingRate * this->population);
	}
	this->carbonEmission += (long long)(this->energies.carbonPerProduce * this->energies.firePowerPlants);
	//��źȭ�¹����� ����* ������ ���� ���� ź�ҹ��ⷮ
	this->carbonEmission += (long long)(this->life.carPerPerson * this->population * (1 - this->life.ecocarRatio) * this->life.carbonPerCar);
	//1��� �ڵ��� ���� ����*�α���*ȭ�������ڵ�������*�ڵ��� 1�� �� ����ź�ҹ��ⷮ
	this->carbonEmission += (long long)(this->life.houses * (1 - this->life.greenhouses) * (1 - this->life.sunhouses) * this->life.carbonPerHouse);
	//�� �ǹ� ����*�׸� ���𵨸��� �¾籤�г� �̼�ġ �ǹ� ����*�ǹ� �� ���� ź�ҹ��ⷮ
	this->carbonEmission += (long long)(this->life.houses * (1 - this->life.greenhouses) * (this->life.sunhouses) * this->life.carbonPerHouse * 0.65);
	//�� �ǹ� ����*�¾籤�г� ��ġ �ǹ� ����*�ǹ� �� ���� ź�ҹ��ⷮ*65%
	this->carbonEmission += (long long)(this->life.carbonPerPerson * this->population);
	//1�δ� �ϻ�� ź�ҹ��ⷮ*�α���

}

///<summary>
///#�Լ� ���� : ���� �� �α��� �ջ� (��-����ڹݿ�)
///</summary>
void Country::add_totalPopulation()
{
	this->population = (long long)(this->defaultPopulation * (1 - this->deadRate));
}

///<summary>
///#�Լ����� : ������� �ʿ�� �ϴ� �������� ���
///</summary>
void Country::total_industryEnergy()
{
	this->industryEnergy = 0;

	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		this->industryEnergy += (int)(this->industries[i].day_energyPerProduce * this->industries[i].workingRate * this->population);
		//�ʿ�� �ϴ� �������� += �� ����� ��������� ��������뷮 * �����ڼ�
	}
}


///<summary>
///#�Լ����� : ��Ȱ���� �ʿ�� �ϴ� �������� ���
///</summary>
void Country::total_lifeEnergy()
{
	this->lifeEnergy = 0;

	this->lifeEnergy += (int)(this->life.day_energyPerHouse * this->life.houses * (1 - this->life.greenhouses) * (1 - this->life.sunghouses));
	//�׸����𵨸��� �¾籤 �г� ��ġ ���� ���� �ǹ� �� * �ǹ� �� �������Ҹ��
	this->lifeEnergy += (int)(this->life.day_energyPerHouse * 0.65 * this->life.houses * (1 - this->life.greenhouses) * (this->life.sunhouses));
	//�¾籤 �г� ��ġ�� �ǹ� �� * �ǹ� �� ������ �Ҹ�� 65%
	this->lifeEnergy += (int)(this->life.day_energyPerPerson * this->population);
	//�α��� * 1�δ� ��Ȱ�� �ʿ��� ��������
}


///<summary>
///#�Լ����� : �� �ʿ�� �ϴ� �������� ���
///</summary>
void Country::total_needEnergy()
{
	this->total_needEnergy = (this->industryEnergy + this->lifeEnergy);
}


///<summary>
///#�Լ� ���� : �� ź�Ҽ� �� ��å���ݿ� ���� ���� �߰�
///</summary>
void Country::add_monthTax()
{
	for (int i = 0; i < INDUSTRY_NUM; i++)
	{
		//@ �� ���� ȣ�� �ֱ⸦ ������ test������ �Ϸ� ������ ȯ���ϹǷ� ������ 30��������.
		this->budget += (long long)(this->industries[i].taxIndex * this->industries[i].day_gdpPerProduce * 30 * industries[i].workingRate * this->population);
		// �� �߰� ���� += ��� ���ݺ��� * ���� ����� gdp * 30�� * ��� �����ڼ�
		//�� �� ���� ��å�� ���� ����� �߰� �ΰ��� ź�Ҽ� ������ *0���� �߰� ���� �Ҵ� ����
		// �� ��å�� ���� ź�Ҽ� �ΰ��� ��å ���� �����޺��� ȿ�� �߻��ϵ��� �˸����� �ֱ�

		this->budget += (long long)(this->life.taxTransport * this->life.carPerPerson * (1 - this->life.ecocarRatio) * this->population);
		//���������� �ڵ��� �����ŭ ���� �������� �ΰ�
		this->budget += (long long)(this->life.taxHouse * this->life.houses * (1 - this->life.greenhouses) * (1 - this->life.sunhouses));
		//�׸� ���𵨸��� ���ϰ�, �¾籤 �гε� ��ġ ���� �ǹ� ����ŭ �ְ� �������� �ΰ�
		this->budget += (long long)(this->life.taxHouse * 0.65 * this->life.houses * (1 - this->life.greenhouses) * (this->life.sunhouses));
		//�׸� ���𵨸��� ��������, �¾籤 �г��� ��ġ�� �ǹ��� �ְ� ���������� 65%�� ���� �ΰ�
		this->budget += (long long)(this->life.taxLife * this->population);
		//��Ȱ�� �ΰ��� ���������� �� ���ο��� ����.

		//@���� ���� : industry�� ���������� float������, life�� ���������� �޷� �����ӿ� ��������.
		//(�ֳ��ϸ� industry�� ����߻� gdp��� ��ġ�� �ֱ⿡ ������ ���� �� ������, life�� �׷� �� ���� ����)

	}

}

///<summary>
///#�Լ� ���� : ���� ���� �긲�� ��ȭ (��)
///</summary>
void Country::calculator_monthForest()
{
	this->countryForest = (int)(this->countryForest * (1 - this->removeForest));
}


///<summary>
///#�Լ� ���� : gdp�� ������ �����Ͽ� ���� ������ �Ҵ��ϴ� �Լ�
///</summary>
void Country::calculator_budget()
{
	this->budget += (gdp * taxRate); //@ �� ���� ȣ�� �ֱ⸦ ������ test������ 1�� �ֱ�� ȯ�������Ƿ� ������ 360
}

///<summary>
///#�Լ� ���� : gdp 0���� reset (��)
///</summary>
void Country::reset_annualGDP()
{
	this->gdp = 0;
}


void Country::printStatus()
{
	cout << "***CountryCode : " << countryCode << endl;//����
	cout << "***population : " << population << " ��" << endl; //�α���
	cout << "***GDP : $ " << gdp << endl; //�����ѻ���
	cout << "***taxRate : " << taxRate << " % " << endl;// ����
	cout << "***budget: $ " << budget << endl; //���� ����
	cout << "***carbonEmission : " << carbonEmission << " (t)" << endl; //ź�ҹ��ⷮ

}


///<summary>
///#�Լ� ���� : �Ҹ��� �Լ�
///</summary>
Country::~Country()
{
	delete[] industries;
}