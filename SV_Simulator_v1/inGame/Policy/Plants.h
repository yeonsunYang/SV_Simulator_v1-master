#pragma once
class Plants {
public:
	Plants(int _cost, int _refund) :
		cost(_cost), refund(_refund) {}

	~Plants() {}

	int Cost() { return cost; }
	int Refund() { return refund; }
protected:
	const int cost;
	const int refund;
};