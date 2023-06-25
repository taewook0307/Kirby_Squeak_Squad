#include "BaseActor.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
}

void BaseActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityAcceleration * 2.0f * _Delta;

	AddPos(GravityVector * _Delta);
}

void BaseActor::FlyGravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityAcceleration * 0.5f * _Delta;

	float4 BaseActorPos = GetPos();
	float4 MovePos = BaseActorPos + GravityVector * _Delta;

	if (MovePos.Y >= 100.0f)
	{
		AddPos(GravityVector * _Delta);
	}
	else
	{
		GravityReset();
	}
}

void BaseActor::SetGroundBitMap(const std::string& _GroundBitMap)
{
	GroundBitMap = ResourcesManager::GetInst().FindTexture(_GroundBitMap);

	if (nullptr == GroundBitMap)
	{
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}

}

void BaseActor::SetGroundBitMap(GameEngineWindowTexture* _BitMap)
{
	GroundBitMap = _BitMap;
}

int BaseActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundBitMap)
	{
		MsgBoxAssert("땅 체크용 텍스처가 존재하지 않습니다.");
	}

	return GroundBitMap->GetColor(_DefaultColor, GetPos() + _Pos);
}

float4 BaseActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}

void BaseActor::SoundEffectLoad() {}