#pragma once
#include "LifePolicyCode.h"
#include "Policy.h"

class LifePolicy : public Policy
{
public:
	LifePolicy(int _cost, int _effect, int _effect2, int _needRecognition)
		: Policy(_cost, _effect), effect2(_effect2), needRecognition(_needRecognition) {}

	int NeedRecognition() { return needRecognition; }
	int Effect2() { return effect2; }
	~LifePolicy() {}

private:
	const int needRecognition;
	const int effect2;


};

