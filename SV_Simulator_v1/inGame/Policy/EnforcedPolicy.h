#pragma once
#include "LifePolicyCode.h"
#include "EduPolicyCode.h"

class EnforcedPolicy
{
public:
	EnforcedPolicy() { enforceCnt = 0; }

	int Count() { return enforceCnt; }
	bool IsEnforce() { (enforceCnt > 0) ?  true : false; }
	void Enforce() { enforceCnt++; }

	~EnforcedPolicy(){}


private:
	int enforceCnt;

};

