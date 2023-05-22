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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_IceKirby.Bmp"), 10, 10);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_IceKirby.Bmp"), 10, 10);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Ice_Idle", "Right_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Down", "Right_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Right_Ice_Slide", "Right_IceKirby.Bmp", 4, 5, 1.0f, true);
		MainRenderer->CreateAnimation("Right_Ice_Jump", "Right_IceKirby.Bmp", 6, 6, 1.0f, true);
		MainRenderer->CreateAnimation("Right_Ice_JumpToDown", "Right_IceKirby.Bmp", 7, 14, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_JumpToLand", "Right_IceKirby.Bmp", 14, 15, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Ice_Walk", "Right_IceKirby.Bmp", 16, 24, 0.05f, true);

		MainRenderer->CreateAnimation("Left_Ice_Idle", "Left_IceKirby.Bmp", 0, 1, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Down", "Left_IceKirby.Bmp", 2, 3, 0.5f, true);
		MainRenderer->CreateAnimation("Left_Ice_Slide", "Left_IceKirby.Bmp", 4, 5, 1.0f, true);
		MainRenderer->CreateAnimation("Left_Ice_Jump", "Left_IceKirby.Bmp", 6, 6, 1.0f, true);
		MainRenderer->CreateAnimation("Left_Ice_JumpToDown", "Left_IceKirby.Bmp", 7, 14, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_JumpToLand", "Left_IceKirby.Bmp", 14, 15, 0.3f, true);
		MainRenderer->CreateAnimation("Left_Ice_Walk", "Left_IceKirby.Bmp", 16, 24, 0.05f, true);

		MainRenderer->ChangeAnimation("Right_Ice_Idle");
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(4.0f);
	}

	ChangeState(KirbyState::Idle);
}

void IceKirby::Update(float _Delta)
{
	Kirby::StateUpdate(_Delta);
}

void IceKirby::StateUpdate(float _Delta)
{
	Kirby::StateUpdate(_Delta);
}

void IceKirby::ChangeState(KirbyState _State)
{
	Kirby::ChangeState(_State);
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