#pragma once

#include "BaseActor.h"

#include <vector>

#define OBSTACLECOLLISIONPOS { 0.0f, -30.0f }
#define OBSTACLECOLLISIONSCALE { 60.0f, 60.0f }

class Obstacle : public BaseActor
{
public:
	// constrcuter destructer
	Obstacle();
	~Obstacle();

	// delete Function
	Obstacle(const Obstacle& _Other) = delete;
	Obstacle(Obstacle&& _Other) noexcept = delete;
	Obstacle& operator=(const Obstacle& _Other) = delete;
	Obstacle& operator=(Obstacle&& _Other) noexcept = delete;

	void SetRendererRatio(float _Value);

	void ChangeFloorObstacle();
protected:

private:
	float RatioValue = 4.0f;
	bool AttackCheck = false;
	std::vector<GameEngineCollision*> ObsCol;

	void Start() override;
	void Update(float _Delta) override;
};