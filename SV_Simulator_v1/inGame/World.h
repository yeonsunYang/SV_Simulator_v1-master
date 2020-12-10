#pragma once

class World
{
public:
	static World* GetInstance()
	{
		if (instance == nullptr) {
			instance = new World();
		}
		return instance;
	}

	void DataInit();

	void SetPopulation(int _population, int _live, int _dead);
	void SetEnergy(int _needEnergy, int _supplyEnergy);
	void SetPlants(int _firePlants, int _greenPlants);
	void SetEmission(int _emission);
	void SetStartTemperature();
	void SetRecognition(int _recognition);

	void CalTemperature();


	int Population() { return population; }
	int Live() { return live; }
	int Dead() { return dead; }
	int DDead() { return dailyDead; }

	int NeedEnergy() { return needEnergy; }
	int DNeedEnergy() { return deltaNeedEnergy; }
	int SupplyEnergy() { return supplyEnergy; }
	int DSupplyEnergy() { return deltaSupplyEnergy; }
	int FirePlants() { return firePlants; }
	int GreenPlants() { return greenPlants; }
	int DEmission() { return dailyEmission; }
	int TEmission() { return totalEmission; }

	int Recognition() { return recognition; }
	int DRecognition() { return deltaRecognition; }

	int CarbonPPM_p2() { return carbonPPM_p2; }
	int Temperature_p2() { return temperature_p2; }
	int ElevatedTemperature_p2() { return temperature_p2 - startTemperature_p2; }

	float CarbonPPM() { return static_cast<float> (carbonPPM_p2) / 100; }
	float Temperature() { return static_cast<float> (temperature_p2) / 100; }
	float ElevatedTemperature() { return static_cast<float> (temperature_p2 - startTemperature_p2) / 100; }




private:

	int needEnergy;
	int deltaNeedEnergy;
	int supplyEnergy;
	int deltaSupplyEnergy;
	int firePlants;
	int greenPlants;

	int population;
	int live;
	int dead;
	int dailyDead;

	int dailyEmission;
	int totalEmission;
	int carbonPPM_p2;
	int temperature_p2;
	int startTemperature_p2;

	int recognition;
	int deltaRecognition;

	

	static World* instance;

	World();
	World(const World& other);
	~World();
};

