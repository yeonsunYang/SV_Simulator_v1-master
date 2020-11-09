#pragma once
#include <string>

class Country;

class World
{
private:
	Country* countries; //������ ��� ���� ������
	int countryNum; // (+)�߰����� : ���� ����
	float worldTemperature; //������ ��տµ�
	long worldCarbonEmission; //������ ź�ҹ��ⷮ
	long long worldPopulation; //������ �α���
	long worldCarbonAbsorbing; //������ ź�������
	float worldCarbonPPM; //������ ���ź�ҳ�(ppm)
	
public:
	/*#####################################
	1. �ʱ�ȭ �Ǿ�� �ϴ� �κ�
		# ������ 
			���� ���� �ʱ�ȭ
			-���� ����
			-��� �µ� �ʱ�ȭ 
			-ź�ҹ��ⷮ �ʱ�ȭ
			-�α��� �ʱ�ȭ 
			-ź������� �ʱ�ȭ
			-ź�ҳ��ʱ�ȭ
		
	
	2. �ֱ� ���� ����� �ʿ��� �Լ�
		# ������ ��տµ� ��� (ź�� �� �ʿ�)
		# ź�ҳ󵵰�� (ź�ҹ��ⷮ�� ����� �ʿ�)
		# ������ ź�ҹ��ⷮ �ջ�
		# ������ ź������� �ջ�
		# ������ �α��� ���
	
	3. �̺�Ʈ �Լ�
		# ź�ҹ��ⷮ ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
		# ź������� ��ȭ�Ǵ� �̺�Ʈ �� ȣ�� (����)
		
	#########################################*/

	///<summary>
	///#�Լ� ���� : ����������� �ʱ�ȭ�����ִ� ������ �Լ� 
	///#�Ű����� countiryNum : ������ ���� ����
	///</summary>
	World(int countryNum); 

	///<summary>
	///#�Լ� ���� : ��� ������ �α����� �ջ��ϴ� �Լ�
	///</summary>
	void total_PopulationOfCountries();

	///<summary>
	///#�Լ� ���� : ��� ������ ź�ҹ��ⷮ�� �ջ��ϴ� �Լ�
	///</summary>
	void total_CarbonEmissionOfCountries();

	///<summary>
	///#�Լ� ���� : ��� ������ ź��������� �ջ��ϴ� �Լ�
	///</summary>
	void total_CarbonAbsorbingOfCountries();

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

};