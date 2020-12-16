#include "Country.h"
#include <cmath>
#include <ctime>

Country::Country()
{
	DataInit(0, 0, 0, 0, 0); //0으로 초기화
}

Country::~Country()
{

}

void Country::DataInit(int _population, int _fire, int _green, int _recognition, int _needEnergyPerson)
{//인구수, 화력발전소 개수, 재생에너지발전소 개수, 인식률, 1인당 에너지소요량  초기화
	world = World::GetInstance();

	population = _population;//인구수를 _인구수 초기화
	live = _population;//살아있는 사람수를 _인구수로 초기화
	dead = 0;//사망자수 0으로 초기화
	dailyDead = 0;//하루사망자수 0으로 초기화

	needEnergy = 0;//에너지소요량 0으로 초기화
	needEnergyPerson = _needEnergyPerson;//1인당 에너지소요량을 _1인당에너지소요량으로 초기화
	deltaNeedEnergy = 0;//delta에너지소요량을 0으로 초기화
	supplyEnergy = 0;//에너지공급량 0으로 초기화
	deltaSupplyEnergy = 0;//delta에너지공급량 0으로 초기화
	savingEnergy = 0;//에너지절약량 0으로 초기화

	firePlants = _fire;//화력발전소개수 _화력발전소개수로 초기화
	deltaFirePlants = 0;//delta화력발전소개수 0으로 초기화
	greenPlants = _green;//재생에너지발전소개수 _재생에너지발전소개수로 초기화
	deltaGreenPlants = 0;//delta재생에너지발전소개수 0으로 초기화

	dailyEmission = 0;//국가하루배출량 0으로 초기화
	totalEmission = 0;//국가전체배출량 0으로 초기화

	dailyGold = 0;//국가하루골드 0으로 초기화
	totalGold = 0;//국가총골드 0으로 초기화
	support = 30;//국가 지지도 30으로 초기화
	deltaSupport = 0;//국가delta지지도 0으로 초기화
	recognition = _recognition;//국가인식률 _인식률로 초기화
	deltaRecognition = 0; //delta인식률 0으로 초기화

	CalEnergy();//에너지계산

	srand(static_cast<unsigned int> (time(0)));
}


void Country::CalEnergy()
{
	int enrgy = (firePlants * fireInfo.Supply()) 
		+ (greenPlants * greenInfo.Supply());

	int newNeedEnergy = static_cast<int> ((live * needEnergyPerson) / 100) - savingEnergy;
	//소요에너지 = (int) ((국가생존자수* 1인당 에너지소요량)/100)-에너지절약량;
	if (newNeedEnergy < 0) //소요에너지가 0보다 작으면
		newNeedEnergy = 0; //0으로 다시 초기화

	deltaNeedEnergy = newNeedEnergy - needEnergy; //delta에너지소요량 = 새로계산한에너지소요량 - 이전에너지소요량 //즉 어제 대비 변화량 구한셈
	deltaSupplyEnergy = enrgy - supplyEnergy;// delta에너지공급량 = 새로계산한공급량 - 이전에너지공급량 //즉 어제 대비 공급변화량 구한셈

	needEnergy = newNeedEnergy; //변화량 계산했으니 이제 에너지소요량을 갱신해주자
	supplyEnergy = enrgy; //변화량 계산했으니 이제 에너지공급량을 갱신해주자
}
// 발전소 개수가 변화될 때만 사용하는 private 멤버함수
// CalEnergy와 delta~~~~ 변수 계산만 다름.
void Country::ReCalEnergy() 
{
	int enrgy = (firePlants * fireInfo.Supply())
		+ (greenPlants * greenInfo.Supply());
	int newNeedEnergy = static_cast<int> ((live * needEnergyPerson) / 100) - savingEnergy;

	if (newNeedEnergy < 0)
		newNeedEnergy = 0;

	deltaNeedEnergy += newNeedEnergy - needEnergy; 
	deltaSupplyEnergy += enrgy - supplyEnergy;

	needEnergy = newNeedEnergy;
	supplyEnergy = enrgy;
}

