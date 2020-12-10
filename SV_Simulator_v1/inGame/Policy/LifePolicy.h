#pragma once
#include "LifePolicyCode.h"
#include "Policy.h"

class LifePolicy : public Policy
{
public:
	LifePolicy(int _cost, int _effect)
		: Policy(_cost, _effect) {}

	~LifePolicy() {}

};

