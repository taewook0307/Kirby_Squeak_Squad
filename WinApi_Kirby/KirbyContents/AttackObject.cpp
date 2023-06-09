﻿#include "AttackObject.h"
#include "BossMonster.h"
#include "KirbyGameEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>

AttackObject::AttackObject()
{
}

AttackObject::~AttackObject()
{
}

void AttackObject::Start()
{
	if (ResourcesManager::GetInst().FindSprite("Star.Bmp") == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Kirby\\Normal\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Star.Bmp"), 5, 3);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);

		MainRenderer->CreateAnimation("Star_Idle", "Star.Bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Star_Death", "Star.Bmp", 8, 11, 0.1f, false);
		MainRenderer->SetRenderScaleToTexture();
		MainRenderer->SetScaleRatio(RatioValue);

		MainRenderer->ChangeAnimation("Star_Idle");
	}

	{
		AttackCollision = CreateCollision(CollisionOrder::Attack);
		AttackCollision->SetCollisionPos(STARCOLLISIONPOS);
		AttackCollision->SetCollisionScale(STARCOLLISIONSCALE);
		AttackCollision->SetCollisionType(CollisionType::Rect);
	}
}

void AttackObject::Update(float _Delta)
{
	float4 MovePos = float4::ZERO;
	unsigned int Color = EMPTYCOLOR;

	if (Dir == ActorDir::Left)
	{
		MovePos = float4::LEFT * _Delta * Speed;
		float4 CheckPos = LEFTCHECKPOS;

		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}
	else
	{
		MovePos = float4::RIGHT * _Delta * Speed;
		float4 CheckPos = RIGHTCHECKPOS;

		Color = GetGroundColor(EMPTYCOLOR, CheckPos);
	}

	if (false == CollisionCheck && (EMPTYCOLOR == Color || DOORCOLOR == Color))
	{
		AddPos(MovePos);
	}
	else if (EMPTYCOLOR != Color && DOORCOLOR != Color)
	{
		MainRenderer->ChangeAnimation("Star_Death");

		if (true == MainRenderer->IsAnimationEnd())
		{
			Death();
			return;
		}
	}

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody, StarCol, CollisionType::Rect, CollisionType::Rect)
		|| true == AttackCollision->Collision(CollisionOrder::BossBody, StarCol, CollisionType::Rect, CollisionType::Rect)
		|| true == AttackCollision->Collision(CollisionOrder::Obstacle, StarCol, CollisionType::Rect, CollisionType::Rect)
		|| true == AttackCollision->Collision(CollisionOrder::FloorObstacle, StarCol, CollisionType::Rect, CollisionType::Rect))
	{
		CollisionCheck = true;

		MainRenderer->ChangeAnimation("Star_Death");

		if (true == MainRenderer->IsAnimationEnd())
		{
			Death();
			return;
		}
	}

	if (1.0f < GetLiveTime())
	{
		Death();
		return;
	}
}