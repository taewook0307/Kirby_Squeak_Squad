#include "Monster.h"
#include "KirbyGameEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Right_NormalEnermy.Bmp") == nullptr && ResourcesManager::GetInst().FindSprite("Left_NormalEnermy.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Enermy\\NormalEnermy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_NormalEnermy.Bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_NormalEnermy.Bmp"), 5, 4);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Monster);

		MainRenderer->CreateAnimation("Right_Monster_Idle", "Right_NormalEnermy.Bmp", 0, 3, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Monster_Walk", "Right_NormalEnermy.Bmp", 4, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Monster_Inhale", "Right_NormalEnermy.Bmp", 8, 9, 0.5f, false);
		MainRenderer->CreateAnimation("Right_Monster_Damage", "Right_NormalEnermy.Bmp", 8, 9, 0.5f, false);
		MainRenderer->CreateAnimation("Right_Monster_Death", "Right_NormalEnermy.Bmp", 10, 19, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Monster_Idle", "Left_NormalEnermy.Bmp", 0, 3, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Monster_Walk", "Left_NormalEnermy.Bmp", 4, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Monster_Inhale", "Left_NormalEnermy.Bmp", 8, 9, 0.5f, false);
		MainRenderer->CreateAnimation("Left_Monster_Damage", "Left_NormalEnermy.Bmp", 8, 9, 0.5f, false);
		MainRenderer->CreateAnimation("Left_Monster_Death", "Left_NormalEnermy.Bmp", 10, 19, 0.1f, false);

		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionPos(MONSTERBODYCOLLISONPOS);
		BodyCollision->SetCollisionScale(MONSTERBODYCOLLISIONSCALE);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	ChangeState(MonsterState::Idle);
}

void Monster::Update(float _Delta)
{
	StateUpdate(_Delta);
	DamageStateMove();

	if (true == BodyCollision->Collision(CollisionOrder::Body, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Death);
		return;
	}

	// Debug 용
	if (true == GameEngineInput::IsDown('J'))
	{
		IsCheckPosPointChange();
	}
}

void Monster::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	if (true == IsCheckPosPoint)
	{
		Data.Pos = ActorCameraPos();
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 TOPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTTOPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTTOPCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 LEFTBOTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + float4 RIGHTBOTCHECKPOS;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

void Monster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Walk:
		return WalkUpdate(_Delta);
	case MonsterState::Inhale:
		return InhaleUpdate(_Delta);
	case MonsterState::Damage:
		return DamageUpdate(_Delta);
	case MonsterState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void Monster::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Walk:
			WalkStart();
			break;
		case MonsterState::Inhale:
			InhaleStart();
			break;
		case MonsterState::Damage:
			DamageStart();
			break;
		case MonsterState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Monster::DirChange()
{
	ActorDir CheckDir = Dir;

	if (Dir == ActorDir::Left)
	{
		CheckDir = ActorDir::Right;
	}
	
	if (Dir == ActorDir::Right)
	{
		CheckDir = ActorDir::Left;
	}

	if (CheckDir != Dir)
	{
		Dir = CheckDir;
		ChangeAnimationState(CurState);
	}
}

void Monster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_Monster_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_Monster_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}