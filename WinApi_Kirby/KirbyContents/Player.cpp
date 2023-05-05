#include "Player.h"

#include <Windows.h>
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
	if (false == ResourcesManager::GetInst().IsLoadTexture("Idle.Bmp"))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Enermy\\Waddle Dee Large\\Idle\\Idle.Bmp");
		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
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
	GameEngineTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Idle.Bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	BitBlt(WindowDC, 100, 100, 200, 200, ImageDC, 0, 0, SRCCOPY);
}

void Player::Release()
{

}