#pragma once
class Policy {
public:
	Policy(int _cost, int _effect)
		: cost(_cost), effect(_effect) {}

	~Policy() {}

	int Cost() { return cost; }
	int Effect() { return effect; }


protected:
	const int cost;
	const int effect;
};