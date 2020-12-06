#pragma once

#include "Player.h"
#include "World.h"
#include "Country.h"

#define COUNTRY_NUM 7

class Game
{
public:
	static Game* GetInstance()
	{
		if (instance == nullptr) {
			instance = new Game();
		}
		return instance;
	}

	int Today();
	void OneDay();
	void Play();
	void End();
	void PrintPlayer();
	void PrintDate();
	void PrintWorld();
	void PrintCountriesAll();
	void PrintCountriesDetail(char _input);

	void TotalPopulation();
	void TotalEnergy();
	void TotalPlants();
	void TotalEmission();
	void TotalGold();
	void TotalSupport();
	void TotalRecognition();
	Country* CountryInstance(int _countryCode) { return countries[_countryCode]; }

private:

	Player* player;
	World* world;
	Country* countries[COUNTRY_NUM];

	int date;


	static Game* instance;

	Game();
	Game(const Game& other);
	~Game();
};

