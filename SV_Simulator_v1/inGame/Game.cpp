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




//여기서 부터 작성 가능 ============================================

//규칙적으로 호출되는 함수*******************************************

void Game::InitializeGame() {
	// 게임 초기화 관련 코드 작성, main thread만 호출 가능

	world = new World();

	// <정책 생성>
	//carbontax = new IndustryPolicy(Carbontax, Steel, 1000, 0.1, 0, 0);
	// IndustryPolicyCode, IndustryCode, 필요예산, 세금지수변화율, 종사자비율변화율, 탄소배출량변화율

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
	// 게임 종료시 필요한 코드 작성, main thread만 호출 가능

	//for (int i = 0; i < COUNTRY_NUM; i++)
	//{
	//	world->countries[i]->~Country();
	//}
	//world->~World();
	delete world;
	//delete carbontax;


}
//******************************************************************



//이벤트 함수*********************************************************
/*
void Game::EnforcePolicy(int _countryCode, int _policyCode) {
	//정책 실행시 호출시 필요한 코드 작성.




	switch (_policyCode)
	{
	case IndustryPolicyCode::Carbontax:
		//		cout << "Carbontax 정책이 시행되었습니다." << endl;
		break;

	default:
		break;

	}
	carbontax->enforce(*world->countries[_countryCode]); //carbontax를 해당 국가에 대하여 실행


}
*/
//*******************************************************************
//===================================================================