#pragma once

class Life
{
	friend class Country;
	friend class LifePolicy;
private:

	float carPerPerson; //인구 1명당 자동차 소유 비율
	float ecocarRatio; // 친환경 자동차 비율 (탄소배출량 : 0)
	long long houses; //총 건물 개수
	float greenhouses; //그린 리모델링 비율 (탄소배출량 : 0)
	float sunhouses; //태양광 패널 설치 비율 (탄소배출량 35% 감소)
	long long carbonPerHouse; //건물 당 일일 탄소배출량
	long long carbonPerCar; //자동차 당 일일 탄소배출량
	long long carbonPerPerson; //일상에서 인구 1명당 탄소배출량
	int taxTransport; //교통에 부과된 세금지수 (달러 단위)
	int taxHouse; //주거에 부과된 세금지수 (달러 단위)
	int taxLife; //일상에 부과된 세금지수 (달러 단위)
	int day_energyPerHouse; //건물 한 채 당 에너지양
	int day_energyPerPerson; //1인 당 일상 에너지양

public:
	/*#####################################
	1. 초기화 되어야 하는 부분
		# 초기화 함수 (!= 생성자 함수)
			-자동차 소유 비율
			-친환경 자동차 비율
			-총 건물 개수
			-그린 리모델링 비율
			-태양광 패널 설치 비율
			-건물 당 탄소배출량 초기화
			-자동차 당 탄소배출량 초기화
			-일상 인구 1명당 탄소배출량
			-세금지수 모두 0으로 초기화
			-건물 한 채당 에너지양 초기화
			-1인당 일상 에너지양

			//@-초기화 라고 적힌 항목 이외는 모두 매개변수로 초기화 해주기

	2. 주기 별로 계산이 필요한 함수
		<day>
		# 건물,차, 일상에서 발생한 탄소배출량 총합 (일단위 리셋)

	#########################################*/

	///<summary>
	///#함수역할 : 초기화 함수
	///</summary>
	void init_Life(float _carPerPerson, float _ecocarRatio, long long _houses, float _greenhouses, float _sunhouses, long long _carbonPerPerson, int _day_energyPerPerson);

};
