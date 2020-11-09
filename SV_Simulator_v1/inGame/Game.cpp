#include "Game.h"


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




}

void Game::Oneday() {
	date += 1;

	// 1일 단위로 진행되는 연산 코드 작성, sub thread에서 호출됨.



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
		std::cout << "KOR에서 ";
		break;

	case CountryCode::USA:
		std::cout << "USA에서 ";
		break;

	default:
		break;
	}

	switch (_policyCode)
	{
	case IndustryPolicyCode::CarbonTax:
		std::cout << "CarbonTax 정책이 시행되었습니다." << std::endl;
		break;

	case IndustryPolicyCode::CER:
		std::cout << "CER 정책이 시행되었습니다." << std::endl;
		break;

	default:
		break;

	}
	


}

//*******************************************************************
//===================================================================