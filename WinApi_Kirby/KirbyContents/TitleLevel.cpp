#include "TitleLevel.h"
#include "KirbyNormal.h"
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