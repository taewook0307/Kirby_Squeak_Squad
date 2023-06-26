#pragma once

#include "BaseActor.h"

#include <vector>

#define HEALITEMPOS { 0.0f, 0.0f }
#define HEALITEMSCALE { 100.0f, 100.0f }
#define HEALITEMCOLLISIONPOS { 0.0f, 0.0f }
#define HEALITEMCOLLISIONSCALE { 50.0f, 50.0f }

class GameEngineRenderer;
class GameEngineCollision;
class HealItem : public BaseActor
{
public:
	// constrcuter destructer
	HealItem();
	~HealItem();

	// delete Function
	HealItem(const HealItem& _Other) = delete;
	HealItem(HealItem&& _Other) noexcept = delete;
	HealItem& operator=(const HealItem& _Other) = delete;
	HealItem& operator=(HealItem&& _Other) noexcept = delete;

protected:

private:
	int HealValue = 0;
	std::vector<GameEngineCollision*> HealItemCol;

	void Start();
	void Update(float _Delta);
};