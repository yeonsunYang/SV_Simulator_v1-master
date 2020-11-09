#pragma once
#include "IndustryPolicyCode.h"
#include "World.h"
#include "Country.h"
#include <iostream>


class Game {
private:
	int date;

	/// <summary>
	/// Game과 관련된 것들을 초기화 하는 함수. 일반적으로 생성자에서 호출.
	/// </summary>
	void InitializeGame();
	/// <summary>
	/// 게임 종료 직전 소멸자로 부터 호출됨.
	/// </summary>
	void EndGame();



public:
	Game();	

	/// <summary>
	/// 1일 단위로 호출되는 함수
	/// </summary>
	void Oneday();

	/// <summary>
	/// 정책이 실행될경우 호출되는 이벤트 함수
	/// </summary>
	/// <param name="_countryCode"> 정책을 실행한 국가 코드</param>
	/// <param name="_policyCode"> 실행하려는 정책 코드</param>
	void EnforcePolicy(int _countryCode, int _policyCode);

	int Today() { return date; };

	~Game();

//여기서 부터 작성해주세요.******************************************

private:
	World* world;

public:

protected:

};