void Country::CalEmission()
{
	dailyEmission = firePlants * 10; //오늘 배출량 = 화력발전소개수 * 10 //10바꾸면 UI에서도바꿔야함
	totalEmission += dailyEmission; //국가총탄소배출량 += 오늘배출량
}

void Country::CalDeath()
{
	if (live <= 0) //산사람수가 0명이하면 죽은사람 계산할것도 없다
		return;

	int ElevatedTemp_p2 = world->ElevatedTemperature_p2();//온도증가량(*100된 상태)
	int newLive = 0;

	if (ElevatedTemp_p2  > 150) {//온도가 1.5도 이상 증가했다면
		dailyDead = static_cast<int> (population * 0.07 * (rand() % 4));//오늘죽은사람 = 인구의 7퍼센트~21퍼센트 랜덤하게 죽는다
	}
	else if (ElevatedTemp_p2 > 100) {//온도가 1도 이상 증가했다면
		dailyDead = static_cast<int> (population * 0.005 * (rand() % 3)); //오늘죽은사람 = 인구의 0.5퍼센트~1퍼센트 랜덤하게 죽는다
;	}

	else if (ElevatedTemp_p2 > 50) { //온도가 0.5도 이상 증가했다면
		dailyDead = static_cast<int> (population * 0.001 * (rand() % 2)); //오늘죽은사람 = 인구의 0.1퍼센트 랜덤하게 죽는다
	}

	dead += dailyDead; //오늘 죽은사람을 총죽은인구에 누적
	if (dead > population)//총죽은인구가 전체인구수보다 많다면
		dead = population; //총죽은사람수는 전체인구수

	newLive = population - dead;//생존자 = 총인구수-누적사망자수

	live = newLive; //생존자수 갱신
}


void Country::CalRecognition()
{//인식률 계산
	deltaRecognition = 0;

	float dailyDeadRation = static_cast<float> (dailyDead) / population;//오늘죽은사람비율 = 오늘죽은사람수 / 총인구수
	if (population <= 0)
		return;

	if (dailyDeadRation > 0.07) {//죽은사람비율이 7퍼센트 이상이면
		if (rand() % 100 < 50)//50%의 확률로
			deltaRecognition += 3;//인식률을 3%증가시킨다

	}
	else if (dailyDeadRation > 0.005) {//오늘죽은사람의비율이 0.5퍼센트 이상이면
		if (rand() % 100 < 35)//35%의 확률로
			deltaRecognition += 3;//인식률을 3증가시킨다

	}
	else if (dailyDeadRation > 0.0001) {//오늘죽은사람비율이 0.01퍼센트 이상이면
		if (rand() % 100 < 25)//25%의 확률로
			deltaRecognition += 3;//인식률을 3증가시킨다
	}

	recognition += deltaRecognition;
}
void Country::CalSupport()
{//지지도 계산
	deltaSupport = 0;
	float dailyDeadRation = static_cast<float> (dailyDead) / population; //하루사망자비율
	if (population <= 0)
		return;

	if (dailyDeadRation > 0.07) { //하루사망자비율이 7퍼센트 이상이면
		if (rand() % 100 < 50)//50퍼센트의 확률로
			deltaSupport -= 1;//지지도가 1%떨어진다

	}
	else if (dailyDeadRation > 0.005) {//하루사망자비율이 0.5퍼센트 이상이면
		if (rand() % 100 < 35)//35퍼센트의 확률로
			deltaSupport -= 1;//지지도가 1%떨어진다

	}
	else if (dailyDeadRation > 0.0001) {//하루사망자비율이 0.01퍼센트 이상이면
		if (rand() % 100 < 25)//25퍼센트의 확률로
			deltaSupport -= 1;//지지도가 1%떨어진다
	}

	int energyShortage = needEnergy - supplyEnergy;//부족한에너지 = 에너지소요량-에너지공급량

	if (energyShortage > 0) //에너지가 공급량에 비해 부족하면
		if (rand() % 100 < 20)//20퍼센트의 확률로
			deltaSupport -= 1;//지지도가 1%떨어진다

	support += deltaSupport; //지지도 갱신
}
void Country::ReceiveGold()
{//골드수급
	if (population <= 0)
		return;

	int liveRate = (live * 100) / population; //생존자비율 = (생존자*100)/인구수 (0~100까지의 range)

	//20 * 100 ~ 0 * 20
	if (liveRate > 90) { //생존자비율 90%이상이면
		dailyGold = (recognition / 7) * (rand() % 2); //인식률/7 에 해당하는 만큼 골드수급
	}
	else if (liveRate > 45) { //생존자비율이 45%이상이면
		dailyGold = (recognition / 11) * (rand() % 2);//인식률/11에 해당하는만큼 골드수급
	}
	else if (liveRate > 15)//생존자비율이 15%이상이면
		dailyGold = (recognition / 17) * (rand() % 2);//인식률/17에 해당하는만큼 골드수급


	totalGold += dailyGold;
}
void Country::EnforceEduPolicy(int _eduPolicyCode, int _effect)
{//교육정책실행 //매개변수는 정책코드와 효과
	if (_eduPolicyCode >= EDU_POLICY_NUM || _eduPolicyCode < 0)
		return;

	eduPolicy[_eduPolicyCode].Enforce();//정책코드 실행
	deltaRecognition += _effect; //delta인식률 _효과만큼 증가
	recognition += _effect;//인식률 _효과만큼 증가 
}

