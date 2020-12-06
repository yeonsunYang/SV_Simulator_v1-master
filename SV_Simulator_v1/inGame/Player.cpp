#include "Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	dailyGold = 0;
	totalGold = 0;
	support = 30;
	deltaSupport = 30;
}
Player::Player(const Player& other)
{
	dailyGold = 0;
	totalGold = 0;
	support = 0;
	deltaSupport = 0;
}
Player::~Player()
{

}

void Player::SetGold(int _gold)
{
	dailyGold = _gold;
	totalGold += dailyGold;
}

void Player::SetSupport(int _support)
{
	deltaSupport = _support - support;
	support = _support;
}