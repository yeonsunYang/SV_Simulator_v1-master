#pragma once
#include <string>
#define COUNTRY_NUM 2

class Country;

class World
{
	friend class Game;
private:
	Country* countries; //������ ��� ���� ������
	float worldTemperature; //������ ��տµ�
	long long worldCarbonEmission; //������ ź�ҹ��ⷮ(�� ����)
	long long worldPopulation; //������ �α� ��
	float worldCarbonPPM; //������ ���ź�ҳ�(ppm)
	
public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# ������ 
			-���� ����
			-��� �µ� �ʱ�ȭ 
			-ź�ҹ��ⷮ �ʱ�ȭ
			-�α��� �ʱ�ȭ 
			-ź������� �ʱ�ȭ
			-ź�� �� �ʱ�ȭ
		
	
	2. �ֱ� ���� ����� �ʿ��� �Լ�
		<day>
		# ������ ��տµ� ��� (ź�� �� �ʿ�)
		# ź�ҳ󵵰�� (ź�ҹ��ⷮ�� ����� �ʿ�)
		# ������ ź�ҹ��ⷮ �ջ�
		# ������ �α��� �ջ�
		
	#########################################*/

	///<summary>
	///#�Լ� ���� : ����������� �ʱ�ȭ�����ִ� ������ �Լ� 
	///#�Ű����� countiryNum : ������ ���� ����
	///</summary>
	World(); 

	///<summary>
	///#�Լ� ���� : ��� ������ ź�ҹ��ⷮ�� �ջ��ϴ� �Լ�
	///</summary>
	void total_CarbonEmissionOfCountries();

	///<summary>
	///#�Լ� ���� : ��� ������ �α����� �ջ��ϴ� �Լ�
	///</summary>
	void total_PopulationOfCountries();

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
	///#�Լ� ���� : ����� �� �׽�Ʈ �Լ�
	///</summary>
	void printStatus();

	~World();
};