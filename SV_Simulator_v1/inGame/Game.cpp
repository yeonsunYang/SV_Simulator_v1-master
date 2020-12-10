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
		->DataInit(7540, 73, 12);

	countries[static_cast<int>(CountryCode::United_States_of_America)]
		->DataInit(3270, 35, 17);

	countries[static_cast<int>(CountryCode::China)]
		->DataInit(2520, 22, 3);

	countries[static_cast<int>(CountryCode::Germany)]
		->DataInit(910, 10, 4);

	countries[static_cast<int>(CountryCode::Syria)]
		->DataInit(2300, 15, 8);

	countries[static_cast<int>(CountryCode::Brazil)]
		->DataInit(1000, 12, 3);

	countries[static_cast<int>(CountryCode::Australia)]
		->DataInit(6050, 35, 23);


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
