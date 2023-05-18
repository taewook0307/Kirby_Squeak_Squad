#include "Kirby.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void Kirby::IdleStart()
{
	MainRenderer->ChangeAnimation("Right_Idle");
}

void Kirby::WalkStart()
{
	MainRenderer->ChangeAnimation("Right_Walk");
}

void Kirby::RunStart()
{
	MainRenderer->ChangeAnimation("Right_Run");
}

void Kirby::StopStart()
{
	MainRenderer->ChangeAnimation("Right_Stop");
}

void Kirby::JumpStart()
{
	MainRenderer->ChangeAnimation("Right_Jump");
}

void Kirby::IdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		ChangeState(KirbyState::Walk);
		return;
	}
}

void Kirby::WalkUpdate(float _Delta)
{
	DirChange();

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (MovePos == float4::ZERO)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	AddPos(MovePos);
}

void Kirby::RunUpdate(float _Delta)
{

}

void Kirby::StopUpdate(float _Delta)
{

}

void Kirby::JumpUpdate(float _Delta)
{

}