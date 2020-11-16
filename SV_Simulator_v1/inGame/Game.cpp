#include "Game.h"
#include <iostream>

using namespace std;


//*******************************

Game::Game() {
	date = 1;
	
	InitializeGame();
}

Game::~Game() {
	EndGame();
}
//*******************************




//���⼭ ���� �ۼ� ���� ============================================

//��Ģ������ ȣ��Ǵ� �Լ�*******************************************

void Game::InitializeGame() {
	// ���� �ʱ�ȭ ���� �ڵ� �ۼ�, main thread�� ȣ�� ����

	world = new World();

	// <��å ����>
	carbontax = new IndustryPolicy(Carbontax, Steel, 1000, 0.1, 0, 0); 
	// IndustryPolicyCode, IndustryCode, �ʿ俹��, ����������ȭ��, �����ں�����ȭ��, ź�ҹ��ⷮ��ȭ��

}

void Game::Oneday() {

	// 1�� ������ ����Ǵ� ���� �ڵ� �ۼ�, sub thread���� ȣ���.

	cout << "\n#######�� ���� ����#######\n" << endl;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		world->countries[i].printStatus();
		cout << endl;
		if (i != COUNTRY_NUM - 1)
		{
			cout << "-----------------------------\n" << endl;
		}
	}
	cout << "#########################" << endl;
	cout << "\n#######������ ����#######\n" << endl;
	world->printStatus();
	cout << endl;
	cout << "#########################" << endl;

	date += 1;

	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		world->countries[i].reset_annualGDP();
		world->countries[i].add_totalGDP();
		world->countries[i].calculator_budget();
		world->countries[i].add_totalCarbonEmission();
		world->countries[i].add_monthTax();
	}
	world->total_CarbonEmissionOfCountries();
	world->calculator_worldCarbonPPM();
	world->calculator_worldTemperature();

}

void Game::EndGame() {
	// ���� ����� �ʿ��� �ڵ� �ۼ�, main thread�� ȣ�� ����



}
//******************************************************************



//�̺�Ʈ �Լ�*********************************************************

void Game::EnforcePolicy(int _countryCode, int _policyCode) {
	//��å ����� ȣ��� �ʿ��� �ڵ� �ۼ�.


	//example

	switch (_countryCode)
	{
	case CountryCode::KOR:
		cout << "KOR���� ";
		break;

	case CountryCode::USA:
		cout << "USA���� ";
		break;

	default:
		break;
	}

	switch (_policyCode)
	{
	case IndustryPolicyCode::Carbontax:
		cout << "Carbontax ��å�� ����Ǿ����ϴ�." << endl;
		break;

	default:
		break;

	}
	carbontax->enforce(world->countries[_countryCode]); //carbontax�� �ش� ������ ���Ͽ� ����


}

//*******************************************************************
//===================================================================