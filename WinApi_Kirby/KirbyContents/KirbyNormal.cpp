#include "KirbyNormal.h"
#include "KirbyGameEnum.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

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
		FilePath.MoveChild("Resources\\Kirby\\NormalKirby\\Idle\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFliePath("Kirby_Idle_1.Bmp"));
	}

	GameEngineRenderer* Ptr = CreateRenderer("Kirby_Idle_1.Bmp", RenderOrder::Play);
	Ptr->SetRenderScale({ 200, 200 });
	Ptr->SetTexture("Kirby_Idle_1.Bmp");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	SetPos(WinScale.Half());
}

void KirbyNormal::Update(float _Delta)
{
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (0 != GetAsyncKeyState('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (0 != GetAsyncKeyState('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);
}

void KirbyNormal::Render()
{
	
}

void KirbyNormal::Release()
{

}