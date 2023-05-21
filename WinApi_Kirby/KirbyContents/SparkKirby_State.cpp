#include "SparkKirby.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void SparkKirby::IdleStart()
{
	Kirby::IdleStart();
}

void SparkKirby::DownStart()
{
	Kirby::DownStart();
}

void SparkKirby::SlideStart()
{
	Kirby::SlideStart();
}

void SparkKirby::WalkStart()
{
	Kirby::WalkStart();
}

void SparkKirby::IdleUpdate(float _Delta)
{
	Kirby::IdleUpdate(_Delta);
}

void SparkKirby::DownUpdate(float _Delta)
{
	Kirby::DownUpdate(_Delta);
}

void SparkKirby::SlideUpdate(float _Delta)
{
	Kirby::SlideUpdate(_Delta);
}

void SparkKirby::WalkUpdate(float _Delta)
{
	Kirby::WalkUpdate(_Delta);
}