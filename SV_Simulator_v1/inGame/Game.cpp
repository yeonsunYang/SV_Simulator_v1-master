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




//���⼭ ���� �ۼ� ���� ============================================

//��Ģ������ ȣ��Ǵ� �Լ�*******************************************

void Game::InitializeGame() {
	// ���� �ʱ�ȭ ���� �ڵ� �ۼ�, main thread�� ȣ�� ����




}

void Game::Oneday() {
	date += 1;

	// 1�� ������ ����Ǵ� ���� �ڵ� �ۼ�, sub thread���� ȣ���.



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
		std::cout << "KOR���� ";
		break;

	case CountryCode::USA:
		std::cout << "USA���� ";
		break;

	default:
		break;
	}

	switch (_policyCode)
	{
	case IndustryPolicyCode::CarbonTax:
		std::cout << "CarbonTax ��å�� ����Ǿ����ϴ�." << std::endl;
		break;

	case IndustryPolicyCode::CER:
		std::cout << "CER ��å�� ����Ǿ����ϴ�." << std::endl;
		break;

	default:
		break;

	}
	


}

//*******************************************************************
//===================================================================