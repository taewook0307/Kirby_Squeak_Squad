#include "IceKirby.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

IceKirby::IceKirby()
{
}

IceKirby::~IceKirby()
{
}

void IceKirby::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\IceKirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_IceKirby.Bmp"), 10, 12);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_IceKirby.Bmp"), 10, 12);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Ice_Idle", "Right_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Down", "Right_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Slide", "Right_IceKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_Jump", "Right_IceKirby.Bmp", 14, 14, 1.0f, false);
		MainRenderer->CreateAnimation("Right_Ice_JumpToDown", "Right_IceKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Ice_JumpToLand", "Right_IceKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Ice_Walk", "Right_IceKirby.Bmp", 24, 33, 0.05f, true);

		MainRenderer->CreateAnimation("Left_Ice_Idle", "Left_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Down", "Left_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Slide", "Left_IceKirby.Bmp", 4, 13, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_Jump", "Left_IceKirby.Bmp", 14, 14, 1.0f, false);
		MainRenderer->CreateAnimation("Left_Ice_JumpToDown", "Left_IceKirby.Bmp", 15, 22, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Ice_JumpToLand", "Left_IceKirby.Bmp", 23, 23, 0.3f, false);
		MainRenderer->CreateAnimation("Left_Ice_Walk", "Left_IceKirby.Bmp", 24, 33, 0.05f, true);

		MainRenderer->ChangeAnimation("Right_Ice_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::Body);
		BodyCollision->SetCollisionPos(BODYCOLLISIONPOS);
		BodyCollision->SetCollisionScale(BODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	ChangeState(KirbyState::Idle);
}

void IceKirby::StateUpdate(float _Delta)
{
	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::Down:
		return DownUpdate(_Delta);
	case KirbyState::Slide:
		return SlideUpdate(_Delta);
	case KirbyState::Jump:
		return JumpUpdate(_Delta);
	case KirbyState::JumpToDown:
		return JumpToDownUpdate(_Delta);
	case KirbyState::JumpToLand:
		return JumpToLandUpdate(_Delta);
	case KirbyState::Walk:
		return WalkUpdate(_Delta);
	default:
		break;
	}
}

void IceKirby::ChangeState(KirbyState _State)
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
		case KirbyState::Jump:
			JumpStart();
			break;
		case KirbyState::JumpToDown:
			JumpToDownStart();
			break;
		case KirbyState::JumpToLand:
			JumpToLandStart();
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

void IceKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Ice_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Ice_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}