int Country::CountEduPolicy(int _eduPolicyCode)
{//교육정책 실행횟수 세기
	if (_eduPolicyCode >= EDU_POLICY_NUM || _eduPolicyCode < 0)
		return -1;

	return eduPolicy[_eduPolicyCode].Count();
}

void Country::EnforceLifePolicy(int _lifePolicyCode, int _effect, int _effec2)
{//생활정책실행 //매개변수 정책코드, 효과1, 효과2
	if (_lifePolicyCode >= LIFE_POLICY_NUM || _lifePolicyCode < 0)
		return;

	lifePolicy[_lifePolicyCode].Enforce();//생활정책실행
	savingEnergy += _effect; //에너지절약량 _효과1만큼 증가
	//deltaNeedEnergy -= _effect;//에너지소요량변화량 -= _효과1
	//needEnergy -= _effect; //에너지소요량 -=_효과1 ??????????
	needEnergyPerson -= _effec2; //1인당에너지소요량 -= 효과2

	if (needEnergy < 0)
		needEnergy = 0;
	if (needEnergyPerson < 0)
		needEnergyPerson = 0;
	
}

int Country::CountLifePolicy(int _lifePolicyCode)
{
	if (_lifePolicyCode >= LIFE_POLICY_NUM || _lifePolicyCode < 0)
		return -1;

	return lifePolicy[_lifePolicyCode].Count();
}

void Country::BuildFirePlants(int _numPlants)
{//화력발전소 건설 //매개변수 건설갯수 
	firePlants += _numPlants; //건설했으므로 개수 추가

	if(recognition > 35) //인식률이 35% 이상이면
		for (int i = 0; i < _numPlants; i++)
		{
			if (rand() % 100 <= 10) {//10%의 확률로
				deltaSupport--;
				support--;//지지도 1하락
			}
		}
	ReCalEnergy();
}

void Country::BuildGreenPlants(int _numPlants)
{ //재생에너지발전소 건설
	greenPlants += _numPlants;

	if(recognition < 35) //인식률이 35이하면
		for (int i = 0; i < _numPlants; i++)
		{
			if (rand() % 100 <= 10) {//10퍼센트의 확률로
				deltaSupport--;//지지도 1하락
				support--;
			}
		}
	ReCalEnergy();
}

void Country::DestroyFirePlants(int _numDestroy)
{
	firePlants -= _numDestroy;
	ReCalEnergy();

}

void Country::DestroyGreenPlants(int _numDestroy)
{
	greenPlants -= _numDestroy;
	ReCalEnergy();
}