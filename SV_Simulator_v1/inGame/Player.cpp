#include "Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	DataInit();

}
Player::Player(const Player& other)
{
	DataInit();
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

void Player::SetSupport(int _support)
{
	deltaSupport = _support - support;
	support = _support;
}