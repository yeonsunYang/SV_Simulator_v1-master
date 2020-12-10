#include "Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	DataInit();

}
Player::Player(const Player& other) : Player::Player()
{

}
Player::~Player()
{

}
void Player::DataInit()
{
	dailyGold = 0;
	totalGold = 0;
	support = 0;
	deltaSupport = 0;
}
void Player::SetGold(int _gold)
{
	dailyGold = _gold;
	totalGold += dailyGold;
}
void Player::RefundGold(int _refund)
{
	dailyGold += _refund;
	totalGold += _refund;
}

void Player::SetSupport(int _support)
{
	deltaSupport = _support - support;
	support = _support;
}
void Player::PayGold(int _cost)
{
	totalGold -= _cost;
}