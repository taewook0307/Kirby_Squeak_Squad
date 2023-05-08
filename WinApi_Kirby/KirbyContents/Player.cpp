#include "Player.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
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
	if (false == ResourcesManager::GetInst().IsLoadTexture("Kirby_Idle_1.Bmp"))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Kirby\\Kirby\\Idle\\Kirby_Idle_1.Bmp");
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
	GameEngineTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Kirby_Idle_1.Bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	if (!BitBlt(WindowDC,
		GetPos().iX() - GetScale().ihX(),
		GetPos().iY() - GetScale().ihY(),
		GetPos().iX() + GetScale().ihX(),
		GetPos().iY() + GetScale().ihY(),
		ImageDC,
		0,
		0,
		SRCCOPY))
	{
		MsgBoxAssert("이미지 Render에 실패했습니다.");
		return;
	}
}

void Player::Release()
{

}