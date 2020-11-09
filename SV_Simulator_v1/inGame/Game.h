#pragma once
#include "IndustryPolicyCode.h"
#include "World.h"
#include "Country.h"
#include <iostream>


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



public:
	Game();	

	/// <summary>
	/// 1�� ������ ȣ��Ǵ� �Լ�
	/// </summary>
	void Oneday();

	/// <summary>
	/// ��å�� ����ɰ�� ȣ��Ǵ� �̺�Ʈ �Լ�
	/// </summary>
	/// <param name="_countryCode"> ��å�� ������ ���� �ڵ�</param>
	/// <param name="_policyCode"> �����Ϸ��� ��å �ڵ�</param>
	void EnforcePolicy(int _countryCode, int _policyCode);

	int Today() { return date; };

	~Game();

//���⼭ ���� �ۼ����ּ���.******************************************

private:
	World* world;

public:

protected:

};