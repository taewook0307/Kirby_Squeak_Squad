#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::Update(float _Delta)
{
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (0 != GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}

	if (0 != GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}

	if (0 != GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (0 != GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (MovePos.X != 0.0f || MovePos.Y != 0.0f)
	{
		MainRenderer->ChangeAnimation("Run");
	}
	else
	{
		MainRenderer->ChangeAnimation("Idle");
	}

	AddPos(MovePos);
}

void Kirby::FormInit(const std::string& _ImagePath, const std::string& _ImageName)
{
	float4 Scale = float4::ZERO;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_ImageName))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Kirby\\" + _ImagePath);

		//GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFliePath(_ImageName));
		//Scale = Text->GetScale();
		FolderPath.MoveChild("Resources\\Kirby\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FolderPath.PlusFliePath("Left_Player.bmp"), 5, 17);

		//MainRenderer = CreateRenderer(_ImageName, RenderOrder::Play);
		//MainRenderer->SetRenderScale(Scale * 5.0f);
		//MainRenderer->SetTexture(_ImageName);
		MainRenderer = CreateRenderer(RenderOrder::Play);
		MainRenderer->SetRenderScale({ 200, 200 });

		MainRenderer->CreateAnimation("Idle", "Left_Player.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Run", "Left_Player.bmp", 3, 6, 0.1f, true);
		MainRenderer->ChangeAnimation("Idle");

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();

		SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	}
}