#include "World.h"
#include "Country.h"
///<summary>
	///#�Լ� ���� : ����������� �ʱ�ȭ�����ִ� ������ �Լ� 
	///#�Ű����� countiryNum : ������ ���� ����
	///</summary>
World::World(int _countryNum)
{
	this->countryNum = _countryNum;
	countries = new Country[countryNum];
	
	//�Ű����� : �����ڵ� / ������� / gdp / ���� / �α� �� / ź�ҹ��ⷮ / ź�������
	countries[KOR].init_Country(KOR,1,1619000000000, 0.3, 51640000, 616096687, 0);
	countries[USA].init_Country(USA,1,20540000000000, 0.2, 328200000, 5269529513, 0);

	this->worldCarbonPPM = 411.29; //(2020�� 9�� ���� ��)
	calculator_worldTemperature(); //�ʱ�ȭ�� �� �������� ��տµ� ����
	total_CarbonEmissionOfCountries();//������ ź�ҹ��ⷮ �ջ갪���� �ʱ�ȭ
	total_CarbonAbsorbingOfCountries(); //������ ź������� �ջ갪���� �ʱ�ȭ
	total_PopulationOfCountries(); //������ �α��� �ջ갪���� �ʱ�ȭ

}


///<summary>
///#�Լ� ���� : ��� ������ �α����� �ջ��ϴ� �Լ�
///</summary>
void World::total_PopulationOfCountries()
{
	this->worldPopulation = 0;
	for (int i = 0; i < this->countryNum; i++)
	{
		this->worldPopulation += this->countries[i].population;
	}
}
///<summary>
///#�Լ� ���� : ��� ������ ź�ҹ��ⷮ�� �ջ��ϴ� �Լ�
///</summary>
void World::total_CarbonEmissionOfCountries()
{
	this->worldCarbonEmission = 0;
	for (int i = 0; i < this->countryNum; i++)
	{
		this->worldCarbonEmission += this->countries[i].carbonEmission;
	}
}

///<summary>
///#�Լ� ���� : ��� ������ ź��������� �ջ��ϴ� �Լ�
///</summary>
void World::total_CarbonAbsorbingOfCountries()
{
	this->worldCarbonAbsorbing = 0;
	for (int i = 0; i < this->countryNum; i++)
	{
		this->worldCarbonAbsorbing += this->countries[i].carbonAbsorbing;
	}
}

///<summary>
///#�Լ� ���� : ���� �µ��� ����ϴ� �Լ�
///#w1 = 0.008984563 , b=12.366367558
///</summary>
void World::calculator_worldTemperature()
{
	this->worldTemperature = 0.008984563 * this->worldCarbonPPM + 12.366367558;
}

///<summary>
///#�Լ� ���� : ���� ź�� �󵵸� ����ϴ� �Լ�
///#w1 = 1.2 b=0
///</summary>
void World::calculator_worldCarbonPPM()
{
	this->worldCarbonPPM = 1.2 * (this->worldCarbonEmission - this->worldCarbonAbsorbing);
}