#pragma once

#include "BaseActor.h"

class AttackEffect : public BaseActor
{
public:
	// constrcuter destructer
	AttackEffect();
	~AttackEffect();

	// delete Function
	AttackEffect(const AttackEffect& _Other) = delete;
	AttackEffect(AttackEffect&& _Other) noexcept = delete;
	AttackEffect& operator=(const AttackEffect& _Other) = delete;
	AttackEffect& operator=(AttackEffect&& _Other) noexcept = delete;

protected:

private:

};