#include "Kirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
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

		ResourcesManager::GetInst().CreateSpriteFolder("NormalKirby", FolderPath.PlusFilePath("NormalKirby"));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		
		MainRenderer->CreateAnimation("Right_Idle", "NormalKirby", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Walk", "NormalKirby", 21, 30, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Run", "NormalKirby", 12, 19, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Stop", "NormalKirby", 20, 20, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Jump", "NormalKirby", 2, 11, 0.1f, true);

		MainRenderer->ChangeAnimation("Right_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(4.0f);
	}

	ChangeState(KirbyState::Idle);
}

void Kirby::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Kirby::StateUpdate(float _Delta)
{
	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::Walk:
		return WalkUpdate(_Delta);
	case KirbyState::Run:
		return RunUpdate(_Delta);
	case KirbyState::Stop:
		return StopUpdate(_Delta);
	case KirbyState::Jump:
		return JumpUpdate(_Delta);
	default:
		break;
	}
}

void Kirby::ChangeState(KirbyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case KirbyState::Idle:
			IdleStart();
			break;
		case KirbyState::Walk:
			WalkStart();
			break;
		case KirbyState::Run:
			RunStart();
			break;
		case KirbyState::Stop:
			StopStart();
			break;
		case KirbyState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Kirby::DirChange()
{
	ActorDir CheckDir = Dir;

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = ActorDir::Left;
	}
	if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = ActorDir::Right;
	}

	if (CheckDir != Dir)
	{
		Dir = CheckDir;
	}
}