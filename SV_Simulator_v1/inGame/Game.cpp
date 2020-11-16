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




//여기서 부터 작성 가능 ============================================

//규칙적으로 호출되는 함수*******************************************

void Game::InitializeGame() {
	// 게임 초기화 관련 코드 작성, main thread만 호출 가능

	world = new World();

	// <정책 생성>
	carbontax = new IndustryPolicy(Carbontax, Steel, 1000, 0.1, 0, 0); 
	// IndustryPolicyCode, IndustryCode, 필요예산, 세금지수변화율, 종사자비율변화율, 탄소배출량변화율

}

void Game::Oneday() {

	// 1일 단위로 진행되는 연산 코드 작성, sub thread에서 호출됨.

	cout << "\n#######각 국의 정보#######\n" << endl;
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
	cout << "\n#######전지구 정보#######\n" << endl;
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
	// 게임 종료시 필요한 코드 작성, main thread만 호출 가능



}
//******************************************************************



//이벤트 함수*********************************************************

void Game::EnforcePolicy(int _countryCode, int _policyCode) {
	//정책 실행시 호출시 필요한 코드 작성.


	//example

	switch (_countryCode)
	{
	case CountryCode::KOR:
		cout << "KOR에서 ";
		break;

	case CountryCode::USA:
		cout << "USA에서 ";
		break;

	default:
		break;
	}

	switch (_policyCode)
	{
	case IndustryPolicyCode::Carbontax:
		cout << "Carbontax 정책이 시행되었습니다." << endl;
		break;

	default:
		break;

	}
	carbontax->enforce(world->countries[_countryCode]); //carbontax를 해당 국가에 대하여 실행


}

//*******************************************************************
//===================================================================