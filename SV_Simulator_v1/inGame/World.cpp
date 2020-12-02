#include "World.h"
#include "Country.h"
#include <iostream>
using namespace std;
///<summary>
	///#�Լ� ���� : ����������� �ʱ�ȭ�����ִ� ������ �Լ� 
	///#�Ű����� countiryNum : ������ ���� ����
	///</summary>
World::World()
{
	/*
	(1)���� ����
	(2)�ʱ���տµ� �� ����(�̸� ���� �긲�����ջ�, ��������, ���ⷮ���, �󵵰��)
	(3)�ʱ��۹����귮 �� ����(�̸� ���� ������ �۹����귮 �ջ�)
	(4)�糭�߻�Ȯ�� �ʱ�ȭ
	*/

	//(1)
	countries = new Country[COUNTRY_NUM];

	/*init_Country(CountryCode _code, long long _budget, float _taxRate, long long _population, int _forest, float _refugeeRate, long long _food, float _removeForest,
	float workingRate_st, float workingRate_oil, float workingRate_sv, float workingRate_mf, float workingRate_ag,
		float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson,
		int _firePlants, int _greenPlants)*/

	countries[South_Korea].init_Country(South_Korea, 16190000, 0.3, 51640000, 411290, 0.02, 50000000, 0.03, 0.1, 0.05, 0.2, 0.1, 0.01, 1.2, 0.01, 5000000, 0.01, 0.09, 15, 15, 5, 1);
	countries[United_States_of_America].init_Country(United_States_of_America, 205400000, 0.2, 328200000, 5269520, 0.08, 120000000, 0.06, 0.12, 0.09, 0.3, 0.06, 0.07, 1.8, 0.05, 12000000, 0.1, 0.12, 30, 30, 10, 5);

	//(2)
	total_ForestOfCountries();
	total_CarbonAbsorbedOfCountries();
	total_CarbonEmissionOfCountries();
	calculator_worldCarbonPPM();
	calculator_worldTemperature();
	this->defaultWorldTemperature = this->worldTemperature;

	//(3)
	total_FoodOfCountries();
	this->defaultWorldFood = this->worldFood;

	//(4)
	this->disasterProbability = 0.01;
}


///<summary>
///#�Լ� ���� : ��� ������ ź�ҹ��ⷮ�� �ջ��ϴ� �Լ� (1�� ������ ����)
///</summary>
void World::total_CarbonEmissionOfCountries()
{
	this->worldCarbonEmission = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldCarbonEmission += this->countries[i].carbonEmission;
	}
}


///<summary>
///#�Լ� ���� : ��� ������ �긲������ �ջ��ϴ� �Լ�
///</summary>
void World::total_ForestOfCountries()
{
	this->worldForest = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldForest += this->countries[i].countryForest;
	}
}


///<summary>
///#�Լ� ���� : ��� ������ ź��������� �ջ��ϴ� �Լ�
///</summary>
void World::total_CarbonAbsorbedOfCountries()
{
	this->worldCarbonAbsorbed = (long long)(this->worldForest * 0.001);
}

///<summary>
///#�Լ� ���� : ��� ������ �α����� �ջ��ϴ� �Լ�
///</summary>
void World::total_PopulationOfCountries()
{
	this->worldPopulation = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldPopulation += this->countries[i].population;
	}
}

///<summary>
///#�Լ� ���� : ��� ������ ���μ��� �ջ��ϴ� �Լ�
///</summary>
void World::total_RefugeesOfCountries()
{
	this->worldRefugees = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldRefugees += this->countries[i].refugeeRate * this->countries[i].population;
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
	this->worldCarbonPPM = 0.001 * (this->worldCarbonEmission - this->worldCarbonAbsorbed);
}

///<summary>
///#�Լ� ���� : ��տµ��� �Ӱ����� �˻��ϴ� �Լ�
///</summary>
void World::check_worldTemperature()
{
	/*
	(1)�ʱ� �µ����� ���� �µ��� �������� �Ӱ����� �Ѿ����� �˻�
	(2)�Ѿ��ٸ�, �糭�߻�Ȯ�� �����ϸ� ��� ������ �۹����귮�� ����
	(3)��� ������ �νķ� ����
	(4)�ʱ�µ� ����
	*/

	if ((this->worldTemperature - this->defaultWorldTemperature) >= 0.1)
	{
		//�ʱ� �µ����� 0.1�� �����ߴٸ�, 
		this->disasterProbability += 0.05;
		for (int i = 0; i < COUNTRY_NUM; i++)
		{
			this->countries[i].recognitionRate += 0.08; //�νķ� ����
			this->countries[i].food -= (long long)(this->countries[i].food * 0.1);//�ķ�����
		}
	}
	this->defaultWorldTemperature += 0.1;
}

