#include "World.h"
#include "Country.h"
//#include <iostream>
//using namespace std;
///<summary>
	///#�Լ� ���� : ����������� �ʱ�ȭ�����ִ� ������ �Լ� 
	///#�Ű����� countiryNum : ������ ���� ����
	///</summary>
World::World()
{
	for (int i = 0; i < COUNTRY_NUM; i++)
		countries[i] = new Country();

	//�Ű����� : �����ڵ� / gdp / ���� / �α� �� / ź�ҹ��ⷮ
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		countries[i]->init_Country(
			static_cast<CountryCode> (i),
			(i + 1 % 5) * 384700000,
			0.3,
			(i % 5 + 1) * 1000000,
			(i % 3 + 1) * 50000);
	}

	this->worldCarbonPPM = 411.29; //(2020�� 9�� ���� ��)
	calculator_worldTemperature(); //�ʱ�ȭ�� �� �������� ��տµ� ����
	total_CarbonEmissionOfCountries();//������ ź�ҹ��ⷮ �ջ갪���� �ʱ�ȭ
	total_PopulationOfCountries(); //������ �α��� �ջ갪���� �ʱ�ȭ
}
World::~World()
{
	for (int i = 0; i < COUNTRY_NUM; i++)
		delete countries[i];

}


///<summary>
///#�Լ� ���� : ��� ������ ź�ҹ��ⷮ�� �ջ��ϴ� �Լ�
///</summary>
void World::total_CarbonEmissionOfCountries()
{
	this->worldCarbonEmission = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldCarbonEmission += this->countries[i]->carbonEmission;
	}
}

///<summary>
///#�Լ� ���� : ��� ������ �α����� �ջ��ϴ� �Լ�
///</summary>
void World::total_PopulationOfCountries()
{
	this->worldPopulation = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldPopulation += this->countries[i]->population;
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
	this->worldCarbonPPM = 0.001 * (this->worldCarbonEmission);
}

///<summary>
///#�Լ� ���� : ����� �� �׽�Ʈ �Լ�
///</summary>
void World::printStatus()
{
	//cout << "countryNum: " << COUNTRY_NUM << endl; // (+)�߰����� : ���� ����
	//cout << "worldTemperature: " << worldTemperature << endl; //������ ��տµ�
	//cout << "worldCarbonEmission: " << worldCarbonEmission << endl; //������ ź�ҹ��ⷮ
	//cout << "worldPopulation: " << worldPopulation << endl; //������ �α���
	//cout << "worldCarbonPPM: " << worldCarbonPPM << endl; //������ ���ź�ҳ�(ppm)

}