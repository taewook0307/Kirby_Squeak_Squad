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

		ResourcesManager::GetInst().CreateSpriteFolder("Right_Kirby", FolderPath.PlusFilePath("Right_Kirby"));
		ResourcesManager::GetInst().CreateSpriteFolder("Left_Kirby", FolderPath.PlusFilePath("Left_Kirby"));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		
		MainRenderer->CreateAnimation("Right_Idle", "Right_Kirby", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Walk", "Right_Kirby", 21, 30, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Kirby", 12, 19, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Stop", "Right_Kirby", 20, 20, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Jump", "Right_Kirby", 2, 11, 0.1f, true);

		MainRenderer->CreateAnimation("Left_Idle", "Left_Kirby", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Walk", "Left_Kirby", 2, 11, 0.05f, true);

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
		ChangeAnimationState(CurState);
	}
}

void Kirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}