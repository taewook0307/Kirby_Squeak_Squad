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
	BackGround* Back = CreateActor<BackGround>(RenderOrder::BackGround);
	Back->Init("FirstStage_1.Bmp");
	CreateActor<KirbyNormal>(RenderOrder::Play);
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