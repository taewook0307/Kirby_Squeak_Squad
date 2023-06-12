#include "BossMonster.h"

void BossMonster::JumpReadyStart()
{
	ChangeAnimationState("JumpReady");
}

void BossMonster::JumpStart()
{
	ChangeAnimationState("Jump");
}

void BossMonster::DropStart()
{
	ChangeAnimationState("Drop");
}

void BossMonster::JumpReadyUpdate(float _Delta)
{

}

void BossMonster::JumpUpdate(float _Delta)
{

}

void BossMonster::DropUpdate(float _Delta)
{

}