///<summary>
///#�Լ� ���� : ��� ������ �۹����귮�� �ջ��ϴ� �Լ�
///</summary>
void World::total_FoodOfCountries()
{
	this->worldFood = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldFood += this->countries[i].food;
	}
}

///<summary>
///#�Լ� ���� : �۹����귮�� �Ӱ����� �˻��ϴ� �Լ�
///</summary>
void World::check_worldFood()
{
	/*
	(1)�ʱ� �۹����귮���� ���� �۹����귮�� �Ӱ��� �Ѿ����� �˻�
	(2)�Ѿ��ٸ�, ��� ������ ����ڼ��� ���ĳ��μ� ����
	(3)��� ������ �νķ� ����
	(4)�ʱ� �۹����귮 ����
	*/

	if ((this->defaultWorldFood - this->worldFood) >= 50000000)
	{
		//�Ӱ��� �Ѿ��ٸ�
		for (int i = 0; i < COUNTRY_NUM; i++)
		{
			this->countries[i].recognitionRate += 0.1; //�νķ� ����
			this->countries[i].deadRate += 0.05; //����� ���� ����
			this->countries[i].refugeeRate += 0.08; //���� ���� ����
		}
	}
	this->defaultWorldFood -= 50000000;
}

///<summary>
///#�Լ� ���� : Ȯ���� ���� �糭�� �߻��ϴ� �Լ�
///</summary>
void World::random_disaster()
{
	bool disaster[100] = { false };
	int probability = (int)(this->disasterProbability * 100);
	for (int i = 0; i < probability; i++)
	{
		disaster[i] = true;
	} //100�� �� �糭�� �߻��� Ȯ���� ����ŭ true�� ��ȯ

	srand(time(0));
	int temp;
	int rn;
	for (int i = 0; i < 99; i++)
	{
		rn = rand() % (100 - i) + i; //i���� 99������ ������ ���� ����
		temp = disaster[i];
		disaster[i] = disaster[rn];
		disaster[rn] = temp; //�����ϰ� ���� index�� i��° index ����.
	}//100���� �迭 ���� �˰���.

	int select_oneDay = rand() % 100; //�糭�߻�Ȯ���� �°� �������� �������� ��

	if (disaster[select_oneDay] == true)
	{
		//�糭�߻� (���ĳ��� ���� ����� �� ����, �۹����귮 ����)
		int randomCountry = rand() % COUNTRY_NUM; //�߻��� �����ϰ� ����
		float deadRate = (rand() % 6) / 100; //����� ���� 6%�ȿ��� �����ϰ�
		float refugeeRate = (rand() % 12) / 100; //���� ���� 12% �ȿ��� �����ϰ�

		this->countries[randomCountry].refugeeRate += refugeeRate; //���� ����
		this->countries[randomCountry].deadRate += deadRate; //����ڼ� ����
		this->countries[randomCountry].food -= (long long)(this->countries[randomCountry].food * 0.08);//�ķ�����
		this->countries[randomCountry].recognitionRate += (refugeeRate); //�νķ� ����

	}
}


///<summary>
///#�Լ� ���� : ����� �� �׽�Ʈ �Լ�
///</summary>
void World::printStatus()
{
	cout << "countryNum: " << COUNTRY_NUM << endl; // (+)�߰����� : ���� ����
	cout << "worldTemperature: " << worldTemperature << endl; //������ ��տµ�
	cout << "worldCarbonEmission: " << worldCarbonEmission << endl; //������ ź�ҹ��ⷮ
	cout << "worldPopulation: " << worldPopulation << endl; //������ �α���
	cout << "worldCarbonPPM: " << worldCarbonPPM << endl; //������ ���ź�ҳ�(ppm)

}


///<summary>
///#�Լ� ���� : �Ҹ��� �Լ� 
///</summary>
World::~World()
{
	delete[] countries;
}

