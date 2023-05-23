#pragma once

#include "Kirby.h"

class SparkKirby : public Kirby
{
public:
	// constrcuter destructer
	SparkKirby();
	~SparkKirby();

	// delete Function
	SparkKirby(const SparkKirby& _Other) = delete;
	SparkKirby(SparkKirby&& _Other) noexcept = delete;
	SparkKirby& operator=(const SparkKirby& _Other) = delete;
	SparkKirby& operator=(SparkKirby&& _Other) noexcept = delete;

protected:

	void ChangeAnimationState(const std::string& _StateName);
private:

	void Start() override;
};

