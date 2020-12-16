#include "Game.h"
#include "CountryCode.h"
#include <Windows.h>

Game* Game::instance = nullptr;

Game::Game()
{
	player = Player::GetInstance();
	world = World::GetInstance();



	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		countries[i] = new Country();
	}

	date = 0;
}

Game::~Game()
{

	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		delete countries[i];
	}
}
Game::Game(const Game& other) : Game::Game()
{

}

void Game::Init()
{

	date = 0;

	world->DataInit();
	player->DataInit();

	countries[static_cast<int>(CountryCode::South_Korea)]
		->DataInit(5164, 28, 2, 27, 58);

	countries[static_cast<int>(CountryCode::United_States_of_America)]
		->DataInit(32820, 182, 66, 18, 67);

	countries[static_cast<int>(CountryCode::Germany)]
		->DataInit(8302, 18, 20, 56, 36);

	countries[static_cast<int>(CountryCode::China)]
		->DataInit(139300, 240, 148, 48, 24);

	countries[static_cast<int>(CountryCode::Australia)]
		->DataInit(2499, 11, 4, 31, 54);

	countries[static_cast<int>(CountryCode::Brazil)]
		->DataInit(20950, 5, 40, 56, 14);

	countries[static_cast<int>(CountryCode::Russia)]
		->DataInit(14450, 64, 23, 38, 54);

	countries[static_cast<int>(CountryCode::Algeria)]
		->DataInit(4223, 6, 0, 41, 15);

	countries[static_cast<int>(CountryCode::Saudi_Arabia)]
		->DataInit(3370, 21, 0, 22, 61);

	countries[static_cast<int>(CountryCode::Sweden)]
		->DataInit(1023, 2, 5, 78, 46);


	OneDay();

	world->SetStartTemperature();

	//Sleep(2000);
}

int Game::Today()
{
	return date;
}

void Game::OneDay()
{
	date++;

	for (Country* country : countries) 
	{
		country->CalEmission();
		country->CalDeath();
		country->CalEnergy();
		country->CalSupport();
		country->ReceiveGold();
	}

	TotalPopulation();
	TotalPlants();
	TotalEnergy();
	TotalEmission();
	TotalGold();
	TotalSupport();
	TotalRecognition();


	world->CalTemperature();
}


void Game::TotalPopulation()
{
	int population, live, dead;

	population = live = dead = 0;

	for (Country* country : countries)
	{
		population += country->Population();
		live += country->Live();
		dead += country->Dead();
	}

	world->SetPopulation(population, live, dead);

}

void Game::TotalEnergy()
{
	int need, dNeed, supply,dSupply, saving;

	need = dNeed = supply = dSupply = saving = 0;

	for (Country* country : countries)
	{
		need += country->NeedEnergy();
		dNeed += country->DNeedEnergy();
		supply += country->SupplyEnergy();
		dSupply += country->DSupplyEnergy();
		saving += country->SavingEnergy();

	}

	world->SetEnergy(need, dNeed, supply, dSupply, saving);
}

void Game::TotalPlants()
{
	int fire, green;

	fire = green = 0;

	for (Country* country : countries)
	{
		fire += country->FirePlants();
		green += country->GreenPlants();
	}

	world->SetPlants(fire, green);
}

void Game::TotalEmission()
{
	int emission = 0;

	for (Country* country : countries)
	{
		emission += country->DEmission();
	}

	world->SetEmission(emission);

}

void Game::TotalGold()
{
	int gold = 0;

	for (Country* country : countries)
	{
		gold += country->DGold();
	}

	player->SetGold(gold);
}
void Game::TotalSupport()
{
	int support = 0;

	for (Country* country : countries)
	{
		support += country->Support();
	}

	support /= COUNTRY_NUM;

	player->SetSupport(support);
}

void Game::TotalRecognition()
{
	int recognition;
	recognition = 0;

	for (Country* country : countries)
	{
		recognition += country->Recognition();
	}

	recognition /= COUNTRY_NUM;

	world->SetRecognition(recognition);
}
