#include "EndingLevel.h"
#include "BackGround.h"
#include "KirbyGameEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->Init("EndingLevel.bmp");
}