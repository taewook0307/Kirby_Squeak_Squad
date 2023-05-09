#include "TitleLevel.h"
#include "KirbyNormal.h"
#include "BackGround.h"
#include "KirbyGameEnum.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	CreateActor<KirbyNormal>(static_cast<int>(KirbyGameEnum::Kirby));
	BackGround* Back = CreateActor<BackGround>(static_cast<int>(KirbyGameEnum::Floor));
	Back->Init("FirstStage_1.Bmp");
}

void TitleLevel::Update(float _Delta)
{

}

void TitleLevel::Render()
{

}

void TitleLevel::Release()
{

}