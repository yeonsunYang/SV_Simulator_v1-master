#pragma once
#include <iostream>
class Player
{
public:
	static Player* GetInstance()
	{
		if (instance == nullptr) {
			instance = new Player();
		}
		return instance;
	}

	int DGold() { return dailyGold; }
	int TGold() { return totalGold; }
	int Support() { return support; }
	int DSupport() { return deltaSupport; }

	void SetGold(int _gold);
	void SetSupport(int _support);

private:

	int dailyGold;
	int totalGold;
	int support;
	int deltaSupport;

	static Player* instance;

	Player();
	Player(const Player& other);
	~Player();
};

