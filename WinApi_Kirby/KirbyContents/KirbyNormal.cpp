#include "KirbyNormal.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>

KirbyNormal::KirbyNormal()
{
}

KirbyNormal::~KirbyNormal()
{
}

void KirbyNormal::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Kirby_Idle_1.Bmp"))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Kirby\\NormalKirby\\Idle\\Kirby_Idle_1.Bmp");
		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	SetPos({ 200, 200 });
	SetScale({ 100, 100 });
}

void KirbyNormal::Update(float _Delta)
{
	AddPos({ 100.0f * _Delta, 0.0f });
}

void KirbyNormal::Render()
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetWindowBuffer();
	GameEngineWindowTexture* FindTexture = ResourcesManager::GetInst().FindTexture("Kirby_Idle_1.Bmp");
	BackBuffer->BitCopy(FindTexture, GetPos(), GetScale());
}

void KirbyNormal::Release()
{

}