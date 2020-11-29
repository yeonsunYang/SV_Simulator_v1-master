#pragma once
#include "World.h"
#include "Country.h"
#include "Industry.h"
#include "IndustryPolicyCode.h"
#include "CountryCode.h"

class IndustryPolicy
{
private:
	IndustryPolicyCode policyCode; //정책코드
	IndustryCode industryCode; //산업코드
	bool isAccept[COUNTRY_NUM]; //국가별 정책시행여부
	long long needBudget; //소요예산
	float rateOfChange_tax; //세금지수 변화율
	float rateOfChange_working; //종사자비율 변화율
	float rateOfChange_carbon; //탄소배출량 변화율

public:
	/*#####################################
	1. 초기화 되어야 하는 부분
		# 생성자 함수
			- policyCode
			- industryCode
			- 국가별 정책시행여부 (isPolicyAccept)
			- 필요 예산
			- 세금지수 변동
			- 탄소배출량 변동
			- 종사자비율 변동

	2. 이벤트 함수
		# 탄소배출량 변경
		# 예산 사용
		# 국가별 정책시행여부 수정
		# 세금지수 변경
		# 종사자비율 변경
	#########################################*/

	///<summary>
	///#함수역할 : 생성자 함수
	///</summary>
	IndustryPolicy(IndustryPolicyCode _pCode, IndustryCode _iCode, long long _needBudget, float _rateOfChange_tax, float _rateOfChange_working, float _rateOfChange_carbon);

	///<summary>
	///#함수역할 : 정책 실행함수
	///</summary>
	void enforce(Country country);

	///<summary>
	///#함수역할 : 정책 실행함수 - 예산 수정
	///</summary>
	void enforce_budget(Country country);

	///<summary>
	///#함수역할 : 정책 실행함수 - 탄소배출량 수정
	///</summary>
	void enforce_carbonEmission(Country country);

	///<summary>
	///#함수역할 : 정책 실행함수 - 산업세율 수정
	///</summary>
	void enforce_tax(Country country);

	///<summary>
	///#함수역할 : 정책 실행함수 - 종사자비율 수정
	///</summary>
	void enforce_working(Country country);
};