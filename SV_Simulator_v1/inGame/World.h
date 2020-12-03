#pragma once
#include <string>
#include <time.h>
#include <stdlib.h>
#define COUNTRY_NUM 175
//#define COUNTRY_NUM 175

class Country;

class World
{
	friend class Game;
private:
	Country* countries[COUNTRY_NUM]; //������ ��� ���� ������
	float worldTemperature; //������ ��տµ�
	float worldCarbonPPM; //������ ���ź�ҳ�(ppm)
	long long worldCarbonEmission; //������ ź�ҹ��ⷮ(�� ����)
	long long worldCarbonAbsorbed; //������ ź�������(�� ����)
	long long worldForest; //������ �긲����
	long long worldPopulation; //������ �α� ��
	long long worldDead; //������ ����� ��
	long long worldRefugees; //������ ���ĳ��� ��
	long long worldFood; //������ �۹����귮
	float disasterProbability; //�糭�߻�Ȯ��
	long long foodCriticalPoint; //�۹����귮 �Ӱ���
	long long defaultWorldFood; //�ʱ� �۹����귮 �� (�Ӱ��� �� ���� ����)
	float tempCriticalPoint; //��տµ� �Ӱ���
	float defaultWorldTemperature; //�ʱ� ��տµ� (�Ӱ��� �� ���� ����)

public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# ������
			-���� ����
			-�ʱ���տµ� �� ����(�̸� ���� �긲�����ջ�, ��������, ���ⷮ���, �󵵰��)
			-�ʱ��۹����귮 �� ����(�̸� ���� ������ �۹����귮 �ջ�)
			-�糭�߻�Ȯ�� �ʱ�ȭ


	2. �ֱ� ���� ����� �ʿ��� �Լ�
		<day>
		# ������ �긲���� �ջ�
		# ������ ź������� ���
		# ������ ź�ҹ��ⷮ �ջ�
		# ź�� �� ���
		# ������ ��տµ� ���
		# ��տµ� �Ӱ��� �˻�
		# ������ �۹����귮 �ջ�
		# �۹����귮 �Ӱ��� �˻�
		# �糭 �߻�
		# ������ �α��� �ջ�
		# ������ ���μ� �ջ�

	#########################################*/

	///<summary>
	///#�Լ� ���� : ����������� �ʱ�ȭ�����ִ� ������ �Լ� 
	///#�Ű����� countiryNum : ������ ���� ����
	///</summary>
	World();

	///<summary>
	///#�Լ� ���� : ��� ������ �긲������ �ջ��ϴ� �Լ�
	///</summary>
	void total_ForestOfCountries();

	///<summary>
	///#�Լ� ���� : ��� ������ ź�ҹ��ⷮ�� �ջ��ϴ� �Լ�
	///</summary>
	void total_CarbonEmissionOfCountries();

	///<summary>
	///#�Լ� ���� : ��� ������ ź��������� �ջ��ϴ� �Լ�
	///</summary>
	void total_CarbonAbsorbedOfCountries();

	///<summary>
	///#�Լ� ���� : ��� ������ �α����� �ջ��ϴ� �Լ�
	///</summary>
	void total_PopulationOfCountries();

	///<summary>
	///#�Լ� ���� : ��� ������ ���μ��� �ջ��ϴ� �Լ�
	///</summary>
	void total_RefugeesOfCountries();

	///<summary>
	///#�Լ� ���� : ���� �µ��� ����ϴ� �Լ�
	///#w1 = 0.008984563 , b=12.366367558
	///</summary>
	void calculator_worldTemperature();

	///<summary>
	///#�Լ� ���� : ���� ź�� �󵵸� ����ϴ� �Լ�
	///#w1 = 1 b=0
	///</summary>
	void calculator_worldCarbonPPM();

	///<summary>
	///#�Լ� ���� : ��տµ��� �Ӱ����� �˻��ϴ� �Լ�
	///</summary>
	void check_worldTemperature();

	///<summary>
	///#�Լ� ���� : ��� ������ �۹����귮�� �ջ��ϴ� �Լ�
	///</summary>
	void total_FoodOfCountries();

	///<summary>
	///#�Լ� ���� : �۹����귮�� �Ӱ����� �˻��ϴ� �Լ�
	///</summary>
	void check_worldFood();

	///<summary>
	///#�Լ� ���� : Ȯ���� ���� �糭�� �߻��ϴ� �Լ�
	///</summary>
	void random_disaster();

	///<summary>
	///#�Լ� ���� : ����� �� �׽�Ʈ �Լ�
	///</summary>
	void printStatus();


	///<summary>
	///#�Լ� ���� : �Ҹ��� �Լ� 
	///</summary>
	~World();
};