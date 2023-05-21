#include "Gravity.h"

#include <GameEngineBase/GameEngineMath.h>

float Gravity::Acceleration = 9.8f;
bool Gravity::GravityCheck = true;

Gravity::Gravity()
{
}

Gravity::~Gravity()
{
}

void Gravity::GravityOn(float _Delta)
{
	float4 GravityPos = float4::DOWN;

	if (true == GravityCheck)
	{
		GravityPos *= Acceleration * _Delta;
	}
}

void Gravity::GravityOff()
{

}