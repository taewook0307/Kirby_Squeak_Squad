#include "IceKirby.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void IceKirby::IdleStart()
{
	Kirby::IdleStart();
}

void IceKirby::DownStart()
{
	Kirby::DownStart();
}

void IceKirby::SlideStart()
{
	Kirby::SlideStart();
}

void IceKirby::WalkStart()
{
	Kirby::WalkStart();
}

void IceKirby::IdleUpdate(float _Delta)
{
	Kirby::IdleUpdate(_Delta);
}

void IceKirby::DownUpdate(float _Delta)
{
	Kirby::DownUpdate(_Delta);
}

void IceKirby::SlideUpdate(float _Delta)
{
	Kirby::SlideUpdate(_Delta);
}

void IceKirby::WalkUpdate(float _Delta)
{
	Kirby::WalkUpdate(_Delta);
}