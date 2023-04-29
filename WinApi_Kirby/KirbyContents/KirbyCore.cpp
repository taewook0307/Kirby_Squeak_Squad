#include "KirbyCore.h"
#include "TitleLevel.h"
#include "FirstStageLevel.h"
#include "SecondStageLevel.h"
#include "BossStageLevel.h"
#include "EndingLevel.h"

#include <GameEngineCore/GameEngineCore.h>

KirbyCore::KirbyCore()
{
}

KirbyCore::~KirbyCore()
{
}

void KirbyCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<FirstStageLevel>("FirstStageLevel");
	GameEngineCore::CreateLevel<SecondStageLevel>("SecondStageLevel");
	GameEngineCore::CreateLevel<BossStageLevel>("BossStageLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	GameEngineCore::ChangeLevel("TitleLevel");
}

void KirbyCore::Update()
{

}

void KirbyCore::Render()
{

}

void KirbyCore::Release()
{

}