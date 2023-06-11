#pragma once

#include "FormKirby.h"

#define SPARKATTACKCOLLISIONSCALE { 210.0f, 210.0f }

class SparkKirby : public FormKirby
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
	void ChangeAnimationState(const std::string& _StateName) override;

	void JumpUpdate(float _Delta) override;
	void JumpToDropUpdate(float _Delta) override;
	void DropUpdate(float _Delta) override;
	void AttackUpdate(float _Delta) override;
private:
	void Start() override;
};

