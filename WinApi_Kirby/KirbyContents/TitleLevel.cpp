#include "TitleLevel.h"
#include "Player.h"
#include "KirbyGameEnum.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	CreateActor<Player>(static_cast<int>(KirbyGameEnum::Kirby));
}

void TitleLevel::Update()
{

}

void TitleLevel::Render()
{

}

void TitleLevel::Release()
{

}