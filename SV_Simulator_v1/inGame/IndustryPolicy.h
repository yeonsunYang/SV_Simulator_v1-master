#pragma once
#include "World.h"
#include "IndustryPolicyCode.h"
#define INDUSTRY_NUM 1

class IndustryPolicy
{
private:
	IndustryPolicyCode policyCode; //정책코드
	bool isAccept[INDUSTRY_NUM][COUNTRY_NUM]; //국가별 정책시행여부
	long long needBudget; //소요예산
	float rateOfChange_tax; //세금지수 변화율
	float rateOfChange_working; //종사자비율 변화율
	float rateOfChange_carbon; //탄소배출량 변화율

public:
/*#####################################
1. 초기화 되어야 하는 부분
	# 생성자 함수
		- policyCode
		- 국가별 정책시행여부 (isPolicyAccept)
		- 필요 예산
		- 세금지수 변동
		- 탄소배출량 변동

2. 이벤트 함수
	# 탄소배출량 변경
	# 예산 사용
	# 국가별 정책시행여부 수정
	# 세금지수 변경
	# 종사자비율 변경

#########################################*/
};