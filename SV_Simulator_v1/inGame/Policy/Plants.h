#pragma once
class Plants {
public:
	Plants(int _cost, int _refund, int _supply, int _emission) :
		cost(_cost), refund(_refund), supply(_supply), emission(_emission) {}

	~Plants() {}

	int Cost() { return cost; }
	int Refund() { return refund; }
	int Supply() { return supply; }
	int Emission() { return emission; }

protected:
	const int cost;
	const int refund;
	const int supply;
	const int emission;
};