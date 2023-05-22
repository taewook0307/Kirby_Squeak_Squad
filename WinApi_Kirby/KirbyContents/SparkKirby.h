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
	void StateUpdate(float _Delta) override;
	void ChangeState(KirbyState _State) override;

	void IdleStart() override;
	void DownStart() override;
	void SlideStart() override;
	void WalkStart() override;

	void IdleUpdate(float _Delta) override;
	void DownUpdate(float _Delta) override;
	void SlideUpdate(float _Delta) override;
	void WalkUpdate(float _Delta) override;

	void ChangeAnimationState(const std::string& _StateName);
private:

	void Start() override;
	void Update(float _Delta) override;
};

