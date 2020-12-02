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
	/// Game�� ���õ� �͵��� �ʱ�ȭ �ϴ� �Լ�. �Ϲ������� �����ڿ��� ȣ��.
	/// </summary>
	void InitializeGame();
	/// <summary>
	/// ���� ���� ���� �Ҹ��ڷ� ���� ȣ���.
	/// </summary>
	void EndGame();

	/// <summary>
	/// #�Լ� ���: (_countryCode)�� �ش��ϴ� Country ��ü�� ������ ��ȯ.
	/// </summary>
	/// <param name="_countryCode:">��ȯ�ް��� �ϴ� Country�� code</param>
	/// <returns>Country ��ü�� ������</returns>
	Country* GetCountry(CountryCode _countryCode);


public:
	Game();

	/// <summary>
	/// 1�� ������ ȣ��Ǵ� �Լ�
	/// </summary>
	void Oneday();

	/// <summary>
	/// 30�� ������ ȣ��Ǵ� �Լ�
	/// </summary>
	void OneMonth();

	/// <summary>
	/// 360�� ������ ȣ��Ǵ� �Լ�
	/// </summary>
	void OneYear();

	/// <summary>
	/// ��å�� ����ɰ�� ȣ��Ǵ� �̺�Ʈ �Լ�
	/// </summary>
	/// <param name="_countryCode"> ��å�� ������ ���� �ڵ�</param>
	/// <param name="_policyCode"> �����Ϸ��� ��å �ڵ�</param>
	///void EnforcePolicy(int _countryCode, int _policyCode);


	/// <summary>
	/// ���� ��¥�� ��ȯ
	/// </summary>
	/// <returns></returns>
	int Today() { return date; };

	/// <summary>
	/// #�Լ� ���: (_countryCode)�� �ش��ϴ� Country�� Budget ��ȯ
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country�� Buget</returns>
	long long GetBudget(CountryCode _countryCode);

	/// <summary>
	/// #�Լ� ���: (_countryCode)�� �ش��ϴ� Country�� GDP ��ȯ
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country�� GDP</returns>
	long long GetGDP(CountryCode _countryCode);

	/// <summary>
	/// #�Լ� ���: (_countryCode)�� �ش��ϴ� Country�� Population ��ȯ
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country�� Population</returns>
	long long GetPopulation(CountryCode _countryCode);

	/// <summary>
	/// #�Լ� ���: (_countryCode)�� �ش��ϴ� Country�� CarbonEmission ��ȯ
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country�� CarbonEmission</returns>
	long long GetCarbonEmission(CountryCode _countryCode);

	/// <summary>
	/// #�Լ� ���: (_countryCode)�� �ش��ϴ� Country�� TaxRate ��ȯ
	/// </summary>
	/// <param name="_countryCode">(_countryCode)</param>
	/// <returns>Country�� TaxRate</returns>
	float GetTaxRate(CountryCode _countryCode);

	/// <summary>
	/// #�Լ� ���: worldTemperature ��ȯ
	/// </summary>
	/// <returns>worldTemperature</returns>
	float GetWorldTemperature();

	/// <summary>
	/// #�Լ� ���: worldCarbonEmission ��ȯ
	/// </summary>
	/// <returns>worldCarbonEmission</returns>
	long long GetWorldCarbonEmission();

	/// <summary>
	/// #�Լ� ���: worldPopulation ��ȯ
	/// </summary>
	/// <returns>worldPopulation</returns>
	long long GetWorldPopulation();

	/// <summary>
	/// #�Լ� ���: worldCarbonPPM
	/// </summary>
	/// <returns></returns>
	float GetWorldCarbonPPM();

	~Game();

	//���⼭ ���� �ۼ����ּ���.******************************************

private:
	World* world;

public:

protected:

};