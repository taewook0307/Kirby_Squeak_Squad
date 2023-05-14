#include "Kirby.h"
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

void Kirby::FormInit(const std::string& _ImagePath, const std::string& _ImageName)
{
	float4 Scale = float4::ZERO;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_ImageName))
	{
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Kirby\\" + _ImagePath);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFliePath(_ImageName));
		Scale = Text->GetScale();

		GameEngineRenderer* Ptr = CreateRenderer(_ImageName, RenderOrder::Play);
		Ptr->SetRenderScale(Scale * 5.0f);
		Ptr->SetTexture(_ImageName);

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();

		SetPos({ WinScale.Half().Half().X, WinScale.Half().Half().Y });
	}
}