#include "Industry.h"
#include <iostream>

void Industry::init_Industry(IndustryCode _code, long long _gdp, long long _carbon, float _workingRate)
{
	this->industryCode = _code;
	this->day_gdpPerProduce = _gdp;
	this->day_carbonPerProduce = _carbon;
	this->workingRate = _workingRate;
	this->taxIndex = 0; //��� ��å ���� �� ����� �ΰ�
}

///<summary>
///#�Լ����� : ź�ҹ��ⷮ ��ȭ
///</summary>
void Industry::change_carbonPerProduce(float _rateOfChange_carbon)
{
	// ex) �Ű������� 0.3�� ���´ٸ� �� ź�ҹ��ⷮ�� 30% �����Ѵ�
	// ex) �Ű������� -0.2�� ���´ٸ� �� ź�ҹ��ⷮ�� 20% �����Ѵ�
	long long temp = this->day_carbonPerProduce * _rateOfChange_carbon;
	this->day_carbonPerProduce += temp;
}

///<summary>
///#�Լ����� : �����ں��� ��ȭ
///</summary>
void Industry::change_workingRate(float _rateOfChange_working)
{
	//�̹� �Ǽ� �����̹Ƿ� %�� �������� ���� ��Ÿ����.
	// ex) �Ű������� 0.01�� ���´ٸ� �����ں����� 0.01 �����Ѵ�.
	this->workingRate += _rateOfChange_working;

	if (this->workingRate > 1)
	{
		this->workingRate = 1;
	} //�����ں��� 100 �ʰ��� ��� 100���� �ٽ� ����
}

///<summary>
///#�Լ����� : �������� ��ȭ
///</summary>
void Industry::change_taxIndex(float _rateOfChange_tax)
{
	//�̹� �Ǽ� �����̹Ƿ� %�� �������� ���� ��Ÿ����.
	// ex) �Ű������� 0.01�� ���´ٸ� ���ݺ����� 0.01 �����Ѵ�.
	this->taxIndex += _rateOfChange_tax;
}
