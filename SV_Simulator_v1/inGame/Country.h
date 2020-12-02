#pragma once
#include <string>
#include "CountryCode.h"
#include "IndustryCode.h"
#define INDUSTRY_NUM 5
class Industry;
class Energy;
class Life;

class Country
{
private:
	friend class World;
	friend class IndustryPolicy;

	CountryCode countryCode; //�����ڵ�
	long long budget; //���� ��������
	long long gdp; //���� gdp
	long long population; //���� �α���
	long long defaultPopulation; //���� �ʱ� �α���
	long long carbonEmission; //���� ź�ҹ��ⷮ
	int countryForest; //���� �긲 ����
	Industry* industries; //���� ����ι� ������
	Energy energies; //���� �������ι� 
	Life life; //���� ��Ȱ�ι� 
	float taxRate; //���� ����
	float supportRate; //������
	float recognitionRate; //�νķ�
	float refugeeRate; //���� ���ĳ��� ����
	float deadRate; //���� ����� ����
	long long food; //�۹����귮 (��� �з�����)
	float removeForest; //�����
	int industryEnergy; //������� �ʿ�� �ϴ� ��������(����)
	int lifeEnergy; //��Ȱ���� �ʿ�� �ϴ� ��������(����)
	int total_needEnergy; //�� �ʿ�� �ϴ� ��������(����)

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
	///<summary>
	///#�Լ� ���� : �ʱ�ȭ �Լ�
	///</summary>
	void init_Country(CountryCode _code, long long _budget, float _taxRate, long long _population, int _forest, float _refugeeRate, long long _food, float _removeForest,
		float workingRate_st, float workingRate_oil, float workingRate_sv, float workingRate_mf, float workingRate_ag,
		float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson,
		int _firePlants, int _greenPlants);


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
	void printStatus();

};