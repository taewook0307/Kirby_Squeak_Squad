#include "KirbySword.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>

KirbySword::KirbySword()
{
}

KirbySword::~KirbySword()
{
}

void KirbySword::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("SwordKirby_Idle_1.Bmp"))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Kirby\\SwordKirby\\Idle\\SwordKirby_Idle_1.Bmp");
		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void KirbySword::Update(float _Delta)
{
	AddPos({ 100.0f * _Delta, 0.0f });
}

void KirbySword::Render()
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetWindowBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture("SwordKirby_Idle_1.Bmp");
	BackBuffer->BitCopy(FindTexture, GetPos(), GetScale());
}

void KirbySword::Release()
{

}