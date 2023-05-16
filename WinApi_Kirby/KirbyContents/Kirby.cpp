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

void Kirby::Start()
{
	{
		GameEnginePath FolderPath;
		FolderPath.SetCurrentPath();
		FolderPath.MoveParentToExistsChild("Resources");

		FolderPath.MoveChild("Resources\\Kirby\\");

		ResourcesManager::GetInst().CreateSpriteFolder("NormalKirby", FolderPath.PlusFliePath("NormalKirby"));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		
		MainRenderer->CreateAnimation("Right_Idle", "NormalKirby", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Walk", "NormalKirby", 21, 30, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Run", "NormalKirby", 12, 19, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Stop", "NormalKirby", 20, 20, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Jump", "NormalKirby", 2, 11, 0.1f, true);

		MainRenderer->ChangeAnimation("Right_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(5.0f);
	}

	ChangeState(PlayerState::Idle);
}

void Kirby::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Kirby::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Walk:
		return WalkUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Stop:
		return StopUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	default:
		break;
	}
}

void Kirby::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Walk:
			WalkStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Stop:
			StopStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}