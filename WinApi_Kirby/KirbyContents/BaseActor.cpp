﻿#include "BaseActor.h"

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

void BaseActor::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
}

void BaseActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityAcceleration * _Delta;

	AddPos(GravityVector);
}

void BaseActor::SetGroundBitMap(const std::string& _GroundBitMap)
{
	GroundBitMap = ResourcesManager::GetInst().FindTexture(_GroundBitMap);

	if (nullptr == GroundBitMap)
	{
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}

}

int BaseActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundBitMap)
	{
		MsgBoxAssert("땅 체크용 텍스처가 존재하지 않습니다.");
	}

	return GroundBitMap->GetColor(_DefaultColor, GetPos() + _Pos);
}