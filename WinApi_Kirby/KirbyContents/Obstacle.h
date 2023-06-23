#pragma once

#include "BaseActor.h"

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

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};

