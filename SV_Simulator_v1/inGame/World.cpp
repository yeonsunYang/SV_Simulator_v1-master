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
	/*
	(1)���� ����
	(2)�ʱ���տµ� �� ����(�̸� ���� �긲�����ջ�, ��������, ���ⷮ���, �󵵰��)
	(3)�ʱ��۹����귮 �� ����(�̸� ���� ������ �۹����귮 �ջ�)
	(4)�糭�߻�Ȯ�� �ʱ�ȭ
	*/

	//(1)
	for (int i = 0; i < COUNTRY_NUM; i++) {
		countries[i] = new Country();

		if (i == static_cast<int> (CountryCode::South_Korea)) {
			countries[i]->init_Country_Info(static_cast<CountryCode> (i), 411290, 50000000ll, 0.03f);
			countries[i]->init_Country_Finance(16190000ll, 0.3f);
			countries[i]->init_Country_Population(51640000ll, 0.02f);
			countries[i]->init_Country_Industry(0.1f, 0.05f, 0.2f, 0.1f, 0.01f);
			countries[i]->init_Country_Transport(1.2f, 0.01f);
			countries[i]->init_Country_House(5000000ll, 0.01f, 0.09f);
			countries[i]->init_Country_Person(15ll, 15);
			countries[i]->init_Country_Plants(5, 1);

		}
		else if (i == static_cast<int> (CountryCode::United_States_of_America)) {
			countries[i]->init_Country_Info(static_cast<CountryCode> (i), 5269520, 120000000ll, 0.06f);
			countries[i]->init_Country_Finance(205400000ll, 0.2f);
			countries[i]->init_Country_Population(328200000ll, 0.08f);
			countries[i]->init_Country_Industry(0.12f, 0.09f, 0.3f, 0.06f, 0.07f);
			countries[i]->init_Country_Transport(1.8f, 0.05f);
			countries[i]->init_Country_House(12000000ll, 0.1f, 0.12f);
			countries[i]->init_Country_Person(30ll, 30);
			countries[i]->init_Country_Plants(10, 5);
		}
		else
		{
			countries[i]->init_Country_Info(static_cast<CountryCode> (i), 1000000 + (i * 10), 200000ll + (i * 10), 0.06f);
			countries[i]->init_Country_Finance(100000ll, 0.2f);
			countries[i]->init_Country_Population(25000000ll + (i * 10), 0.08f);
			countries[i]->init_Country_Industry(0.12f, 0.09f, 0.3f, 0.06f, 0.07f);
			countries[i]->init_Country_Transport(1.8f, 0.05f);
			countries[i]->init_Country_House(12000000ll, 0.1f, 0.12f);
			countries[i]->init_Country_Person(30ll, 30);
			countries[i]->init_Country_Plants(10, 5);
		}
	}

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
	this->disasterProbability = 0.01f;
}


///<summary>
///#�Լ� ���� : ��� ������ ź�ҹ��ⷮ�� �ջ��ϴ� �Լ� (1�� ������ ����)
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
///#�Լ� ���� : ��� ������ �긲������ �ջ��ϴ� �Լ�
///</summary>
void World::total_ForestOfCountries()
{
	this->worldForest = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldForest += this->countries[i]->countryForest;
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
		this->worldPopulation += this->countries[i]->population;
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
		this->worldRefugees += this->countries[i]->refugeeRate * this->countries[i]->population;
	}
}

///<summary>
///#�Լ� ���� : ���� �µ��� ����ϴ� �Լ�
///#w1 = 0.008984563 , b=12.366367558
///</summary>
void World::calculator_worldTemperature()
{
	this->worldTemperature = 0.008984563f * this->worldCarbonPPM + 12.366367558f;
}

///<summary>
///#�Լ� ���� : ���� ź�� �󵵸� ����ϴ� �Լ�
///#w1 = 1.2 b=0
///</summary>
void World::calculator_worldCarbonPPM()
{
	this->worldCarbonPPM = 0.001f * (this->worldCarbonEmission - this->worldCarbonAbsorbed);
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
		this->disasterProbability += 0.05f;
		for (int i = 0; i < COUNTRY_NUM; i++)
		{
			this->countries[i]->recognitionRate += 0.08f; //�νķ� ����
			this->countries[i]->food -= (long long)(this->countries[i]->food * 0.1f);//�ķ�����
		}
	}
	this->defaultWorldTemperature += 0.1f;
}

///<summary>
///#�Լ� ���� : ��� ������ �۹����귮�� �ջ��ϴ� �Լ�
///</summary>
void World::total_FoodOfCountries()
{
	this->worldFood = 0;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		this->worldFood += this->countries[i]->food;
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
			this->countries[i]->recognitionRate += 0.1f; //�νķ� ����
			this->countries[i]->deadRate += 0.05f; //����� ���� ����
			this->countries[i]->refugeeRate += 0.08f; //���� ���� ����
		}
	}
	this->defaultWorldFood -= 50000000;
}

///<summary>
///#�Լ� ���� : Ȯ���� ���� �糭�� �߻��ϴ� �Լ�
///</summary>
void World::random_disaster()
{
	bool disaster[100] = { true };
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

	if (select_oneDay == true)
	{
		//�糭�߻� (���ĳ��� ���� ����� �� ����, �۹����귮 ����)
		int randomCountry = rand() % COUNTRY_NUM; //�߻��� �����ϰ� ����
		float deadRate = (rand() % 6) / 100; //����� ���� 6%�ȿ��� �����ϰ�
		float refugeeRate = (rand() % 12) / 100; //���� ���� 12% �ȿ��� �����ϰ�

		this->countries[randomCountry]->refugeeRate += refugeeRate; //���� ����
		this->countries[randomCountry]->deadRate += deadRate; //����ڼ� ����
		this->countries[randomCountry]->food -= (long long)(this->countries[randomCountry]->food * 0.08);//�ķ�����
		this->countries[randomCountry]->recognitionRate += (refugeeRate); //�νķ� ����

	}
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


///<summary>
///#�Լ� ���� : �Ҹ��� �Լ� 
///</summary>
World::~World()
{
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		if (countries[i] != nullptr)
		delete countries[i];
		countries[i] = nullptr;
	}
}

