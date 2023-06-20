#include "IceObject.h"
#include "Monster.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>

IceObject::IceObject()
{
}

IceObject::~IceObject()
{
}

void IceObject::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Ice.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\IceKirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Ice.Bmp"), 5, 2);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Ice_Idle", "Ice.Bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Ice_Death", "Ice.Bmp", 2, 6, 0.1f, false);
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);

		MainRenderer->ChangeAnimation("Ice_Idle");
	}

	{
		AttackCollision = CreateCollision(CollisionOrder::Attack);
		AttackCollision->SetCollisionPos(STARCOLLISIONPOS);
		AttackCollision->SetCollisionScale(STARCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}
}

void IceObject::Update(float _Delta)
{
	float4 MovePos = float4::ZERO;

	unsigned int Color = EMPTYCOLOR;

	if (true == AttackCollision->Collision(CollisionOrder::Body, IceCol, CollisionType::Rect, CollisionType::Rect))
	{
		CollidePlayerCheck = true;

		GameEngineCollision* PlayerCollision = IceCol[IceCol.size() - 1];
		GameEngineActor* CurPlayer = PlayerCollision->GetActor();

		float4 DirPos = GetPos() - CurPlayer->GetPos();

		if (0.0f > DirPos.X)
		{
			Dir = ActorDir::Left;
		}
		else
		{
			Dir = ActorDir::Right;
		}
	}

	if (true == CollidePlayerCheck && ActorDir::Left == Dir)
	{
		MovePos = float4::LEFT * Speed * _Delta;
		float4 CheckPos = LEFTCHECKPOS;

		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}
	else if (true == CollidePlayerCheck && ActorDir::Right == Dir)
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		float4 CheckPos = RIGHTCHECKPOS;

		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}
	else
	{
		MovePos = float4::ZERO;
		Color = EMPTYCOLOR;
	}

	if (false == CollideMonsterCheck && true == CollidePlayerCheck && (EMPTYCOLOR == Color || DOORCOLOR == Color))
	{
		AddPos(MovePos);
	}
	else if (EMPTYCOLOR != Color && DOORCOLOR != Color)
	{
		MainRenderer->ChangeAnimation("Ice_Death");

		if (true == MainRenderer->IsAnimationEnd())
		{
			Death();
			return;
		}
	}

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody, IceCol, CollisionType::Rect, CollisionType::Rect)
		|| true == AttackCollision->Collision(CollisionOrder::BossBody, IceCol, CollisionType::Rect, CollisionType::Rect))
	{
		CollideMonsterCheck = true;

		MainRenderer->ChangeAnimation("Ice_Death");
	}

	if (true == MainRenderer->IsAnimationEnd() && true == CollideMonsterCheck)
	{
		Death();
		return;
	}

	if (7.0f < GetLiveTime())
	{
		Death();
		return;
	}
}