﻿#include "TitleLevel.h"
#include "KirbyNormal.h"
#include "BackGround.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	BackGround* TitleBack = CreateActor<BackGround>(RenderOrder::BackGround);
	TitleBack->Init("TitleLevel.bmp");
}

void TitleLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("FirstStageLevel");
	}
}