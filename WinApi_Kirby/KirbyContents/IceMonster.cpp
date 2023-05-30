#include "IceMonster.h"
#include "ActorEnum.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

IceMonster::IceMonster()
{
}

IceMonster::~IceMonster()
{
}

void IceMonster::Start()
{
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\IceEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_IceMonster.Bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_IceMonster.Bmp"), 5, 2);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Right_Ice_Monster_Idle", "Right_IceMonster.Bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_Monster_Walk", "Right_IceMonster.Bmp", 1, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Ice_Monster_Attack", "Right_IceMonster.Bmp", 3, 5, 0.2f, false);
		MainRenderer->CreateAnimation("Right_Ice_Monster_Damage", "Right_IceMonster.Bmp", 6, 7, 0.2f, false);

		MainRenderer->CreateAnimation("Left_Ice_Monster_Idle", "Left_IceMonster.Bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_Monster_Walk", "Left_IceMonster.Bmp", 1, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Ice_Monster_Attack", "Left_IceMonster.Bmp", 3, 5, 0.2f, false);
		MainRenderer->CreateAnimation("Left_Ice_Monster_Damage", "Left_IceMonster.Bmp", 6, 7, 0.2f, false);
	}
}

void IceMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Ice_Monster_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Ice_Monster_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}