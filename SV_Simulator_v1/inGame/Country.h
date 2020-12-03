#pragma once
#include "CountryCode.h"
#include "IndustryCode.h"
#include "Energy.h"
#include "Life.h"
#include "Industry.h"
#define INDUSTRY_NUM 5


class Country
{
private:
	friend class World;
	friend class IndustryPolicy;

	CountryCode countryCode; //�����ڵ�
	long long budget; //���� ��������
	long long gdp; //���� gdp
	long long population; //���� �α���(����ڼ�)
	long long defaultPopulation; //���� �ʱ� �α���
	long long carbonEmission; //���� ź�ҹ��ⷮ
	int countryForest; //���� �긲 ����
	float taxRate; //���� ����
	float supportRate; //������
	float recognitionRate; //�νķ�
	float refugeeRate; //���� ���ĳ��� ����
	float deadRate; //���� ����� ����
	long long food; //�۹����귮 (��� �з�����)
	float removeForest; //�����
	int industryEnergy; //������� �ʿ�� �ϴ� ��������(����)
	int lifeEnergy; //��Ȱ���� �ʿ�� �ϴ� ��������(����)
	int needEnergy; //�� �ʿ�� �ϴ� ��������(����)

public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# �ʱ�ȭ �Լ� (!= ������ �Լ�)
			-�����ڵ� �ʱ�ȭ
			-�������� �ʱ�ȭ
			-�ʱ��α��� �ʱ�ȭ
			-�긲���� �ʱ�ȭ
			-��� �ʱ�ȭ
			-������ �ʱ�ȭ
			-��Ȱ �ʱ�ȭ
			-���� ���� �ʱ�ȭ
			-������ 10 �ʱ�ȭ
			-�νķ� 10 �ʱ�ȭ
			-���ĳ��κ��� 5 �ʱ�ȭ
			-����� 0 �ʱ�ȭ
			-�۹����귮 �α��� ��ŭ �ʱ�ȭ
			-����� 5 �ʱ�ȭ

	2. �ֱ� ���� ����� �ʿ��� �Լ�
		<day>
		# ������� �߻��� ���� �� GDP����
		# ����� ��Ȱ���� �߻��� ź�ҹ��ⷮ ����(�� ������ ����)
		# ���� �α��� ��� (����� �ݿ��Ͽ�)
		# ������� �ʿ�� �ϴ� �������� ���
		# ��Ȱ���� �ʿ�� �ϴ� �������� ���
		# �� �ʿ��� �������� ���

		<month>
		# ���ݿ� ���� ���� �߰�
		# ���� ���� �긲�� ��ȭ

		<year>
		# 1�� ���� å��
		# 1�� ������ GDP 0���� ����

	#########################################*/

	/* ���� ���� �ι�
	* countryCode, forest, food, removeForest
	*/
	void init_Country_Info(CountryCode _code, int _forest, long long _food, float _removeForest);

	/* �����ι�
	* budget, taxRate,
	*/
	void init_Country_Finance(long long _budget, float _taxRate);

	/* �α� �ι�
	* population, refugeeRate
	*/
	void init_Country_Population(long long _population, float _refugeeRate);

	/* ��� �ι�
	* workingRate_st, workingRate_oil, workingRate_sv, workingRate_mf, workingRate_ag
	*/
	void init_Country_Industry(float _workingRate_st, float _workingRate_oil, float _workingRate_sv, float _workingRate_mf, float _workingRate_ag);

	/* ��� �ι�
	* carPerPerson, ecocarRatio
	*/
	void init_Country_Transport(float _carPerPerson, float _ecocarRatio);

	/* �ְ� �ι�
	* houses, greenhouses, sunhouses
	*/
	void init_Country_House(long long _houses, float _greenhouses, float _sunhouses);

	/* ��Ȱ �ι�
	* carbonPerPerson, day_energyPerPerson
	*/
	void init_Country_Person(long long _carbonPerPerson, int _day_energyPerPerson);

	/* ���� �ι�
	* firePlants, greenPlants
	*/
	void init_Country_Plants(int _firePlants, int _greenPlants);



	///<summary>
	///#�Լ� ���� : ����߻� ���� �� gdp ���� (��)
	///</summary>
	void add_totalGDP();


	///<summary>
	///#�Լ� ���� : ���� �� �α��� �ջ� (��-����ڹݿ�)
	///</summary>
	void add_totalPopulation();


	///<summary>
	///#�Լ� ���� : ���+��Ȱ+������ �߻� ź�ҹ��ⷮ �ջ�(��-����)
	///</summary>
	void add_totalCarbonEmission();



	///<summary>
	///#�Լ����� : ������� �ʿ�� �ϴ� �������� ���
	///</summary>
	void total_industryEnergy();


	///<summary>
	///#�Լ����� : ��Ȱ���� �ʿ�� �ϴ� �������� ���
	///</summary>
	void total_lifeEnergy();


	///<summary>
	///#�Լ����� : �� �ʿ�� �ϴ� �������� ���
	///</summary>
	void total_needEnergy();

	///<summary>
	///#�Լ� ���� : �� ź�Ҽ� �� ��å���ݿ� ���� ���� �߰� (��)
	///</summary>
	void add_monthTax();


	///<summary>
	///#�Լ� ���� : ���� ���� �긲�� ��ȭ (��)
	///</summary>
	void calculator_monthForest();


	///<summary>
	///#�Լ� ���� : gdp 0���� reset (��)
	///</summary>
	void reset_annualGDP();


	///<summary>
	///#�Լ� ���� : gdp�� ������ �����Ͽ� 1�� ���� ������ �Ҵ��ϴ� �Լ� (��)
	///</summary>
	void calculator_budget();


	///<summary>
	///#�Լ� ���� : ����� �� �׽�Ʈ �Լ�
	///</summary>
	//void printStatus();

	long long GetBudget() { return budget; }//���� ��������
	long long GetGdp() { return gdp; } //���� gdp
	long long GetPopulation() { return population; } //���� �α���(����ڼ�)
	long long GetDefaultPopulation() {return defaultPopulation;} //���� �ʱ� �α���
	long long GetCarbonEmission() { return carbonEmission; } //���� ź�ҹ��ⷮ
	int GetCountryForest() { return countryForest; } //���� �긲 ����
	Energy energies; //���� �������ι� 
	Life life; //���� ��Ȱ�ι� 
	Industry industries[INDUSTRY_NUM]; //���� ����ι� �迭
	int tesst[3];

	float GetTaxRate() { return taxRate; } //���� ����
	float GetSupportRate() { return supportRate; } //������
	float GetRecognitionRate() { return recognitionRate; } //�νķ�
	float GetRefugeeRate() { return refugeeRate; } //���� ���ĳ��� ����
	float GetDeadRate() { return deadRate; } //���� ����� ����
	long long GetFood() { return food; } //�۹����귮 (��� �з�����)
	float GetRemoveForest() { return removeForest; } //�����
	int GetIndustryEnergy() { return industryEnergy; } //������� �ʿ�� �ϴ� ��������(����)
	int GetLifeEnergy() { return lifeEnergy; } //��Ȱ���� �ʿ�� �ϴ� ��������(����)
	int GetNeedEnergy() { return needEnergy; } //�� �ʿ�� �ϴ� ��������(����)

	~Country();
};