#pragma once

#include "Monster.h"

class TornadoMonster : public Monster
{
public:
	// constrcuter destructer
	TornadoMonster();
	~TornadoMonster();

	// delete Function
	TornadoMonster(const TornadoMonster& _Other) = delete;
	TornadoMonster(TornadoMonster&& _Other) noexcept = delete;
	TornadoMonster& operator=(const TornadoMonster& _Other) = delete;
	TornadoMonster& operator=(TornadoMonster&& _Other) noexcept = delete;

protected:

private:

};

