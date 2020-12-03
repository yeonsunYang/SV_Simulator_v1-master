#include "Game.h"
#include <iostream>

using namespace std;


//*******************************

Game::Game() {
	date = 0;
	InitializeGame();
}

Game::~Game() {
	EndGame();
}


Country* Game::GetCountry(int _countryCode)
{
	return world->countries[_countryCode];
}

/*
long long Game::GetBudget(CountryCode _countryCode)
{
	return this->GetCountry(_countryCode)->GetbudGet();
}

long long Game::GetGDP(CountryCode _countryCode)
{
	return this->GetCountry(_countryCode)->GetGDP();
}

long long Game::GetPopulation(CountryCode _countryCode)
{
	return this->GetCountry(_countryCode)->GetPopulation();
}
long long Game::GetCarbonEmission(CountryCode _countryCode)
{
	return this->GetCountry(_countryCode)->GetCarbonEmission();
}
float Game::GetTaxRate(CountryCode _countryCode)
{
	return this->GetCountry(_countryCode)->GettaxRate();
}
*/

float Game::GetWorldTemperature()
{
	return world->worldTemperature;
}
long long Game::GetWorldCarbonEmission()
{
	return world->worldCarbonEmission;
}
long long Game::GetWorldPopulation()
{
	return world->worldPopulation;
}
float Game::GetWorldCarbonPPM()
{
	return world->worldCarbonPPM;
}
//*******************************




//���⼭ ���� �ۼ� ���� ============================================

//��Ģ������ ȣ��Ǵ� �Լ�*******************************************

void Game::InitializeGame() {
	// ���� �ʱ�ȭ ���� �ڵ� �ۼ�, main thread�� ȣ�� ����

	world = new World();

	// <��å ����>
	//carbontax = new IndustryPolicy(Carbontax, Steel, 1000, 0.1, 0, 0);
	// IndustryPolicyCode, IndustryCode, �ʿ俹��, ����������ȭ��, �����ں�����ȭ��, ź�ҹ��ⷮ��ȭ��

}

void Game::Oneday() {

	date += 1;

	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		world->countries[i]->add_totalGDP();
		world->countries[i]->add_totalCarbonEmission();
		world->countries[i]->add_totalPopulation();
		world->countries[i]->total_industryEnergy();
		world->countries[i]->total_lifeEnergy();
		world->countries[i]->total_needEnergy();
	}
	world->total_ForestOfCountries();
	world->total_CarbonAbsorbedOfCountries();
	world->total_CarbonEmissionOfCountries();
	world->calculator_worldCarbonPPM();
	world->calculator_worldTemperature();
	world->check_worldTemperature();
	world->total_FoodOfCountries();
	world->check_worldFood();
	//world->random_disaster();
	world->total_PopulationOfCountries();
	world->total_RefugeesOfCountries();
}

void Game::OneMonth()
{
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		world->countries[i]->add_monthTax();
		world->countries[i]->calculator_monthForest();
	}
}

void Game::OneYear()
{
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		world->countries[i]->calculator_budget();
		world->countries[i]->reset_annualGDP();
	}
}
void Game::EndGame() {
	// ���� ����� �ʿ��� �ڵ� �ۼ�, main thread�� ȣ�� ����

	//for (int i = 0; i < COUNTRY_NUM; i++)
	//{
	//	world->countries[i]->~Country();
	//}
	//world->~World();
	delete world;
	//delete carbontax;


}
//******************************************************************



//�̺�Ʈ �Լ�*********************************************************
/*
void Game::EnforcePolicy(int _countryCode, int _policyCode) {
	//��å ����� ȣ��� �ʿ��� �ڵ� �ۼ�.




	switch (_policyCode)
	{
	case IndustryPolicyCode::Carbontax:
		//		cout << "Carbontax ��å�� ����Ǿ����ϴ�." << endl;
		break;

	default:
		break;

	}
	carbontax->enforce(*world->countries[_countryCode]); //carbontax�� �ش� ������ ���Ͽ� ����


}
*/
//*******************************************************************
//===================================================================