#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Player::Update()
{
	AddPos({ 1.0f, 0.0f });
}

void Player::Render()
{
	HDC WindowDC = GameEngineWindow::MainWindow.GetHDC();

	Rectangle(WindowDC,
		GetPos().iX() - GetScale().ihX(),
		GetPos().iY() - GetScale().ihY(),
		GetPos().iX() + GetScale().ihX(),
		GetPos().iY() + GetScale().ihY()
	);
}

void Player::Release()
{

}