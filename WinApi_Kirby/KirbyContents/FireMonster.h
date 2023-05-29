#pragma once

#include "Monster.h"

class FireMonster : public Monster
{
public:
	// constrcuter destructer
	FireMonster();
	~FireMonster();

	// delete Function
	FireMonster(const FireMonster& _Other) = delete;
	FireMonster(FireMonster&& _Other) noexcept = delete;
	FireMonster& operator=(const FireMonster& _Other) = delete;
	FireMonster& operator=(FireMonster&& _Other) noexcept = delete;

protected:

private:

};

