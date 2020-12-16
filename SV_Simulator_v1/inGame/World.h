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

	void DataInit();//데이터 초기화

	void SetPopulation(int _population, int _live, int _dead);//인구수set
	void SetEnergy(int _need, int _dNeed, int _supply, int _dSupply, int _saving);
	void SetPlants(int _firePlants, int _greenPlants);
	void SetEmission(int _emission);
	void SetStartTemperature();
	void SetRecognition(int _recognition);

	void CalTemperature();

	//단순 리턴 함수~~//

	int Population() { return population; }//전세계인구수 리턴
	int Live() { return live; }//전세계생존자수 리턴
	int Dead() { return dead; }//전세계사망자수 리턴
	int DDead() { return dailyDead; }//전세계 일일사망자수 리턴

	int NeedEnergy() { return needEnergy; }
	int DNeedEnergy() { return deltaNeedEnergy; }
	int SupplyEnergy() { return supplyEnergy; }
	int DSupplyEnergy() { return deltaSupplyEnergy; }
	int SavingEnergy() { return savingEnergy; }
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
	
	//~~단순 리턴 함수//



private:

	int needEnergy;
	int deltaNeedEnergy;
	int supplyEnergy;
	int deltaSupplyEnergy;
	int savingEnergy;
	int firePlants;
	int greenPlants;

	int population;
	int live;
	int dead;
	int dailyDead;

	int dailyEmission;
	int totalEmission;
	int carbonPPM_p2;//농도에 100곱해진 수치
	int temperature_p2;//온도에 100곱해진 수치
	int startTemperature_p2;//시작온도에 100곱해진 수치

	int recognition;
	int deltaRecognition;



	static World* instance;

	World();
	World(const World& other);
	~World();
};

