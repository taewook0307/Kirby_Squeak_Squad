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
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\Normal\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Kirby.Bmp"), 10, 21);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Kirby.Bmp"), 10, 21);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		
		MainRenderer->CreateAnimation("Right_Idle", "Right_Kirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Down", "Right_Kirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Slide", "Right_Kirby.Bmp", 4, 5, 1.0f, true);
		MainRenderer->CreateAnimation("Right_Jump", "Right_Kirby.Bmp", 6, 6, 0.1f, true);
		MainRenderer->CreateAnimation("Right_JumpToDown", "Right_Kirby.Bmp", 7, 14, 0.1f, true);
		MainRenderer->CreateAnimation("Right_JumpToLand", "Right_Kirby.Bmp", 14, 15, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Walk", "Right_Kirby.Bmp", 16, 25, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Kirby.Bmp", 26, 33, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Stop", "Right_Kirby.Bmp", 34, 34, 0.1f, true);
		MainRenderer->CreateAnimation("Right_StopToIdle", "Right_Kirby.Bmp", 35, 36, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Breathe", "Right_Kirby.Bmp", 37, 41, 0.1f, true);
		MainRenderer->CreateAnimation("Right_BreatheOut", "Right_Kirby.Bmp", 60, 61, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Fly", "Right_Kirby.Bmp", 42, 59, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Drop", "Right_Kirby.Bmp", 62, 77, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Move", "Right_Kirby.Bmp", 78, 81, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Damage", "Right_Kirby.Bmp", 82, 86, 0.1f, true);


		MainRenderer->CreateAnimation("Left_Idle", "Left_Kirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Down", "Left_Kirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Slide", "Left_Kirby.Bmp", 4, 5, 1.0f, true);
		MainRenderer->CreateAnimation("Left_Jump", "Left_Kirby.Bmp", 6, 6, 0.1f, true);
		MainRenderer->CreateAnimation("Left_JumpToDown", "Left_Kirby.Bmp", 7, 14, 0.1f, true);
		MainRenderer->CreateAnimation("Left_JumpToLand", "Left_Kirby.Bmp", 14, 15, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Walk", "Left_Kirby.Bmp", 16, 25, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Run", "Left_Kirby.Bmp", 26, 33, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Stop", "Left_Kirby.Bmp", 34, 34, 0.1f, true);
		MainRenderer->CreateAnimation("Left_StopToIdle", "Left_Kirby.Bmp", 35, 36, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Breathe", "Left_Kirby.Bmp", 37, 41, 0.1f, true);
		MainRenderer->CreateAnimation("Left_BreatheOut", "Left_Kirby.Bmp", 60, 61, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Fly", "Left_Kirby.Bmp", 42, 59, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Drop", "Left_Kirby.Bmp", 62, 77, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Move", "Left_Kirby.Bmp", 78, 81, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Damage", "Left_Kirby.Bmp", 82, 86, 0.1f, true);

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
	case KirbyState::Down:
		return DownUpdate(_Delta);
	case KirbyState::Slide:
		return SlideUpdate(_Delta);
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
		case KirbyState::Down:
			DownStart();
			break;
		case KirbyState::Slide:
			SlideStart();
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

void Kirby::DirCheck()
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