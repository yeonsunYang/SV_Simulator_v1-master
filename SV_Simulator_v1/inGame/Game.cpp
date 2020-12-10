#include "Game.h"
#include "CountryCode.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

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
Game::Game(const Game& other)
{

}

void Game::Init()
{
	system("cls");
	cout << "=========================" << endl;
	cout << "잠시 후 게임을 시작합니다." << endl; 
	cout << "=========================" << endl;


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

}

int Game::Today()
{
	return date;
}

void Game::OneDay()
{
	date++;

	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		countries[i]->CalEmission();
		countries[i]->CalDeath();
		countries[i]->CalEnergy();
		countries[i]->CalSupport();
		countries[i]->ReceiveGold();

	}

	TotalPopulation();
	TotalPlants();
	TotalEnergy();
	TotalEmission();
	TotalGold();
	TotalSupport();
	

	world->CalTemperature();
}

void Game::End()
{
	system("cls");
	cout << "=========================" << endl;
	cout << "게임이 종료됩니다." << endl;
	cout << "=========================" << endl;
}
void Game::PrintDate()
{
	cout << fixed;
	cout.precision(2);

	cout <<"|"<< setw(4) << date << " 일차  " 
		<< setw(8) << "| 온도: " << setw(5) << world->Temperature()
		<< " ( ▲" << setw(5) << world->ElevatedTemperature() << " )"
		<< setw(8) << "| 농도: " << setw(6) << world->CarbonPPM() << endl;
}
void Game::PrintPlayer()
{
	cout << "|" << setw(8) << "골드:" << setw(4) << player->TGold()
		<< " ▲" << setw(3) << player->DGold()
		<< setw(10) << "| 지지도:" << setw(4) << player->Support();
		
	if(player->DSupport() == 0)
		cout << " ◆" << setw(2) << player->DSupport() << endl;
	else if (player->DSupport() > 0)
		cout << " ▲" << setw(3) << player->DSupport() << endl;
	else if (player->DSupport() < 0)
		cout << " ▼" << setw(3) << player->DSupport() << endl;

}

void Game::PrintWorld()
{
	cout << "|" << "인구수(   전체 /   생존 /   사망 )" << endl;
	cout << "|" << setw(7) << "("
		<< setw(7) << world->Population() << " /"
		<< setw(7) << world->Live() << " /"
		<< setw(7) << world->Dead() << " )" 
		<< " ▲ "<< world->DDead()<< endl;


	cout << "|" << "배출량(   일일 /   누적 )" << endl;
	cout << "|" << setw(7) << "("
		<< setw(7) << world->DEmission() << " /"
		<< setw(7) << world->TEmission() << " )"<<  endl;

	cout << "|" << "에너지(   수요 /    공급 )" << endl;
	cout << "|" << setw(7) << "("
		<< setw(7) << world->NeedEnergy()<< " / " 
		<< setw(7) << world->SupplyEnergy() << " )" << endl;

	cout << "|" << "  인식(" <<setw(4) <<world->Recognition() << " )";

	if (world->DRecognition() == 0)
		cout << " ◆" << setw(2) << world->DRecognition() << endl;
	else if (world->DRecognition() > 0)					 
		cout << " ▲" << setw(3) << world->DRecognition() << endl;
	else if (world->DRecognition() < 0)					 
		cout << " ▼" << setw(3) << world->DRecognition() << endl;
}

void Game::PrintCountriesAll()
{
	cout << "| ( No. )  전체  /  생존  /  사망   " << endl;
	for (int i = 0; i < COUNTRY_NUM; i++)
	{
		cout << "| ( " <<setw(3)<< i <<" )"
			<<setw(7) << countries[i]->Population() << " /"
			<<setw(7) << countries[i]->Live() << " /"
			<<setw(7) << countries[i]->Dead() << " "
			<< " ▲ " << countries[i]->DDead() << endl;
	}
}
void Game::PrintCountriesDetail(char _input)
{
	int countryCode = static_cast<int>(_input) - 48;

	if (countryCode >= COUNTRY_NUM) {
		cout << " 비정상적인 접근입니다" << endl;
		return;
	}
	cout << "| ( " << setw(3) << countryCode << " ) 국가의 정보" << endl;
	cout << "| ( " << setw(3) << countryCode << " )"
		<< setw(7) << countries[countryCode]->Population() << " /"
		<< setw(7) << countries[countryCode]->Live() << " /"
		<< setw(7) << countries[countryCode]->Dead() << " "
		<< " ▲ " << countries[countryCode]->DDead() << endl;
	cout << endl;

	cout << "|     [골드]" << endl;
	cout << "|   일일 수입:" << setw(7) << countries[countryCode]->DGold() << endl;
	cout << "|   누적 수입:" << setw(7) << countries[countryCode]->TGold() << endl;
	cout << endl;

	cout << "|     [지지도]" << endl;
	cout << "| 지지도 변화:" << setw(7) << countries[countryCode]->DSupport() << endl;
	cout << "|      지지도:" << setw(7) << countries[countryCode]->Support() << endl;
	cout << endl;

	cout << "| [기후위기 인식]" << endl;
	cout << "| 인식의 변화:" << setw(7) << countries[countryCode]->DSupport() << endl;
	cout << "|      인식도:" << setw(7) << countries[countryCode]->Recognition() << endl;
	cout << endl;

	cout << "|     [에너지]" << endl;
	cout << "| 에너지 수요:" << setw(7) << countries[countryCode]->NeedEnergy() << endl;
	cout << "| 에너지 공급:" << setw(7) << countries[countryCode]->SupplyEnergy() << endl;
	cout << endl;

	cout << "|     [발전소]" << endl;
	cout << "| 화력 발전소:" << setw(7) << countries[countryCode]->FirePlants() << endl;
	cout << "| 재생 발전소:" << setw(7) << countries[countryCode]->GreenPlants() << endl;
	cout << endl;



}

void Game::TotalPopulation()
{
	int population, live, dead;

	population = live = dead = 0;

	for (Country* _country : countries)
	{
		population += _country->Population();
		live += _country->Live();
		dead += _country->Dead();
	}

	world->SetPopulation(population, live, dead);

}

void Game::TotalEnergy()
{
	int need, supply;
	
	need = supply = 0;

	for (Country* _country : countries)
	{
		need += _country->NeedEnergy();
		supply += _country->SupplyEnergy();
	}

	world->SetEnergy(need, supply);
}

void Game::TotalPlants()
{
	int fire, green;

	fire = green = 0;

	for (Country* _country : countries)
	{
		fire += _country->FirePlants();
		green += _country->GreenPlants();
	}

	world->SetPlants(fire, green);
}

void Game::TotalEmission()
{
	int emission = 0;

	for (Country* _country : countries)
	{
		emission += _country->DEmission();
	}

	world->SetEmission(emission);

}

void Game::TotalGold()
{
	int gold = 0;

	for (Country* _country : countries)
	{
		gold += _country->DGold();
	}

	player->SetGold(gold);
}
void Game::TotalSupport()
{
	int support = 0;

	for (Country* _country : countries)
	{
		support += _country->Support();
	}

	support /= COUNTRY_NUM;

	player->SetSupport(support);
}

void Game::TotalRecognition()
{
	int recognition = 0;

	for (Country* _country : countries)
	{
		recognition += _country->Recognition();
	}

	recognition /= COUNTRY_NUM;

	world->SetRecognition(recognition);
}
