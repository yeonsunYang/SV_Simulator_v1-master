#pragma once
#include "EduPolicyCode.h"
#include "Policy.h"

class EduPolicy : public Policy
{
public:
	EduPolicy(int _cost, int _effect)
		: Policy(_cost, _effect) {}

	~EduPolicy() {}

};
