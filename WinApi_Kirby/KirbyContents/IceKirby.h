#pragma once

#include "FormKirby.h"

#define LEFTATTACKCOLLISIONPOS { -140.0f, -30.0f }
#define RIGHTTATTACKCOLLISIONPOS { 140.0f, -30.0f }
#define ICEATTACKCOLLISIONSCALE { 130.0f, 70.0f }

class IceKirby : public FormKirby
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
	void ChangeAnimationState(const std::string& _StateName) override;

	void AttackLoopUpdate(float _Delta) override;
private:
	void Start() override;
};

