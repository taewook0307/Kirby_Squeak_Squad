#include "Player.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/ResourcesManager.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Player_Idle.Bmp"))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		FilePath.MoveParent();

		ResourcesManager::GetInst().TextureLoad("Player_Idle.Bmp");
	}

	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void Player::Update(float _Delta)
{
	AddPos({ 100.0f * _Delta, 0.0f });
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