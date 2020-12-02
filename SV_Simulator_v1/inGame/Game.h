#pragma once
#include "World.h"
#include "Country.h"
#include "Industry.h"
#include "Life.h"
#include "Energy.h"
//#include <iostream>


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

	/// <summary>
	/// #함수 기능: (_countryCode)에 해당하는 Country 객체의 포인터 반환.
	/// </summary>
	/// <param name="_countryCode:">반환받고자 하는 Country의 code</param>
	/// <returns>Country 객체의 포인터</returns>
	Country* GetCountry(CountryCode _countryCode);


public:
	Game();

	/// <summary>
	/// 1일 단위로 호출되는 함수
	/// </summary>
	void Oneday();

	/// <summary>
	/// 30일 단위로 호출되는 함수
	/// </summary>
	void OneMonth();

	/// <summary>
	/// 360일 단위로 호출되는 함수
	/// </summary>
	void OneYear();

	/// <summary>
	/// 정책이 실행될경우 호출되는 이벤트 함수
	/// </summary>
	/// <param name="_countryCode"> 정책을 실행한 국가 코드</param>
	/// <param name="_policyCode"> 실행하려는 정책 코드</param>
	///void EnforcePolicy(int _countryCode, int _policyCode);


	/// <summary>
	/// 현재 날짜를 반환
	/// </summary>
	/// <returns></returns>
	int Today() { return date; };

	/// <summary>
	/// #함수 기능: (_countryCode)에 해당하는 Country의 Budget 반환
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country의 Buget</returns>
	long long GetBudget(CountryCode _countryCode);

	/// <summary>
	/// #함수 기능: (_countryCode)에 해당하는 Country의 GDP 반환
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country의 GDP</returns>
	long long GetGDP(CountryCode _countryCode);

	/// <summary>
	/// #함수 기능: (_countryCode)에 해당하는 Country의 Population 반환
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country의 Population</returns>
	long long GetPopulation(CountryCode _countryCode);

	/// <summary>
	/// #함수 기능: (_countryCode)에 해당하는 Country의 CarbonEmission 반환
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country의 CarbonEmission</returns>
	long long GetCarbonEmission(CountryCode _countryCode);

	/// <summary>
	/// #함수 기능: (_countryCode)에 해당하는 Country의 TaxRate 반환
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country의 TaxRate</returns>
	float GetTaxRate(CountryCode _countryCode);

	/// <summary>
	/// #함수 기능: worldTemperature 반환
	/// </summary>
	/// <returns>worldTemperature</returns>
	float GetWorldTemperature();

	/// <summary>
	/// #함수 기능: worldCarbonEmission 반환
	/// </summary>
	/// <returns>worldCarbonEmission</returns>
	long long GetWorldCarbonEmission();

	/// <summary>
	/// #함수 기능: worldPopulation 반환
	/// </summary>
	/// <returns>worldPopulation</returns>
	long long GetWorldPopulation();

	/// <summary>
	/// #함수 기능: worldCarbonPPM
	/// </summary>
	/// <returns></returns>
	float GetWorldCarbonPPM();

	~Game();

	//여기서 부터 작성해주세요.******************************************

private:
	World* world;

public:

protected:

};