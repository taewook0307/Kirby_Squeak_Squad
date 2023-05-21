#pragma once

#include "Kirby.h"

class IceKirby : public Kirby
{
public:
	// constrcuter destructer
	IceKirby();
	~IceKirby();

	// delete Function
	IceKirby(const IceKirby& _Other) = delete;
	IceKirby(IceKirby&& _Other) noexcept = delete;
	IceKirby& operator=(const IceKirby& _Other) = delete;
	IceKirby& operator=(IceKirby&& _Other) noexcept = delete;

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

	void DirCheck() override;

	void ChangeAnimationState(const std::string& _StateName);
private:

	void Start() override;
	void Update(float _Delta) override;
};

